## ./bsp/board/CMakeLists.txt
##Default values
set(MCU_CARD  TRUE)
set(DIP_SOCKET  FALSE)
set(MIKROBUS  TRUE)
set(SHIELD FALSE)
set(IS_CUSTOM_BOARD FALSE)
set(PIM_SOCKET FALSE)

#CUSTOM BOARD SETTING
foreach(__CUSTOM_INCLUDE_FILE__ IN LISTS __MSDK_CUSTOM_BOARD_INCLUDES__)
    include("${__CUSTOM_INCLUDE_FILE__}")
endforeach()

## DEVELOPMENT BOARDS
if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_UNI_DS_V8")
    set(BOARD_PATH   "include/boards/board_uni_ds_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_ARM_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_arm_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_STM32_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_stm32_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_TIVA_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_tiva_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_KINETIS_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_kinetis_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_PRO_V8")
    set(BOARD_PATH   "include/boards/board_easypic_pro_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8")
    set(BOARD_PATH   "include/boards/board_easypic_v8")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "EASY24_33_V6")
    set(BOARD_PATH   "include/boards/board_easy24_33_v6")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_PIC32_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_pic32_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FUSION_FOR_PIC_V8")
    set(BOARD_PATH   "include/boards/board_fusion_for_pic_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYMX_PRO_V7_FOR_STM32")
    set(BOARD_PATH   "include/boards/board_easymx_pro_v7_for_stm32")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYMX_PRO_V7_FOR_TIVA")
    set(BOARD_PATH   "include/boards/board_easymx_pro_v7_for_tiva")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_PRO_V7")
    set(BOARD_PATH   "include/boards/board_easypic_pro_v7")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V7")
    set(BOARD_PATH   "include/boards/board_easypic_v7")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_FUSION_V7")
    set(BOARD_PATH   "include/boards/board_easypic_fusion_v7")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_HEXIWEAR_WORKSTATION")
    set(BOARD_PATH   "include/boards/board_hexiwear_workstation")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_HEXIWEAR_BATTERY_PACK")
    set(BOARD_PATH   "include/boards/board_hexiwear_battery_pack")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_HEXIWEAR_DOCKING_STATION")
    set(BOARD_PATH   "include/boards/board_hexiwear_docking_station")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_PICPLC16_V7")
    set(BOARD_PATH   "include/boards/board_picplc16_v7")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_FLOWPAW")
    set(BOARD_PATH   "include/boards/board_flowpaw")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_QUAIL")
    set(BOARD_PATH   "include/boards/board_quail")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_PRO_V8")
    set(BOARD_PATH   "include/boards/board_easyavr_pro_v8")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_V7")
    set(BOARD_PATH   "include/boards/board_easyavr_v7")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC30")
    set(BOARD_PATH   "include/boards/board_easypic_v8_for_dspic30")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC24_33")
    set(BOARD_PATH   "include/boards/board_easypic_v8_for_dspic24_33")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V7_FOR_DSPIC30")
    set(BOARD_PATH   "include/boards/board_easypic_v7_for_dspic30")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EXPLORER_16_32")
    set(BOARD_PATH   "include/boards/board_explorer16_32")
    set(PIM_SOCKET TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_NANO_WITH_PIC18F57Q43")
    set(BOARD_PATH   "include/boards/board_curiosity_nano_with_pic18f57q43")
    set(MCU_CARD  FALSE)
    set(SHIELD  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_NANO_WITH_PIC18F47Q10")
    set(BOARD_PATH   "include/boards/board_curiosity_nano_with_pic18f47q10")
    set(MCU_CARD  FALSE)
    set(SHIELD  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_NANO_WITH_PIC18F47K42")
    set(BOARD_PATH   "include/boards/board_curiosity_nano_with_pic18f47k42")
    set(MCU_CARD  FALSE)
    set(SHIELD  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "KIT_DISCOVERY_WITH_STM32F407VG_MCU")
    set(BOARD_PATH   "include/boards/board_discovery_with_stm32f407vg")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "KIT_DISCOVERY_WITH_STM32F303VC_MCU")
    set(BOARD_PATH   "include/boards/board_discovery_with_stm32f303vc")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32F722ZE")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32f722ze")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32H743ZI")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32h743zi")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32F413ZH")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32f413zh")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32F446ZE")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32f446ze")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32L496ZG")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32l496zg")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32L4R5ZI")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32l4r5zi")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_144_WITH_STM32F412ZG")
    set(BOARD_PATH   "include/boards/board_nucleo_144_with_stm32f412zg")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32F401RE")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32f401re")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32L433RC_P")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32l433rc_p")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32L073RZ")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32l073rz")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32L476RG")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32l476rg")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32F070RB")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32f070rb")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32F091RC")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32f091rc")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_NUCLEO_64_WITH_STM32F030R8")
    set(BOARD_PATH   "include/boards/board_nucleo_64_with_stm32f030r8")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

## CLICKER BOARDS
if(${_MSDK_BOARD_NAME_} STREQUAL "STM32_M4_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_stm32_m4")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_STM32")
    set(BOARD_PATH   "include/boards/clicker_2_for_stm32")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_4_FOR_STM32")
    set(BOARD_PATH   "include/boards/clicker_4_for_stm32")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_4_FOR_STM32F4")
    set(BOARD_PATH   "include/boards/clicker_4_for_stm32f4")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_4_FOR_PIC18F")
    set(BOARD_PATH   "include/boards/clicker_4_for_pic18f")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "UNI_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_uni")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "PIC_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_pic")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_PIC18FK")
    set(BOARD_PATH   "include/boards/clicker_2_for_pic18fk")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_PIC18FJ")
    set(BOARD_PATH   "include/boards/clicker_2_for_pic18fj")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "PIC32MX_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_pic32mx")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "PIC32MZ_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_pic32mz")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "6LOWPAN_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_6lowpan")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_PIC32MX")
    set(BOARD_PATH   "include/boards/clicker_2_for_pic32mx")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_PIC32MZ")
    set(BOARD_PATH   "include/boards/clicker_2_for_pic32mz")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "KINETIS_CLICKER")
    set(BOARD_PATH   "include/boards/clicker_kinetis")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_KINETIS")
    set(BOARD_PATH   "include/boards/clicker_2_for_kinetis")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_DSPIC33")
    set(BOARD_PATH   "include/boards/clicker_2_for_dspic33")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "CLICKER_2_FOR_PIC24")
    set(BOARD_PATH   "include/boards/clicker_2_for_pic24")
    set(MCU_CARD  FALSE)
endif()

## MIKROMEDIA BOARDS
if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32F2CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32f2_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32F2CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32f2_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32F4CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32f4_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32F4RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32f4_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORSTM32F4CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_stm32f4_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F2CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f2_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F4CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f4_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F4CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f4_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F4RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f4_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F4RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f4_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F2RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f2_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F7CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f7_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORSTM32F7RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_stm32f7_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F4CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f4_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F4CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f4_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F4RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f4_resistive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F7CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f7_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F7CAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f7_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F7RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f7_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORSTM32F7RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_stm32f7_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAPLUSFORSTM32")
    set(BOARD_PATH   "include/boards/mikromedia_plus_stm32")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAPLUSFORSTM32F7")
    set(BOARD_PATH   "include/boards/mikromedia_plus_stm32f7")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPICCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPICRESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPICCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic_capacitive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPICRESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPIC32MZCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic32mz_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORPIC32MZCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_pic32mz_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORPIC32MZCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_pic32mz_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORPIC32MZCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_pic32mz_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORPIC32MZCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_pic32mz_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORPIC32MZCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_pic32mz_capacitive_fpi")
    set(MCU_CARD  FALSE)
    set(MIKROBUS  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAPLUSFORPIC32MX7")
    set(BOARD_PATH   "include/boards/mikromedia_plus_pic32mx7")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORKINETISCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_3_kinetis_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA3FORKINETISCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_3_kinetis_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORKINETISCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_kinetis_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORKINETISCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_kinetis_capacitive_fpi")
    set(MCU_CARD  FALSE)
    set(MIKROBUS  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORKINETISRESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_4_kinetis_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA4FORKINETISRESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_4_kinetis_resistive_fpi")
    set(MCU_CARD  FALSE)
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORKINETISCAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_kinetis_capacitive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORKINETISRESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_5_kinetis_resistive")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORKINETISCAPACITIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_kinetis_capacitive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA5FORKINETISRESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_5_kinetis_resistive_fpi")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA7FORSTM32F4")
    set(BOARD_PATH   "include/boards/mikromedia_7_stm32f4")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA7FORSTM32F7")
    set(BOARD_PATH   "include/boards/mikromedia_7_stm32f7")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA7CAPACITIVE")
    set(BOARD_PATH   "include/boards/mikromedia_7_capacitive")
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA7RESISTIVE")
    set(BOARD_PATH   "include/boards/mikromedia_7_resistive")
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIA7RESISTIVEFPI")
    set(BOARD_PATH   "include/boards/mikromedia_7_resistive_fpi")
    set(SHIELD FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORPIC32")
    set(BOARD_PATH   "include/boards/mikromedia_for_pic32")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORXMEGA")
    set(BOARD_PATH   "include/boards/mikromedia_for_xmega")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORPIC18FJ")
    set(BOARD_PATH   "include/boards/mikromedia_for_pic18fj")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORPIC18FK")
    set(BOARD_PATH   "include/boards/mikromedia_for_pic18fk")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORTIVACSERIES")
    set(BOARD_PATH   "include/boards/mikromedia_for_tiva")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORSTM32F3F4")
    set(BOARD_PATH   "include/boards/mikromedia_for_stm32_f3_f4")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORDSPIC33")
    set(BOARD_PATH   "include/boards/mikromedia_for_dspic33")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORDSPIC33EP")
    set(BOARD_PATH   "include/boards/mikromedia_for_dspic33ep")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORPIC24")
    set(BOARD_PATH   "include/boards/mikromedia_for_pic24")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "MIKROMEDIAFORPIC24EP")
    set(BOARD_PATH   "include/boards/mikromedia_for_pic24ep")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

## FLIP AND CLICK BOARDS
if(${_MSDK_BOARD_NAME_} STREQUAL "FLIP_AND_CLICK_PIC32MZ")
    set(BOARD_PATH   "include/boards/flip_and_click_pic32mz")
    set(MCU_CARD  FALSE)
endif()

## GENERIC BOARD
if(${_MSDK_BOARD_NAME_} MATCHES "GENERIC(.+)BOARD")
    set(BOARD_PATH   "include/boards/board_generic")
    set(MCU_CARD  FALSE)
    set(MIKROBUS  FALSE)
endif()

## NON MIKROE BOARDS
if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_PIC24FJ256GA7")
    set(BOARD_PATH   "include/boards/board_curiosity_pic24fj256ga7")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_PIC32MZ_EF")
    set(BOARD_PATH   "include/boards/board_curiosity_pic32_mz_ef")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_CURIOSITY_HPC")
    set(BOARD_PATH   "include/boards/board_curiosity_hpc")
    set(MCU_CARD  FALSE)
    set(DIP_SOCKET  TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_MICROMOD_MIKROBUS_CARRIER")
    set(BOARD_PATH   "include/boards/board_micromod_mikrobus_carrier")
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "KIT_DISCOVERY_WITH_STM32L4R9AI_MCU")
    set(BOARD_PATH   "include/boards/kit_discovery_with_stm32l4r9ai_mcu")
    set(MCU_CARD  FALSE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_ARDUINO_UNO_REV3")
    set(BOARD_PATH   "include/boards/board_arduino_uno_rev3")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(${_MSDK_BOARD_NAME_} STREQUAL "BOARD_ARDUINO_MEGA_2560_REV3")
    set(BOARD_PATH   "include/boards/board_arduino_mega_2560_rev3")
    set(MCU_CARD  FALSE)
    set(SHIELD TRUE)
endif()

if(MCU_CARD)
    string(TOLOWER ${_MSDK_MCU_CARD_NAME_} MSDK_FILTERED_MCU_CARD)
    if(${_MSDK_MCU_CARD_NAME_} STREQUAL "")
        set(BOARD_PATH   "include/boards/board_generic")
        set(MCU_CARD  FALSE)
        set(MIKROBUS  FALSE)
    endif()
elseif(DIP_SOCKET)
    string(TOLOWER ${_MSDK_DIP_SOCKET_TYPE_} MSDK_FILTERED_DIP_SOCKET_TYPE)
    if(${_MSDK_DIP_SOCKET_TYPE_} STREQUAL "")
        set(BOARD_PATH   "include/boards/board_generic")
        set(MCU_CARD  FALSE)
        set(DIP_SOCKET  FALSE)
        set(MIKROBUS  FALSE)
    endif()
endif()

if (NOT DEFINED MSDK_SHIELD)
    set(MSDK_SHIELD "false")
endif()

if (SHIELD)
    string(TOLOWER ${_MSDK_SHIELD_} SHIELD_PATH)
else()
    set(SHIELD_PATH "SHIELD_WRONG_PATH")
endif()

if (MCU_CARD)
    set(MCU_CARD_PATH  ${MSDK_FILTERED_MCU_CARD})
else()
    set(MCU_CARD_PATH  "MCU_CARD_WRONG_PATH")
endif()

if (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "(^dip((14$)|(18$)|(20$)|(28$)|(40$)))")
    set(dip_socket_check TRUE)
else()
    set(dip_socket_check FALSE)
endif()

if ((DIP_SOCKET) AND (dip_socket_check))
    set(BOARD_DIP_SOCKET_PATH  ${MSDK_FILTERED_DIP_SOCKET_TYPE})
elseif((DIP_SOCKET) AND (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip.*"))
    set(BOARD_DIP_SOCKET_PATH  "WRONG_DIP_SELECTED")
elseif((DIP_SOCKET) AND NOT (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip.*"))
    set(BOARD_DIP_SOCKET_PATH  "NO_DIP_SELECTED")
endif()

set(HEADERS_LIST ${BOARD_PATH}/board.h)
set(INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH})

if (MCU_CARD)
        list(APPEND HEADERS_LIST include/mcu_cards/${MCU_CARD_PATH}/mcu_card.h)
        list(APPEND INCLUDE_HEADERS_PATH_LIST include/mcu_cards/${MCU_CARD_PATH})
endif()
if(DIP_SOCKET)
        # TODO
        # Add appropriate dip_socket header files per MCU.
        # At the moment all non AVR and dsPIC MCUs take one socket header file.
        # e.g. if DIP40 socket on the board has both A and B sockets, socket B will be taken by default.
        list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH})
        if ( (${MSDK_FILTERED_DIP_SOCKET_TYPE} MATCHES "^dip[24]0$") AND (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYAVR_V7") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC30") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V7_FOR_DSPIC30") OR (${_MSDK_BOARD_NAME_} STREQUAL "BOARD_EASYPIC_V8_FOR_DSPIC24_33"))
            list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/dip_sockets)
            if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip20")
                set (BOARD_DIP_SOCKET_PATH dip20b)
                list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip20b/dip_socket.h)
            endif()
            if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip28")
                set (BOARD_DIP_SOCKET_PATH dip28c)
                list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip28c/dip_socket.h)
            endif()
            if (${MSDK_FILTERED_DIP_SOCKET_TYPE} STREQUAL "dip40")
                set (BOARD_DIP_SOCKET_PATH dip40b)
                list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/dip40b/dip_socket.h)
            endif()
        else()
            list(APPEND HEADERS_LIST ${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH}/dip_socket.h)
        endif()
endif()

if (PIM_SOCKET)
    list(APPEND INCLUDE_HEADERS_PATH_LIST ${BOARD_PATH}/pim_socket)
    list(APPEND HEADERS_LIST ${BOARD_PATH}/pim_socket/pim_socket.h)
endif()

if (SHIELD)
    list(APPEND HEADERS_LIST include/shields/${SHIELD_PATH}/shield.h)
endif()

mikrosdk_add_interface_library(lib_board MikroSDK.Board
    ${HEADERS_LIST}
)

set(BOARD_PATH_INTERFACE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/")
if(IS_CUSTOM_BOARD)
    set(BOARD_PATH_INTERFACE_INCLUDE "")
endif()

target_include_directories(lib_board
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${BOARD_PATH_INTERFACE_INCLUDE}${BOARD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/shields/${SHIELD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcu_cards/${MCU_CARD_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${BOARD_PATH}/dip_sockets/${BOARD_DIP_SOCKET_PATH}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${BOARD_PATH}/pim_socket>
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/board>
)

target_link_libraries(lib_board INTERFACE
    MikroC.Core
    MikroSDK.HalInterface
    MikroSDK.MikroBus
)

mikrosdk_install(MikroSDK.Board)
install_headers(${CMAKE_INSTALL_PREFIX}/include/board MikroSDK.Board ${HEADERS_LIST})
