## ./targets/CMakeLists.txt
## Mikroe specific implementation necessities
if(${_MSDK_HAL_LOW_LEVEL_TARGET_} MATCHES "mikroe")
    find_chip_architecture(chip_architecture)
else()
    set(chip_architecture "__implementation_error__")
endif()

include(utils)

set(errata_include_list "")
errata_check(${MCU_NAME} errata_include_list)

message(STATUS "Errata definitions: ${errata_include_list}")

foreach(ERRATA ${errata_include_list})
    add_compile_definitions(${ERRATA})
endforeach()

add_subdirectory(${chip_architecture}/${_MSDK_HAL_LOW_LEVEL_TARGET_})

## If flatten level is undefined, default to NONE.
if(NOT FLATTEN_ME_LEVEL)
    set(FLATTEN_ME_LEVEL "FLATTEN_ME_LEVEL_NONE")
    set(FLATTEN_ME "false")
endif()

## Generate header selecting flatten level, NONE by default.
flatten_code_level_selection(
    ${CMAKE_CURRENT_SOURCE_DIR}/${chip_architecture}/${_MSDK_HAL_LOW_LEVEL_TARGET_}/common/include flatten_me.h
    ${FLATTEN_ME} ${FLATTEN_ME_LEVEL}
)
