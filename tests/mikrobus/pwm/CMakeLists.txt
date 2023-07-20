## ./tests/mikrobus/pwm/CMakeLists.txt
add_executable(test_mikrobus_pwm
    src/main.c
    inc/mikrobus_pwm.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_pwm
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_pwm PUBLIC
    MikroC.Core
    MikroSDK.Driver.PWM
    MikroSDK.Driver.UART
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
)
