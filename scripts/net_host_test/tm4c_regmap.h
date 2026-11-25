/*
 * Register map of the TM4C129 Ethernet driver against TI's headers (hw_emac.h,
 * hw_sysctl.h, hw_gpio.h, hw_memmap.h, pin_map.h), same scheme as
 * stm32_regmap.h: X( name, driver's value, TI's value ).
 */
#ifndef TM4C_REGMAP_H
#define TM4C_REGMAP_H

#define OFF( reg, base ) ( ( uintptr_t )&( reg ) - ( uintptr_t )( base ) )
#define ABS( reg ) ( ( uintptr_t )&( reg ) )
/* pin_map.h: 0x000PSSVV -> port P, PCTL shift SS, value VV */
#define PCTL_FIELD( pinmap ) ( ( ( pinmap ) & 0xFu ) << ( ( ( pinmap ) >> 8 ) & 0xFFu ) )

#define REGMAP( X ) \
    X( EMAC_BASE,           NET_TM4C_EMAC_BASE,                         EMAC0_BASE ) \
    X( off_CFG,             OFF( EMAC_CFG, NET_TM4C_EMAC_BASE ),        EMAC_O_CFG ) \
    X( off_FRAMEFLTR,       OFF( EMAC_FRAMEFLTR, NET_TM4C_EMAC_BASE ),  EMAC_O_FRAMEFLTR ) \
    X( off_MIIADDR,         OFF( EMAC_MIIADDR, NET_TM4C_EMAC_BASE ),    EMAC_O_MIIADDR ) \
    X( off_MIIDATA,         OFF( EMAC_MIIDATA, NET_TM4C_EMAC_BASE ),    EMAC_O_MIIDATA ) \
    X( off_FLOWCTL,         OFF( EMAC_FLOWCTL, NET_TM4C_EMAC_BASE ),    EMAC_O_FLOWCTL ) \
    X( off_ADDR0H,          OFF( EMAC_ADDR0H, NET_TM4C_EMAC_BASE ),     EMAC_O_ADDR0H ) \
    X( off_ADDR0L,          OFF( EMAC_ADDR0L, NET_TM4C_EMAC_BASE ),     EMAC_O_ADDR0L ) \
    X( off_DMABUSMOD,       OFF( EMAC_DMABUSMOD, NET_TM4C_EMAC_BASE ),  EMAC_O_DMABUSMOD ) \
    X( off_TXPOLLD,         OFF( EMAC_TXPOLLD, NET_TM4C_EMAC_BASE ),    EMAC_O_TXPOLLD ) \
    X( off_RXPOLLD,         OFF( EMAC_RXPOLLD, NET_TM4C_EMAC_BASE ),    EMAC_O_RXPOLLD ) \
    X( off_RXDLADDR,        OFF( EMAC_RXDLADDR, NET_TM4C_EMAC_BASE ),   EMAC_O_RXDLADDR ) \
    X( off_TXDLADDR,        OFF( EMAC_TXDLADDR, NET_TM4C_EMAC_BASE ),   EMAC_O_TXDLADDR ) \
    X( off_DMARIS,          OFF( EMAC_DMARIS, NET_TM4C_EMAC_BASE ),     EMAC_O_DMARIS ) \
    X( off_DMAOPMODE,       OFF( EMAC_DMAOPMODE, NET_TM4C_EMAC_BASE ),  EMAC_O_DMAOPMODE ) \
    X( off_DMAIM,           OFF( EMAC_DMAIM, NET_TM4C_EMAC_BASE ),      EMAC_O_DMAIM ) \
    X( off_PC,              OFF( EMAC_PC, NET_TM4C_EMAC_BASE ),         EMAC_O_PC ) \
    X( CFG_RE,              CFG_RE,                                     EMAC_CFG_RE ) \
    X( CFG_TE,              CFG_TE,                                     EMAC_CFG_TE ) \
    X( CFG_DUPM,            CFG_DUPM,                                   EMAC_CFG_DUPM ) \
    X( CFG_FES,             CFG_FES,                                    EMAC_CFG_FES ) \
    X( CFG_PS,              CFG_PS,                                     EMAC_CFG_PS ) \
    X( FRAMEFLTR_PM,        FRAMEFLTR_PM,                               EMAC_FRAMEFLTR_PM ) \
    X( MIIADDR_MIIB,        MIIADDR_MIIB,                               EMAC_MIIADDR_MIIB ) \
    X( MIIADDR_MIIW,        MIIADDR_MIIW,                               EMAC_MIIADDR_MIIW ) \
    X( MIIADDR_CR_mask,     0xFUL << MIIADDR_CR_POS,                    EMAC_MIIADDR_CR_M ) \
    X( MIIADDR_CR_60_100,   0UL << MIIADDR_CR_POS,                      EMAC_MIIADDR_CR_60_100 ) \
    X( MIIADDR_CR_100_150,  1UL << MIIADDR_CR_POS,                      EMAC_MIIADDR_CR_100_150 ) \
    X( MIIADDR_CR_20_35,    2UL << MIIADDR_CR_POS,                      EMAC_MIIADDR_CR_20_35 ) \
    X( MIIADDR_CR_35_60,    3UL << MIIADDR_CR_POS,                      EMAC_MIIADDR_CR_35_60 ) \
    X( MIIADDR_MII_POS,     MIIADDR_MII_POS,                            EMAC_MIIADDR_MII_S ) \
    X( MIIADDR_PLA_POS,     MIIADDR_PLA_POS,                            EMAC_MIIADDR_PLA_S ) \
    X( DMABUSMOD_SWR,       DMABUSMOD_SWR,                              EMAC_DMABUSMOD_SWR ) \
    X( DMABUSMOD_PBL_32,    DMABUSMOD_PBL_32,                           32UL << EMAC_DMABUSMOD_PBL_S ) \
    X( DMABUSMOD_FB,        DMABUSMOD_FB,                               EMAC_DMABUSMOD_FB ) \
    X( DMABUSMOD_RPBL_32,   DMABUSMOD_RPBL_32,                          32UL << EMAC_DMABUSMOD_RPBL_S ) \
    X( DMABUSMOD_USP,       DMABUSMOD_USP,                              EMAC_DMABUSMOD_USP ) \
    X( DMABUSMOD_AAL,       DMABUSMOD_AAL,                              EMAC_DMABUSMOD_AAL ) \
    X( DMARIS_TU,           DMARIS_TU,                                  EMAC_DMARIS_TU ) \
    X( DMARIS_RU,           DMARIS_RU,                                  EMAC_DMARIS_RU ) \
    X( DMAOPMODE_SR,        DMAOPMODE_SR,                               EMAC_DMAOPMODE_SR ) \
    X( DMAOPMODE_ST,        DMAOPMODE_ST,                               EMAC_DMAOPMODE_ST ) \
    X( DMAOPMODE_FTF,       DMAOPMODE_FTF,                              EMAC_DMAOPMODE_FTF ) \
    X( DMAOPMODE_TSF,       DMAOPMODE_TSF,                              EMAC_DMAOPMODE_TSF ) \
    X( DMAOPMODE_RSF,       DMAOPMODE_RSF,                              EMAC_DMAOPMODE_RSF ) \
    X( PC_ANEN,             PC_ANEN,                                    EMAC_PC_ANEN ) \
    X( PC_ANMODE_ALL,       PC_ANMODE_ALL,                              EMAC_PC_ANMODE_M ) \
    X( PC_MDIXEN,           PC_MDIXEN,                                  EMAC_PC_MDIXEN ) \
    X( SYSCTL_SREPHY,       ABS( SYSCTL_SREPHY ),                       SYSCTL_SREPHY ) \
    X( SYSCTL_SREMAC,       ABS( SYSCTL_SREMAC ),                       SYSCTL_SREMAC ) \
    X( SYSCTL_RCGCGPIO,     ABS( SYSCTL_RCGCGPIO ),                     SYSCTL_RCGCGPIO ) \
    X( SYSCTL_RCGCEPHY,     ABS( SYSCTL_RCGCEPHY ),                     SYSCTL_RCGCEPHY ) \
    X( SYSCTL_RCGCEMAC,     ABS( SYSCTL_RCGCEMAC ),                     SYSCTL_RCGCEMAC ) \
    X( SYSCTL_PCEPHY,       ABS( SYSCTL_PCEPHY ),                       SYSCTL_PCEPHY ) \
    X( SYSCTL_PCEMAC,       ABS( SYSCTL_PCEMAC ),                       SYSCTL_PCEMAC ) \
    X( SYSCTL_PRGPIO,       ABS( SYSCTL_PRGPIO ),                       SYSCTL_PRGPIO ) \
    X( SYSCTL_PREPHY,       ABS( SYSCTL_PREPHY ),                       SYSCTL_PREPHY ) \
    X( SYSCTL_PREMAC,       ABS( SYSCTL_PREMAC ),                       SYSCTL_PREMAC ) \
    X( SYSCTL_EMAC0,        SYSCTL_EMAC0,                               SYSCTL_RCGCEMAC_R0 | SYSCTL_PREMAC_R0 | SYSCTL_SREMAC_R0 | SYSCTL_PCEMAC_P0 | SYSCTL_RCGCEPHY_R0 | SYSCTL_PREPHY_R0 | SYSCTL_SREPHY_R0 | SYSCTL_PCEPHY_P0 ) \
    X( SYSCTL_GPIOK,        SYSCTL_GPIOK,                               SYSCTL_RCGCGPIO_R9 | SYSCTL_PRGPIO_R9 ) \
    X( GPIOK_BASE,          NET_TM4C_GPIOK_BASE,                        GPIO_PORTK_BASE ) \
    X( off_GPIO_AFSEL,      OFF( GPIOK_AFSEL, NET_TM4C_GPIOK_BASE ),    GPIO_O_AFSEL ) \
    X( off_GPIO_DEN,        OFF( GPIOK_DEN, NET_TM4C_GPIOK_BASE ),      GPIO_O_DEN ) \
    X( off_GPIO_PCTL,       OFF( GPIOK_PCTL, NET_TM4C_GPIOK_BASE ),     GPIO_O_PCTL ) \
    X( PCTL_PK4_EN0LED0,    PCTL_EN0LED << 16,                          PCTL_FIELD( GPIO_PK4_EN0LED0 ) ) \
    X( PCTL_PK5_EN0LED2,    PCTL_EN0LED << 20,                          PCTL_FIELD( GPIO_PK5_EN0LED2 ) ) \
    X( PCTL_PK6_EN0LED1,    PCTL_EN0LED << 24,                          PCTL_FIELD( GPIO_PK6_EN0LED1 ) )

#endif
