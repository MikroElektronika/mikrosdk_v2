## ./platform/ring/lib/CMakeLists.txt
mikrosdk_add_library(lib_ring MikroSDK.RingBuffer
    src/ring.c
    include/ring.h
)

target_link_libraries(lib_ring 
    PUBLIC
        MikroC.Core
)

target_include_directories(lib_ring
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(MikroSDK.RingBuffer)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.RingBuffer include/ring.h)
