/*!
 * @file   mcu_reg_addresses.h
 * @brief  MCU specific register address definitions.
 * @details TMPM4L4FYAUG register address definitions.
 * @note   Source: Toshiba TMPM4L Reference Manuals & Memory Map.
 */
#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// TMPM4L4FYAUG REGISTER DEFINITIONS

//GPIO port base addresses
#define PA_BASE_ADDR    0x40080000UL
#define PB_BASE_ADDR    0x40080100UL
#define PC_BASE_ADDR    0x40080200UL
#define PD_BASE_ADDR    0x40080300UL
#define PE_BASE_ADDR    0x40080400UL
#define PF_BASE_ADDR    0x40080500UL
#define PG_BASE_ADDR    0x40080600UL
#define PH_BASE_ADDR    0x40080700UL
#define PJ_BASE_ADDR    0x40080800UL
#define PK_BASE_ADDR    0x40080900UL

//GPIO register offsets
#define GPIO_DATA_OFFSET    0x0000UL
#define GPIO_CR_OFFSET      0x0004UL
#define GPIO_FR1_OFFSET     0x0008UL
#define GPIO_FR2_OFFSET     0x000CUL
#define GPIO_FR3_OFFSET     0x0010UL
#define GPIO_FR4_OFFSET     0x0014UL
#define GPIO_FR5_OFFSET     0x0018UL
#define GPIO_FR6_OFFSET     0x001CUL
#define GPIO_OD_OFFSET      0x0028UL
#define GPIO_PUP_OFFSET     0x002CUL
#define GPIO_PDN_OFFSET     0x0030UL
#define GPIO_IE_OFFSET      0x0038UL

//UART Base Addresses
#define UART0_BASE_ADDR     0x400E0000UL
#define UART1_BASE_ADDR     0x400E0100UL
#define UART2_BASE_ADDR     0x400E0200UL
#define UART3_BASE_ADDR     0x400E0300UL

//SPI Base Addresses
#define SPI0_BASE_ADDR      0x400D0000UL
#define SPI1_BASE_ADDR      0x400D0100UL
#define SPI2_BASE_ADDR      0x400D0200UL

//I2C Base Addresses
#define I2C0_BASE_ADDR      0x400E2000UL
#define I2C1_BASE_ADDR      0x400E2100UL

//TIM Base Addresses
#define TIM0_BASE_ADDR      0x400C0000UL
#define TIM1_BASE_ADDR      0x400C0100UL
#define TIM2_BASE_ADDR      0x400C0200UL
#define TIM3_BASE_ADDR      0x400C0300UL

//ADC Base Address
#define ADC0_BASE_ADDR      0x400B0000UL

// EOF REGISTER DEFINITIONS
#endif // _MCU_REG_ADDRESSES_H_
