#############################################################################
## Disable MCUs without enough FLASH and/or RAM memory for FreeRTOS
#############################################################################
function(check_rtos_requirements check_rtos)
    set(${check_rtos} "false" PARENT_SCOPE)

    # TODO: tune thresholds
    set(check_flash 65536)   # 64KB
    set(check_ram   16384)   # 16KB

    if (NOT MCU_FLASH)
        message(FATAL_ERROR ": MCU_FLASH not added to database for ${MCU_NAME}.")
    endif()
    if (NOT MCU_RAM)
        message(FATAL_ERROR ": MCU_RAM not added to database for ${MCU_NAME}.")
    endif()

    if (${MCU_FLASH} GREATER_EQUAL check_flash)
        if (${MCU_RAM} GREATER_EQUAL check_ram)
            set(${check_rtos} "true" PARENT_SCOPE)
        endif()
    endif()
endfunction()

#############################################################################
## FreeRTOS: resolve kernel root path
#############################################################################
function(rtos_freertos_get_kernel_root out_kernel_root)
    set(${out_kernel_root}
        ${CMAKE_SOURCE_DIR}/thirdparty/rtos/freertos/freertos-kernel
        PARENT_SCOPE
    )
endfunction()

#############################################################################
## FreeRTOS: resolve compiler folder for portable/<compiler>
#############################################################################
function(rtos_freertos_get_port_compiler out_port_compiler)
    if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
        if(${TOOLCHAIN_ID} MATCHES "mchp_xc")
            set(${out_port_compiler} "MPLAB" PARENT_SCOPE)
        else()
            set(${out_port_compiler} "GCC" PARENT_SCOPE)
        endif()
    else()
        message(FATAL_ERROR "FreeRTOS: Unsupported TOOLCHAIN_LANGUAGE='${TOOLCHAIN_LANGUAGE}', TOOLCHAIN_ID='${TOOLCHAIN_ID}'")
    endif()
endfunction()

#############################################################################
## FreeRTOS: resolve arch folder for portable/<arch>
#############################################################################
function(rtos_freertos_get_port_arch out_port_arch)
    if(${CORE_NAME} MATCHES "M0")
        set(${out_port_arch} "ARM_CM0" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "M3")
        set(${out_port_arch} "ARM_CM3" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "M23")
        set(${out_port_arch} "ARM_CM23_NTZ/non_secure" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "M33EF")
        set(${out_port_arch} "ARM_CM33_NTZ/non_secure" PARENT_SCOPE)
    elseif(${CORE_NAME} MATCHES "M4")
        set(${out_port_arch} "ARM_CM4F" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "M7")
        set(${out_port_arch} "ARM_CM7/r0p1" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "M85")
        set(${out_port_arch} "ARM_CM85_NTZ" PARENT_SCOPE)
    elseif(${CORE_NAME} STREQUAL "RISCV")
        set(${out_port_arch} "RISC-V" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "FreeRTOS: Unsupported CORE_NAME='${CORE_NAME}'")
    endif()
endfunction()

#############################################################################
## FreeRTOS: resolve full port directory (portable/<compiler>/<arch>)
#############################################################################
function(rtos_freertos_get_port_dir out_port_dir)
    rtos_freertos_get_kernel_root(_kernel_root)
    rtos_freertos_get_port_compiler(_compiler)
    rtos_freertos_get_port_arch(_arch)

    set(${out_port_dir}
        ${_kernel_root}/portable/${_compiler}/${_arch}
        PARENT_SCOPE
    )
endfunction()

#############################################################################
## FreeRTOS: resolve heap source
#############################################################################
function(rtos_freertos_get_heap_source out_heap_source)
    rtos_freertos_get_kernel_root(_kernel_root)
    set(${out_heap_source}
        ${_kernel_root}/portable/MemMang/heap_4.c
        PARENT_SCOPE
    )
endfunction()

#############################################################################
## FreeRTOS: resolve FreeRTOSConfig directory (STATIC mapping for now)
## NOTE:step 3 will replace this with generated config.
#############################################################################
function(rtos_freertos_get_config_dir out_config_dir)
    set(_config_root ${CMAKE_SOURCE_DIR}/middleware/freertos/include/FreeRTOSConfig)

    if("${MCU_NAME}" MATCHES "^STM32(.+)$")
        set(_dir ${_config_root}/STM32/${MCU_NAME})
    elseif("${MCU_NAME}" MATCHES "^R7F(.+)$")
        set(_dir ${_config_root}/RENESAS/${MCU_NAME})
    else()
        message(STATUS
            "FreeRTOS: No FreeRTOSConfig mapping for MCU_NAME='${MCU_NAME}'. "
            "Expected file at ${_config_root}/<ARCH>/${MCU_NAME}/FreeRTOSConfig.h"
        )
        set(_dir ${_config_root}/UNKNOWN/${MCU_NAME})
    endif()

    if(NOT EXISTS "${_dir}/FreeRTOSConfig.h")
        message(STATUS
            "FreeRTOS: FreeRTOSConfig.h not found for MCU '${MCU_NAME}' in path: "
            "${_dir}/FreeRTOSConfig.h"
        )
    endif()

    set(${out_config_dir} ${_dir} PARENT_SCOPE)
endfunction()

#############################################################################
## FreeRTOS: kernel sources list
#############################################################################
function(rtos_freertos_get_kernel_sources out_sources)
    rtos_freertos_get_kernel_root(_kernel_root)
    set(_list "")
    list(APPEND _list
        ${_kernel_root}/event_groups.c
        ${_kernel_root}/list.c
        ${_kernel_root}/queue.c
        ${_kernel_root}/stream_buffer.c
        ${_kernel_root}/tasks.c
        ${_kernel_root}/timers.c
    )
    set(${out_sources} ${_list} PARENT_SCOPE)
endfunction()

#############################################################################
## FreeRTOS: port sources list (includes optional portasm.c)
#############################################################################
function(rtos_freertos_get_port_sources out_sources)
    rtos_freertos_get_port_dir(_port_dir)
    set(_list "")
    list(APPEND _list
        ${_port_dir}/port.c
    )

    if(EXISTS "${_port_dir}/portasm.c")
        list(APPEND _list ${_port_dir}/portasm.c)
    endif()

    set(${out_sources} ${_list} PARENT_SCOPE)
endfunction()
