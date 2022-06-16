set(hal_ll_core_def_list "")
string(SUBSTRING ${MCU_NAME} 0 5 MEMAKE_MCU_NAME_FIRST_5)
string(SUBSTRING ${MCU_NAME} 0 6 MEMAKE_MCU_NAME_FIRST_6)

if (${MCU_NAME} MATCHES "PIC18")
    set(hal_ll_core_source "hal_ll_core.c")
    list(APPEND hal_ll_core_def_list "__pic18__")
    if(${MCU_NAME} MATCHES "PIC18LF")
        list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_6}"xx")
    else()
        list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_5}"xx")
    endif()
else()    ## TODO Only PIC18 MCUs supported at the moment.
    list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_5}"xx")
    set(hal_ll_core_source "pic_not_supported.c")
    set(hal_ll_core_def_list "__family_not_supported__")
endif()

string(LENGTH ${MCU_NAME} MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## K42 and Q43 have different assembly instructions
if((${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q43"))
    list(APPEND hal_ll_core_def_list "__hal_ll_core_subimplementation_1__")
else()
    list(APPEND hal_ll_core_def_list "__hal_ll_core_subimplementation_2__")
endif()

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/${hal_ll_core_source}

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
