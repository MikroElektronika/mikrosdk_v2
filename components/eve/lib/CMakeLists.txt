## ./components/eve/lib/CMakeLists.txt
# EVE_CLICK -> MIKROBUS_POSITION_EVE (same rule NECTO uses to name the variable it passes).
display_mikrobus_selection(eve_mikrobus.h)

mikrosdk_add_library(lib_eve Components.EveDisplay
    src/eve.c

    include/eve.h
    ${CMAKE_BINARY_DIR}/generated/eve_mikrobus.h
)

target_link_libraries(lib_eve
    PUBLIC
        MikroC.Core
        MikroSDK.Driver.GPIO.Out
        MikroSDK.Driver.SPI.Master
        MikroSDK.MikroBus
        MikroSDK.Ft800
        MikroSDK.GraphicLibrary
)
target_compile_definitions(lib_eve
    PUBLIC
        "TFT_MAP_PINOUTS=EVE_MAP_PINOUTS"
)

target_include_directories(lib_eve
    PRIVATE
        include
        ${CMAKE_BINARY_DIR}/generated
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include/components/eve>
)

mikrosdk_install(Components.EveDisplay)
install_headers(${CMAKE_INSTALL_PREFIX}/include/components/eve Components.EveDisplay include/eve.h ${CMAKE_BINARY_DIR}/generated/eve_mikrobus.h)
