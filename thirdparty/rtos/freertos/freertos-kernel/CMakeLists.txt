cmake_minimum_required(VERSION 3.17)

# rtosUtils.cmake is included via cmake/utils.cmake, so its functions are available.
include(${CMAKE_SOURCE_DIR}/cmake/rtosUtils.cmake)

# Gather sources via helpers
rtos_freertos_get_kernel_sources(FREERTOS_KERNEL_SOURCES)
message(STATUS "FREERTOS_KERNEL_SOURCES='${FREERTOS_KERNEL_SOURCES}'")
rtos_freertos_get_port_sources(FREERTOS_PORT_SOURCES)
message(STATUS "FREERTOS_PORT_SOURCES='${FREERTOS_PORT_SOURCES}'")
rtos_freertos_get_heap_source(FREERTOS_HEAP_SOURCE)
message(STATUS "FREERTOS_HEAP_SOURCE='${FREERTOS_HEAP_SOURCE}'")
rtos_freertos_get_port_dir(FREERTOS_PORT_DIR)
rtos_freertos_get_kernel_root(FREERTOS_KERNEL_ROOT)
rtos_freertos_get_config_dir(FREERTOS_CONFIG_DIR)

# Create library (mentor naming: lib_freertos)
add_library(lib_freertos STATIC
    ${FREERTOS_KERNEL_SOURCES}
    ${FREERTOS_PORT_SOURCES}
    ${FREERTOS_HEAP_SOURCE}
)

# Include dirs
target_include_directories(lib_freertos PUBLIC
    ${FREERTOS_KERNEL_ROOT}/include
    ${FREERTOS_PORT_DIR}
    ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include
    ${FREERTOS_CONFIG_DIR}
)

# ---------------------------------------------------------------------------
# renesas has SCB already defined in core files while STM32 does not 
# ---------------------------------------------------------------------------

if("${MCU_NAME}" MATCHES "^STM32.+$")
     target_compile_definitions(lib_freertos PUBLIC MSDK_SYSTICK_DEFINE_CORE_TYPES)
endif()

# ---------------------------------------------------------------------------
# SCB->SHP (STM32) vs SCB->SHPR (Renesas RA)
# ---------------------------------------------------------------------------

if(MCU_NAME MATCHES "^R7F.+")
    # this macro is used in systick.h to use SCB->SHPR[] instead of SCB->SHP[]
    target_compile_definitions(lib_freertos PUBLIC MSDK_SYSTICK_USE_SHPR)
endif()

