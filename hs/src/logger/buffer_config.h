#ifndef HS_SRC_LOGGER_BUFFER_CONFIG_H
#define  HS_SRC_LOGGER_BUFFER_CONFIG_H

#include <cstddef>
namespace hs::detail {

inline constexpr std::size_t LOG_MESSAGE_INLINE_CAPACITY        = 256;
inline constexpr std::size_t PRINTF_FORMAT_INLINE_CAPACITY      = 256;
inline constexpr std::size_t FORMATTED_RECORD_INLINE_CAPACITY   = 512;

}

#endif