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
# function(rtos_freertos_get_config_dir out_config_dir)
#     set(_config_root ${CMAKE_SOURCE_DIR}/middleware/freertos/include/FreeRTOSConfig)

#     if("${MCU_NAME}" MATCHES "^STM32(.+)$")
#         set(_dir ${_config_root}/STM32/${MCU_NAME})
#     elseif("${MCU_NAME}" MATCHES "^R7F(.+)$")
#         set(_dir ${_config_root}/RENESAS/${MCU_NAME})
#     else()
#         message(STATUS
#             "FreeRTOS: No FreeRTOSConfig mapping for MCU_NAME='${MCU_NAME}'. "
#             "Expected file at ${_config_root}/<ARCH>/${MCU_NAME}/FreeRTOSConfig.h"
#         )
#         set(_dir ${_config_root}/UNKNOWN/${MCU_NAME})
#     endif()

#     if(NOT EXISTS "${_dir}/FreeRTOSConfig.h")
#         message(STATUS
#             "FreeRTOS: FreeRTOSConfig.h not found for MCU '${MCU_NAME}' in path: "
#             "${_dir}/FreeRTOSConfig.h"
#         )
#     endif()

#     set(${out_config_dir} ${_dir} PARENT_SCOPE)
# endfunction()

#############################################################################
## FreeRTOS: resolve FreeRTOSConfig directory (GENERATED)
#############################################################################
function(rtos_freertos_get_config_dir out_config_dir)
    # One static include directory for all MCUs (generated file differs)
    set(_gen_dir ${CMAKE_BINARY_DIR}/generated/freertos)

    # Generate FreeRTOSConfig.h into _gen_dir
    rtos_freertos_generate_config("${_gen_dir}" "FreeRTOSConfig.h")

    # Return generated directory
    set(${out_config_dir} ${_gen_dir} PARENT_SCOPE)
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

#############################################################################
## FreeRTOS: generate FreeRTOSConfig.h
#############################################################################
macro(rtos_freertos_generate_config fileDestination fileName)
    # Detect arch (to decide whether to emit Cortex-M handler mappings)
    rtos_freertos_get_port_arch(_port_arch)

    # ---------------------------------------------------------------------
    # Decide configPRIO_BITS
    # current rules:
    # - STM32G0..., STM32L0..., R7FA2E3... => 2
    # - R7FA4M3... => 3
    # - default => 4
    # Plus a safe fallback based on CORE_NAME for M0/M23.
    # ---------------------------------------------------------------------
    set(_prio_bits 4)

    if(MCU_NAME MATCHES "^STM32G0.+$" OR MCU_NAME MATCHES "^STM32L0.+$" OR MCU_NAME MATCHES "^R7FA2E3.+$")
        set(_prio_bits 2)
    elseif(MCU_NAME MATCHES "^R7FA4M3.+$")
        set(_prio_bits 3)
    elseif(CORE_NAME MATCHES "M0")
        set(_prio_bits 2)
    elseif(CORE_NAME STREQUAL "M23")
        set(_prio_bits 2)
    endif()

    # ---------------------------------------------------------------------
    # Decide interrupt priority constants from prio bits
    # lowest = (2^prio_bits - 1)
    # max syscall: keep your established defaults by prio-bits
    #   2 bits  -> 1
    #   3 bits  -> 2
    #   4 bits  -> 5
    # ---------------------------------------------------------------------
    math(EXPR _lowest_irq_prio "(1 << ${_prio_bits}) - 1")

    if(_prio_bits EQUAL 2)
        set(_max_syscall_irq_prio 1)
    elseif(_prio_bits EQUAL 3)
        set(_max_syscall_irq_prio 2)
    else()
        set(_max_syscall_irq_prio 5)
    endif()

    # ---------------------------------------------------------------------
    # Decide heap size from MCU_RAM (bytes)
    # ---------------------------------------------------------------------
    if(NOT MCU_RAM)
        message(FATAL_ERROR "FreeRTOS: MCU_RAM is not defined for ${MCU_NAME}")
    endif()

    set(_heap_bytes 8192)
    if(MCU_RAM LESS 24576)          # < 24KB
        set(_heap_bytes 4096)
    elseif(MCU_RAM LESS 49152)      # < 48KB
        set(_heap_bytes 8192)
    elseif(MCU_RAM LESS 98304)      # < 96KB
        set(_heap_bytes 16384)
    elseif(MCU_RAM LESS 131072)     # < 128KB
        set(_heap_bytes 24576)
    else()
        set(_heap_bytes 32768)
    endif()

    # Minimal stack size in *words* (typical Cortex-M ports use 32-bit words).
    # Keep it proportional and conservative;
    set(_min_stack_words 256)
    if(_heap_bytes LESS_EQUAL 4096)
        set(_min_stack_words 128)
    elseif(_heap_bytes LESS_EQUAL 8192)
        set(_min_stack_words 192)
    elseif(_heap_bytes LESS_EQUAL 16384)
        set(_min_stack_words 256)
    elseif(_heap_bytes LESS_EQUAL 24576)
        set(_min_stack_words 320)
    else()
        set(_min_stack_words 384)
    endif()

    # ---------------------------------------------------------------------
    # Build MACRO_LIST to inject into template
    # ---------------------------------------------------------------------
    set(MACRO_LIST "")

    # CPU clock: keep it generic and MCU-driven (preferred for SDK).
    # If your environment defines FOSC_KHZ_VALUE (as used by systick.h), use it.
    # Otherwise, fall back to SystemCoreClock.
# CPU clock: prefer FOSC_KHZ_VALUE; otherwise use SystemCoreClock on Cortex-M
string(APPEND MACRO_LIST
"#ifndef configCPU_CLOCK_HZ\n"
"  #if defined(FOSC_KHZ_VALUE)\n"
"    #define configCPU_CLOCK_HZ ( ( uint32_t ) ( (uint32_t)(FOSC_KHZ_VALUE) * 1000UL ) )\n"
"  #else\n"
"    #error \"configCPU_CLOCK_HZ: FOSC_KHZ_VALUE is not defined (include <core_header.h> and ensure core is reachable)\"\n"
"  #endif\n"
"#endif\n"
)

    string(APPEND MACRO_LIST "#define configTOTAL_HEAP_SIZE ( ( size_t ) ${_heap_bytes} )\n")
    string(APPEND MACRO_LIST "#define configMINIMAL_STACK_SIZE ( ${_min_stack_words} )\n")

    string(APPEND MACRO_LIST "#define configPRIO_BITS ( ${_prio_bits} )\n")
    string(APPEND MACRO_LIST "#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY ( ${_lowest_irq_prio} )\n")
    string(APPEND MACRO_LIST "#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY ( ${_max_syscall_irq_prio} )\n")

    # Allocation model (since you use heap_4.c in rtosUtils.cmake)
    string(APPEND MACRO_LIST "#define configSUPPORT_DYNAMIC_ALLOCATION 1\n")
    string(APPEND MACRO_LIST "#define configSUPPORT_STATIC_ALLOCATION  0\n")

    # Cortex-M handler mappings only for ARM_CM* ports
    if(_port_arch MATCHES "^ARM_CM")
        string(APPEND MACRO_LIST "#define vPortSVCHandler      SVC_Handler\n")
        string(APPEND MACRO_LIST "#define xPortPendSVHandler   PendSV_Handler\n")
    endif()

    # ---------------------------------------------------------------------
    # Generate output file
    # ---------------------------------------------------------------------
    file(MAKE_DIRECTORY "${fileDestination}")

    configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/InstallHeaderFreeRTOSConfig.cmake.in
        ${fileDestination}/${fileName}
        @ONLY
    )
endmacro()

