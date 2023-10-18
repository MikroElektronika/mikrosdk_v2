## ./drv/lib/src/lib_drv_uart/CMakeLists.txt
mikrosdk_add_library(lib_drv_uart MikroSDK.Driver.UART
    drv_uart.c

    ../../include/drv_uart.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_uart  PUBLIC
    MikroC.Core
    MikroSDK.Hal.UART
    MikroSDK.RingBuffer
)

target_include_directories(lib_drv_uart
PRIVATE
    ../../include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.UART)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.UART ../../include/drv_uart.h)
