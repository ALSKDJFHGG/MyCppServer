#include "hs/logger/log_level.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <string_view>
namespace hs {

std::string_view LogLevel::ToString(Level level) noexcept {
    switch (level) {
#define XX(name) case Level::LOG_LV_##name: return #name;
#include "hs/logger/log_levels.inc"
#undef XX
    }
    return "UNKNOWN";
}

LogLevel::Level LogLevel::FromString(std::string_view value) noexcept {
    std::array<char, 6> normalized{};
    std::transform(value.begin(), value.end(), normalized.begin(), [](unsigned char character) {
        return static_cast<char>(std::toupper(character));
    });
    const std::string_view upper_value(normalized.data(), value.size());
#define XX(name) if (upper_value == #name) return Level::LOG_LV_##name;
#include "hs/logger/log_levels.inc"
#undef XX
    return Level::LOG_LV_OFF;
}

}