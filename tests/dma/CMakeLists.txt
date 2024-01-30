# ## ./tests/dma/CMakeLists.txt

## 8K Flash and 4K RAM minimum for all tests.
memory_sdk_test_check(memory_issue 8192 4096)

if (${memory_issue} STREQUAL "FALSE")
    add_subdirectory(test_dma_m2m)
    if (${MCU_NAME} MATCHES "^PIC18.+K42$")
        add_subdirectory(pic18/test_dma_k42_bus_arbiter)
    endif()
    add_subdirectory(test_dma_m2p)
    add_subdirectory(test_dma_m2p_uart)
    add_subdirectory(test_dma_p2p_uart_echo)
    add_subdirectory(test_dma_m2m_p2p_2dmas)
else()
    message(INFO ": ${MCU_NAME} does not have enough memory for DMA tests.")
endif()
