## ./targets/arm/mikroe/tiva/src/rtc/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN RTC
list(APPEND hal_ll_def_list "MACRO_USAGE_RTC")

if(${MCU_NAME} MATCHES "TM4C129.+")
    set(rtc_subimplementation "implementation_1/hal_ll_rtc.c")
elseif(${MCU_NAME} MATCHES "TM4C123[137BG].+")
    set(rtc_subimplementation "implementation_2/hal_ll_rtc.c")
endif()
## END RTC

mikrosdk_add_library(lib_hal_ll_rtc MikroSDK.HalLowLevel.RTC
    ${rtc_subimplementation}

    ../../include/rtc/hal_ll_rtc.h)

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
        ../../include/rtc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/rtc>
        $<INSTALL_INTERFACE:include/hal_ll_port>
)

mikrosdk_install(MikroSDK.HalLowLevel.RTC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.RTC ../../include/rtc/hal_ll_rtc.h)
