mikrosdk_add_interface_library(lib_generic_pointer MikroSDK.GenericPointer
   include/generic_pointer.h
)

target_include_directories(lib_generic_pointer
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/board>
)

mikrosdk_install(MikroSDK.GenericPointer)

install(
    FILES
        include/generic_pointer.h
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/board
)
