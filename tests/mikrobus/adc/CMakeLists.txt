## ./tests/mikrobus/adc/CMakeLists.txt
add_executable(test_mikrobus_adc
    src/main.c
    inc/mikrobus_adc.h
    ReadMe.txt
)

target_compile_definitions(test_mikrobus_adc PRIVATE
    R7FA8D1BHECBD
    R7FA8M1
)

target_compile_options(test_mikrobus_adc PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
)

target_include_directories(test_mikrobus_adc
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_options(test_mikrobus_adc PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wl,--gc-sections
)

target_link_libraries(test_mikrobus_adc PUBLIC
    MikroC.Core
    MikroSDK.Conversions
    MikroSDK.Driver.ADC
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
