## ./hal/interface/CMakeLists.txt
mikrosdk_add_interface_library(lib_hal_interface MikroSDK.HalInterface
    hal_target.h
)

target_link_libraries(lib_hal_interface  INTERFACE
    MikroSDK.RingBuffer
)
target_compile_definitions(lib_hal_interface INTERFACE ${MCU_NAME})

if(${_MSDK_HAL_LOW_LEVEL_TARGET_} MATCHES "mikroe")
    find_chip_architecture(chip_architecture)
else()
    set(chip_architecture "__implementation_error__")
endif()

if(${MCU_NAME} MATCHES "(^STM32(.+)$)")
    set(vendor_id "stm32")
elseif(${MCU_NAME} MATCHES "(^MK(.+)$)")
    set(vendor_id "nxp")
elseif(${MCU_NAME} MATCHES "(^TM4C1(.+)$)")
    set(vendor_id "tiva")
elseif(${MCU_NAME} MATCHES "(^PIC32(.+)$)")
    set(vendor_id "pic32")
elseif(${MCU_NAME} MATCHES "(^PIC18(.+)$)")
    set(vendor_id "pic18")
elseif(${MCU_NAME} MATCHES "(^GD32VF(.+)$)")
    set(vendor_id "gigadevice")
elseif(${MCU_NAME} MATCHES "AT")
    set(vendor_id "avr")
elseif(${MCU_NAME} MATCHES "^(ds)?PIC(24|30|33).*")
    set(vendor_id "dspic")
else()
    set(vendor_id "__implementation_error__")
endif()

string(TOUPPER ${vendor_id} vendor_id_upper)
target_include_directories(lib_hal_interface
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/targets/${chip_architecture}/${_MSDK_HAL_LOW_LEVEL_TARGET_}/${vendor_id}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/targets/${chip_architecture}/${_MSDK_HAL_LOW_LEVEL_TARGET_}/common/include/mcu_definitions/${vendor_id_upper}/${MCU_NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/hal>
)

resolve_compiler_definitions(REDUCE_LAYER)

mikrosdk_install(MikroSDK.HalInterface)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal MikroSDK.HalInterface hal_target.h)
