add_executable(test_mikrobus_i2c
    src/main.c
    inc/mikrobus_i2c.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_i2c
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_i2c PUBLIC
    MikroC.Core
    MikroSDK.Driver.I2C.Master
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.In
    MikroSDK.Board
)
