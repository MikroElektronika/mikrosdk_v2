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
    ${SDK_ROOT}/middleware/net/src/net_http_server.c
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

## Unit tests (on-chip MAC support, time base), no network needed.
set(UNIT_OPTIONS -g -O1 -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer
    -Wall -Wextra -Werror)

add_executable(test_phy test_phy.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
target_include_directories(test_phy PRIVATE ${SDK_ROOT}/middleware/net/drivers/phy)

## The PIC32MZ driver against fake registers (fakes/pic32mz/mcu.h); it includes the driver source.
add_executable(test_pic32mz test_pic32mz.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
target_include_directories(test_pic32mz PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fakes/pic32mz
    ${CMAKE_CURRENT_LIST_DIR}/fakes/common
    ${SDK_ROOT}/middleware/net/include
    ${SDK_ROOT}/middleware/net/drivers/phy
    ${SDK_ROOT}/middleware/net/drivers/pic32mz
)
## PHYS() keeps 32 bits of a host pointer: harmless here, the fake controller never follows them.
target_compile_options(test_pic32mz PRIVATE -Wno-pointer-to-int-cast)

## platform/systime with a fake cycle counter (168 MHz).
add_executable(test_systime test_systime.c ${SDK_ROOT}/platform/systime/lib/src/systime.c)
target_include_directories(test_systime PRIVATE ${SDK_ROOT}/platform/systime/lib/include)
target_compile_definitions(test_systime PRIVATE SYSTIME_TEST_COUNTER SYSTIME_TEST_TICKS_PER_MS=168000u)

set(UNIT_TESTS test_phy test_pic32mz test_systime)

## STM32 Ethernet driver, one build per family: a functional test (fake registers,
## hardware model) and, where ST's CMSIS header is in the repository, a check of
## the register map against it.
set(ST_HEADERS ${SDK_ROOT}/thirdparty/ethernet/cyclonetcp/config/arm/st)
set(STM32_FAMILIES F1 F2 F4 F7)
set(STM32_F1 STM32F1xx 72000  stm32f107xc.h)
set(STM32_F2 STM32F2xx 120000 stm32f207xx.h)
set(STM32_F4 STM32F4xx 168000 stm32f407xx.h)
set(STM32_F7 STM32F7xx 216000 stm32f746xx.h)
foreach(fam ${STM32_FAMILIES})
    list(GET STM32_${fam} 0 st_family)
    list(GET STM32_${fam} 1 fosc_khz)
    list(GET STM32_${fam} 2 st_header)
    set(stm32_defs NET_STM32_${fam} ${st_family} FOSC_KHZ_VALUE=${fosc_khz})
    set(stm32_includes
        ${CMAKE_CURRENT_LIST_DIR}/fakes/stm32
        ${CMAKE_CURRENT_LIST_DIR}/fakes/common
        ${SDK_ROOT}/targets/arm/mikroe/stm32/include/gpio
        ${SDK_ROOT}/middleware/net/include
        ${SDK_ROOT}/middleware/net/drivers/phy
        ${SDK_ROOT}/middleware/net/drivers/stm32
    )
    string(TOLOWER ${fam} f)

    add_executable(test_stm32_${f} test_stm32.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
    target_include_directories(test_stm32_${f} PRIVATE ${stm32_includes})
    target_compile_definitions(test_stm32_${f} PRIVATE ${stm32_defs})
    target_compile_options(test_stm32_${f} PRIVATE -Wno-pointer-to-int-cast)
    list(APPEND UNIT_TESTS test_stm32_${f})

    if (EXISTS ${ST_HEADERS}/${st_header})
        add_library(stm32_regmap_ours_${f} OBJECT stm32_regmap_ours.c)
        target_include_directories(stm32_regmap_ours_${f} PRIVATE ${stm32_includes})
        target_compile_definitions(stm32_regmap_ours_${f} PRIVATE ${stm32_defs})
        target_compile_options(stm32_regmap_ours_${f} PRIVATE -Wno-unused-function -Wno-pointer-to-int-cast)
        add_library(stm32_regmap_st_${f} OBJECT stm32_regmap_st.c)
        target_include_directories(stm32_regmap_st_${f} PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/fakes/stm32/cmsis ${ST_HEADERS} ${CMAKE_CURRENT_LIST_DIR})
        target_compile_definitions(stm32_regmap_st_${f} PRIVATE NET_STM32_${fam} "ST_DEVICE_HEADER=\"${st_header}\"")
        add_executable(test_stm32_regmap_${f} stm32_regmap_main.c
            $<TARGET_OBJECTS:stm32_regmap_ours_${f}> $<TARGET_OBJECTS:stm32_regmap_st_${f}>)
        list(APPEND UNIT_TESTS test_stm32_regmap_${f})
    endif()
endforeach()

## The list run.sh runs.
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/unit_tests.txt CONTENT "$<JOIN:${UNIT_TESTS},\n>\n")

foreach(t ${UNIT_TESTS})
    set_property(TARGET ${t} PROPERTY C_STANDARD 99)
    target_compile_definitions(${t} PRIVATE code=)
    target_compile_options(${t} PRIVATE ${UNIT_OPTIONS})
    target_link_options(${t} PRIVATE -fsanitize=address,undefined)
endforeach()

## Strict warnings for the mikroSDK files (lwIP keeps its own style).
set_source_files_properties(
    ${SDK_ROOT}/middleware/net/src/net_common.c
    ${SDK_ROOT}/middleware/net/src/net_http.c
    ${SDK_ROOT}/middleware/net/src/net_http_server.c
    ${SDK_ROOT}/middleware/net/src/net_lwip.c
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Werror;-Wshadow;-Wconversion;-Wno-sign-conversion"
)
