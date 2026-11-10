## ./targets/rx/mikroe/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^R5(.+)$)")
    set(vendor_id "renesas")
else()
    set(vendor_id "__implementation_error__")
endif()

add_subdirectory(common)
add_subdirectory(core)

add_subdirectory(${vendor_id})
