## ./middleware/hw/hw_usb/CMakeLists.txt
usb_set_init_sequence(init_file)

mikrosdk_add_interface_library(lib_usb_hw MikroSDK.USB.HW
    include/${init_file}/usb_hw.h
)

target_link_libraries(lib_usb_hw INTERFACE
    MikroC.Core
)

target_compile_definitions(lib_usb_hw INTERFACE
    ${_MSDK_MCU_CARD_NAME_}
)

target_include_directories(lib_usb_hw
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${init_file}>
        $<INSTALL_INTERFACE:include/middleware/usb>
)

mikrosdk_install(MikroSDK.USB.HW)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/usb MikroSDK.USB.HW include/${init_file}/usb_hw.h)
