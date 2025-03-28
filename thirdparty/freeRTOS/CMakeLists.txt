## ./thirdparty/freeRTOS/
# set(SOURCE_FILES
#     list.c 
#     queue.c 
#     timers.c 
#     tasks.c
#     stream_buffer.c 
#     event_groups.c 
#     croutine.c
#     #portable/GCC/ARM_CM4_MPU/port.c 
#     #portable/GCC/ARM_CM4_MPU/mpu_wrappers_v2_asm.c
# # )
# add_library(freeRTOS
#     STATIC
#     ${SOURCE_FILES}
    # ../../FreeRTOSConfig.h
    # include/atomic.h
    # include/croutine.h
    # include/deprecated_definitions.h
    # include/event_groups.h
    # include/FreeRTOS.h
    # include/list.h
    # include/message_buffer.h
    # include/mpu_prototypes.h
    # include/mpu_syscall_numbers.h
    # include/mpu_wrappers.h
    # include/newlib-freertos.h
    # include/picolibc-freertos.h
    # include/portable.h
    # include/projdefs.h
    # include/queue.h
    # include/semphr.h
    # include/stack_macros.h
    # include/StackMacros.h
    # include/stream_buffer.h
    # include/task.h
    # include/timers.h
# )

# target_include_directories(freeRTOS PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     #${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4_MPU
#     ${CMAKE_CURRENT_SOURCE_DIR}/../..
# )

#add_executable(sources_freeRTOS ${SOURCE_FILES})
#target_include_directories(freeRTOS PRIVATE ${include})
#target_include_directories(sources_freeRTOS
 #   PRIVATE
 #       ${CMAKE_CURRENT_SOURCE_DIR}/include  
#)
## Define the minimum required CMake version
## Generate source files and header for the example module

## Add tinyusb as a library.
mikrosdk_add_library(lib_freeRTOS MikroSDK.FreeRTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/event_groups.c
  
    ${CMAKE_CURRENT_SOURCE_DIR}/list.c
   ${CMAKE_CURRENT_SOURCE_DIR}/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stream_buffer.c
  
    ${CMAKE_CURRENT_SOURCE_DIR}/tasks.c
    
    ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f429xx.s
    ${CMAKE_CURRENT_SOURCE_DIR}/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FreeRTOSConfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/atomic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/croutine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/deprecated_definitions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/event_groups.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FreeRTOS.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/list.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/stm32f4xx_it.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/stm32f4xx_hal_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/message_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_prototypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_syscall_numbers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mpu_wrappers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newlib-freertos.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/picolibc-freertos.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/portable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/projdefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/queue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semphr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stack_macros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StackMacros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stream_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/task.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/timers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F/portmacro.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/heap_4.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h 
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include/stm32f429xx.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_armclang_ltm.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_compiler.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_gcc.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_iccarm.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_version.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_armcc.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_armv81mml.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_armv8mbl.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_armv8mml.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm0.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm0plus.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm1.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm23.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm3.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm33.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm35p.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm4.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm55.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm7.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_cm85.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_sc000.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_sc300.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/core_starmc1.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/mpu_armv7.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/mpu_armv8.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/pac_armv81.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/pmu_armv8.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/tz_context.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include/cmsis_armclang.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_bus.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_cortex.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_dma.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_exti.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_gpio.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_pwr.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_rcc.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_system.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_tim.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_utils.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
)
#${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_RTOS/cmsis_os.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_RTOS/cmsis_os.c
## Link MikroE Core library.
target_link_libraries(lib_freeRTOS PUBLIC
    MikroC.Core
)


## Include search paths.
target_include_directories(lib_freeRTOS
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/portable
        ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F
        ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang
        # ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS
        # ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/CMSIS>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver>
        $<INSTALL_INTERFACE:include/thirdparty/freeRTOS>
)

## First generate library with `MikroSDK.USB.Tiny` alias and generis `tusb.h` header file.
mikrosdk_install(MikroSDK.FreeRTOS)
install_headers(${CMAKE_INSTALL_PREFIX}/include/thirdparty/freeRTOS MikroSDK.FreeRTOS /include/FreeRTOS.h /include/FreeRTOSConfig.h /portable/GCC/ARM_CM4F/portmacro.h  ) #/CMSIS_RTOS/cmsis_os.h /STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_tim.h /CMSIS/Include/core_cm4.h