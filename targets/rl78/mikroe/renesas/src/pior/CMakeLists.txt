## ./targets/rl78/mikroe/renesas/src/pior/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN PIOR
if(${MCU_NAME} MATCHES "^R7F100.+$") # TODO
    list(APPEND hal_ll_def_list "__rl78__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

set(pior_subimplementation "implementation_1/hal_ll_pior_port.c")
## END PIOR

list(APPEND hal_ll_def_list "MACRO_USAGE_PIOR")

mikrosdk_add_library(lib_hal_ll_pior MikroSDK.HalLowLevel.PIOR
    hal_ll_pior.c
    ${pior_subimplementation}

    ../../include/hal_ll_target.h
##  BEGIN PIOR
    ../../include/pior/hal_ll_pior.h
    ../../include/pior/hal_ll_pior_port.h
    ../../include/pior/hal_ll_pior_defines.h
    ../../include/pior/hal_ll_pior_struct_def.h
    ../../include/pior/hal_ll_pior_connection_defs/${MCU_NAME}/hal_ll_pior_connection_defs.h
##  END PIOR
)

target_compile_definitions(lib_hal_ll_pior PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_pior PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_pior
    PRIVATE
        ../../include
        ../../include/gpio
        #BEGINPIOR
        ../../include/pior
        ../../include/pior/hal_ll_pior_connection_defs
        ../../include/pior/hal_ll_pior_connection_defs/${MCU_NAME}
        #ENDPIOR
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pior>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pior/hal_ll_pior_connection_defs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/pior/hal_ll_pior_connection_defs/${MCU_NAME}>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.PIOR)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.PIOR ../../include/pior/hal_ll_pior.h ../../include/pior/hal_ll_pior_port.h ../../include/pior/hal_ll_pior_defines.h ../../include/pior/hal_ll_pior_struct_def.h ../../include/pior/hal_ll_pior_connection_defs/${MCU_NAME}/hal_ll_pior_connection_defs.h)
