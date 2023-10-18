## ./targets/riscv/mikroe/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^GD32VF(.+)$)")
    set(vendor_id "gigadevice")
else()
    set(vendor_id "__implementation_error__")
endif()

add_subdirectory(${vendor_id})
add_subdirectory(common)
add_subdirectory(core)
