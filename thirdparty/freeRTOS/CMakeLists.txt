set (ADDITIONAL_FILES "")
if (${MCU_NAME} MATCHES "(^STM32F10[137](.+)$)")
    set(HEADERS_INST "GCC/ARM_CM3")
elseif(${MCU_NAME} MATCHES "(^STM32F7(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM7/r0p1")
elseif(${MCU_NAME} MATCHES "(^STM32F2(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM3")
elseif(${MCU_NAME} MATCHES "(^STM32F405(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM4F")
elseif(${MCU_NAME} MATCHES "(^STM32F429(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM4F")
elseif(${MCU_NAME} MATCHES "(^STM32F373(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM4F")
elseif(${MCU_NAME} MATCHES "(^STM32F301(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM4F")
elseif(${MCU_NAME} MATCHES "(^STM32L(.+)$)")
    set(HEADERS_INST "GCC/ARM_CM0")
    list(APPEND ADDITIONAL_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}/portasm.c" "${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}/portasm.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}/mpu_wrappers_v2_asm.c")
endif()

mikrosdk_add_library(lib_freeRTOS MikroSDK.FreeRTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FreeRTOSConfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/atomic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/croutine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/deprecated_definitions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/event_groups.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FreeRTOS.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/message_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_prototypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_syscall_numbers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_wrappers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newlib-freertos.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/picolibc-freertos.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/portable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/projdefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/queue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semphr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stack_macros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StackMacros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stream_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/task.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/timers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}/portmacro.h
    ${ADDITIONAL_FILES}
)

target_link_libraries(lib_freeRTOS PUBLIC
    MikroC.Core
)

target_include_directories(lib_freeRTOS
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/portable
        ${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}
        ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable/${HEADERS_INST}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang>

        $<INSTALL_INTERFACE:include/thirdparty/freeRTOS>
)

mikrosdk_install(MikroSDK.FreeRTOS)
install_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/freeRTOS MikroSDK.FreeRTOS /include/FreeRTOS.h /include/FreeRTOSConfig.h /portable/${HEADERS_INST}/portmacro.h  ) 