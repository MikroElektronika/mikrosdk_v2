# thirdparty/rtos/freertos/CMakeLists.txt

# FreeRTOS Kernel Root in this folder
set(FREERTOS_KERNEL_ROOT ${CMAKE_CURRENT_LIST_DIR}/freertos-kernel)

if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    if(${TOOLCHAIN_ID} MATCHES "mchp_xc")
        set(FREERTOS_PORT_COMPILER "MPLAB")
    else()
        set(FREERTOS_PORT_COMPILER "GCC")
    endif()
else()
    message(FATAL_ERROR "FreeRTOS: Unsupported TOOLCHAIN_ID='${TOOLCHAIN_ID}'")
endif()

if(${CORE_NAME} MATCHES "M0")
    set(FREERTOS_PORT_ARCH "ARM_CM0")
elseif(${CORE_NAME} STREQUAL "M3")
    set(FREERTOS_PORT_ARCH "ARM_CM3")
elseif(${CORE_NAME} STREQUAL "M23")
    set(FREERTOS_PORT_ARCH "ARM_CM23_NTZ")
elseif(${CORE_NAME} STREQUAL "M33EF")
    set(FREERTOS_PORT_ARCH "ARM_CM33_NTZ")
elseif (${CORE_NAME} MATCHES "M4")
    set(FREERTOS_PORT_ARCH "ARM_CM4F")
elseif(${CORE_NAME} STREQUAL "M7")
    set(FREERTOS_PORT_ARCH "ARM_CM7/r0p1")
elseif(${CORE_NAME} STREQUAL "M85")
    set(FREERTOS_PORT_ARCH "ARM_CM85_NTZ")
elseif(${CORE_NAME} STREQUAL "RISCV")
    set(FREERTOS_PORT_ARCH "RISC-V")
else()
    message(FATAL_ERROR "FreeRTOS: Unsupported CORE_NAME='${CORE_NAME}'")
endif()

set(FREERTOS_PORT_DIR
    ${FREERTOS_KERNEL_ROOT}/portable/${FREERTOS_PORT_COMPILER}/${FREERTOS_PORT_ARCH}
)

set(FREERTOS_CONFIG_ROOT
    ${CMAKE_SOURCE_DIR}/middleware/freertos/include/FreeRTOSConfig
)

if("${MCU_NAME}" MATCHES "^STM32(.+)$")
    set(FREERTOS_CONFIG_DIR ${FREERTOS_CONFIG_ROOT}/STM32/${MCU_NAME})
else()
    message(STATUS
        "FreeRTOS: No FreeRTOSConfig mapping for MCU_NAME='${MCU_NAME}'. "
        "Expected file at ${FREERTOS_CONFIG_ROOT}/<ARCH>/${MCU_NAME>/FreeRTOSConfig.h")
endif()

if(NOT EXISTS "${FREERTOS_CONFIG_DIR}/FreeRTOSConfig.h")
    message(STATUS
        "FreeRTOS: FreeRTOSConfig.h not found for MCU '${MCU_NAME}' in path: "
        "${FREERTOS_CONFIG_DIR}/FreeRTOSConfig.h")
endif()

# Heap implementation
set(FREERTOS_MEMMANG_SOURCE
    ${FREERTOS_KERNEL_ROOT}/portable/MemMang/heap_4.c
)

if(EXISTS "${FREERTOS_PORT_DIR}/portasm.c")
    add_library(lib_freertos STATIC
        ${FREERTOS_KERNEL_ROOT}/event_groups.c
        ${FREERTOS_KERNEL_ROOT}/list.c
        ${FREERTOS_KERNEL_ROOT}/queue.c
        ${FREERTOS_KERNEL_ROOT}/stream_buffer.c
        ${FREERTOS_KERNEL_ROOT}/tasks.c
        ${FREERTOS_KERNEL_ROOT}/timers.c
        ${FREERTOS_PORT_DIR}/port.c
        ${FREERTOS_PORT_DIR}/portasm.c
        ${FREERTOS_MEMMANG_SOURCE}
    )
else()
    add_library(lib_freertos STATIC
    ${FREERTOS_KERNEL_ROOT}/event_groups.c
    ${FREERTOS_KERNEL_ROOT}/list.c
    ${FREERTOS_KERNEL_ROOT}/queue.c
    ${FREERTOS_KERNEL_ROOT}/stream_buffer.c
    ${FREERTOS_KERNEL_ROOT}/tasks.c
    ${FREERTOS_KERNEL_ROOT}/timers.c
    ${FREERTOS_PORT_DIR}/port.c
    ${FREERTOS_MEMMANG_SOURCE}
)
endif()

target_include_directories(lib_freertos PUBLIC
    ${FREERTOS_KERNEL_ROOT}/include
    ${FREERTOS_PORT_DIR}
    ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include
    ${FREERTOS_CONFIG_DIR}
)
