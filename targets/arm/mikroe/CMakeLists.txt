## ./targets/arm/mikroe/CMakeLists.txt
if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    set(vendor_id "stm32")
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    set(vendor_id "nxp")
elseif(${MCU_NAME} MATCHES "(^TM4C1(.+)$)")
    ## TIVA has only the 71 MCUs already implemented
    set(vendor_id "tiva")
elseif(${MCU_NAME} MATCHES "(^(AT)?SAM(.+)$)")
    set(vendor_id "sam")
else()
    set(vendor_id "__implementation_error__")
endif()

add_subdirectory(common)
add_subdirectory(core)

if(AI_GENERATED_SDK)
    add_subdirectory(ai_generated/${vendor_id})
else()
    add_subdirectory(${vendor_id})
endif()
