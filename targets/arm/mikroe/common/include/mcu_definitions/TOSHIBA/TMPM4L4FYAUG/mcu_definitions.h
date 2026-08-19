/*!
 * @file  mcu_definitions.h
 * @brief MCU specific pin and module definitions.
 * @details TMPM4L4FYAUG definitions.
 * @note Source: Toshiba "TMPM4L Group(1) Input/Output Ports" Reference
 *       Manual (PORT-M4L(1)), Rev. 1.1.
 */
#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"

// GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PE7_CN
#define __PF0_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PH0_CN
#define __PH1_CN
#define __PJ0_CN
#define __PJ1_CN
#define __PK0_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN
#define __PORT_J_CN
#define __PORT_K_CN

#define PORT_SIZE (8)
#define PORT_COUNT (10)
// EOF GPIO

// ADC
#ifdef __PF0_CN
#define ADC_A00_PF0
#endif
#ifdef __PG0_CN
#define ADC_A01_PG0
#endif
#ifdef __PG3_CN
#define ADC_A02_PG3
#endif
#ifdef __PG1_CN
#define ADC_A03_PG1
#endif
#ifdef __PG2_CN
#define ADC_A04_PG2
#endif
#ifdef __PH0_CN
#define ADC_A05_PH0
#endif
#ifdef __PH1_CN
#define ADC_A06_PH1
#endif
#define ADC_MODULE_0 1
#define ADC_MODULE_COUNT 1
// EOF ADC

// SPI
#ifdef __PC1_CN
#define SPI0_RXD_PC1
#endif
#ifdef __PC0_CN
#define SPI0_TXD_PC0
#endif
#ifdef __PC2_CN
#define SPI0_SCK_PC2
#endif
#ifdef __PD3_CN
#define SPI1_RXD_PD3
#endif
#ifdef __PD2_CN
#define SPI1_TXD_PD2
#endif
#ifdef __PD1_CN
#define SPI1_SCK_PD1
#endif
#ifdef __PA2_CN
#define SPI2_RXD_PA2
#endif
#ifdef __PA1_CN
#define SPI2_TXD_PA1
#endif
#ifdef __PA0_CN
#define SPI2_SCK_PA0
#endif
#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3
#define SPI_MODULE_COUNT 3
// EOF SPI

// TIM
#ifdef __PD0_CN
#define TIM00_INA0_PD0
#define TIM00_OUTA_PD0
#endif
#ifdef __PD4_CN
#define TIM00_INB0_PD4
#define TIM00_OUTB_PD4
#endif
#ifdef __PC3_CN
#define TIM01_INA0_PC3
#define TIM01_OUTA_PC3
#endif
#ifdef __PA3_CN
#define TIM01_INB0_PA3
#define TIM01_OUTB_PA3
#endif
#ifdef __PC4_CN
#define TIM02_INA0_PC4
#endif
#ifdef __PC5_CN
#define TIM02_OUTA_PC5
#define TIM02_INB0_PC5
#endif
#ifdef __PA2_CN
#define TIM03_INA0_PA2
#endif
#ifdef __PA1_CN
#define TIM03_OUTA_PA1
#define TIM03_INB0_PA1
#endif
#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_COUNT 4
// EOF TIM

// I2C
#ifndef I2C_MODULE_COUNT
#define I2C_MODULE_COUNT 2
#endif

#ifndef I2C_MODULE_0
#define I2C_MODULE_0 1
#endif

#ifndef I2C_MODULE_1
#define I2C_MODULE_1 2
#endif

#ifndef I2C0_SCL_PA0
#define I2C0_SCL_PA0
#endif
#ifndef I2C0_SDA_PA1
#define I2C0_SDA_PA1
#endif

#ifndef I2C1_SCL_PA2
#define I2C1_SCL_PA2
#endif
#ifndef I2C1_SDA_PA3
#define I2C1_SDA_PA3
#endif

#ifndef I2C_CHANNEL_0
#define I2C_CHANNEL_0 0
#endif
#ifndef I2C_CHANNEL_1
#define I2C_CHANNEL_1 1
#endif
// EOF I2C

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_COUNT 4

#define UART0_RX_NVIC   12
#define UART0_TX_NVIC   13

#define UART1_RX_NVIC   15
#define UART1_TX_NVIC   16

#define UART2_RX_NVIC   18
#define UART2_TX_NVIC   19

#define UART3_RX_NVIC   21
#define UART3_TX_NVIC   22

// UART 0 
#ifdef __PC1_CN
#define UART0_RX_PC1
#endif
#ifdef __PC0_CN
#define UART0_TX_PC0
#endif
#ifdef __PC2_CN
#define UART0_CTS_N_PC2
#endif
#ifdef __PD2_CN
#define UART0_TX_PD2_AF1
#define UART0_RX_PD2_AF1
#endif
#ifdef __PD3_CN
#define UART0_TX_PD3_AF1
#define UART0_RX_PD3_AF1
#endif

// UART 1
#ifdef __PD3_CN
#define UART1_RX_PD3
#endif
#ifdef __PD2_CN
#define UART1_TX_PD2
#endif
#ifdef __PD1_CN
#define UART1_CTS_N_PD1
#endif
#ifdef __PA3_CN
#define UART1_TX_PA3_AF1
#define UART1_RX_PA3_AF1
#endif
#ifdef __PA4_CN
#define UART1_TX_PA4_AF1
#define UART1_RX_PA4_AF1
#endif
#ifdef __PA5_CN
#define UART1_TX_PA5_AF1
#define UART1_RX_PA5_AF1
#endif
#ifdef __PA6_CN
#define UART1_TX_PA6_AF1
#define UART1_RX_PA6_AF1
#endif

// UART 2
#ifdef __PA1_CN
#define UART2_RX_PA1
#define UART2_TX_PA1_AF1
#define UART2_RX_PA1_AF1
#endif
#ifdef __PA2_CN
#define UART2_TX_PA2
#define UART2_TX_PA2_AF1
#define UART2_RX_PA2_AF1
#endif
#ifdef __PA0_CN
#define UART2_CTS_N_PA0
#endif
#ifdef __PC2_CN
#define UART2_TX_PC2_AF1
#define UART2_RX_PC2_AF1
#endif
#ifdef __PC3_CN
#define UART2_TX_PC3_AF1
#define UART2_RX_PC3_AF1
#endif

// UART 3
#ifdef __PC0_CN
#define UART3_TX_PC0_AF1
#define UART3_RX_PC0_AF1
#endif
#ifdef __PC1_CN
#define UART3_TX_PC1_AF1
#define UART3_RX_PC1_AF1
#endif
#ifdef __PD4_CN
#define UART3_TX_PD4_AF1
#define UART3_RX_PD4_AF1
#endif
#ifdef __PD5_CN
#define UART3_TX_PD5_AF1
#define UART3_RX_PD5_AF1
#endif

// EOF UART

#endif // _MCU_DEFINITIONS_H_
