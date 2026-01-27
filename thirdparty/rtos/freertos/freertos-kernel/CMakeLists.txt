cmake_minimum_required(VERSION 3.17)

set(KERNEL_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Gather sources via utility functions from rtosUtils.cmake
rtos_freertos_get_include_dirs(KERNEL_ROOT PORT_DIR)
rtos_freertos_get_sources(KERNEL_ROOT PORT_DIR FREERTOS_SOURCES)
rtos_freertos_get_config_dir(CONFIG_DIR)
rtos_freertos_get_mikrosdk_common_include_dir(MIKROSDK_COMMON_INCLUDE_DIR)

# Create library
add_library(lib_freertos STATIC
    ${FREERTOS_SOURCES}
)

target_link_libraries(lib_freertos PUBLIC
    MikroC.Core
)

# Include dirs
target_include_directories(lib_freertos PUBLIC
    ${KERNEL_ROOT}/include
    ${PORT_DIR}
    ${MIKROSDK_COMMON_INCLUDE_DIR}
    ${CONFIG_DIR}
)

get_rtos_compile_definitions(RTOS_COMPILE_DEFS)
target_compile_definitions(lib_freertos PUBLIC ${RTOS_COMPILE_DEFS})
