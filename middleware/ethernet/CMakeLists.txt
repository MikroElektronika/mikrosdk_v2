## ./middleware/ethernet/CMakeLists.txt

## Bus and controller independent core (eth_transport_* API, driver and bus interfaces)
add_subdirectory(core)

## Bus bindings (each implements eth_bus_ops_t), add new buses here
add_subdirectory(spi)

## Transport independent protocol helpers
add_subdirectory(net)
