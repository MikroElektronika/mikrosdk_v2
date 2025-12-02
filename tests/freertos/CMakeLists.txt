## ./tests/freertos/CMakeLists.txt

# FreeRTOS testovi su trenutno podržani samo za STM32F429ZI
if(NOT ${MCU_NAME} STREQUAL "STM32F429ZI")
    message(STATUS "Skipping FreeRTOS tests for MCU ${MCU_NAME}")
    return()
endif()

add_subdirectory(task_test)
add_subdirectory(task_notification)
add_subdirectory(sw_timer)
add_subdirectory(queue)
add_subdirectory(mutex)
add_subdirectory(event_group)
add_subdirectory(counting_semaphore)
add_subdirectory(binary_semaphore)
