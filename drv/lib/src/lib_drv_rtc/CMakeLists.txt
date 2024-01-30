## ./drv/lib/src/lib_drv_rtc/CMakeLists.txt
mikrosdk_add_library(lib_drv_rtc MikroSDK.Driver.RTC
    drv_rtc.c

    ../../include/drv_rtc.h
)

target_link_libraries(lib_drv_rtc PUBLIC
     MikroC.Core
     MikroSDK.Hal.RTC
)

target_include_directories(lib_drv_rtc
    PRIVATE
        ../../include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.RTC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.RTC ../../include/drv_rtc.h)
