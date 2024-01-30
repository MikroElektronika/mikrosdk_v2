## ./tests/dma/test_dma_m2m/CMakeLists.txt
add_executable(test_dma_m2m
    main.c
    ReadMe.txt
    ${systick_include}
)

target_link_libraries(test_dma_m2m PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
