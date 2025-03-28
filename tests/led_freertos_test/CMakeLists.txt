add_executable( led_freertos_test
    main.c
)

target_link_libraries( led_freertos_test PUBLIC
    MikroC.Core
    MikroSDK.Driver.GPIO.Out
    MikroSDK.Board
    MikroSDK.FreeRTOS
    #${PROJECT_SOURCE_DIR}/../thirdparty/freeRTOS/
)
target_include_directories(led_freertos_test PUBLIC
    ${PROJECT_SOURCE_DIR}/../thirdparty/freeRTOS/include
	${PROJECT_SOURCE_DIR}/
) 
 target_sources(led_freertos_test PRIVATE ./systick.h)

# target_sources(led_freertos_test PRIVATE 

#     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/croutine.c    
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/list.c  
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/tasks.c  
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/queue.c  
#    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/timers.c  
#    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/freeRTOS/event_groups.c  
# )