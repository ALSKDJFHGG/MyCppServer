#include <atomic>
#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>
#include <vector>
int thread_count{10};
int N{1000000};
std::atomic<int> give_me_money{0};
std::mutex give_me_mutex;
void add_momeny() {
    for (int i{0}; i < N; ++i) {
        // std::lock_guard<std::mutex> lock(give_me_mutex);
        ++give_me_money;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i{0}; i < thread_count; ++i) {
        threads.emplace_back(add_momeny);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "-------------: " << give_me_money << std::endl;
    return 0;
}