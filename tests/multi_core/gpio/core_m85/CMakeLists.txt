add_executable(core_m85
    main.c
)

set(CORE_SPECIFIC_SETUP_DIR ${CMAKE_SOURCE_DIR}/.meproject/setup/Debug/core_m85)
list(APPEND CMAKE_PREFIX_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)
list(APPEND CMAKE_MODULE_PATH ${CORE_SPECIFIC_SETUP_DIR}/lib/cmake)

set(CORE_NAME "M85")
include(coreUtils)
set_flags(FLAGS)

target_compile_options(core_m85 PRIVATE ${FLAGS})
target_link_options(core_m85 PRIVATE ${FLAGS})
target_compile_definitions(core_m85 PRIVATE CORE_CM85)

set(PRIMARY_CORE "core_m85" CACHE STRING "Primary core selection" FORCE)

target_link_libraries(core_m85  PUBLIC
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
