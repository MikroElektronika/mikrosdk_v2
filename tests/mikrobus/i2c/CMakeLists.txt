## ./tests/mikrobus/i2c/CMakeLists.txt
add_executable(test_mikrobus_i2c
    src/main.c
    inc/mikrobus_i2c.h
    ReadMe.txt
)

target_compile_definitions(test_mikrobus_i2c PRIVATE
    R7FA8D1BHECBD
    R7FA8M1
)

target_compile_options(test_mikrobus_i2c PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
)

target_link_options(test_mikrobus_i2c PRIVATE
    -mcpu=cortex-m85
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wl,--gc-sections
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
