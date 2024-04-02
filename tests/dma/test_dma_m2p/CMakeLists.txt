## ./tests/dma/test_dma_m2p/CMakeLists.txt
set(executable_files "")
list(APPEND executable_files "main.c")
list(APPEND executable_files "ReadMe.txt")

add_executable(test_dma_m2p
    ${executable_files}
)

target_link_libraries(test_dma_m2p PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
)
