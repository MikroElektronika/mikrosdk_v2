## ./tests/dma/test_dma_m2p_uart/CMakeLists.txt
add_executable(test_dma_m2p_uart
    main.c
    ReadMe.txt
    ../inc/dma_test.h
)

target_include_directories(test_dma_m2p_uart
PRIVATE
    ../inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
)

target_link_libraries(test_dma_m2p_uart PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
