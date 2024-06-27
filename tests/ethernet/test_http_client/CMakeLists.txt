## ./tests/ethernet/test_http_client/CMakeLists.txt
add_executable(test_ethernet_http_client
    main.c
)

if (NOT ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    target_sources(test_ethernet_http_client PRIVATE ../systick.h)
endif()

target_link_libraries(test_ethernet_http_client PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Ethernet.CycloneTCP
)

# Include search paths.
if (NOT ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    target_include_directories(test_ethernet_http_client
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../
    )
endif()

if (${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    ## TODO Consider adding more in case of instability. CycloneTCP demo uses 81920.
    target_link_options(test_ethernet_http_client PRIVATE "LINKER:--defsym=_min_heap_size=16384")
endif()

if (NOT ${TOOLCHAIN_ID} STREQUAL "mchp_xc32")
    add_compile_definitions(SYSTICK_PRESENT)
elseif (${MCU_NAME} MATCHES "PIC32MX")
    add_compile_definitions(PIC32MX)
elseif (${MCU_NAME} MATCHES "PIC32MZ")
    add_compile_definitions(PIC32MZ)
endif()

add_compile_definitions(
    "MCU_NAME_CMAKE=\"${MCU_NAME}\""
)
