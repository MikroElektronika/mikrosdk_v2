## ./tests/dma/test_dma_m2m_p2p_2dmas/CMakeLists.txt
add_executable(test_dma_m2m_p2p_2dmas
    main.c
    ReadMe.txt
    ../inc/dma_test.h
)

target_include_directories(test_dma_m2m_p2p_2dmas
PRIVATE
    ../inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
)

target_link_libraries(test_dma_m2m_p2p_2dmas PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.UART
    MikroSDK.Board
)
