INSERT INTO Devices (
    def_file,family_uid,flash,
    icon,
    max_speed,name,ram,sdk_config,
    necto_config,uid,vendor,compiler_flags,
    linker_flags,tft_socket,sdk_support
)
VALUES (
    "STM32F746VG.json","STM32","1024",
    "images/mcu_cards/card-v7-easymx-pro-v7-stm32-stm32f746vgt6.png",
    "216.000",
    "EasyMx PRO v7 for STM32 MCUcard with STM32F746VGT6",
    "327680",
    '{"MCU_NAME":"STM32F746VG","CORE_NAME":"M7","_MSDK_HAL_LOW_LEVEL_TARGET_":"mikroe","_MSDK_ETH_PHY_CHIP_":"&lan8720PhyDriver","_MSDK_MCU_CARD_NAME_":"EASYMX_PRO_V7_FOR_STM32_MCUCARD_WITH_STM32F746VGT6"}',
    NULL,
    "EASYMX_PRO_V7_FOR_STM32_MCUCARD_WITH_STM32F746VGT6",
    "STMicroelectronics",
    NULL,NULL,1,1,NULL
);
