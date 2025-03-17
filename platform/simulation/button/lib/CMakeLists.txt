## ./platform/simulation/button/lib/CMakeLists.txt
mikrosdk_add_library(lib_simulation_button MikroSDK.Simulation.Button
    src/simulation_button.c
    include/simulation_button.h
)

target_link_libraries(lib_simulation_button
    PUBLIC
        MikroC.Core
        MikroSDK.Hal.GPIO
)

target_include_directories(lib_simulation_button
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(MikroSDK.Simulation.Button)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Simulation.Button include/simulation_button.h)
