## ./api/log/lib/CMakeLists.txt
mikrosdk_add_library(lib_log MikroSDK.Log
    src/log.c
    src/log_printf_implementation.c
    src/log_printf_implementation.h
    include/log.h
)

target_link_libraries(lib_log  PUBLIC
    MikroC.Core
    MikroSDK.Driver.UART
    MikroSDK.GenericPointer
)

target_include_directories(lib_log
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/api/log>
)
set(TARGET_DEFINES_LIST "")

if (${MEMAKE_TOOLCHAIN_ID} MATCHES "mikrocpic")
    list(APPEND TARGET_DEFINES_LIST PIC_MANTIS) ## Additional information
    list(APPEND TARGET_DEFINES_LIST __mantis_value__=24)
else()
    list(APPEND TARGET_DEFINES_LIST IEEE_MANTIS) ## Additional information
    list(APPEND TARGET_DEFINES_LIST __mantis_value__=23)
endif()

target_compile_definitions(lib_log
    PUBLIC
        ${TARGET_DEFINES_LIST}

)
get_target_property(compile_defs lib_log COMPILE_DEFINITIONS)

mikrosdk_install(MikroSDK.Log)
install_headers(${CMAKE_INSTALL_PREFIX}/include/api/log MikroSDK.Log include/log.h)
