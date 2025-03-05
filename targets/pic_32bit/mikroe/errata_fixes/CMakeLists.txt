## ./targets/pic_32bit/mikroe/errata_fixes/CMakeLists.txt
set(hal_ll_errata_def_list "")

if (${MCU_NAME} MATCHES "PIC32")
    list(APPEND hal_ll_errata_def_list "__pic32__")
endif()

if (${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    list(APPEND hal_ll_errata_def_list ${MCU_NAME_FIRST_7}xx)
else()
    list(APPEND hal_ll_errata_def_list "__family_not_supported__")
endif()

mikrosdk_add_library(lib_hal_ll_errata MikroSDK.HalLowLevelErrata
    src/hal_ll_errata.c
    include/hal_ll_errata.h

    ../pic32/include/i2c/hal_ll_i2c_master.h
    ../pic32/include/gpio/hal_ll_gpio.h
)

target_compile_definitions(lib_hal_ll_errata
    PUBLIC
        ${hal_ll_errata_def_list}
)

target_link_libraries(lib_hal_ll_errata PUBLIC
    MikroSDK.HalLowLevelCommon
)

target_include_directories(lib_hal_ll_errata
    PRIVATE
        include
        ../pic32/include
        ../pic32/include/gpio
        ../pic32/include/i2c
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../pic32/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../pic32/include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../pic32/include/i2c>

        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelErrata)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.ERRATA include/hal_ll_errata.h ../pic32/include/i2c/hal_ll_i2c_master.h ../pic32/include/gpio/hal_ll_gpio.h)
