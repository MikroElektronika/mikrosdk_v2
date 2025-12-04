# thirdparty/FreeRTOS/CMakeLists.txt

# FreeRTOS Kernel Root in this folder
set(FREERTOS_KERNEL_ROOT ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)

if( "${MCU_NAME}" MATCHES "^STM32F4(.+)$" )
    set(FREERTOS_PORT_COMPILER GCC)
    set(FREERTOS_PORT_ARCH     ARM_CM4F)
else()
    message(FATAL_ERROR
        "FreeRTOS: Unsupported TOOLCHAIN_ID='${TOOLCHAIN_ID}' or MCU_NAME='${MCU_NAME}'. "
        "Add proper mapping in thirdparty/FreeRTOS/CMakeLists.txt")
endif()


set(FREERTOS_PORT_DIR
    ${FREERTOS_KERNEL_ROOT}/portable/${FREERTOS_PORT_COMPILER}/${FREERTOS_PORT_ARCH}
)

# Heap implementation 
set(FREERTOS_MEMMANG_SOURCE
    ${FREERTOS_KERNEL_ROOT}/portable/MemMang/heap_4.c
)

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

# Include paths:
#  - FreeRTOS-Kernel/include
#  - portable/GCC/ARM_CM4F
#  - common SDK include
#  - FreeRTOSConfig.h for STM32F429ZI
target_include_directories(MikroSDK.FreeRTOSKernel PUBLIC
    ${FREERTOS_KERNEL_ROOT}/include
    ${FREERTOS_PORT_DIR}
    ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include
    ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include/FreeRTOSConfig/STM32/STM32F429ZI
)
