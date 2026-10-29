## ./components/tft8/CMakeLists.txt
add_subdirectory(lib)
add_subdirectory(common)

# DMA flush engine for the 16-bit 8080 TFT bus. Built wherever MikroSDK.LVGL.Common is (same
# board condition), for every MCU and toolchain: families without a DMA backend get a stub whose
# tft8_dma_flush_init() fails, so display drivers can always link it and fall back to the CPU.
if(_MSDK_TFT_BOARD_)
    if(${_MSDK_TFT_BOARD_} MATCHES "(TFT_BOARD_[3457]_(CAPACITIVE|RESISTIVE))|(^MIKROMEDIA(.+)$)")
        add_subdirectory(dma_flush)
    endif()
endif()
