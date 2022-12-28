## ./tests/mikrobus/adc/CMakeLists.txt
add_executable(test_mikrobus_adc
    src/main.c
    inc/mikrobus_adc.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_adc
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_adc PUBLIC
    MikroC.Core
    MikroSDK.Driver.ADC
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
    MikroSDK.Conversions
)
