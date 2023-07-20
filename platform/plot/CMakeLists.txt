## ./platform/plot/CMakeLists.txt
mikrosdk_add_interface_library(lib_plot MikroSDK.Plot
    include/plot.h
)

target_link_libraries(lib_plot INTERFACE
    MikroSDK.GenericPointer
)

target_include_directories(lib_plot
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(MikroSDK.Plot)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Plot include/plot.h)
