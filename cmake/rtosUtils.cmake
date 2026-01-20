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
## FreeRTOS: resolve FreeRTOSConfig directory (GENERATED)
#############################################################################
function(rtos_freertos_get_config_dir out_config_dir)
    # One static include directory for all MCUs
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
    # - default => 4
    # - STM32 : CM0(G0,L0,F0)  => 2
    # - Renesas: CM23(R7FA2E3) => 2
    #            CM33(R7FA4M3) => 3
    # ---------------------------------------------------------------------
    # Default: Cortex-M3/M4/M7/M85
    set(_prio_bits 4)

    # Cortex-M0 / M23
    if(CORE_NAME MATCHES "M0" OR CORE_NAME STREQUAL "M23")
        set(_prio_bits 2)

    # Supported Cortex-M33 targets (Renesas RA4M3/RA6M3)
    elseif(CORE_NAME MATCHES "M33")
        set(_prio_bits 3)
    endif()

    # ---------------------------------------------------------------------
    # Decide interrupt priority constants from prio bits
    # lowest = (2^prio_bits - 1)
    # max syscall: keep established defaults by prio-bits
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

    set(_heap_bytes 8192)           # Default: 8KB
    if(MCU_RAM LESS 18432)          # 18 * 1024
        set(_heap_bytes 6144)       # 6 * 1024
    elseif(MCU_RAM LESS 24576)      # 24 * 1024
        set(_heap_bytes 8192)       # 8 * 1024
    elseif(MCU_RAM LESS 40960)      # 40 * 1024
        set(_heap_bytes 10240)      # 10 * 1024
    elseif(MCU_RAM LESS 73728)      # 72 * 1024
        set(_heap_bytes 12288)      # 12 * 1024
    elseif(MCU_RAM LESS 98304)      # 96 * 1024
        set(_heap_bytes 20480)      # 20 * 1024
    elseif(MCU_RAM LESS 163840)     # 160 * 1024
        set(_heap_bytes 24576)      # 24 * 1024
    elseif(MCU_RAM LESS 294912)     # 288 * 1024
        set(_heap_bytes 40960)      # 40 * 1024
    elseif(MCU_RAM LESS 786432)     # 768 * 1024
        set(_heap_bytes 51200)      # 50 * 1024
    else()
        set(_heap_bytes 65536)      # 64 * 1024
    endif()

    # Minimal stack size in *words* (typical Cortex-M ports use 32-bit words).
    set(_min_stack_words 128)
    if(MCU_RAM LESS 32768)          # < 32KB
        set(_min_stack_words 64)
    else()
        set(_min_stack_words 128)
    endif()

    # ---------------------------------------------------------------------
    # Build MACRO_LIST to inject into template
    # ---------------------------------------------------------------------
    set(MACRO_LIST "")

    # CPU clock: keep it MCU-driven with already defined FOSC_KHZ_VALUE
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

