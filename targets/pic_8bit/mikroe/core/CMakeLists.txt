## ./targets/pic_8bit/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")
string(SUBSTRING ${MCU_NAME} 0 5 MEMAKE_MCU_NAME_FIRST_5)
string(SUBSTRING ${MCU_NAME} 0 6 MEMAKE_MCU_NAME_FIRST_6)

core_implementation_select(${MCU_NAME} core_implementation)

if (${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_core_def_list "__pic18__")
    if(${MCU_NAME} MATCHES "PIC18LF")
        list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_6}"xx")
    else()
        list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_5}"xx")
    endif()
else()    ## TODO Only PIC18 MCUs supported at the moment.
    list(APPEND hal_ll_core_def_list ${MEMAKE_MCU_NAME_FIRST_5}"xx")
    set(core_implementation "pic_not_supported.c")
    set(hal_ll_core_def_list "__family_not_supported__")
endif()

if (${MCU_NAME} MATCHES "^PIC18L?F[245][4-7]((K(42|83))|Q(43|8[34]))$")
    list(APPEND hal_ll_core_def_list "INTCON_REG=INTCON0")
else()
    list(APPEND hal_ll_core_def_list "INTCON_REG=INTCON")
endif()

string(LENGTH ${MCU_NAME} MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## K42 and Q43 have different assembly instructions
if((${MCU_NAME_LAST_3} MATCHES "K42") OR (${MCU_NAME_LAST_3} MATCHES "Q(43|8[34])"))
    list(APPEND hal_ll_core_def_list "__hal_ll_core_subimplementation_1__")
else()
    list(APPEND hal_ll_core_def_list "__hal_ll_core_subimplementation_2__")
endif()

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/${core_implementation}

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
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.CORE include/hal_ll_core.h include/hal_ll_core_defines.h)
