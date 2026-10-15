#############################################################################
## Macro to generate IPS LVGL mikroBUS selection header file.
## Usage:
##   ips_lvgl_mikrobus_selection(<fileDestination> <fileName> [MIKROBUS_x])
## If no mikroBUS is passed, DISPLAY_SPI_MIKROBUS is left undefined and
## the default (MIKROBUS_1) from lvgl_common.h is used.
#############################################################################
macro(ips_lvgl_mikrobus_selection fileDestination fileName)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set(extra_args ${ARGN})

    set(IPS_LVGL_MIKROBUS_DEFINE "")

    # Did we get the optional mikroBUS argument?
    list(LENGTH extra_args extra_count)
    if(${extra_count} GREATER 0)
        list(GET extra_args 0 _mikrobus_display)
        if(NOT "${_mikrobus_display}" STREQUAL "")
            string(APPEND IPS_LVGL_MIKROBUS_DEFINE "#define DISPLAY_SPI_MIKROBUS ${_mikrobus_display}\n")
        endif()
    endif()

    # Generate output file with adequate name and mikroBUS define.
    configure_file(${PROJECT_SOURCE_DIR}/cmake/ipsLvglMikrobus.cmake.in ${CMAKE_BINARY_DIR}/generated/${fileName} @ONLY)
    message(INFO "Generated ${CMAKE_BINARY_DIR}/generated/${fileName} with DISPLAY_SPI_MIKROBUS=${MIKROBUS_POSITION_IPSDISPLAY2}")
endmacro()
