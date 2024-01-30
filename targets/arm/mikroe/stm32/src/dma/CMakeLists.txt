## ./targets/arm/mikroe/stm32/src/dma/CMakeLists.txt
set(hal_ll_def_list "")
set(MEMAKE_MCU_NAME_FIRST_7 "")
set(mcu_header_path "")

find_cortex(hal_ll_def_list)

find_mcu_header_path(hal_ll_def_list mcu_header_path MEMAKE_MCU_NAME_FIRST_7)

## BEGIN DMA
## Note1 - STM32(F[013]|L[014]|G0) should have separate implementation.
##         Looks like one will cover all of them.
## Note2 - STM32H7 requires a separate implementation as it has DMA controller
##         sith separate DMAMUX controller per DMA.
if (${MCU_NAME} MATCHES "^STM32F[247].+")
    set(dma_subimplementation "implementation_1/hal_ll_dma.c")
else()
    set(dma_subimplementation "implementation_2/hal_ll_dma.c")
endif()

## Note3 - STM32F0 and STM32L0 have additional CSELR registar and its handled with IMPL_2
## Note4 - STM32L4[RS] and STM32[GH] have additional DMAMUX controller and its handled with IMPL_3
if (${MCU_NAME} MATCHES "^STM32F0.0.+$" OR ${MCU_NAME} MATCHES "^STM32L0.+$")
    list(APPEND hal_ll_def_list "IMPL_2")
elseif(${MCU_NAME} MATCHES "^STM32L4[RS].+$" OR ${MCU_NAME} MATCHES "^STM32[GH].+$")
    list(APPEND hal_ll_def_list "IMPL_3")
endif()
## END DMA

list(APPEND hal_ll_def_list "MACRO_USAGE_DMA")

mikrosdk_add_library(lib_hal_ll_dma MikroSDK.HalLowLevel.DMA
    ${dma_subimplementation}

    ../../include/hal_ll_rcc.h
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
