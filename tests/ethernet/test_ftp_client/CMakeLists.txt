## ./tests/ethernet/test_ftp_client/CMakeLists.txt
add_executable(test_ethernet_ftp_client
    main.c
    ../systick.h
)

target_link_libraries(test_ethernet_ftp_client PUBLIC
    MikroC.Core
    MikroSDK.Log
    MikroSDK.Board
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Ethernet.CycloneTCP
)

## Include search paths.
target_include_directories(test_ethernet_ftp_client
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

add_compile_definitions(
    "MCU_NAME_CMAKE=\"${MCU_NAME}\""
)
