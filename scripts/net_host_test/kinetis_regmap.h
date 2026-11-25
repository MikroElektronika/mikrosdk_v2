/*
 * Register map of the Kinetis ENET driver against NXP's device headers, same
 * scheme as stm32_regmap.h: X( name, driver's value, NXP's value ), each side
 * compiled on its own (kinetis_regmap_ours.c, kinetis_regmap_nxp.c).
 */
#ifndef KINETIS_REGMAP_H
#define KINETIS_REGMAP_H

#include <stddef.h>

#define OFF( reg, base ) ( ( uintptr_t )&( reg ) - ( uintptr_t )( base ) )

#define REGMAP( X ) \
    X( ENET_BASE,           NET_KINETIS_ENET_BASE,                  ENET_BASE ) \
    X( off_EIR,             OFF( ENET_EIR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, EIR ) ) \
    X( off_EIMR,            OFF( ENET_EIMR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, EIMR ) ) \
    X( off_RDAR,            OFF( ENET_RDAR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, RDAR ) ) \
    X( off_TDAR,            OFF( ENET_TDAR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, TDAR ) ) \
    X( off_ECR,             OFF( ENET_ECR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, ECR ) ) \
    X( off_MMFR,            OFF( ENET_MMFR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, MMFR ) ) \
    X( off_MSCR,            OFF( ENET_MSCR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, MSCR ) ) \
    X( off_RCR,             OFF( ENET_RCR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, RCR ) ) \
    X( off_TCR,             OFF( ENET_TCR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, TCR ) ) \
    X( off_PALR,            OFF( ENET_PALR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, PALR ) ) \
    X( off_PAUR,            OFF( ENET_PAUR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, PAUR ) ) \
    X( off_IAUR,            OFF( ENET_IAUR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, IAUR ) ) \
    X( off_IALR,            OFF( ENET_IALR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, IALR ) ) \
    X( off_GAUR,            OFF( ENET_GAUR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, GAUR ) ) \
    X( off_GALR,            OFF( ENET_GALR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, GALR ) ) \
    X( off_TFWR,            OFF( ENET_TFWR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, TFWR ) ) \
    X( off_RDSR,            OFF( ENET_RDSR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, RDSR ) ) \
    X( off_TDSR,            OFF( ENET_TDSR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, TDSR ) ) \
    X( off_MRBR,            OFF( ENET_MRBR, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, MRBR ) ) \
    X( off_RSFL,            OFF( ENET_RSFL, NET_KINETIS_ENET_BASE ), offsetof( ENET_Type, RSFL ) ) \
    X( ECR_RESET,           ECR_RESET,                              ENET_ECR_RESET_MASK ) \
    X( ECR_ETHEREN,         ECR_ETHEREN,                            ENET_ECR_ETHEREN_MASK ) \
    X( ECR_DBSWP,           ECR_DBSWP,                              ENET_ECR_DBSWP_MASK ) \
    X( EIR_MII,             EIR_MII,                                ENET_EIR_MII_MASK ) \
    X( MMFR_ST,             MMFR_ST,                                ENET_MMFR_ST( 1 ) ) \
    X( MMFR_OP_WRITE,       MMFR_OP_WRITE,                          ENET_MMFR_OP( 1 ) ) \
    X( MMFR_OP_READ,        MMFR_OP_READ,                           ENET_MMFR_OP( 2 ) ) \
    X( MMFR_PA_POS,         MMFR_PA_POS,                            ENET_MMFR_PA_SHIFT ) \
    X( MMFR_RA_POS,         MMFR_RA_POS,                            ENET_MMFR_RA_SHIFT ) \
    X( MMFR_TA,             MMFR_TA,                                ENET_MMFR_TA( 2 ) ) \
    X( MSCR_MII_SPEED_POS,  MSCR_MII_SPEED_POS,                     ENET_MSCR_MII_SPEED_SHIFT ) \
    X( MSCR_HOLDTIME_POS,   MSCR_HOLDTIME_POS,                      ENET_MSCR_HOLDTIME_SHIFT ) \
    X( RCR_DRT,             RCR_DRT,                                ENET_RCR_DRT_MASK ) \
    X( RCR_MII_MODE,        RCR_MII_MODE,                           ENET_RCR_MII_MODE_MASK ) \
    X( RCR_RMII_MODE,       RCR_RMII_MODE,                          ENET_RCR_RMII_MODE_MASK ) \
    X( RCR_RMII_10T,        RCR_RMII_10T,                           ENET_RCR_RMII_10T_MASK ) \
    X( RCR_CRCFWD,          RCR_CRCFWD,                             ENET_RCR_CRCFWD_MASK ) \
    X( RCR_MAX_FL_POS,      RCR_MAX_FL_POS,                         ENET_RCR_MAX_FL_SHIFT ) \
    X( TCR_FDEN,            TCR_FDEN,                               ENET_TCR_FDEN_MASK ) \
    X( TFWR_STRFWD,         TFWR_STRFWD,                            ENET_TFWR_STRFWD_MASK ) \
    X( RDAR_ACTIVE,         DAR_ACTIVE,                             ENET_RDAR_RDAR_MASK ) \
    X( TDAR_ACTIVE,         DAR_ACTIVE,                             ENET_TDAR_TDAR_MASK ) \
    X( SIM_BASE,            NET_KINETIS_SIM_BASE,                   SIM_BASE ) \
    X( off_SIM_SOPT2,       OFF( SIM_SOPT2, NET_KINETIS_SIM_BASE ), offsetof( SIM_Type, SOPT2 ) ) \
    X( off_SIM_SCGC2,       OFF( SIM_SCGC2, NET_KINETIS_SIM_BASE ), offsetof( SIM_Type, SCGC2 ) ) \
    X( off_SIM_SCGC5,       OFF( SIM_SCGC5, NET_KINETIS_SIM_BASE ), offsetof( SIM_Type, SCGC5 ) ) \
    X( SOPT2_TIMESRC,       SIM_SOPT2_TIMESRC,                      SIM_SOPT2_TIMESRC_MASK ) \
    X( SOPT2_RMIISRC,       SIM_SOPT2_RMIISRC,                      SIM_SOPT2_RMIISRC_MASK ) \
    X( SCGC2_ENET,          SIM_SCGC2_ENET,                         SIM_SCGC2_ENET_MASK ) \
    X( SCGC5_PORTA,         SIM_SCGC5_PORTA,                        SIM_SCGC5_PORTA_MASK ) \
    X( SCGC5_PORTB,         SIM_SCGC5_PORTB,                        SIM_SCGC5_PORTB_MASK ) \
    X( SCGC5_PORTE,         SIM_SCGC5_PORTE,                        SIM_SCGC5_PORTE_MASK ) \
    X( PORTA_BASE,          NET_KINETIS_PORTA_BASE,                 PORTA_BASE ) \
    X( PORTB_BASE,          NET_KINETIS_PORTB_BASE,                 PORTB_BASE ) \
    X( PORTE_BASE,          NET_KINETIS_PORTE_BASE,                 PORTE_BASE ) \
    X( off_PCR5,            OFF( PCR( NET_KINETIS_PORTA_BASE, 5 ), NET_KINETIS_PORTA_BASE ), offsetof( PORT_Type, PCR[ 5 ] ) ) \
    X( PCR_MUX4,            PCR_MUX( 4 ),                           PORT_PCR_MUX( 4 ) ) \
    X( PCR_PE,              PCR_PE,                                 PORT_PCR_PE_MASK ) \
    X( PCR_PS,              PCR_PS,                                 PORT_PCR_PS_MASK ) \
    X( MPU_BASE,            NET_KINETIS_MPU_BASE,                   SYSMPU_BASE ) \
    X( off_MPU_CESR,        OFF( MPU_CESR, NET_KINETIS_MPU_BASE ),  offsetof( SYSMPU_Type, CESR ) ) \
    X( MPU_CESR_VLD,        MPU_CESR_VLD,                           SYSMPU_CESR_VLD_MASK )

#endif
