## ./drv/lib/src/lib_drv_can/CMakeLists.txt
mikrosdk_add_library(lib_drv_can MikroSDK.Driver.CAN
    drv_can.c

    ../../include/drv_can.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_can PUBLIC
    MikroC.Core
    MikroSDK.Hal.CAN
)

target_include_directories(lib_drv_can
    PRIVATE
        ../../include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.CAN)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.CAN ../../include/drv_can.h)
