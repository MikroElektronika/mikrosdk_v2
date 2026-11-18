## ./platform/trace/lib/CMakeLists.txt
# The drivers know nothing of the trace: linking this library sends their calls to the wrappers of
# src/wrappers/trace_*.c (GNU ld / lld --wrap), and only for the drivers the MCU has.
#
# The wrappers are compiled into the application (INTERFACE sources), not archived in the library:
# a library that calls a driver (a click) may come after MikroSDK.Trace on the link line, and the
# linker would not go back to the archive for its __wrap_ symbol. Objects of the application are
# always linked; --gc-sections drops the wrappers of the drivers it does not call.
set(module_list "")
set(module_list_supported "")
set_module_support(module_list module_list_supported ${MCU_NAME} "drv_layer")

set(trace_wrappers "")
set(trace_drivers "")
set(trace_wrapped "")

if (msdk_i2c_master IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_i2c.c)
    list(APPEND trace_drivers MikroSDK.Driver.I2C.Master)
    list(APPEND trace_wrapped i2c_master_write i2c_master_read i2c_master_write_then_read)
endif()
if (msdk_spi_master IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_spi.c)
    list(APPEND trace_drivers MikroSDK.Driver.SPI.Master)
    list(APPEND trace_wrapped spi_master_select_device spi_master_deselect_device spi_master_write
                              spi_master_read spi_master_write_then_read spi_master_transfer)
endif()
if (msdk_uart IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_uart.c)
    list(APPEND trace_drivers MikroSDK.Driver.UART)
    list(APPEND trace_wrapped uart_write uart_print uart_println uart_read)
endif()
if (msdk_gpio_out IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_gpio_out.c)
    list(APPEND trace_drivers MikroSDK.Driver.GPIO.Out)
    # With FLATTEN_ME_LEVEL_HIGH only the init is a function; wrapping a missing one is harmless.
    list(APPEND trace_wrapped digital_out_init digital_out_high digital_out_low digital_out_toggle
                              digital_out_write)
endif()
if (msdk_gpio_in IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_gpio_in.c)
    list(APPEND trace_drivers MikroSDK.Driver.GPIO.In)
    list(APPEND trace_wrapped digital_in_init digital_in_read)
endif()
if (msdk_adc IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_adc.c)
    list(APPEND trace_drivers MikroSDK.Driver.ADC)
    list(APPEND trace_wrapped analog_in_read analog_in_read_voltage)
endif()
if (msdk_onewire IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_one_wire.c)
    list(APPEND trace_drivers MikroSDK.Driver.OneWire)
    list(APPEND trace_wrapped one_wire_reset one_wire_read_rom one_wire_skip_rom one_wire_match_rom
                              one_wire_search_first_device one_wire_search_next_device
                              one_wire_write_byte one_wire_read_byte)
endif()

mikrosdk_add_library(lib_trace MikroSDK.Trace
    src/trace.c
    src/trace_hooks.h
    src/trace_port.h
    include/trace.h
)

foreach(wrapper ${trace_wrappers})
    target_sources(lib_trace INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/wrappers/${wrapper}>
        $<INSTALL_INTERFACE:src/platform/trace/wrappers/${wrapper}>
    )
endforeach()

target_link_libraries(lib_trace
    PUBLIC
        MikroC.Core
        ${trace_drivers}
)

target_include_directories(lib_trace
    PRIVATE
        include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/platform>
)

# Linking the library is all an application needs. trace_init is kept by name, so that the trace
# (and the buffer the debugger reads) is linked even when no driver is called. The flattened GPIO
# macros need MIKROSDK_TRACE in the application.
foreach(symbol ${trace_wrapped})
    target_link_options(lib_trace INTERFACE "LINKER:--wrap=${symbol}")
endforeach()
target_link_options(lib_trace INTERFACE "LINKER:--undefined=trace_init")
target_compile_definitions(lib_trace INTERFACE MIKROSDK_TRACE)

mikrosdk_install(MikroSDK.Trace)
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform MikroSDK.Trace include/trace.h)
# The wrappers, one folder below the private header they include (../trace_hooks.h).
list(TRANSFORM trace_wrappers PREPEND src/wrappers/)
install(FILES ${trace_wrappers} DESTINATION src/platform/trace/wrappers)
install(FILES src/trace_hooks.h DESTINATION src/platform/trace)
