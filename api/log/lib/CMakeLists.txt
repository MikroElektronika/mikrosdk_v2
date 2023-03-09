## ./api/log/lib/CMakeLists.txt
set(file_list "")
set(module_list "")
set(module_log_path "")
mikrosdk_get_log_libs(module_list file_list module_log_path)

mikrosdk_add_library(lib_log MikroSDK.Log
    ${file_list}
)

target_link_libraries(lib_log  PUBLIC
    ${module_list}
)

target_include_directories(lib_log
PRIVATE
    include/${module_log_path}
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${module_log_path}>
    $<INSTALL_INTERFACE:include/api/log/${module_log_path}>
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

set(compiler_path "")
mikrosdk_set_compiler_path(compiler_path)

mikrosdk_install(MikroSDK.Log)
install_headers(${CMAKE_INSTALL_PREFIX}/include/api/log/${module_log_path} MikroSDK.Log include/${module_log_path}/log.h ${compiler_path}/include/cstdio.h)
