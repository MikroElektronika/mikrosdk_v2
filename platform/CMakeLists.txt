## ./platform/CMakeLists.txt
add_subdirectory(conversions)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(plot)
    add_subdirectory(ring)
    add_subdirectory(mikrosdk_version)
    add_subdirectory(mikrobus)
    # Following implementation is NECTO Studio specific, so it is not added if
    # the SDK is not used in NECTO Studio.
    if (${IS_NECTO})
        # Firmware trace: needs a linker with --wrap and a port in platform/trace/lib/src/trace_port.h:
        # Cortex-M, RISC-V and PIC32 with GCC, Clang and XC32. Not mikroC: its linker cannot wrap.
        # Clang for Arm is "clang-llvm", for RISC-V "clang-llvm-riscv" (caught by CORE_NAME).
        if ((NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC") AND
            ((${TOOLCHAIN_ID} MATCHES "arm") OR (${TOOLCHAIN_ID} STREQUAL "clang-llvm") OR
            (${CORE_NAME} MATCHES "RISCV") OR (${TOOLCHAIN_ID} STREQUAL "mchp_xc32")))
            add_subdirectory(trace)
        endif()
    endif()
    add_subdirectory(simulation)
    add_subdirectory(sprint)
    # Millisecond time from the core's cycle counter (GNU toolchains): Cortex-M3 and newer,
    # PIC32 (CP0 Count) and RISC-V. Cortex-M0/M0+/M23 have no cycle counter.
    if ((NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC") AND
        ((${CORE_NAME} MATCHES "^(M3|M4|M7|M33|M55|M85)") OR (${CORE_NAME} MATCHES "MIPS32|MICROAPTIV") OR
         (${CORE_NAME} MATCHES "RISCV")))
        add_subdirectory(systime)
    endif()
endif()
