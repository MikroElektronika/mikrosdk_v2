## ./hal/lib/src/lib_hal_can/CMakeLists.txt
mikrosdk_add_library(lib_hal_can MikroSDK.Hal.CAN
    hal_can.c

    ../../include/hal_can.h
)

target_link_libraries(lib_hal_can  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.CAN
)

target_include_directories(lib_hal_can
    PRIVATE
        ../../include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.CAN ../../include/hal_can.h)
