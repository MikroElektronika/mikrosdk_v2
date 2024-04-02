## ./platform/conversions/lib/CMakeLists.txt
if (${IS_BARE_METAL})
    set(LIBRARY_NAME "Generic.Conversions")
else()
    set(LIBRARY_NAME "MikroSDK.Conversions")
endif()

mikrosdk_add_library(lib_platform ${LIBRARY_NAME}
    src/conversions.c

    include/conversions.h
)

target_link_libraries(lib_platform  PUBLIC
    MikroC.Core
)

set(conversions_def_list "")

if((${MCU_NAME} MATCHES "^PIC18.*") OR (${MCU_NAME} MATCHES "AT"))
    list(APPEND conversions_def_list __CONVERSIONS_CHIPS_8BIT__)
else()
    list(APPEND conversions_def_list __CONVERSIONS_CHIPS_16BIT_32BIT__)
endif()

if((${MCU_NAME} MATCHES "^PIC18.*") OR ((${MCU_NAME} MATCHES "^STM.*") AND (${CORE_NAME} MATCHES "M0")) OR (${MCU_NAME} MATCHES "AT") OR (${CORE_NAME} STREQUAL "DSPIC"))
    list(APPEND conversions_def_list __CONVERSIONS_SUBSET__)
else()
    list(APPEND conversions_def_list __CONVERSIONS_SET__)
endif()

target_compile_definitions(lib_platform PUBLIC
    ${conversions_def_list}
)

target_include_directories(lib_platform
PRIVATE
    include
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/platform>
)

mikrosdk_install(${LIBRARY_NAME})
install_headers(${CMAKE_INSTALL_PREFIX}/include/platform/ ${LIBRARY_NAME} include/conversions.h)
