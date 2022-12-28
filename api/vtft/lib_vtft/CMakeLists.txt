## ./api/vtft/lib_vtft/CMakeLists.txt
mikrosdk_add_library(lib_vtft MikroSDK.VisualTft
    src/vtft.c
    src/vtft_drawing.c
    src/vtft_touch.c

    include/vtft.h
    include/vtft_drawing.h
    include/vtft_types.h
)

target_link_libraries(lib_vtft  PUBLIC
    MikroC.Core
    MikroSDK.TouchPanel
    MikroSDK.Conversions
    MikroSDK.GraphicLibrary
    MikroSDK.GenericPointer
)

target_include_directories(lib_vtft
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/vtft>
)

mikrosdk_install(MikroSDK.VisualTft)
install_headers(${CMAKE_INSTALL_PREFIX}/include/vtft MikroSDK.VisualTft include/vtft_types.h include/vtft.h)
