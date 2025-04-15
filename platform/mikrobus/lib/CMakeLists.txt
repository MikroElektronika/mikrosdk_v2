## ./platform/mikrobus/lib/CMakeLists.txt
mikrosdk_add_interface_library(lib_mikrobus MikroSDK.MikroBus
    include/mikrobus.h
    include/mikrobus_id.h
)

target_include_directories(lib_mikrobus
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/bsp/mikrobus>
)

mikrosdk_install(MikroSDK.MikroBus)
install_headers(${CMAKE_INSTALL_PREFIX}/include/bsp/mikrobus MikroSDK.MikroBus include/mikrobus.h include/mikrobus_id.h)
