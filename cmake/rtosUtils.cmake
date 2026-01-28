#############################################################################
## Check if RTOS components should be enabled for the current target
#############################################################################
function(check_rtos_components has_rtos)
    set(${has_rtos} "false" PARENT_SCOPE)

    # AI-generated SDK: limited RTOS support (per review comment)
    if(AI_GENERATED_SDK)
        if("${MCU_NAME}" MATCHES "^STM32(G4|C0|L4|G0).+$")
            set(${has_rtos} "true" PARENT_SCOPE)
        else()
            message(WARNING ": Selected mcu (${MCU_NAME}) is not supported for FreeRTOS in AI_GENERATED_SDK.")
        endif()
        return()
    endif()

    # Non-AI SDK: enable for supported vendor families
    if("${MCU_NAME}" MATCHES "^STM32.+$" OR "${MCU_NAME}" MATCHES "^R7F.+$"  OR "${MCU_NAME}" MATCHES "^PIC32.+$" OR "${MCU_NAME}" MATCHES "^TMPM4K.+$" OR "${MCU_NAME}" MATCHES "^MK.+$")
        set(${has_rtos} "true" PARENT_SCOPE)
    else()
        message(WARNING ": Selected mcu (${MCU_NAME}) doesn't have RTOS support enabled.")
    endif()
endfunction()

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
## FreeRTOS: compile definitions needed for systick/core integration
#############################################################################
function(get_rtos_compile_definitions out_defs)
    set(defs "")

    # STM32: core types for SysTick helper (SCB/SysTick types not always present via core files)
    if("${MCU_NAME}" MATCHES "^STM32.+$" OR "${MCU_NAME}" MATCHES "^MK.+$")
        list(APPEND defs MSDK_SYSTICK_DEFINE_CORE_TYPES)
    endif()

    # Renesas R7F (RA): systick helper must use SCB->SHPR[] instead of SCB->SHP[]
    if("${MCU_NAME}" MATCHES "^R7F.+$")
        list(APPEND defs MSDK_SYSTICK_USE_SHPR)
    endif()

    # Ports that already provide SysTick_Handler in port.c
    if(CORE_NAME MATCHES "M0" OR CORE_NAME STREQUAL "M23" OR CORE_NAME MATCHES "M33")
        list(APPEND defs MSDK_PORT_PROVIDES_SYSTICK_HANDLER)
    endif()

    # PIC32: FreeRTOSConfig.h is included from port_asm.S -> remove inlcuded c libraries
    if("${MCU_NAME}" MATCHES "^PIC32.+$")
        list(APPEND defs MSDK_FREERTOS_CONFIG_ASM_SAFE)
    endif()

    set(${out_defs} "${defs}" PARENT_SCOPE)
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
    # PIC32 ports (portable/MPLAB/PIC32MX or PIC32MZ)
    if("${MCU_NAME}" MATCHES "^PIC32MX.+$")
        set(${out_port_arch} "PIC32MX" PARENT_SCOPE)
        return()
    elseif("${MCU_NAME}" MATCHES "^PIC32MZ.+$")
        set(${out_port_arch} "PIC32MZ" PARENT_SCOPE)
        return()
    endif()

    # ARM/RISC-V ports
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
## FreeRTOS: resolve include dirs from KERNEL_ROOT
#############################################################################
function(rtos_freertos_get_include_dirs kernel_root_var out_port_dir)
    set(kernel_root ${${kernel_root_var}})

    rtos_freertos_get_port_compiler(port_compiler)
    rtos_freertos_get_port_arch(port_arch)

    set(port_dir ${kernel_root}/portable/${port_compiler}/${port_arch})
    set(${out_port_dir} ${port_dir} PARENT_SCOPE)
endfunction()

#############################################################################
## FreeRTOS: resolve all sources (kernel + port + heap) as a single list
#############################################################################
function(rtos_freertos_get_sources kernel_root_var port_dir_var out_sources)
    set(kernel_root ${${kernel_root_var}})
    set(port_dir ${${port_dir_var}})

    set(source_list
        ${kernel_root}/event_groups.c
        ${kernel_root}/list.c
        ${kernel_root}/queue.c
        ${kernel_root}/stream_buffer.c
        ${kernel_root}/tasks.c
        ${kernel_root}/timers.c

        ${port_dir}/port.c

        ${kernel_root}/portable/MemMang/heap_4.c
    )
    
    # Some ports also use portasm.c
    if(EXISTS "${port_dir}/portasm.c")
        list(APPEND source_list ${port_dir}/portasm.c)
    endif()

    # PIC32 ports also use port_asm.S
    if(EXISTS "${port_dir}/port_asm.S")
        list(APPEND source_list ${port_dir}/port_asm.S)
    endif()

    set(${out_sources} ${source_list} PARENT_SCOPE)
endfunction()

#############################################################################
## FreeRTOS: resolve mikroSDK "common/include" directory for current toolchain
#############################################################################
function(rtos_freertos_get_mikrosdk_common_include_dir out_common_include_dir)
    # XC32 => PIC32 tree
    if(TOOLCHAIN_ID MATCHES "mchp_xc32")
        set(common_dir ${CMAKE_SOURCE_DIR}/targets/pic_32bit/mikroe/common/include)
    else()
        # Default => ARM tree (STM32/Renesas RA su i dalje ARM)
        set(common_dir ${CMAKE_SOURCE_DIR}/targets/arm/mikroe/common/include)
    endif()

    set(${out_common_include_dir} ${common_dir} PARENT_SCOPE)
endfunction()


#############################################################################
## FreeRTOS: resolve FreeRTOSConfig directory (GENERATED)
#############################################################################
function(rtos_freertos_get_config_dir out_config_dir)
    # One static include directory for all MCUs
    set(generate_dir ${CMAKE_BINARY_DIR}/generated/freertos)

    # Generate FreeRTOSConfig.h into generate_dir
    rtos_freertos_generate_config("${generate_dir}" "FreeRTOSConfig.h")

    # Return generated directory
    set(${out_config_dir} ${generate_dir} PARENT_SCOPE)
endfunction()

#############################################################################
## FreeRTOS: generate FreeRTOSConfig.h
#############################################################################
macro(rtos_freertos_generate_config fileDestination fileName)
    # Detect arch (to decide whether to emit Cortex-M handler mappings)
    rtos_freertos_get_port_arch(port_arch)

    # ---------------------------------------------------------------------
    # Decide configPRIO_BITS
    # current rules:
    # - default => 4
    # - STM32 : CM0(G0,L0,F0)  => 2
    # - Renesas: CM23(R7FA2E3) => 2
    #            CM33(R7FA4M3) => 3
    # ---------------------------------------------------------------------
    # Default: Cortex-M3/M4/M7/M85
    set(prio_bits 4)

    # Cortex-M0 / M23
    if(CORE_NAME MATCHES "M0" OR CORE_NAME STREQUAL "M23")
        set(prio_bits 2)

    # Supported Cortex-M33 targets (Renesas RA4M3/RA6M3)
    elseif(CORE_NAME MATCHES "M33")
        set(prio_bits 3)
    endif()

    # ---------------------------------------------------------------------
    # Decide interrupt priority constants from prio bits
    # lowest = (2^prio_bits - 1)
    # max syscall: keep established defaults by prio-bits
    #   2 bits  -> 1
    #   3 bits  -> 2
    #   4 bits  -> 5
    # ---------------------------------------------------------------------
    math(EXPR lowest_irq_prio "(1 << ${prio_bits}) - 1")

    if(prio_bits EQUAL 2)
        set(max_syscall_irq_prio 1)
    elseif(prio_bits EQUAL 3)
        set(max_syscall_irq_prio 2)
    else()
        set(max_syscall_irq_prio 5)
    endif()

    # ---------------------------------------------------------------------
    # Decide heap size from MCU_RAM (bytes)
    # ---------------------------------------------------------------------
    if(NOT MCU_RAM)
        message(FATAL_ERROR "FreeRTOS: MCU_RAM is not defined for ${MCU_NAME}")
    endif()

    set(heap_bytes 8192)           # Default: 8KB
    if(MCU_RAM LESS 18432)          # 18 * 1024
        set(heap_bytes 6144)       # 6 * 1024
    elseif(MCU_RAM LESS 24576)      # 24 * 1024
        set(heap_bytes 8192)       # 8 * 1024
    elseif(MCU_RAM LESS 40960)      # 40 * 1024
        set(heap_bytes 10240)      # 10 * 1024
    elseif(MCU_RAM LESS 73728)      # 72 * 1024
        set(heap_bytes 12288)      # 12 * 1024
    elseif(MCU_RAM LESS 98304)      # 96 * 1024
        set(heap_bytes 20480)      # 20 * 1024
    elseif(MCU_RAM LESS 163840)     # 160 * 1024
        set(heap_bytes 24576)      # 24 * 1024
    elseif(MCU_RAM LESS 294912)     # 288 * 1024
        set(heap_bytes 40960)      # 40 * 1024
    elseif(MCU_RAM LESS 786432)     # 768 * 1024
        set(heap_bytes 51200)      # 50 * 1024
    else()
        set(heap_bytes 65536)      # 64 * 1024
    endif()

    # Minimal stack size in *words* (typical Cortex-M ports use 32-bit words).
    set(min_stack_words 128)
    if(MCU_RAM LESS 32768)          # < 32KB
        set(min_stack_words 64)
    else()
        set(min_stack_words 128)
    endif()

    
    set(MACRO_LIST "")
    # ---------------------------------------------------------------------
    # PIC32 config block (assembler-safe)
    # ---------------------------------------------------------------------
    if("${MCU_NAME}" MATCHES "^PIC32.+$")
        # Use OSC_KHZ without including headers
        string(APPEND MACRO_LIST
            "#define configCPU_CLOCK_HZ ( (unsigned long)(OSC_KHZ) * 1000UL )\n"
        )

        # Peripheral clock: match what you currently do (div is a board/system choice)
        if("${MCU_NAME}" MATCHES "^PIC32MX.+$")
            string(APPEND MACRO_LIST
                "#define PBCLK_DIV ( 1UL )\n"
                "#define configPERIPHERAL_CLOCK_HZ ( ( unsigned long ) ( ( OSC_KHZ * 1000UL ) / ( PBCLK_DIV ) ) )\n"
            )
        elseif("${MCU_NAME}" MATCHES "^PIC32MZ.+$")
            string(APPEND MACRO_LIST
                "#define PBCLK3_DIV ( 2UL )\n"
                "#define configPERIPHERAL_CLOCK_HZ ( ( unsigned long ) ( configCPU_CLOCK_HZ / (unsigned long)PBCLK3_DIV ) )\n"
            )
        endif()

        # PIC32-specific required settings
        string(APPEND MACRO_LIST
            "#define configISR_STACK_SIZE ( 512U )\n"
            "#define configKERNEL_INTERRUPT_PRIORITY ( 1 )\n"
            "#define configMAX_SYSCALL_INTERRUPT_PRIORITY ( 3 )\n"
        )

        # Heap/stack: 
        string(APPEND MACRO_LIST
            "#define configTOTAL_HEAP_SIZE ( ${heap_bytes} )\n"
            "#define configMINIMAL_STACK_SIZE ( ${min_stack_words} )\n"
        )

    # ---------------------------------------------------------------------
    # ARM/RISC-V config block
    # ---------------------------------------------------------------------
    else()
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

        string(APPEND MACRO_LIST "#define configTOTAL_HEAP_SIZE ( ( size_t ) ${heap_bytes} )\n")
        string(APPEND MACRO_LIST "#define configMINIMAL_STACK_SIZE ( ${min_stack_words} )\n")

        string(APPEND MACRO_LIST "#define configPRIO_BITS ( ${prio_bits} )\n")
        string(APPEND MACRO_LIST "#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY ( ${lowest_irq_prio} )\n")
        string(APPEND MACRO_LIST "#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY ( ${max_syscall_irq_prio} )\n")

        # Cortex-M handler mappings only for ARM_CM* ports
        if(port_arch MATCHES "^ARM_CM")
            string(APPEND MACRO_LIST "#define vPortSVCHandler      SVC_Handler\n")
            string(APPEND MACRO_LIST "#define xPortPendSVHandler   PendSV_Handler\n")
        endif()
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

