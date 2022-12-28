## ./hal/lib/src/lib_hal_uart/CMakeLists.txt
mikrosdk_add_library(lib_hal_uart MikroSDK.Hal.UART
    hal_uart.c

    ../../include/hal_uart.h
)

target_link_libraries(lib_hal_uart  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.UART
)

target_include_directories(lib_hal_uart
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.UART)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.UART ../../include/hal_uart.h)
