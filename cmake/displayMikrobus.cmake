#############################################################################
## Macro to generate mikroBUS selection header file for display Click boards.
## Usage:
##   display_mikrobus_selection(<fileName>)
## Reads the mikroBUS position NECTO passes for the selected display, named
## after _MSDK_TFT_BOARD_ without trailing _CLICK and without underscores
## (EVE_CLICK -> MIKROBUS_POSITION_EVE). If it is not passed,
## DISPLAY_SPI_MIKROBUS is left undefined and the display header default
## (MIKROBUS_1) is used.
#############################################################################
macro(display_mikrobus_selection fileName)
    string(REGEX REPLACE "_CLICK$" "" _display_click "${_MSDK_TFT_BOARD_}")
    string(REPLACE "_" "" _display_click "${_display_click}")
    set(_display_mikrobus "${MIKROBUS_POSITION_${_display_click}}")

    set(DISPLAY_MIKROBUS_DEFINE "")
    if(NOT "${_display_mikrobus}" STREQUAL "")
        string(APPEND DISPLAY_MIKROBUS_DEFINE "#define DISPLAY_SPI_MIKROBUS ${_display_mikrobus}\n")
    endif()

    # Header guard from file name, e.g. eve_mikrobus.h -> __EVE_MIKROBUS_H__.
    string(TOUPPER "${fileName}" DISPLAY_MIKROBUS_HEADER_GUARD)
    string(REGEX REPLACE "[^A-Z0-9]" "_" DISPLAY_MIKROBUS_HEADER_GUARD "__${DISPLAY_MIKROBUS_HEADER_GUARD}__")
    set(DISPLAY_MIKROBUS_FILE_NAME ${fileName})

    # Generate output file with adequate name and mikroBUS define.
    configure_file(${PROJECT_SOURCE_DIR}/cmake/displayMikrobus.cmake.in ${CMAKE_BINARY_DIR}/generated/${fileName} @ONLY)

    message("${_MSDK_TFT_BOARD_} mikroBUS selection (MIKROBUS_POSITION_${_display_click}): ${_display_mikrobus}")
endmacro()
