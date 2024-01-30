## ./targets/riscv/mikroe/gigadevice/src/dma/CMakeLists.txt
set(hal_ll_def_list "")
set(mcu_header_path "")

list(APPEND hal_ll_def_list ${MCU_NAME})

set(mcu_header_path ${MCU_NAME})

list(APPEND hal_ll_def_list "MACRO_USAGE_DMA")

mikrosdk_add_library(lib_hal_ll_dma MikroSDK.HalLowLevel.DMA
    implementation_1/hal_ll_dma.c

    ../../include/hal_ll_rcu.h
    ../../include/hal_ll_target.h
    #  BEGIN DMA
    ../../include/dma/hal_ll_dma.h
    #  END DMA
)

target_compile_definitions(lib_hal_ll_dma PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_dma PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${mcu_header_path} MCU_HEADER_PATH_LOWER)

target_include_directories(lib_hal_ll_dma
    PRIVATE
        ../../include
        ../../include/gpio
        #  BEGIN DMA
        ../../include/dma
        #  END DMA

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/gpio>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/dma>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.DMA)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.DMA ../../include/dma/hal_ll_dma.h)
