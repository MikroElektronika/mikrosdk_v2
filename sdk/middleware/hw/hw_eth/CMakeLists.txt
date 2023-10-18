## ./middleware/hw/hw_eth/CMakeLists.txt
eth_get_files(init_file "HW")

mikrosdk_add_interface_library(lib_hw_eth MikroSDK.Ethernet.HW
    include/${init_file}/hw_eth.h
)

target_link_libraries(lib_hw_eth INTERFACE
    MikroC.Core
    MikroSDK.Ethernet.CycloneTCP.Config
)

target_compile_definitions(lib_hw_eth INTERFACE
    ${_MSDK_MCU_CARD_NAME_}
)

target_include_directories(lib_hw_eth
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${init_file}>
        $<INSTALL_INTERFACE:include/middleware/eth>
)

mikrosdk_install(MikroSDK.Ethernet.HW)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/eth MikroSDK.Ethernet.HW include/${init_file}/hw_eth.h)
