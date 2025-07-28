add_executable(${CORE_0_NAME} main.c)

set(CORE_SPECIFIC_SETUP_DIR ${CMAKE_SOURCE_DIR}/.meproject/setup/Debug/${CORE_0_NAME})
list(APPEND CMAKE_PREFIX_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)
list(APPEND CMAKE_MODULE_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)

target_compile_options(${CORE_0_NAME} PRIVATE "${CORE_0_COMPILER_FLAGS}")
target_compile_definitions(${CORE_0_NAME} PRIVATE ${CORE_0_MCU_HEADER_CORE_DEFINE})
set(PRIMARY_CORE "${CORE_0_NAME}" CACHE STRING "Primary core selection" FORCE)


find_package(MikroC.Core REQUIRED)
target_link_libraries(${CORE_0_NAME}
    PUBLIC
        MikroC.Core
)

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CORE_SPECIFIC_SETUP_DIR}/FileStartup)

                fetch_startup_name(${CORE_SPECIFIC_SETUP_DIR}/FileStartup startupName)
                if(startupName)
                    add_startup_all_targets(. ${CORE_SPECIFIC_SETUP_DIR}/FileStartup ${startupName})
                endif()
                fetch_linker_name(${CORE_SPECIFIC_SETUP_DIR}/FileLinker linkerName)
                if(linkerName)
                    add_ld_all_targets(. ${CORE_SPECIFIC_SETUP_DIR}/FileLinker ${linkerName})
                endif()
            endif()
        endif()
    endif()
endif()
