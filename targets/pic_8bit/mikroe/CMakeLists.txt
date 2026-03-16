## ./targets/pic_8bit/mikroe/CMakeLists.txt
add_subdirectory(common)
add_subdirectory(core)
if(${MCU_NAME} MATCHES "^PIC18.+")
    add_subdirectory(pic18)
else()
    add_subdirectory(pic16)
endif()
