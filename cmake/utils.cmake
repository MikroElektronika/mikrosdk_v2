include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(usbUtils)
include(ethUtils)
include(lcdUtils)
include(flattenUtils)
include(fsUtils)
include(dsPicUtils)
include(rtcUtils)
include(aiUtils)

#############################################################################
## Macro to get a list of files in the provided folder
#############################################################################
macro(get_files search_path file_list extension)
    file(GLOB ${file_list} ${search_path}/*.${extension})
endmacro()

#############################################################################
## Macro to get all subsequent directories.
#############################################################################
MACRO(SUBDIRLIST dirList curdir relativePath)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}${relativePath})
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND ${dirList} ${child})
        ENDIF()
    ENDFOREACH()
ENDMACRO()

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
    ## INSTALL EXPORT FILE
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
    add_library(${functionAlias} ALIAS ${functionName})
    set_target_properties(${functionName} PROPERTIES LINKER_LANGUAGE C)
    set_property(TARGET ${functionName} PROPERTY C_STANDARD 99)
    set_target_properties(${functionName} PROPERTIES EXPORT_NAME ${functionAlias})
    if(NOT ${functionName} STREQUAL "lvgl")
        target_compile_definitions(${functionName}
            PUBLIC
                code=
        )
    endif()
endmacro()

#############################################################################
## Function to create interface header only library target
#############################################################################
macro(mikrosdk_add_interface_library functionName functionAlias)
    add_library(${functionName} INTERFACE ${ARGN})
    add_library(${functionAlias} ALIAS ${functionName})
    set_target_properties(${functionName} PROPERTIES LINKER_LANGUAGE C)
    set_property(TARGET ${functionName} PROPERTY C_STANDARD 99)
    set_target_properties(${functionName} PROPERTIES EXPORT_NAME ${functionAlias})
    if(NOT ${functionName} STREQUAL "lvgl")
        target_compile_definitions(${functionName}
            INTERFACE
                code=
        )
    endif()
endmacro()

#############################################################################
## Function to create interface headers according to lib alias
#############################################################################
macro(install_headers fileDestination fileAlias)
    # Cannot use ARGN directly with list() command,
    # so copy it to a variable first.
    set (extra_args ${ARGN})

    # Did we get any optional args?
    list(LENGTH extra_args extra_count)
    if (${extra_count} GREATER 0)
        # Create a list of include directives
        set(INCLUDE_DIRECTIVES "")
        foreach(ARGUMENT ${extra_args})
            get_filename_component(FILE_NAME ${ARGUMENT} NAME)
            string(APPEND INCLUDE_DIRECTIVES "#include \"${FILE_NAME}\"\n")
        endforeach()

        # Generate output file with adequate name and include directive
        configure_file(${PROJECT_SOURCE_DIR}/cmake/InstallHeaders.cmake.in ${fileDestination}/${fileAlias})

        # Proceed to copy adequate files
        install(
            FILES
                ${extra_args}
            DESTINATION
                ${fileDestination}
        )
    endif()
endmacro()

#############################################################################
## Function to deduce chip vendor from current MCU name
#############################################################################
function(find_chip_vendor _chip_vendor)
    if(${MCU_NAME} MATCHES "^STM.*")
        set(${_chip_vendor} "stm32" PARENT_SCOPE)
    endif()
    if(${MCU_NAME} MATCHES "^MK.*")
        set(${_chip_vendor} "nxp" PARENT_SCOPE)
    endif()
    if(${MCU_NAME} MATCHES "^TM4C.*")
        set(${_chip_vendor} "tiva" PARENT_SCOPE)
    endif()
endfunction()

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
    elseif(${CORE_NAME} MATCHES "DSPIC")
        set(${_chip_architecture} "pic_16bit" PARENT_SCOPE)
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
    set(CAN FALSE)
    set(DMA FALSE)
    set(RTC FALSE)

    if((${MCU_NAME} MATCHES "(^STM32(F(0([47](2|8G)|9[18])|10[357]|2[01]|3[023579][2-9]|4[0-467][2-9]|7[2-7])|L4).+$)") OR (${MCU_NAME} MATCHES "(^GD32.+$)") OR (${MCU_NAME} MATCHES "(^TM4C.+$)")
        OR (${MCU_NAME} MATCHES "^PIC18L?F[2468][0-9]K?8[0-9]$") OR (${MCU_NAME} MATCHES "(^(ds)?PIC(24|33)(FJ(64GP[57]|128GP[57]|256GP)|EP(256(GU|MU)|512(M[CU]8))).+$|PIC24HJ(64|128|256)GP[56][01][06]A?)|PIC24EP512G[PU]8.+")
        OR (${MCU_NAME} MATCHES "(^MK(V(4|5[68]F[15][1M][02]VL)|6(4F(N1M0V|X5)|0D(N[25][15][26]V[LM][DQ]|X256V[LM][QD])|6)).+$)") OR (${MCU_NAME} MATCHES "^PIC32M(Z[0-9]+EF[FKHM].+|X[75].+)$"))
        if(NOT "${MCU_NAME}${_MSDK_PACKAGE_NAME_}" MATCHES "STM32F048G6Ux|STM32F091RCIx|STM32F098RCIx|STM32F427AGIx|STM32F427AIIx|STM32F429AGIx|STM32F429AIIx|STM32F437AIIx|STM32F439AIIx|STM32F469AEIx|STM32F469AEYx|STM32F469AGIx|STM32F469AGYx|STM32F469AIIx|STM32F469AIYx|STM32F479AGIx|STM32F479AGYx|STM32F479AIIx|STM32F479AIYx|STM32F722ICHx|STM32F722IEHx|STM32F723ICHx|STM32F723IEHx|STM32F723ZCJx|STM32F723ZEJx|STM32F732IEHx|STM32F733IEHx|STM32F733ZEJx|STM32F745IEHx|STM32F745IGHx|STM32F746IEHx|STM32F746IGHx|STM32F756IGHx|STM32F765IGHx|STM32F765IIHx|STM32F767IGHx|STM32F767IIHx|STM32F777IIHx|STM32F777IIHx|STM32L431VCHx|STM32L433VCHx|STM32L443VCHx|STM32L451VCHx|STM32L451VEHx|STM32L452VCHx|STM32L452VEHx|STM32L462VEHx")
            set(CAN TRUE)
        endif()
    endif()
    if((${MCU_NAME} MATCHES "^MK.+") OR (${MCU_NAME} MATCHES "^STM32.+$") OR (${CORE_NAME} MATCHES "RISCV") OR (${MCU_NAME} MATCHES "^TM4C12.+$") OR (${MCU_NAME} MATCHES "^PIC18.+K42$") OR (${MCU_NAME} MATCHES "^PIC18.+7Q43$") OR (${MCU_NAME} MATCHES "^PIC32.+"))
        if (NOT ${MCU_NAME} MATCHES "^PIC32MX(3|4)20F.+")  ## These MCUs only have dedicated DMA, that is only part of some other module.
            set(DMA TRUE)
        endif()
    endif()
    if (${MCU_NAME} MATCHES "^(STM32|PIC32|GD32|MK[0-9]|TM4C12(3[137BG]|9)).+")
        set(RTC TRUE)
    endif()

    if(layer STREQUAL "drv_layer")
        list(APPEND local_list MikroSDK.Driver.ADC)
        list(APPEND local_list MikroSDK.Driver.GPIO.In)
        list(APPEND local_list MikroSDK.Driver.GPIO.Out)
        list(APPEND local_list MikroSDK.Driver.GPIO.Port)
        list(APPEND local_list MikroSDK.Driver.I2C.Master)
        list(APPEND local_list MikroSDK.Driver.PWM)
        list(APPEND local_list MikroSDK.Driver.SPI.Master)
        list(APPEND local_list MikroSDK.Driver.UART)
        list(APPEND local_list MikroSDK.Driver.OneWire)
        if(CAN)
            list(APPEND local_list MikroSDK.Driver.CAN)
        endif()
        if(DMA)
            list(APPEND local_list MikroSDK.Driver.DMA)
        endif()
        if(RTC)
            list(APPEND local_list MikroSDK.Driver.RTC)
        endif()
    elseif (layer STREQUAL "hal_layer")
        list(APPEND local_list MikroSDK.Hal.ADC)
        list(APPEND local_list MikroSDK.Hal.GPIO)
        list(APPEND local_list MikroSDK.Hal.I2C.Master)
        list(APPEND local_list MikroSDK.Hal.PWM)
        list(APPEND local_list MikroSDK.Hal.SPI.Master)
        list(APPEND local_list MikroSDK.Hal.UART)
        list(APPEND local_list MikroSDK.Hal.OneWire)
        if(CAN)
            list(APPEND local_list MikroSDK.Hal.CAN)
        endif()
        if(DMA)
            list(APPEND local_list MikroSDK.Hal.DMA)
        endif()
        if(RTC)
            list(APPEND local_list MikroSDK.Hal.RTC)
        endif()
    elseif(layer STREQUAL "hal_ll_layer")
        list(APPEND local_list MikroSDK.HalLowLevel.ADC)
        list(APPEND local_list MikroSDK.HalLowLevel.GPIO)
        list(APPEND local_list MikroSDK.HalLowLevel.I2C.Master)
        list(APPEND local_list MikroSDK.HalLowLevel.TIM)
        list(APPEND local_list MikroSDK.HalLowLevel.SPI.Master)
        list(APPEND local_list MikroSDK.HalLowLevel.UART)
        list(APPEND local_list MikroSDK.HalLowLevel.OneWire)
        if(CAN)
            list(APPEND local_list MikroSDK.HalLowLevel.CAN)
        endif()
        if(DMA)
            list(APPEND local_list MikroSDK.HalLowLevel.DMA)
        endif()
        if(RTC)
            list(APPEND local_list MikroSDK.HalLowLevel.RTC)
        endif()
    endif()

    if(AI_GENERATED_SDK)
        find_chip_vendor(chip_vendor)
        find_chip_architecture(chip_arhictecture)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/adc local_list_modules msdk_adc)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/gpio local_list_modules msdk_gpio_in)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/gpio local_list_modules msdk_gpio_out)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/gpio local_list_modules msdk_gpio_port)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/i2c local_list_modules msdk_i2c_master)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/tim local_list_modules msdk_pwm)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/spi_master local_list_modules msdk_spi_master)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/uart local_list_modules msdk_uart)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/one_wire local_list_modules msdk_onewire)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/can local_list_modules msdk_can)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/dma local_list_modules msdk_dma)
        add_module_if_generated(${CMAKE_SOURCE_DIR}/targets/${chip_arhictecture}/mikroe/ai_generated/${chip_vendor}/src/rtc local_list_modules msdk_rtc)
    else()
        list(APPEND local_list_modules msdk_adc)
        list(APPEND local_list_modules msdk_gpio_in)
        list(APPEND local_list_modules msdk_gpio_out)
        list(APPEND local_list_modules msdk_gpio_port)
        list(APPEND local_list_modules msdk_i2c_master)
        list(APPEND local_list_modules msdk_pwm)
        list(APPEND local_list_modules msdk_spi_master)
        list(APPEND local_list_modules msdk_uart)
        list(APPEND local_list_modules msdk_onewire)
        if(CAN)
            list(APPEND local_list_modules msdk_can)
        endif()
        if(DMA)
            list(APPEND local_list_modules msdk_dma)
        endif()
        if(RTC)
            list(APPEND local_list_modules msdk_rtc)
        endif()
    endif()

    set(${list} ${local_list} PARENT_SCOPE)
    set(${list} ${local_list_modules} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to set adequate default ADC resolution
#############################################################################
function(set_resolution cmake_adc_resolution)
    find_chip_architecture(chip_architecture)

    if (${chip_architecture} STREQUAL "arm")
        set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
    elseif(${chip_architecture} STREQUAL "riscv")
        set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
    elseif(${chip_architecture} STREQUAL "pic_32bit")
        if (${MCU_NAME} MATCHES "^PIC32M[XZ](.+)$")
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        else()
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        endif()
    elseif(${chip_architecture} STREQUAL "avr_8bit")
        if (${MCU_NAME} MATCHES "^ATXMEGA.+")
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        else()
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        endif()
    elseif(${chip_architecture} STREQUAL "pic_8bit")
        string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
        MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
        MATH(EXPR BEGIN_INDEX_5TH "${MEMAKE_MCU_NAME_LENGTH}-5")
        MATH(EXPR BEGIN_INDEX_4TH "${MEMAKE_MCU_NAME_LENGTH}-4")
        string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)
        string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 1 MCU_NAME_5TH_CHAR)
        string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_4TH} 1 MCU_NAME_4TH_CHAR)
        string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX_5TH} 5 MCU_NAME_LAST5_CHARS)

        if (${MCU_NAME_LAST_3} STREQUAL "J94")
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        elseif ((${MCU_NAME_LAST_3} STREQUAL "K50") OR (${MCU_NAME} MATCHES "(^PIC18(((.+)4[56]K22$)|((.+)26K22$)))"))
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        elseif ((${MCU_NAME_LAST_3} STREQUAL "K22") OR (${MCU_NAME_LAST_3} STREQUAL "K80") OR (${MCU_NAME_LAST_3} STREQUAL "K90"))
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        elseif ((${MCU_NAME_LAST_3} STREQUAL "K40") OR (${MCU_NAME_LAST_3} STREQUAL "Q10"))
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        elseif ((${MCU_NAME_LAST_3} STREQUAL "K42") OR (${MCU_NAME_LAST_3} STREQUAL "Q43"))
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        elseif ((${MCU_NAME_LAST_3} STREQUAL "J55") OR (${MCU_NAME_LAST5_CHARS} STREQUAL "66J16") OR (${MCU_NAME_LAST5_CHARS} STREQUAL "86J16"))
            set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
        elseif (((${MCU_NAME_LAST_3} STREQUAL "J50") OR (${MCU_NAME_LAST_3} STREQUAL "J13") OR (${MCU_NAME_LAST_3} STREQUAL "J53")) AND ((${MCU_NAME_5TH_CHAR} STREQUAL "2") OR (${MCU_NAME_5TH_CHAR} STREQUAL "4")))
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        elseif (${MCU_NAME_LAST_3} STREQUAL "J11")
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        else()
            set(${cmake_adc_resolution} "RESOLUTION_10_BIT" PARENT_SCOPE)
        endif()
    elseif(${chip_architecture} STREQUAL "pic_16bit")
        set(${cmake_adc_resolution} "RESOLUTION_12_BIT" PARENT_SCOPE)
    else()
        set(${cmake_adc_resolution} "RESOLUTION_NOT_SET" PARENT_SCOPE)
    endif()
endfunction()

#############################################################################
## Function to set adequate pins for resistive touch
#############################################################################
function(set_tp_mikroe_pins _cmake_tp_mikroe_read_x _cmake_tp_mikroe_read_y)
    find_chip_architecture(chip_architecture)

    if (${chip_architecture} STREQUAL "arm")
        if (${MCU_NAME} MATCHES "^STM.*$")
            set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_YD" PARENT_SCOPE)
            set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_XL" PARENT_SCOPE)
        else()
            set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_XL" PARENT_SCOPE)
            set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_YD" PARENT_SCOPE)
        endif()
    elseif (${chip_architecture} STREQUAL "pic_32bit")
        set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_XL" PARENT_SCOPE)
        set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_YU" PARENT_SCOPE)
    elseif (${chip_architecture} STREQUAL "avr_8bit")
        set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_YD" PARENT_SCOPE)
        set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_XL" PARENT_SCOPE)
    elseif (${chip_architecture} STREQUAL "pic_8bit")
        if (${_MSDK_BOARD_NAME_} MATCHES "^MIKROMEDIAFORPIC18F[JK]$")
            set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_XL" PARENT_SCOPE)
            set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_YU" PARENT_SCOPE)
        else()
            set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_YD" PARENT_SCOPE)
            set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_XL" PARENT_SCOPE)
        endif()
    elseif (${chip_architecture} STREQUAL "pic_16bit")
            set(${_cmake_tp_mikroe_read_x} "TP_MIKROE_XR" PARENT_SCOPE)
            set(${_cmake_tp_mikroe_read_y} "TP_MIKROE_YU" PARENT_SCOPE)
    endif()
endfunction()

#############################################################################
## Function to link adequate logger APIs
#############################################################################
function(mikrosdk_get_log_libs listArg listSrcArg logInterface)
    set(local_include_list ${listArg})
    set(local_file_list ${listSrcArg})

    list(APPEND local_include_list MikroC.Core)
    list(APPEND local_include_list MikroSDK.Plot)
    list(APPEND local_include_list MikroSDK.GenericPointer)

    if (DEFINED LOG_INTERFACE)
        if(${LOG_INTERFACE} STREQUAL "LOG_INTERFACE_UART")
            list(APPEND local_include_list MikroSDK.Driver.UART)
            set(${logInterface} "uart" PARENT_SCOPE)
            list(APPEND local_file_list src/uart/log.c)
            list(APPEND local_file_list src/uart/log_printf_implementation.c)
            list(APPEND local_file_list src/uart/log_printf_implementation.h)
            list(APPEND local_file_list include/uart/log.h)
        elseif(${LOG_INTERFACE} STREQUAL "LOG_INTERFACE_STDOUT")
            set(${logInterface} "std_out" PARENT_SCOPE)
            list(APPEND local_file_list src/std_out/log.c)
            list(APPEND local_file_list include/std_out/log.h)
        endif()
    else()
        list(APPEND local_include_list MikroSDK.Driver.UART)
        set(${logInterface} "uart" PARENT_SCOPE)
        list(APPEND local_file_list src/uart/log.c)
        list(APPEND local_file_list src/uart/log_printf_implementation.c)
        list(APPEND local_file_list src/uart/log_printf_implementation.h)
        list(APPEND local_file_list include/uart/log.h)
    endif()

    set(${list} ${local_include_list} PARENT_SCOPE)
    set(${list} ${local_file_list} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to set core root directory path
#############################################################################
function(mikrosdk_set_compiler_path compiler_path)
    set(_path "")

    if(DEFINED CMAKE_MikroC_COMPILER)
        cmake_path(GET CMAKE_MikroC_COMPILER PARENT_PATH _path)
    else()
        cmake_path(GET CMAKE_C_COMPILER PARENT_PATH _path)
        cmake_path(GET _path PARENT_PATH _path)
        set(_path "${_path}/core/cstdio")
    endif()

    set(${compiler_path} ${_path} PARENT_SCOPE)
endfunction()

#############################################################################
## Function to check if current MCU memory is greater or equal than provided
## values
#############################################################################
function(memory_sdk_test_check enough_memory memory_flash memory_ram)
    if (NOT MCU_FLASH)
        message(FATAL_ERROR ": MCU_FLASH not added to database for ${MCU_NAME}.")
    endif()
    if (NOT MCU_RAM)
        message(FATAL_ERROR ": MCU_RAM not added to database for ${MCU_NAME}.")
    endif()

    set(${enough_memory} "TRUE" PARENT_SCOPE)
    if (${MCU_FLASH} GREATER_EQUAL memory_flash)
        if (${MCU_RAM} GREATER_EQUAL memory_ram)
            set(${enough_memory} "FALSE" PARENT_SCOPE)
        endif()
    endif()
endfunction()

#############################################################################
## Macro to get supported packages
#############################################################################
macro(find_include_package package_list has_module_list package_name)
    find_package(${package_name})
    if(${package_name}\_FOUND)
        list(APPEND ${package_list} ${package_name})
        string(REPLACE . "" module ${package_name})
        list(APPEND ${has_module_list} ${module})
    endif()
endmacro()
