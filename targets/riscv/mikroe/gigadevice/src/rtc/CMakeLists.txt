## ./targets/risv/mikroe/gigadevice/src/rtc/CMakeLists.txt
set(hal_ll_def_list "")
list(APPEND hal_ll_def_list "MACRO_USAGE_RTC")

set(rtc_subimplementation "implementation_1/hal_ll_rtc.c")

mikrosdk_add_library(lib_hal_ll_rtc MikroSDK.HalLowLevel.RTC
    ${rtc_subimplementation}

    ../../include/rtc/hal_ll_rtc.h
)

target_compile_definitions(lib_hal_ll_rtc PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_rtc PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevelCommon
)

target_include_directories(lib_hal_ll_rtc
    PRIVATE
        ../../include/rtc/
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/rtc/>
        $<INSTALL_INTERFACE:include/hal_ll_port>
)

mikrosdk_install(MikroSDK.HalLowLevel.RTC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.RTC ../../include/rtc/hal_ll_rtc.h)
