## ./components/ips/lib/CMakeLists.txt
mikrosdk_add_library(lib_ips Components.IpsDisplay
    src/ips.c

    include/ips.h
)

target_link_libraries(lib_ips
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.SPI.Master
        MikroSDK.ST7789
        MikroSDK.GraphicLibrary
)
target_compile_definitions(lib_ips
    PUBLIC
        "TFT_MAP_PINOUTS=IPS_MAP_PINOUTS"
)

target_include_directories(lib_ips
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/components/ips>
)

mikrosdk_install(Components.IpsDisplay)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/ips Components.IpsDisplay include/ips.h)
