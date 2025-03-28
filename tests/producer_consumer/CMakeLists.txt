add_executable( producer_consumer
    main.c
)

############################ producer_consumer GENERATED CODE START ###########################
find_package(MikroSDK.Driver.GPIO.Port REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroSDK.Driver.GPIO.Port)
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroSDK.Driver.GPIO.In REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroSDK.Driver.GPIO.In)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(producer_consumer PUBLIC MikroC.Core)
############################ producer_consumer GENERATED CODE END ###########################
target_link_libraries( producer_consumer PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver
    MikroSDK.Driver.GPIO.In
    MikroSDK.Driver.GPIO.Port
    MikroSDK.Driver.GPIO.Out
    MikroSDK.FreeRTOS
    #${PROJECT_SOURCE_DIR}/../thirdparty/freeRTOS/
)
target_include_directories(producer_consumer PUBLIC
    ${PROJECT_SOURCE_DIR}/../thirdparty/freeRTOS/include
	${PROJECT_SOURCE_DIR}/
) 
 target_sources(producer_consumer PRIVATE ./systick.h)

