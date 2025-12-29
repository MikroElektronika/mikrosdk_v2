# thirdparty/FreeRTOS/CMakeLists.txt

# FreeRTOS Kernel Root in this folder
set(FREERTOS_KERNEL_ROOT ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)

if( "${MCU_NAME}" MATCHES "^STM32F4(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM4F)
elseif( "${MCU_NAME}" MATCHES "^STM32F1(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM3)
elseif( "${MCU_NAME}" MATCHES "^STM32F7(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     "ARM_CM7/r0p1")
elseif("${MCU_NAME}" MATCHES "^STM32F2.+$")
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM3)
elseif( "${MCU_NAME}" MATCHES "^STM32F3(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM4F)    
elseif( "${MCU_NAME}" MATCHES "^STM32L4(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM4F)   
elseif( "${MCU_NAME}" MATCHES "^STM32L0(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM0)
elseif( "${MCU_NAME}" MATCHES "^STM32F0.+$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM0)
elseif( "${MCU_NAME}" MATCHES "^STM32L1(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM3)
elseif( "${MCU_NAME}" MATCHES "^STM32H7(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     "ARM_CM7/r0p1")
elseif( "${MCU_NAME}" MATCHES "^STM32G0(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM0)
else()
    message(FATAL_ERROR
        "FreeRTOS: Unsupported TOOLCHAIN_ID='${TOOLCHAIN_ID}' or MCU_NAME='${MCU_NAME}'. "
        "Add proper mapping in thirdparty/FreeRTOS/CMakeLists.txt")
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
    add_library(MikroSDK.FreeRTOSKernel STATIC
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
    add_library(MikroSDK.FreeRTOSKernel STATIC
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

# add_library(MikroSDK.FreeRTOSKernel STATIC
#     ${FREERTOS_KERNEL_ROOT}/event_groups.c
#     ${FREERTOS_KERNEL_ROOT}/list.c
#     ${FREERTOS_KERNEL_ROOT}/queue.c
#     ${FREERTOS_KERNEL_ROOT}/stream_buffer.c
#     ${FREERTOS_KERNEL_ROOT}/tasks.c
#     ${FREERTOS_KERNEL_ROOT}/timers.c
#     ${FREERTOS_PORT_DIR}/port.c
#     ${FREERTOS_MEMMANG_SOURCE}
# )

# Include paths:
#  - FreeRTOS-Kernel/include
#  - portable/GCC/ARM_CM4F
#  - common SDK include
#  - FreeRTOSConfig/<ARCH>/<MCU_NAME>
target_include_directories(MikroSDK.FreeRTOSKernel PUBLIC
    ${FREERTOS_KERNEL_ROOT}/include
    ${FREERTOS_PORT_DIR}
    ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include
    ${FREERTOS_CONFIG_DIR}
)
