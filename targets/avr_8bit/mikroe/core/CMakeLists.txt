## ./targets/avr_8bit/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")
string(SUBSTRING ${MCU_NAME} 0 5 MEMAKE_MCU_NAME_FIRST_5)
string(SUBSTRING ${MCU_NAME} 0 6 MEMAKE_MCU_NAME_FIRST_6)

if (${MCU_NAME} MATCHES "AT")
    set(hal_ll_core_source "hal_ll_core.c")
    list(APPEND hal_ll_core_def_list "__avr__")
else()
    set(hal_ll_core_def_list "__family_not_supported__")
endif()

string(LENGTH ${MCU_NAME} MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

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
