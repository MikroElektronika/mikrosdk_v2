## ./platform/CMakeLists.txt
add_subdirectory(conversions)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(plot)
    add_subdirectory(ring)
    add_subdirectory(mikrosdk_version)
    add_subdirectory(mikrobus)
    # Firmware trace: needs weak symbols (no MikroC) and a port in
    # platform/trace/lib/src/trace_port.h: Cortex-M, RISC-V and PIC32 so far.
    if ((NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC") AND
        ((${TOOLCHAIN_ID} MATCHES "arm") OR (${CORE_NAME} MATCHES "RISCV") OR (${TOOLCHAIN_ID} STREQUAL "mchp_xc32")))
        add_subdirectory(trace)
    endif()
    add_subdirectory(simulation)
    add_subdirectory(sprint)
endif()
