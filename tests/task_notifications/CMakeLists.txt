add_executable( task_notifications
    main.c
)

############################ task_notifications GENERATED CODE START ###########################
find_package(MikroSDK.Driver.GPIO.Port REQUIRED)
target_link_libraries(task_notifications PUBLIC MikroSDK.Driver.GPIO.Port)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries( task_notifications PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver.GPIO.In REQUIRED)
target_link_libraries( task_notifications PUBLIC MikroSDK.Driver.GPIO.In)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries( task_notifications PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries( task_notifications PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries( task_notifications PUBLIC MikroC.Core)
############################ task_notifications GENERATED CODE END ###########################
target_link_libraries( task_notifications PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Driver.GPIO.Out
    MikroSDK.FreeRTOS
)
target_include_directories( task_notifications PUBLIC
    ${PROJECT_SOURCE_DIR}/../thirdparty/freeRTOS/include
	${PROJECT_SOURCE_DIR}/
) 
 target_sources( task_notifications PRIVATE ./systick.h)

