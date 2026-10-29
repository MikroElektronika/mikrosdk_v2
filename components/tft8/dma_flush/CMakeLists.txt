## ./components/tft8/dma_flush/CMakeLists.txt
# Timer-paced DMA flush engine for 16-bit 8080 TFT boards (see include/tft8_dma_flush.h).
# With GCC on STM32F2/F4/F7 the DMA backend is compiled (and the DMA driver linked);
# everywhere else only the stub backend, which makes tft8_dma_flush_init() fail so
# callers use the CPU path. Keep this condition in sync with TFT8_DMA_FLUSH_SUPPORTED.
if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU" AND ${MCU_NAME} MATCHES "^STM32F[247]")
    set(tft8_dma_flush_backend src/tft8_dma_flush_stm32_stream.c)
    set(tft8_dma_flush_deps MikroSDK.Driver.DMA)
else()
    set(tft8_dma_flush_backend src/tft8_dma_flush_none.c)
    set(tft8_dma_flush_deps "")
endif()

mikrosdk_add_library(lib_tft8_dma_flush MikroSDK.Tft8.DmaFlush
    src/tft8_dma_flush.c
    ${tft8_dma_flush_backend}
    src/tft8_dma_flush_backend.h
    include/tft8_dma_flush.h
)

# MikroSDK.Driver provides drv_name.h (err_t) on every target.
target_link_libraries(lib_tft8_dma_flush PUBLIC
    MikroC.Core
    MikroSDK.Driver
    ${tft8_dma_flush_deps}
)

target_include_directories(lib_tft8_dma_flush
    PRIVATE
        include
        src
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/components/tft8_dma_flush>
)

mikrosdk_install(MikroSDK.Tft8.DmaFlush)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/tft8_dma_flush MikroSDK.Tft8.DmaFlush include/tft8_dma_flush.h)
