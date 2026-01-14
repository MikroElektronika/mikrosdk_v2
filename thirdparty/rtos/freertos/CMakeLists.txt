cmake_minimum_required(VERSION 3.17)

if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
    check_rtos_requirements(memory_requirements_passed)
    if(${memory_requirements_passed} STREQUAL "true")
        add_subdirectory(freertos-kernel)
    endif()
endif()