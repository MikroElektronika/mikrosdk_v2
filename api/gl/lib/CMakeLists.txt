## ./api/gl/lib/CMakeLists.txt
mikrosdk_add_library(lib_gl MikroSDK.GraphicLibrary
   src/gl.c
   src/gl_text.c
   src/gl_shapes.c
   src/gl_image.c

   include/gl_colors.h
   include/gl_image.h
   include/gl_shapes.h
   include/gl_text.h
   include/gl_types.h
   include/gl.h
   include/gl_image_format_handlers.h
)

target_link_libraries(lib_gl  PUBLIC
    MikroC.Core
    MikroSDK.GenericPointer
)

target_include_directories(lib_gl
PRIVATE
    include
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/api/gl>
)

mikrosdk_install(MikroSDK.GraphicLibrary)
install_headers(${CMAKE_INSTALL_PREFIX}/include/api/gl MikroSDK.GraphicLibrary include/gl.h include/gl_colors.h include/gl_image.h include/gl_shapes.h include/gl_text.h include/gl_types.h)


include(mikroeUtils)
math_check_target(lib_gl)
