/*
 * Register map of the STM32 Ethernet driver against ST's CMSIS device headers.
 * Each entry: X( name, driver's value, ST's value ). stm32_regmap_ours.c
 * expands the driver side (with the driver's default addresses), and
 * stm32_regmap_st.c the ST side (with the device header); stm32_regmap_main.c
 * compares them. Unused arguments are never expanded, so each side only needs
 * its own names.
 */
#ifndef STM32_REGMAP_H
#define STM32_REGMAP_H

#include <stddef.h>

#define REGMAP_ETH( X ) \
    X( ETH_BASE,            NET_STM32_ETH_BASE,                     ETH_BASE ) \
    X( off_MACCR,           offsetof( stm32_eth_t, MACCR ),         offsetof( ETH_TypeDef, MACCR ) ) \
    X( off_MACFFR,          offsetof( stm32_eth_t, MACFFR ),        offsetof( ETH_TypeDef, MACFFR ) ) \
    X( off_MACMIIAR,        offsetof( stm32_eth_t, MACMIIAR ),      offsetof( ETH_TypeDef, MACMIIAR ) ) \
    X( off_MACMIIDR,        offsetof( stm32_eth_t, MACMIIDR ),      offsetof( ETH_TypeDef, MACMIIDR ) ) \
    X( off_MACFCR,          offsetof( stm32_eth_t, MACFCR ),        offsetof( ETH_TypeDef, MACFCR ) ) \
    X( off_MACSR,           offsetof( stm32_eth_t, MACSR ),         offsetof( ETH_TypeDef, MACSR ) ) \
    X( off_MACIMR,          offsetof( stm32_eth_t, MACIMR ),        offsetof( ETH_TypeDef, MACIMR ) ) \
    X( off_MACA0HR,         offsetof( stm32_eth_t, MACA0HR ),       offsetof( ETH_TypeDef, MACA0HR ) ) \
    X( off_MACA0LR,         offsetof( stm32_eth_t, MACA0LR ),       offsetof( ETH_TypeDef, MACA0LR ) ) \
    X( off_DMABMR,          offsetof( stm32_eth_t, DMABMR ),        offsetof( ETH_TypeDef, DMABMR ) ) \
    X( off_DMATPDR,         offsetof( stm32_eth_t, DMATPDR ),       offsetof( ETH_TypeDef, DMATPDR ) ) \
    X( off_DMARPDR,         offsetof( stm32_eth_t, DMARPDR ),       offsetof( ETH_TypeDef, DMARPDR ) ) \
    X( off_DMARDLAR,        offsetof( stm32_eth_t, DMARDLAR ),      offsetof( ETH_TypeDef, DMARDLAR ) ) \
    X( off_DMATDLAR,        offsetof( stm32_eth_t, DMATDLAR ),      offsetof( ETH_TypeDef, DMATDLAR ) ) \
    X( off_DMASR,           offsetof( stm32_eth_t, DMASR ),         offsetof( ETH_TypeDef, DMASR ) ) \
    X( off_DMAOMR,          offsetof( stm32_eth_t, DMAOMR ),        offsetof( ETH_TypeDef, DMAOMR ) ) \
    X( off_DMAIER,          offsetof( stm32_eth_t, DMAIER ),        offsetof( ETH_TypeDef, DMAIER ) ) \
    X( MACCR_RE,            MACCR_RE,                               ETH_MACCR_RE ) \
    X( MACCR_TE,            MACCR_TE,                               ETH_MACCR_TE ) \
    X( MACCR_DM,            MACCR_DM,                               ETH_MACCR_DM ) \
    X( MACCR_FES,           MACCR_FES,                              ETH_MACCR_FES ) \
    X( MACFFR_PAM,          MACFFR_PAM,                             ETH_MACFFR_PAM ) \
    X( MACMIIAR_MB,         MACMIIAR_MB,                            ETH_MACMIIAR_MB ) \
    X( MACMIIAR_MW,         MACMIIAR_MW,                            ETH_MACMIIAR_MW ) \
    X( MACMIIAR_CR_Pos,     MACMIIAR_CR_POS,                        ETH_MACMIIAR_CR_Pos ) \
    X( MACMIIAR_MR_Pos,     MACMIIAR_MR_POS,                        ETH_MACMIIAR_MR_Pos ) \
    X( MACMIIAR_PA_Pos,     MACMIIAR_PA_POS,                        ETH_MACMIIAR_PA_Pos ) \
    X( DMABMR_SR,           DMABMR_SR,                              ETH_DMABMR_SR ) \
    X( DMABMR_PBL_32,       DMABMR_PBL_32,                          ETH_DMABMR_PBL_32Beat ) \
    X( DMABMR_FB,           DMABMR_FB,                              ETH_DMABMR_FB ) \
    X( DMABMR_RDP_32,       DMABMR_RDP_32,                          ETH_DMABMR_RDP_32Beat ) \
    X( DMABMR_USP,          DMABMR_USP,                             ETH_DMABMR_USP ) \
    X( DMABMR_AAB,          DMABMR_AAB,                             ETH_DMABMR_AAB ) \
    X( DMASR_TBUS,          DMASR_TBUS,                             ETH_DMASR_TBUS ) \
    X( DMASR_RBUS,          DMASR_RBUS,                             ETH_DMASR_RBUS ) \
    X( DMAOMR_SR,           DMAOMR_SR,                              ETH_DMAOMR_SR ) \
    X( DMAOMR_ST,           DMAOMR_ST,                              ETH_DMAOMR_ST ) \
    X( DMAOMR_FTF,          DMAOMR_FTF,                             ETH_DMAOMR_FTF ) \
    X( DMAOMR_TSF,          DMAOMR_TSF,                             ETH_DMAOMR_TSF ) \
    X( DMAOMR_RSF,          DMAOMR_RSF,                             ETH_DMAOMR_RSF )

/* F2/F4/F7: AHB1 clocks, SYSCFG, MCO1 */
#define REGMAP_F2_F7( X ) \
    X( MDC_div42,           0u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_Div42 ) \
    X( MDC_div62,           1u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_Div62 ) \
    X( MDC_div16,           2u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_Div16 ) \
    X( MDC_div26,           3u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_Div26 ) \
    X( RCC_BASE,            NET_STM32_RCC_BASE,                     RCC_BASE ) \
    X( SYSCFG_BASE,         NET_STM32_SYSCFG_BASE,                  SYSCFG_BASE ) \
    X( off_RCC_CFGR,        0x08,                                   offsetof( RCC_TypeDef, CFGR ) ) \
    X( off_RCC_AHB1RSTR,    0x10,                                   offsetof( RCC_TypeDef, AHB1RSTR ) ) \
    X( off_RCC_AHB1ENR,     0x30,                                   offsetof( RCC_TypeDef, AHB1ENR ) ) \
    X( off_RCC_APB2ENR,     0x44,                                   offsetof( RCC_TypeDef, APB2ENR ) ) \
    X( off_SYSCFG_PMC,      0x04,                                   offsetof( SYSCFG_TypeDef, PMC ) ) \
    X( RCC_ETH_CLOCKS,      RCC_ETH_CLOCKS,                         RCC_AHB1ENR_ETHMACEN | RCC_AHB1ENR_ETHMACTXEN | RCC_AHB1ENR_ETHMACRXEN ) \
    X( RCC_ETH_RESET,       RCC_ETH_RESET,                          RCC_AHB1RSTR_ETHMACRST ) \
    X( RCC_SYSCFGEN,        RCC_APB2ENR_SYSCFGEN,                   RCC_APB2ENR_SYSCFGEN ) \
    X( SYSCFG_RMII,         SYSCFG_PMC_MII_RMII_SEL,                SYSCFG_PMC_MII_RMII_SEL ) \
    X( MCO1_mask,           RCC_CFGR_MCO1_MASK,                     RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE ) \
    X( MCO1_PLL,            RCC_CFGR_MCO1_PLL,                      RCC_CFGR_MCO1 ) \
    X( MCO1PRE_div2,        RCC_CFGR_MCO1PRE_DIV( 2 ),              RCC_CFGR_MCO1PRE_2 ) \
    X( MCO1PRE_div3,        RCC_CFGR_MCO1PRE_DIV( 3 ),              RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0 ) \
    X( MCO1PRE_div4,        RCC_CFGR_MCO1PRE_DIV( 4 ),              RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1 ) \
    X( MCO1PRE_div5,        RCC_CFGR_MCO1PRE_DIV( 5 ),              RCC_CFGR_MCO1PRE )

/* F1 (F107): AHB clocks, AFIO, MCO */
#define REGMAP_F1( X ) \
    X( MDC_div42,           0u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_DIV42 ) \
    X( MDC_div16,           2u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_DIV16 ) \
    X( MDC_div26,           3u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_DIV26 ) \
    X( RCC_BASE,            NET_STM32_RCC_BASE,                     RCC_BASE ) \
    X( AFIO_BASE,           NET_STM32_AFIO_BASE,                    AFIO_BASE ) \
    X( off_RCC_CFGR,        0x04,                                   offsetof( RCC_TypeDef, CFGR ) ) \
    X( off_RCC_AHBENR,      0x14,                                   offsetof( RCC_TypeDef, AHBENR ) ) \
    X( off_RCC_AHBRSTR,     0x28,                                   offsetof( RCC_TypeDef, AHBRSTR ) ) \
    X( off_AFIO_MAPR,       0x04,                                   offsetof( AFIO_TypeDef, MAPR ) ) \
    X( RCC_ETH_CLOCKS,      RCC_ETH_CLOCKS,                         RCC_AHBENR_ETHMACEN | RCC_AHBENR_ETHMACTXEN | RCC_AHBENR_ETHMACRXEN ) \
    X( RCC_ETH_RESET,       RCC_ETH_RESET,                          RCC_AHBRSTR_ETHMACRST ) \
    X( AFIO_RMII,           AFIO_MAPR_MII_RMII_SEL,                 AFIO_MAPR_MII_RMII_SEL ) \
    X( MCO_mask,            RCC_CFGR_MCO_MASK,                      RCC_CFGR_MCO ) \
    X( MCO_SYSCLK,          RCC_CFGR_MCO_SYSCLK,                    RCC_CFGR_MCO_SYSCLK )

/* F4/F7: HCLK above 150 MHz */
#define REGMAP_F4_F7( X ) \
    X( MDC_div102,          4u << MACMIIAR_CR_POS,                  ETH_MACMIIAR_CR_Div102 )

#if defined( NET_STM32_F1 )
#define REGMAP( X ) REGMAP_ETH( X ) REGMAP_F1( X )
#elif defined( NET_STM32_F2 )
#define REGMAP( X ) REGMAP_ETH( X ) REGMAP_F2_F7( X )
#else
#define REGMAP( X ) REGMAP_ETH( X ) REGMAP_F2_F7( X ) REGMAP_F4_F7( X )
#endif

#endif
