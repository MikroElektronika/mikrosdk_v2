## ./hal/lib/src/lib_hal_dma/CMakeLists.txt
mikrosdk_add_library(lib_hal_dma MikroSDK.Hal.DMA
    hal_dma.c

    ../../include/hal_dma.h
)

target_link_libraries(lib_hal_dma PUBLIC
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.HalLowLevel.DMA
)

target_include_directories(lib_hal_dma
    PRIVATE
        ../../include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/hal>
)

mikrosdk_install(MikroSDK.Hal.DMA)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.Hal.DMA ../../include/hal_dma.h)
