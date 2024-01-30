## ./middleware/lcd/lib/CMakeLists.txt
cmake_minimum_required(VERSION 3.11)

## Generate source files and headers first.
lcd_generate_driver_list(lcd_driver_list_src lcd_driver_list_hdr)

## Add LCD as a library.
mikrosdk_add_library(lib_lcd MikroSDK.LCD
    ## Common.
    src/lcd.c
    include/lcd.h
    ## All driver files.
    include/drivers/lcd_controllers.h
    ## Link all driver files separatelly
    ## and let user decide which to use.
    ${lcd_driver_list_src}
    ${lcd_driver_list_hdr}
)

## Apply LCD module PLDs.
set(lcd_list "")
target_compile_definitions(lib_lcd PUBLIC
    ${lcd_list}
)

## Link MikroE Core, Board and GPIO Out libraries.
target_link_libraries(lib_lcd PUBLIC
    MikroC.Core
    MikroSDK.Board
    MikroSDK.Driver.GPIO.Out
)

## Include search paths.
target_include_directories(lib_lcd
    PRIVATE
        include
        include/drivers
        include/drivers/controller
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/drivers>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/drivers/controller>
        $<INSTALL_INTERFACE:include/middleware/lcd>
        $<INSTALL_INTERFACE:include/middleware/lcd/drivers>
        $<INSTALL_INTERFACE:include/middleware/lcd/drivers/controller>
)

## Generate a header with all controller drivers.
lcd_get_controller_install_list(lcd_driver_list_hdr_install)
lcd_generate_drivers(${CMAKE_CURRENT_SOURCE_DIR}/include/drivers lcd_controllers.h ${lcd_driver_list_hdr_install})

## Then generate library with `MikroSDK.LCD` alias and generic `lcd.h` header file.
mikrosdk_install(MikroSDK.LCD)
install_headers(${CMAKE_INSTALL_PREFIX}/include/middleware/lcd MikroSDK.LCD include/lcd.h)

## Then install additional header files required by library.
lcd_install_headers(include/drivers/lcd_controllers.h ${CMAKE_INSTALL_PREFIX}/include/middleware/lcd/drivers)
lcd_install_headers(${lcd_driver_list_hdr} ${CMAKE_INSTALL_PREFIX}/include/middleware/lcd/drivers/controller)

## END ##
