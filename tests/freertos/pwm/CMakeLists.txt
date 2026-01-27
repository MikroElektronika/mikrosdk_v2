## ./tests/freertos/pwm/CMakeLists.txt

# Default util for ARM targets
set(TEST_UTIL_SOURCE ${CMAKE_CURRENT_LIST_DIR}/util_arm.c)

# PIC32 ports use Timer1 tick setup
if("${MCU_NAME}" MATCHES "^PIC32(MX|MZ).+$")
    set(TEST_UTIL_SOURCE ${CMAKE_CURRENT_LIST_DIR}/util_pic32.c)
endif()

add_executable(test_default_freertos_pwm
    main.c
    callbacks.c
    ${TEST_UTIL_SOURCE}
)

target_link_libraries(test_default_freertos_pwm PUBLIC
    MikroC.Core
    lib_freertos     
    MikroSDK.Board              
    MikroSDK.Driver.GPIO.Out    
    MikroSDK.Driver.GPIO.In      
    MikroSDK.Driver.PWM     
)
