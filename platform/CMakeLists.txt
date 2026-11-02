## ./platform/CMakeLists.txt
add_subdirectory(conversions)
if (NOT ${IS_BARE_METAL})
    add_subdirectory(plot)
    add_subdirectory(ring)
    add_subdirectory(mikrosdk_version)
    add_subdirectory(mikrobus)
    # Firmware trace: weak hooks and Cortex-M interrupt masking, see platform/trace.
    if ((NOT ${TOOLCHAIN_LANGUAGE} MATCHES "MikroC") AND (${TOOLCHAIN_ID} MATCHES "arm"))
        add_subdirectory(trace)
    endif()
    add_subdirectory(simulation)
    add_subdirectory(sprint)
endif()
