## ./targets/pic_32bit/mikroe/common/CMakeLists.txt
mikrosdk_add_interface_library(lib_hal_ll_common MikroSDK.HalLowLevelCommon
    include/hal_ll_bit_control.h
    include/mcu_definitions/${MCU_NAME}/mcu_definitions.h
    include/common_macros.h
)

target_link_libraries(lib_hal_ll_common
    INTERFACE
        MikroC.Core
)

target_include_directories(lib_hal_ll_common
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_definitions/${MCU_NAME}>

        $<INSTALL_INTERFACE:include>
)

mikrosdk_install(MikroSDK.HalLowLevelCommon)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevelCommon include/hal_ll_bit_control.h include/assembly.h include/common_macros.h)


string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
install(
    FILES
        include/mcu_definitions/${MCU_NAME}/mcu_definitions.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/${MCU_NAME_LOWER}
)
