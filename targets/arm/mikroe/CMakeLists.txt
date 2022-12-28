## ./targets/arm/mikroe/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    set(vendor_id "stm32")
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    set(vendor_id "nxp")
elseif(${MCU_NAME} MATCHES "(^TM4C1(.+)$)")
    set(vendor_id "tiva")
else()
    set(vendor_id "__implementation_error__")
endif()

add_subdirectory(${vendor_id})
add_subdirectory(common)
add_subdirectory(core)
