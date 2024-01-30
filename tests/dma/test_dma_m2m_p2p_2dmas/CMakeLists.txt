## ./tests/dma/test_dma_m2m_p2p_2dmas/CMakeLists.txt
add_executable(test_dma_m2m_p2p_2dmas
    main.c
    ReadMe.txt
    ${systick_include}
)

target_link_libraries(test_dma_m2m_p2p_2dmas PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.UART
    MikroSDK.Board
)
