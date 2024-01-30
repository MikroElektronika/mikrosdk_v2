## ./tests/dma/test_dma_m2p/CMakeLists.txt
set(executable_files "")
list(APPEND executable_files "main.c")
list(APPEND executable_files "ReadMe.txt")

set(systick_is_present "false")
if (${MCU_NAME} MATCHES "^(STM32|MK|TM4C12).+$")
    list(APPEND executable_files "../systick.h")
    set(systick_is_present "true")
endif()

add_executable(test_dma_m2p
    ${executable_files}
)

if(systick_is_present STREQUAL "true")
    target_compile_definitions(test_dma_m2p
        PRIVATE
            "SYSTICK_PRESENT"
    )

    target_include_directories(test_dma_m2p
        PRIVATE
            ../
    )
endif()

target_link_libraries(test_dma_m2p PUBLIC
    MikroC.Core
    MikroSDK.Driver.DMA
    MikroSDK.Driver.SPI.Master
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
)
