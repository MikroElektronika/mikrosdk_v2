## ./platform/CMakeLists.txt
add_subdirectory(conversions)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(plot)
    add_subdirectory(ring)
    add_subdirectory(mikrosdk_version)
    add_subdirectory(mikrobus)
    # Firmware trace: needs weak symbols and a port in platform/trace/lib/src/trace_port.h:
    # Cortex-M, RISC-V and PIC32 with GCC, Clang and XC32; Cortex-M and PIC32 with mikroC.
    if (((NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC") AND
         ((${TOOLCHAIN_ID} MATCHES "arm") OR (${CORE_NAME} MATCHES "RISCV") OR (${TOOLCHAIN_ID} STREQUAL "mchp_xc32"))) OR
        (${TOOLCHAIN_ID} STREQUAL "mikrocarm") OR (${TOOLCHAIN_ID} STREQUAL "mikrocpic32"))
        add_subdirectory(trace)
    endif()
    add_subdirectory(simulation)
    add_subdirectory(sprint)
endif()
