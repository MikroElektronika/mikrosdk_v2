## ./hal/lib/src/lib_hal_rtc/CMakeLists.txt

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    set(rtc_subimplementation implementation_1/hal_rtc.c)
else()
    set(rtc_subimplementation implementation_2/hal_rtc.c)
endif()

mikrosdk_add_library(lib_hal_rtc MikroSDK.Hal.RTC
    ${rtc_subimplementation}

    ../../include/hal_rtc.h
)

target_link_libraries(lib_hal_rtc  PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.RTC
)

target_include_directories(lib_hal_rtc
PRIVATE
    ../../include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.RTC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.RTC ../../include/hal_rtc.h)