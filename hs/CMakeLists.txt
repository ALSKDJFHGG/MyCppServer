file(GLOB_RECURSE HS_SOURCES CONFIGURE_DEPENDS *.cpp *.cc *.c)
file(GLOB_RECURSE HS_HEADERS CONFIGURE_DEPENDS *.hpp *.h)

add_library(hs STATIC ${HS_SOURCES} ${HS_HEADERS})

target_include_directories(hs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_options(hs PUBLIC hs_options) # 继承所有编译//链接选项

target_compile_options(hs PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Werror             # 将警告视为错误
    >
)

# install(TARGETS hs
#     EXPORT hsTargets
#     ARCHIVE DESTINATION $(CMAKE_INSTALL_LIBDIR)
#     LIBRARY DESTINATION $(CMAKE_INSTALL_LIBDIR)
#     RUNTIME DESTINATION $(CMAKE_INSTALL_LIBDIR)
# )

# install(FILES $(HS_HEADERS)
#     DESTINATION $(CMAKE_INSTALL_INCLUDEDIR)/hs
# )