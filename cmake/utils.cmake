include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
#############################################################################
## Function to install and export static library target
#############################################################################
function(mikrosdk_install targetAlias)
## Install library
    get_target_property(_targetName ${targetAlias} ALIASED_TARGET)
    get_target_property(linkLibs ${_targetName} INTERFACE_LINK_LIBRARIES)
    install(TARGETS ${_targetName}
        EXPORT ${targetAlias}Target
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
 # INSTALL EXPORT FILE
    install(EXPORT ${targetAlias}Target
        FILE ${targetAlias}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${targetAlias})
    ## Set variable used in configFile
    set(TARGET_NAME ${targetAlias})
    set(findDepsList "")

    foreach(LIB ${linkLibs})
        list(APPEND findDepsList "find_dependency(${LIB})")
    endforeach()
    if (linkLibs)
        list(JOIN findDepsList "\n" FIND_DEPS)
    else()
        set(FIND_DEPS "")
    endif()
## Configure package file
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/ExportConfig.cmake.in
         "${CMAKE_CURRENT_BINARY_DIR}/${targetAlias}Config.cmake"
         INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${targetAlias})


## configure package version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${targetAlias}ConfigVersion.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
        ARCH_INDEPENDENT)
## Install package export and package version file
    install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/${targetAlias}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${targetAlias}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${targetAlias})
endfunction()
#############################################################################
## Function to create static library target
#############################################################################
macro(mikrosdk_add_library functionName functionAlias)
    add_library(${functionName} STATIC ${ARGN})
    add_library(${functionAlias}  ALIAS ${functionName})
    set_target_properties(${functionName} PROPERTIES LINKER_LANGUAGE C)
    set_property(TARGET ${functionName} PROPERTY C_STANDARD 99)
    set_target_properties(${functionName} PROPERTIES EXPORT_NAME ${functionAlias})
    target_compile_definitions(${functionName}
        PUBLIC
            code=
    )
endmacro()
#############################################################################
## Function to create interface header only library target
#############################################################################
macro(mikrosdk_add_interface_library functionName functionAlias)
    add_library(${functionName} INTERFACE ${ARGN})
    add_library(${functionAlias}  ALIAS ${functionName})
    set_target_properties(${functionName} PROPERTIES LINKER_LANGUAGE C)
    set_property(TARGET ${functionName} PROPERTY C_STANDARD 99)
    set_target_properties(${functionName} PROPERTIES EXPORT_NAME ${functionAlias})
    target_compile_definitions(${functionName}
        INTERFACE
            code=
    )
endmacro()
#############################################################################

#############################################################################
## Function to deduce chip architecture from current MCU name and CORE
#############################################################################
function(find_chip_architecture _chip_architecture)
    if((${CORE_NAME} MATCHES "M0") OR (${CORE_NAME} MATCHES "M3") OR
        (${CORE_NAME} MATCHES "M4EF") OR (${CORE_NAME} MATCHES "M4DSP") OR
        (${CORE_NAME} MATCHES "M7"))
        if(${MCU_NAME} MATCHES "^STM.*")
            set(${_chip_architecture} "arm" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^MK.*")
            set(${_chip_architecture} "arm" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^TM4C.*")
            set(${_chip_architecture} "arm" PARENT_SCOPE)
        else()
            set(${_chip_architecture} "UNSUPPORTED_CHIP_SELECTED_FOR_FOLLOWING_IMPLEMENTATION" PARENT_SCOPE)
        endif()
    elseif(${CORE_NAME} MATCHES "P18")
        if(${MCU_NAME} MATCHES "^PIC18F[2-6][^4]K4.$|^PIC18LF[2-6][^4]K4.$|^PIC18.+K80$|^PIC18.+[24].+K50$|^PIC18.+J94$|^PIC18.+2[^4]J[5][03]$|^PIC18.+4[4-7]J[5][03]$|^PIC18.+[68][5-7]J[59][03]$|^PIC18F[568][567]J10$|^PIC18.+J1[356]$|^PIC18.+J[6][05]$|^PIC18F[68]6J55$|^PIC18F.+J[57][25]$|^PIC18F[24]6K20$|^PIC18.+K90$|^PIC18.+[2468][6]K22$|^PIC18.+[68][57]K22$|^PIC18.+[268][5-9]J11$|^PIC18.+[24][456]J11$|^PIC18F[68][5-7]J11$|^PIC18.+[2][4][^1][58].+$|^PIC18.+25[5][03]$")
            set(${_chip_architecture} "pic_8bit" PARENT_SCOPE)
        elseif(${MCU_NAME} MATCHES "^PIC18.+25[128][5]$|^PIC18.+26[8][025]$|^PIC18.+26[12][0]$|^PIC18.+445[58]$|^PIC18.+45.+[5]$|^PIC18.+455[03]$|^PIC18.+46[128][025]$|^PIC18.+65[28][057]$|^PIC18.+66[28][01278]$|^PIC18.+67[2][023]$|^PIC18.+85[28][057]$|^PIC18.+8[67][28].+$|^PIC18.+245[58]$|^PIC18.+45K22|^PIC18F[245][5-7]Q43$|^PIC18F[24][5-7]Q10$")
            set(${_chip_architecture} "pic_8bit" PARENT_SCOPE)
        else()
            set(${_chip_architecture} "UNSUPPORTED_CHIP_SELECTED_FOR_FOLLOWING_IMPLEMENTATION" PARENT_SCOPE)
        endif()
    elseif((${CORE_NAME} MATCHES "MIPS32") OR (${CORE_NAME} MATCHES "MICROAPTIV_FP") OR (${CORE_NAME} MATCHES "MICROAPTIV"))
        if(${MCU_NAME} MATCHES "(^PIC32MX[1-7][1-79][045]F(512|256|128|064|032|016)[HLBCD]B?$|^PIC32MZ(0512|1024|2048)EF[FEHMGK](064|100|124|144)$)")
            set(${_chip_architecture} "pic_32bit" PARENT_SCOPE)
        else()
            set(${_chip_architecture} "UNSUPPORTED_CHIP_SELECTED_FOR_FOLLOWING_IMPLEMENTATION" PARENT_SCOPE)
        endif()
    elseif(${CORE_NAME} MATCHES "RISCV")
        set(${_chip_architecture} "riscv" PARENT_SCOPE)
    elseif((${CORE_NAME} MATCHES "GT64K") OR (${CORE_NAME} MATCHES "LTE64K"))
        set(${_chip_architecture} "avr_8bit" PARENT_SCOPE)
        else()
        set(${_chip_architecture} "__chip_error__" PARENT_SCOPE)
    endif()
endfunction()

#############################################################################
## Function to deduce cortex name from MCU
#############################################################################
function(find_cortex listArg)
    set(local_list ${listArg})

    if (${MCU_NAME} MATCHES "^......(.)")
        if(${CMAKE_MATCH_1} MATCHES "0")
            list(APPEND local_list __cortex_m0__ PARENT_SCOPE)
        elseif((${CMAKE_MATCH_1} MATCHES "1") OR (${CMAKE_MATCH_1} MATCHES "2"))
            list(APPEND local_list __cortex_m3__ PARENT_SCOPE)
            elseif((${CMAKE_MATCH_1} MATCHES "3") OR (${CMAKE_MATCH_1} MATCHES "4"))
            list(APPEND local_list __cortex_m4__ PARENT_SCOPE)
        elseif(${CMAKE_MATCH_1} MATCHES "7")
            list(APPEND local_list __cortex_m7__ PARENT_SCOPE)
        else()
            list(APPEND local_list __cortex_not_supported__ PARENT_SCOPE)
        endif()
    endif()
    set(${list} ${local_list} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to find path to adequate mcu header file
#############################################################################
function(find_mcu_header_path listArg _mcu_header_path _mcu_name_first_7_chars)

    set(local_list ${listArg})

    string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
    MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-2")
    string(SUBSTRING ${MCU_NAME} 0 ${BEGIN_INDEX} MEMAKE_MCU_NAME_STRIPPED_BY_2)
    list(APPEND local_list ${MEMAKE_MCU_NAME_STRIPPED_BY_2}xx)     #STM32 + Product type + Series number + sub-lines + lines + 'xx'
    string(SUBSTRING ${MCU_NAME} 0 8 MEMAKE_MCU_NAME_FIRST_8)
    list(APPEND local_list ${MEMAKE_MCU_NAME_FIRST_8}x)      #STM32 + Product type + Series number + 'xx'
    string(SUBSTRING ${MCU_NAME} 0 7 MEMAKE_MCU_NAME_FIRST_7)
    set(${_mcu_name_first_7_chars} ${MEMAKE_MCU_NAME_FIRST_7} PARENT_SCOPE)
    list(APPEND local_list ${MEMAKE_MCU_NAME_FIRST_7}xx)     #STM32 + Product type + Series number + 'xx'
    set(${_mcu_header_path} ${MCU_NAME}${_MSDK_PACKAGE_NAME_} PARENT_SCOPE)
    string(SUBSTRING ${MCU_NAME} 11 1 MEMAKE_MCU_NAME_11TH_CHAR)
    if(${MEMAKE_MCU_NAME_11TH_CHAR} MATCHES "_")
    string(SUBSTRING ${_mcu_header_path} 0 11 FIRST_11_CHARS)
       set(${_mcu_header_path} ${FIRST_11_CHARS}${_MSDK_PACKAGE_NAME_} PARENT_SCOPE)
    endif()

    set(${list} ${local_list} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to check if module is supported for specific MCU
#############################################################################
function(set_module_support listArg listModules chip_name layer)
    set(local_list ${listArg})
    set(local_list_modules ${listModules})
    string(TOLOWER ${chip_name} check_chip)

    if(layer STREQUAL "drv_layer")
        list(APPEND local_list MikroSDK.Driver.ADC)
        list(APPEND local_list MikroSDK.Driver.GPIO.In)
        list(APPEND local_list MikroSDK.Driver.GPIO.Out)
        list(APPEND local_list MikroSDK.Driver.GPIO.Port)
        list(APPEND local_list MikroSDK.Driver.I2C.Master)
        list(APPEND local_list MikroSDK.Driver.PWM)
        list(APPEND local_list MikroSDK.Driver.SPI.Master)
        list(APPEND local_list MikroSDK.Driver.UART)
    elseif (layer STREQUAL "hal_layer")
        list(APPEND local_list MikroSDK.Hal.ADC)
        list(APPEND local_list MikroSDK.Hal.GPIO)
        list(APPEND local_list MikroSDK.Hal.I2C.Master)
        list(APPEND local_list MikroSDK.Hal.PWM)
        list(APPEND local_list MikroSDK.Hal.SPI.Master)
        list(APPEND local_list MikroSDK.Hal.UART)
        list(APPEND local_list MikroSDK.Hal.OneWire)
    elseif(layer STREQUAL "hal_ll_layer")
        list(APPEND local_list MikroSDK.HalLowLevel.ADC)
        list(APPEND local_list MikroSDK.HalLowLevel.GPIO)
        list(APPEND local_list MikroSDK.HalLowLevel.I2C.Master)
        list(APPEND local_list MikroSDK.HalLowLevel.TIM)
        list(APPEND local_list MikroSDK.HalLowLevel.SPI.Master)
        list(APPEND local_list MikroSDK.HalLowLevel.UART)
        list(APPEND local_list MikroSDK.HalLowLevel.OneWire)
    endif()

    list(APPEND local_list_modules msdk_adc)
    list(APPEND local_list_modules msdk_gpio_in)
    list(APPEND local_list_modules msdk_gpio_out)
    list(APPEND local_list_modules msdk_gpio_port)
    list(APPEND local_list_modules msdk_i2c_master)
    list(APPEND local_list_modules msdk_pwm)
    list(APPEND local_list_modules msdk_spi_master)
    list(APPEND local_list_modules msdk_uart)

    if(${check_chip} MATCHES "^at.+$")
        message(INFO " One Wire not implemented for ${chip_name} for ${layer}.")
    else()
        list(APPEND local_list MikroSDK.Driver.OneWire)
        list(APPEND local_list_modules msdk_onewire)
    endif()

    set(${list} ${local_list} PARENT_SCOPE)
    set(${list} ${local_list_modules} PARENT_SCOPE)
endfunction()
