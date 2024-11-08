## ./drv/lib/src/lib_drv_dma/CMakeLists.txt
mikrosdk_add_library(lib_drv_dma MikroSDK.Driver.DMA
    drv_dma.c

    ../../include/drv_dma.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_dma PUBLIC
    MikroC.Core
    MikroSDK.Hal.DMA
)

target_include_directories(lib_drv_dma
    PRIVATE
        ../../include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include/drv>
)

resolve_compiler_definitions(REDUCE_LAYER)

mikrosdk_install(MikroSDK.Driver.DMA)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.DMA ../../include/drv_dma.h)
