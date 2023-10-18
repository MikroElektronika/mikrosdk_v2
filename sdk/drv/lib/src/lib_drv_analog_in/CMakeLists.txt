## ./drv/lib/src/lib_drv_analog_in/CMakeLists.txt
set(drv_def_list "")

set_resolution(ANALOG_IN_RESOLUTION_CMAKE_VALUE)
list(APPEND drv_def_list ANALOG_IN_RESOLUTION_CMAKE=ANALOG_IN_${ANALOG_IN_RESOLUTION_CMAKE_VALUE})
message(INFO ":DRIVER LAYER ADC ${ANALOG_IN_RESOLUTION_CMAKE_VALUE} SET")

mikrosdk_add_library(lib_drv_adc MikroSDK.Driver.ADC
    drv_analog_in.c

    ../../include/drv_analog_in.h
    ../../include/drv_name.h
)

target_link_libraries(lib_drv_adc  PUBLIC
    MikroC.Core
    MikroSDK.Hal.ADC
)
target_compile_definitions(lib_drv_adc
 PUBLIC
    ${drv_def_list}
)

target_include_directories(lib_drv_adc
PRIVATE
    ../../include
INTERFACE
    $<INSTALL_INTERFACE:include/drv>
)

mikrosdk_install(MikroSDK.Driver.ADC)
install_headers(${CMAKE_INSTALL_PREFIX}/include/drv MikroSDK.Driver.ADC ../../include/drv_analog_in.h)
