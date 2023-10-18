## ./platform/mikrosdk_version/CMakeLists.txt
mikrosdk_add_interface_library(lib_mikrosdk_version MikroSDK.mikroSDKVersion
    include/mikrosdk_version.h
)
target_include_directories(lib_mikrosdk_version
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(MikroSDK.mikroSDKVersion)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.mikroSDKVersion include/mikrosdk_version.h)
