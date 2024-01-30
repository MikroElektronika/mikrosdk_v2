## ./targets/CMakeLists.txt
## Mikroe specific implementation necessities
if(${_MSDK_HAL_LOW_LEVEL_TARGET_} MATCHES "mikroe")
    find_chip_architecture(chip_architecture)
else()
    set(chip_architecture "__implementation_error__")
endif()

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
