add_library(hs_options INTERFACE)

target_compile_options(hs_options INTERFACE
    # GCC/Clang 通用选项
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:
        -Wall
        -Wextra                 # 额外警告(比 -Wall 更严格)
        -Wpedantic              # 严格遵循标准
        -fno-strict-aliasing
    >
)

target_compile_options(hs_options INTERFACE
    $<$<AND:$<PLATFORM_ID:Linux>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:
        -rdynamic               # 栈回溯需要
    >
)

target_compile_definitions(hs_options INTERFACE
    $<$<CONFIG:Debug>:HS_DEBUG>
)

target_compile_options(hs_options INTERFACE
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-g3>
    $<$<CONFIG:Debug>:-ggdb>
)

target_compile_options(hs_options INTERFACE
    $<$<CONFIG:Release>:-DNDEBUG>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Release>:-fno-omit-frame-pointer>

    $<$<CONFIG:RelWithDebInfo>:-DNDEBUG>
    $<$<CONFIG:RelWithDebInfo>:-O2>
    $<$<CONFIG:RelWithDebInfo>:-g>
    $<$<CONFIG:RelWithDebInfo>:-fno-omit-frame-pointer>
)

option(ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)
if (ENABLE_COVERAGE)
    target_compile_options(hs_options INTERFACE
        $<$<CONFIG:Debug>:--coverage>
    )
    target_link_options(hs_options INTERFACE
        $<$<CONFIG:Debug>:--coverage>
    )
endif()