## ./targets/pic_32bit/mikroe/core/CMakeLists.txt
set(hal_ll_core_def_list "")

if (${MCU_NAME} MATCHES "PIC32")
    list(APPEND hal_ll_core_def_list "__pic32__")
endif()

if (${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    list(APPEND hal_ll_core_def_list ${MCU_NAME_FIRST_7}xx)
else()
    list(APPEND hal_ll_core_def_list "__family_not_supported__")
endif()

mikrosdk_add_library(lib_hal_ll_core MikroSDK.HalLowLevelCore
    src/hal_ll_core.c

    include/hal_ll_core_defines.h
    include/hal_ll_core_port.h
    include/hal_ll_core.h
)

target_compile_definitions(lib_hal_ll_core
    PUBLIC
        ${hal_ll_core_def_list}
)

target_link_libraries(lib_hal_ll_core PUBLIC
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
