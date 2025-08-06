## ./targets/arm/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")
if(${MCU_NAME} MATCHES "^STM32.*")
    set(chip_vendor "stm32")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    string(SUBSTRING ${MCU_NAME} 0 7 STRIPED_MCU_NAME)
    list(APPEND hal_ll_core_def_list ${STRIPED_MCU_NAME}xx)
    string(SUBSTRING ${MCU_NAME} 6 1 MEMAKE_MCU_NAME_6TH_CHAR)
    if (${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "0")
        set(hal_ll_core_source "m0")
        list(APPEND hal_ll_core_def_list __cortex_m0__)
    elseif ((${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "1") OR (${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "2"))
        set(hal_ll_core_source "m3")
        list(APPEND hal_ll_core_def_list __cortex_m3__)
    elseif((${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "3") OR (${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "4"))
        set(hal_ll_core_source "m4")
        list(APPEND hal_ll_core_def_list __cortex_m4__)
    elseif(${MEMAKE_MCU_NAME_6TH_CHAR} MATCHES "7")
        set(hal_ll_core_source "m7")
        list(APPEND hal_ll_core_def_list __cortex_m7__)
    else()
        list(APPEND hal_ll_core_def_list __cortex_not_supported__)
    endif()
elseif(${MCU_NAME} MATCHES "^MK.*")
    set(chip_vendor "nxp")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    if((${CORE_NAME} MATCHES "M4EF") OR (${CORE_NAME} MATCHES "M4DSP"))
        set(hal_ll_core_source "m4")
        list(APPEND hal_ll_core_def_list __cortex_m4__)
    elseif(${CORE_NAME} MATCHES "M7")
        set(hal_ll_core_source "m7")
        list(APPEND hal_ll_core_def_list __cortex_m7__)
    else()
        list(APPEND hal_ll_core_def_list __cortex_not_supported__)
    endif()
elseif(${MCU_NAME} MATCHES "^TM4C.*")
    set(chip_vendor "tiva")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    set(hal_ll_core_source "m4")
elseif(${MCU_NAME} MATCHES "^R7.*")
    set(chip_vendor "renesas")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    if((${CORE_NAME} MATCHES "M4EF") OR (${CORE_NAME} MATCHES "M4DSP"))
        set(hal_ll_core_source "m4")
        list(APPEND hal_ll_core_def_list __cortex_m4__)
    endif()
elseif(${MCU_NAME} MATCHES "^(AT)?SAM.*")
    set(chip_vendor "sam")
    list(APPEND hal_ll_core_def_list ${chip_vendor})
    if(${CORE_NAME} MATCHES "M7")
        set(hal_ll_core_source "m7")
        list(APPEND hal_ll_core_def_list __cortex_m7__)
    endif()
else()
    list(hal_ll_core_def_list __vendor_not_supported__)
endif()

core_implementation_select(${MCU_NAME} core_implementation)

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/${core_implementation}
    src/${chip_vendor}/${hal_ll_core_source}/hal_ll_core_port.c

    include/hal_ll_core_defines.h
    include/hal_ll_core_port.h
    include/hal_ll_core.h
)

target_compile_definitions(lib_hal_ll_core
    PUBLIC
        ${hal_ll_core_def_list}
)

target_link_libraries(lib_hal_ll_core PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCommon
)

target_include_directories(lib_hal_ll_core
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCore)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CORE include/hal_ll_core.h)
