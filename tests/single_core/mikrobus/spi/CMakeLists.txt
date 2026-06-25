## ./tests/mikrobus/spi/CMakeLists.txt
add_executable(test_mikrobus_spi
    src/main.c
    inc/mikrobus_spi.h
    ReadMe.txt
)

target_include_directories(test_mikrobus_spi
PRIVATE
    /inc
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

target_link_libraries(test_mikrobus_spi PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.SPI.Master
)
