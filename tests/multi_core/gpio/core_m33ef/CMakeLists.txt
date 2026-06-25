add_executable(core_m33ef
    main.c
)

set(CORE_SPECIFIC_SETUP_DIR ${CMAKE_SOURCE_DIR}/.meproject/setup/Debug/core_m33ef)
message("BABABA ${CORE_SPECIFIC_SETUP_DIR}")
list(APPEND CMAKE_PREFIX_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)
list(APPEND CMAKE_MODULE_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)

set(CORE_NAME "M33EF")
include(coreUtils)
set_flags(FLAGS)

target_compile_options(core_m33ef PRIVATE ${FLAGS})
target_link_options(core_m33ef PRIVATE ${FLAGS})
target_compile_definitions(core_m33ef PRIVATE CORE_CM33)

set(SECONDARY_CORE "core_m33ef" CACHE STRING "Secondary core selection" FORCE)

target_link_libraries(core_m33ef  PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Board
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
