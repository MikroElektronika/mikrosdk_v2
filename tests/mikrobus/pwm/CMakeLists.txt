add_executable(test_mikrobus_pwm
    src/main.c
    inc/mikrobus_pwm.h
    ReadMe.txt
)

target_compile_definitions(test_mikrobus_pwm PRIVATE
    R7FA8D1BHECBD
    R7FA8M1
)

target_compile_options(test_mikrobus_pwm PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
)

target_link_options(test_mikrobus_pwm PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wl,--gc-sections
)

target_include_directories(test_mikrobus_pwm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_pwm PUBLIC
    MikroC.Core
    MikroSDK.Driver.PWM
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.In
    MikroSDK.Board
)