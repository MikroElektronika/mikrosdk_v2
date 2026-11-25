## Host build of the network layer (middleware/net + lwIP) for tests on Linux.
## Not part of the mikroSDK build: see README.md and run.sh.
cmake_minimum_required(VERSION 3.17)
project(net_host_test C)

set(SDK_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)
include(${SDK_ROOT}/thirdparty/ethernet/lwip/lwip_sources.cmake)

add_executable(test_net
    test_net.c
    tap_driver.c
    ${SDK_ROOT}/middleware/net/src/net_common.c
    ${SDK_ROOT}/middleware/net/src/net_http.c
    ${SDK_ROOT}/middleware/net/src/net_lwip.c
    ${LWIP_SOURCES}
)
set_property(TARGET test_net PROPERTY C_STANDARD 99)
target_include_directories(test_net PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${SDK_ROOT}/middleware/net/include
    ${LWIP_INCLUDE_DIRS}
)
## code= : every mikroSDK library is compiled with it (mikrosdk_add_library), so
## the sources must build with it too. _GNU_SOURCE: getrandom()/usleep() on the host.
target_compile_definitions(test_net PRIVATE code= _GNU_SOURCE)
## Sanitizer findings abort the test (-fno-sanitize-recover), so they fail the run.
target_compile_options(test_net PRIVATE -g -O1 -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer)
target_link_options(test_net PRIVATE -fsanitize=address,undefined)

## Strict warnings for the mikroSDK files (lwIP keeps its own style).
set_source_files_properties(
    ${SDK_ROOT}/middleware/net/src/net_common.c
    ${SDK_ROOT}/middleware/net/src/net_http.c
    ${SDK_ROOT}/middleware/net/src/net_lwip.c
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Werror;-Wshadow;-Wconversion;-Wno-sign-conversion"
)
