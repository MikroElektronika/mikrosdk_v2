## ./targets/pic_8bit/mikroe/pic18/src/dma/CMakeLists.txt
set(hal_ll_def_list "")
if(${MCU_NAME} MATCHES "PIC18")
    list(APPEND hal_ll_def_list "__pic18__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()
list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

if (${MCU_NAME} MATCHES "K42")
    set(dma_subimplementation "implementation_1")

    if (${MCU_NAME} MATCHES ".*5K42$")
        set(gpr_end_address 0x07FF)
    elseif (${MCU_NAME} MATCHES ".*6K42$")
        set(gpr_end_address 0x0FFF)
    elseif (${MCU_NAME} MATCHES ".*7K42$")
        set(gpr_end_address 0x1FFF)
    endif ()

    set (sfr_start_address 0x3800)
elseif (${MCU_NAME} MATCHES ".*Q(43|8[34])$")
    set(dma_subimplementation "implementation_2")

    if (${MCU_NAME} MATCHES ".*5K42$")
        set(gpr_end_address 0x07FF)
    elseif (${MCU_NAME} MATCHES ".*6K42$")
        set(gpr_end_address 0x0FFF)
    elseif (${MCU_NAME} MATCHES ".*7K42$")
        set(gpr_end_address 0x1FFF)
    endif ()

    set (sfr_start_address 0x3800)
endif()

if (${MCU_NAME} MATCHES "^PIC18.*K42$")
    list(APPEND hal_ll_def_list "HAL_LL_DMA_IMPLEMENTATION_1")
elseif (${MCU_NAME} MATCHES "^PIC18.*Q(43|8[34])$")
    list(APPEND hal_ll_def_list "HAL_LL_DMA_IMPLEMENTATION_2")
else()
    list(APPEND hal_ll_def_list "__mcu_not_supported__")
endif()

list(APPEND hal_ll_def_list "MACRO_USAGE_DMA")

mikrosdk_add_library(lib_hal_ll_dma MikroSDK.HalLowLevel.DMA
    ${dma_subimplementation}/hal_ll_dma.c
    ../../include/hal_ll_target.h
    #  BEGIN DMA
    ../../include/dma/hal_ll_dma.h
    #  END DMA
)

target_compile_definitions(lib_hal_ll_dma PUBLIC
    ${hal_ll_def_list}
    HAL_LL_DMA_GPR_END_ADDRESS=${gpr_end_address}
    HAL_LL_DMA_SFR_START_ADDRESS=${sfr_start_address}
)

target_link_libraries(lib_hal_ll_dma
PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)
string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)

target_include_directories(lib_hal_ll_dma
    PRIVATE
        ../../include
        #  BEGIN DMA
        ../../include/dma
        #  END DMA

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/dma>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.DMA)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.DMA ../../include/dma/hal_ll_dma.h)
