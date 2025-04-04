set (ADDITIONAL_FILES "")
set(MEM_SCHEME "heap_4")
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
    endif()
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/freeRTOS.cmake)
freertos_get_source_files(SOURCE_FILES)
freertos_get_header_files(HEADER_FILES)
message("Source files list: ${SOURCE_FILES}")
message("Header files list: ${HEADER_FILES}")
mikrosdk_add_library(lib_freeRTOS MikroSDK.FreeRTOS
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/${MEM_SCHEME}.c
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