## ./targets/pic_32bit/mikroe/pic32/src/dma/CMakeLists.txt
set(hal_ll_def_list "")

## BEGIN DMA
if(${MCU_NAME} MATCHES "PIC32")
    string(SUBSTRING ${MCU_NAME} 0 5 MCU_NAME_FIRST_5)
    string(SUBSTRING ${MCU_NAME} 0 7 MCU_NAME_FIRST_7)
    string(SUBSTRING ${MCU_NAME} 0 8 MCU_NAME_FIRST_8)
    string(SUBSTRING ${MCU_NAME} 0 10 MCU_NAME_FIRST_10)

    list(APPEND hal_ll_def_list ${MCU_NAME})
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_5}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_7}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_8}xx)
    list(APPEND hal_ll_def_list ${MCU_NAME_FIRST_10}xx)

    if (NOT (${MCU_NAME} MATCHES "^PIC32MX(3|4)(2|4|6)0.+"))
        list(APPEND hal_ll_def_list HAL_LL_DMA_DCHCON_CHBUSY_AVAILABLE)
    endif()

    list(APPEND hal_ll_def_list "__pic32__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

if(${MCU_NAME} MATCHES "(^PIC32.*$)")
    set(dma_implementation "implementation_1/hal_ll_dma.c")
endif()

mikrosdk_add_library(lib_hal_ll_dma MikroSDK.HalLowLevel.DMA
    ${dma_implementation}

    ../../include/hal_ll_target.h
    ##  BEGIN DMA
    ../../include/dma/hal_ll_dma.h
    ##  END DMA
)

target_compile_definitions(lib_hal_ll_dma PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_dma PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_HEADER_PATH_LOWER)
target_include_directories(lib_hal_ll_dma
    PRIVATE
        ../../include
        ##  BEGIN DMA
        ../../include/dma
        ##  END DMA
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/dma>

        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_HEADER_PATH_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.DMA)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.DMA ../../include/dma/hal_ll_dma.h)

