#ifndef HS_INCLUDE_HS_LOGGER_LOG_LEVEL_H
#define HS_INCLUDE_HS_LOGGER_LOG_LEVEL_H

#include "hs/export.h"
#include <cstdint>
#include <string_view>

namespace hs {

class HS_API LogLevel final {

public:
#define XX(name) LOG_LV_##name,
    enum class Level: uint8_t {
#include "hs/logger/log_levels.inc"
#undef XX
    };

    [[nodiscard]] static std::string_view ToString(Level) noexcept;
    [[nodiscard]] static LogLevel::Level FromString(std::string_view) noexcept;

};

}

#endif