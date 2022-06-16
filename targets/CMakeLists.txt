## Mikroe specific implementation necessities
if(${_MSDK_HAL_LOW_LEVEL_TARGET_} MATCHES "mikroe")
    find_chip_architecture(chip_architecture)
else()
    set(chip_architecture "__implementation_error__")
endif()

add_subdirectory(${chip_architecture}/${_MSDK_HAL_LOW_LEVEL_TARGET_})
