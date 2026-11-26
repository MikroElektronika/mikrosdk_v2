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
    ${SDK_ROOT}/middleware/net/src/net_sntp.c
    ${SDK_ROOT}/middleware/net/src/net_mqtt.c
    ${SDK_ROOT}/middleware/net/src/net_mdns.c
    ${SDK_ROOT}/middleware/net/src/net_ftp.c
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

## The PIC32MZ driver against fake registers (fakes/pic32/mcu.h); it includes the driver source.
add_executable(test_pic32 test_pic32.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
target_include_directories(test_pic32 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fakes/pic32
    ${CMAKE_CURRENT_LIST_DIR}/fakes/common
    ${SDK_ROOT}/middleware/net/include
    ${SDK_ROOT}/middleware/net/drivers/phy
    ${SDK_ROOT}/middleware/net/drivers/pic32
)
## PHYS() keeps 32 bits of a host pointer: harmless here, the fake controller never follows them.
target_compile_options(test_pic32 PRIVATE -Wno-pointer-to-int-cast)

## platform/systime with a fake cycle counter (168 MHz).
add_executable(test_systime test_systime.c ${SDK_ROOT}/platform/systime/lib/src/systime.c)
target_include_directories(test_systime PRIVATE ${SDK_ROOT}/platform/systime/lib/include)
target_compile_definitions(test_systime PRIVATE SYSTIME_TEST_COUNTER SYSTIME_TEST_TICKS_PER_MS=168000u)

set(UNIT_TESTS test_phy test_pic32 test_systime)

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
            ${CMAKE_CURRENT_LIST_DIR}/fakes/cmsis ${ST_HEADERS} ${CMAKE_CURRENT_LIST_DIR})
        target_compile_definitions(stm32_regmap_st_${f} PRIVATE NET_STM32_${fam} "ST_DEVICE_HEADER=\"${st_header}\"")
        add_executable(test_stm32_regmap_${f} stm32_regmap_main.c
            $<TARGET_OBJECTS:stm32_regmap_ours_${f}> $<TARGET_OBJECTS:stm32_regmap_st_${f}>)
        list(APPEND UNIT_TESTS test_stm32_regmap_${f})
    endif()
endforeach()

## Kinetis ENET driver: a functional test per pin variant, and a register map
## check against each NXP device header in the repository.
set(NXP_HEADERS ${SDK_ROOT}/thirdparty/ethernet/cyclonetcp/config/arm/nxp)
set(KINETIS_TESTS k60:K60_K64:100000:mk60/MK60D10.h k64:K60_K64:120000:mk64/MK64F12.h
                  k65:K65_K66:180000:mk65/MK65F18.h k66:K65_K66:180000:mk66/MK66F18.h
                  kv58:KV58:240000:mkv58/MKV58F24.h)
set(kinetis_functional k64 k66 kv58)
foreach(entry ${KINETIS_TESTS})
    string(REPLACE ":" ";" entry ${entry})
    list(GET entry 0 k)
    list(GET entry 1 variant)
    list(GET entry 2 fosc_khz)
    list(GET entry 3 nxp_header)
    set(kinetis_defs NET_KINETIS_${variant} FOSC_KHZ_VALUE=${fosc_khz})
    set(kinetis_includes
        ${CMAKE_CURRENT_LIST_DIR}/fakes/common
        ${SDK_ROOT}/middleware/net/include
        ${SDK_ROOT}/middleware/net/drivers/phy
        ${SDK_ROOT}/middleware/net/drivers/kinetis
    )
    if (k IN_LIST kinetis_functional)
        add_executable(test_kinetis_${k} test_kinetis.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
        target_include_directories(test_kinetis_${k} PRIVATE ${kinetis_includes})
        target_compile_definitions(test_kinetis_${k} PRIVATE ${kinetis_defs})
        target_compile_options(test_kinetis_${k} PRIVATE -Wno-pointer-to-int-cast)
        list(APPEND UNIT_TESTS test_kinetis_${k})
    endif()
    if (EXISTS ${NXP_HEADERS}/${nxp_header})
        get_filename_component(nxp_dir ${NXP_HEADERS}/${nxp_header} DIRECTORY)
        get_filename_component(nxp_file ${nxp_header} NAME)
        add_library(kinetis_regmap_ours_${k} OBJECT kinetis_regmap_ours.c)
        target_include_directories(kinetis_regmap_ours_${k} PRIVATE ${kinetis_includes})
        target_compile_definitions(kinetis_regmap_ours_${k} PRIVATE ${kinetis_defs})
        target_compile_options(kinetis_regmap_ours_${k} PRIVATE -Wno-unused-function -Wno-pointer-to-int-cast)
        add_library(kinetis_regmap_nxp_${k} OBJECT kinetis_regmap_nxp.c)
        target_include_directories(kinetis_regmap_nxp_${k} PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/fakes/cmsis ${nxp_dir} ${CMAKE_CURRENT_LIST_DIR})
        target_compile_definitions(kinetis_regmap_nxp_${k} PRIVATE "NXP_DEVICE_HEADER=\"${nxp_file}\"")
        add_executable(test_kinetis_regmap_${k} stm32_regmap_main.c
            $<TARGET_OBJECTS:kinetis_regmap_ours_${k}> $<TARGET_OBJECTS:kinetis_regmap_nxp_${k}>)
        list(APPEND UNIT_TESTS test_kinetis_regmap_${k})
    endif()
endforeach()

## TM4C129 Ethernet driver: functional test and register map against TI's headers.
set(TI_HEADERS ${SDK_ROOT}/thirdparty/ethernet/cyclonetcp/config/arm/ti)
set(tm4c_includes
    ${CMAKE_CURRENT_LIST_DIR}/fakes/common
    ${SDK_ROOT}/middleware/net/include
    ${SDK_ROOT}/middleware/net/drivers/phy
    ${SDK_ROOT}/middleware/net/drivers/tm4c
)
add_executable(test_tm4c test_tm4c.c ${SDK_ROOT}/middleware/net/drivers/phy/net_phy.c)
target_include_directories(test_tm4c PRIVATE ${tm4c_includes})
target_compile_definitions(test_tm4c PRIVATE FOSC_KHZ_VALUE=120000)
target_compile_options(test_tm4c PRIVATE -Wno-pointer-to-int-cast)
list(APPEND UNIT_TESTS test_tm4c)
if (EXISTS ${TI_HEADERS}/inc/hw_emac.h)
    add_library(tm4c_regmap_ours OBJECT tm4c_regmap_ours.c)
    target_include_directories(tm4c_regmap_ours PRIVATE ${tm4c_includes})
    target_compile_definitions(tm4c_regmap_ours PRIVATE FOSC_KHZ_VALUE=120000)
    target_compile_options(tm4c_regmap_ours PRIVATE -Wno-unused-function -Wno-pointer-to-int-cast)
    add_library(tm4c_regmap_ti OBJECT tm4c_regmap_ti.c)
    target_include_directories(tm4c_regmap_ti PRIVATE ${TI_HEADERS} ${CMAKE_CURRENT_LIST_DIR})
    target_compile_definitions(tm4c_regmap_ti PRIVATE PART_TM4C1294NCPDT)
    add_executable(test_tm4c_regmap stm32_regmap_main.c
        $<TARGET_OBJECTS:tm4c_regmap_ours> $<TARGET_OBJECTS:tm4c_regmap_ti>)
    list(APPEND UNIT_TESTS test_tm4c_regmap)
endif()

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
    ${SDK_ROOT}/middleware/net/src/net_sntp.c
    ${SDK_ROOT}/middleware/net/src/net_mqtt.c
    ${SDK_ROOT}/middleware/net/src/net_mdns.c
    ${SDK_ROOT}/middleware/net/src/net_ftp.c
    ${SDK_ROOT}/middleware/net/src/net_lwip.c
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Werror;-Wshadow;-Wconversion;-Wno-sign-conversion"
)
