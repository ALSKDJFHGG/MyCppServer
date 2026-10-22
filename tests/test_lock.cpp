#include "hs/macros.h"
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <latch>
#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <thread>
#include <vector>
constexpr int RUNS = 7;

u64 g_target = 0;
u64 g_counter = 0;
std::atomic<u64> g_atomicCounter{0};
std::mutex g_mutex;
std::shared_mutex g_sharedMutex;

u64 OperationsForThread(size_t thread_index, size_t thread_count) {
    const u64 base = g_target / thread_count;
    const u64 remainder = g_target % thread_count;
    return base + (thread_index < remainder ? 1 : 0);
}

template<typename Operation>
std::chrono::nanoseconds BenchmarkThreads(size_t thread_count, Operation&& operation) {
    std::latch ready(static_cast<std::ptrdiff_t>(thread_count));
    std::latch start_gate(1);
    std::latch finished(static_cast<ptrdiff_t>(thread_count));

    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    for (size_t thread_index = 0; thread_index < thread_count; ++thread_index) {
        threads.emplace_back([&, thread_index]() {
            ready.count_down();
            start_gate.wait();
            operation(thread_index, OperationsForThread(thread_index, thread_count));
            finished.count_down();
        });
    }

    ready.wait();
    const auto begin = std::chrono::steady_clock::now();
    start_gate.count_down();
    finished.wait();
    const auto end = std::chrono::steady_clock::now();
    
    for(std::thread& thread : threads) {
        thread.join();
    }
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

std::chrono::nanoseconds BenchmarkMutex(size_t thread_count) {
    g_counter = 0;
    const auto elapsed = BenchmarkThreads(thread_count, [](size_t, u64 operations) {
        for (u64 index = 0; index < operations; ++index) {
            std::lock_guard<std::mutex> lock(g_mutex);
            ++g_counter;
        }
    });
    return elapsed;
}

std::chrono::nanoseconds BenchmarkSharedMutex(size_t thread_count) {
    g_counter = 0;
    const auto elapsed = BenchmarkThreads(thread_count, [](size_t, u64 operations) {
        for (u64 index = 0; index < operations; ++index) {
            std::unique_lock<std::shared_mutex> sharedlock(g_sharedMutex);
            ++g_counter;
        }
        return g_counter;
    });
    return elapsed;
}

std::chrono::nanoseconds BenchmarkAtomic(size_t thread_count) {
    g_atomicCounter.store(0, std::memory_order_relaxed);
    const auto elapsed = BenchmarkThreads(thread_count, [](size_t, u64 operations) {
        for (u64 index = 0; index < operations; ++index) {
            g_atomicCounter.fetch_add(1, std::memory_order_relaxed);
        }
    });
    return elapsed;
}

std::chrono::nanoseconds BenchmarkAtomicCas(size_t thread_count) {
    g_atomicCounter.store(0, std::memory_order_relaxed);
    const auto elapsed = BenchmarkThreads(thread_count, [](size_t, u64 operations) {
        for (u64 index = 0; index < operations; ++index) {
            u64 expected = g_atomicCounter.load(std::memory_order_relaxed);
            while (!g_atomicCounter.compare_exchange_weak(expected, expected + 1, std::memory_order_relaxed, std::memory_order_relaxed)) {
            
            }
        }
    });
    return elapsed;
}

template <typename Benchmark>
double Run(Benchmark&& benchmark) {
    long double total_nanoseconds = 0.0L;
    for (int run = 0; run < RUNS; ++run) {
        total_nanoseconds += static_cast<long double>(benchmark().count());
    }
    return static_cast<double>(total_nanoseconds / RUNS);
}

void PrintResult(std::string_view name, double total_nanoseconds) {
    const double nanoseconds_per_operation = total_nanoseconds / static_cast<double>(g_target);
    std::cout << std::left << std::setw(14) << name << std::right
              << total_nanoseconds << " ns \ttotal, "
              << nanoseconds_per_operation << " ns/op\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./" << __FILE__ << "\n";
        return -1;
    }

    g_target = atoi(argv[1]);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "operations: " << g_target << ", average of" << RUNS << "\n\n";

    const std::vector<size_t> thread_counts = {1, 2, 4, 8, 15};
    for (const size_t thread_count : thread_counts) {
        std::cout << "threads: " << thread_count << "\n";
        PrintResult("mutex",        Run([&]() { return BenchmarkMutex(thread_count); }));
        PrintResult("shared_mutex",        Run([&]() { return BenchmarkSharedMutex(thread_count); }));
        PrintResult("atomic",        Run([&]() { return BenchmarkAtomic(thread_count); }));
        PrintResult("atomic_cas",        Run([&]() { return BenchmarkAtomicCas(thread_count); }));
    }
}