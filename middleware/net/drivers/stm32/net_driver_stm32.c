/****************************************************************************
**
** Copyright ( C ) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

/*!
 * @file net_driver_stm32.c
 * @brief STM32F1/F2/F4/F7 Ethernet MAC driver for the mikroSDK network layer.
 * @details Written from the reference manuals RM0008 (F107), RM0033 (F2),
 * RM0090 (F4) and RM0385 / RM0410 (F7): the four families have the same MAC
 * and DMA with "normal" descriptors. The register map below is checked
 * against ST's CMSIS device headers by scripts/net_host_test (test_stm32).
 *
 * The family comes from the build: NET_STM32_F1, NET_STM32_F2, NET_STM32_F4 or
 * NET_STM32_F7; NET_STM32_TX_PG selects PG11/PG13/PG14 as default TX pins.
 *
 * DMA and the Cortex-M7 data cache (F7): buffers and descriptors are 32-byte
 * aligned whole cache lines; when the application has the data cache on, they
 * are cleaned before the DMA reads them and invalidated before the CPU does.
 */

#include <string.h>

#include "net_driver_stm32.h"
#include "delays.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pin_names.h"
#include "hal_ll_gpio_constants.h"
#if defined( __arm__ )
#include "core_header.h"
#endif

#if !defined( NET_STM32_F1 ) && !defined( NET_STM32_F2 ) && !defined( NET_STM32_F4 ) && !defined( NET_STM32_F7 )
#error "net_driver_stm32: define the family (NET_STM32_F1/F2/F4/F7), set by middleware/net/CMakeLists.txt"
#endif

#ifndef FOSC_KHZ_VALUE
#error "net_driver_stm32: the setup gives no core clock (FOSC_KHZ_VALUE)"
#endif

/* ----------------------------------------------------------- Peripherals --- */

#ifndef NET_STM32_ETH_BASE
#define NET_STM32_ETH_BASE      0x40028000UL
#endif
#ifndef NET_STM32_RCC_BASE
#if defined( NET_STM32_F1 )
#define NET_STM32_RCC_BASE      0x40021000UL
#else
#define NET_STM32_RCC_BASE      0x40023800UL
#endif
#endif
#ifndef NET_STM32_SYSCFG_BASE
#define NET_STM32_SYSCFG_BASE   0x40013800UL     /* F2/F4/F7 */
#endif
#ifndef NET_STM32_AFIO_BASE
#define NET_STM32_AFIO_BASE     0x40010000UL     /* F1 */
#endif
#ifndef NET_STM32_SCB_BASE
#define NET_STM32_SCB_BASE      0xE000E000UL
#endif

#define REG( base, offset )     ( *( volatile uint32_t * )( ( uintptr_t )( base ) + ( offset ) ) )

/* MAC and DMA registers (offsets as in ETH_TypeDef). */
typedef struct
{
    volatile uint32_t MACCR;        /* 0x0000 */
    volatile uint32_t MACFFR;       /* 0x0004 */
    volatile uint32_t MACHTHR;      /* 0x0008 */
    volatile uint32_t MACHTLR;      /* 0x000C */
    volatile uint32_t MACMIIAR;     /* 0x0010 */
    volatile uint32_t MACMIIDR;     /* 0x0014 */
    volatile uint32_t MACFCR;       /* 0x0018 */
    volatile uint32_t MACVLANTR;    /* 0x001C */
    uint32_t reserved0[ 2 ];
    volatile uint32_t MACRWUFFR;    /* 0x0028 */
    volatile uint32_t MACPMTCSR;    /* 0x002C */
    uint32_t reserved1[ 2 ];
    volatile uint32_t MACSR;        /* 0x0038 */
    volatile uint32_t MACIMR;       /* 0x003C */
    volatile uint32_t MACA0HR;      /* 0x0040 */
    volatile uint32_t MACA0LR;      /* 0x0044 */
    uint32_t reserved2[ ( 0x1000 - 0x48 ) / 4 ];
    volatile uint32_t DMABMR;       /* 0x1000 */
    volatile uint32_t DMATPDR;      /* 0x1004 */
    volatile uint32_t DMARPDR;      /* 0x1008 */
    volatile uint32_t DMARDLAR;     /* 0x100C */
    volatile uint32_t DMATDLAR;     /* 0x1010 */
    volatile uint32_t DMASR;        /* 0x1014 */
    volatile uint32_t DMAOMR;       /* 0x1018 */
    volatile uint32_t DMAIER;       /* 0x101C */
} stm32_eth_t;

#define ETH ( ( stm32_eth_t * )( uintptr_t )( NET_STM32_ETH_BASE ) )

/* MACCR */
#define MACCR_RE                ( 1UL << 2 )
#define MACCR_TE                ( 1UL << 3 )
#define MACCR_DM                ( 1UL << 11 )
#define MACCR_FES               ( 1UL << 14 )
/* MACFFR */
#define MACFFR_PAM              ( 1UL << 4 )    /* pass all multicast (mDNS, IPv6) */
/* MACMIIAR */
#define MACMIIAR_MB             ( 1UL << 0 )
#define MACMIIAR_MW             ( 1UL << 1 )
#define MACMIIAR_CR_POS         2
#define MACMIIAR_MR_POS         6
#define MACMIIAR_PA_POS         11
/* DMABMR */
#define DMABMR_SR               ( 1UL << 0 )
#define DMABMR_PBL_32           ( 32UL << 8 )
#define DMABMR_FB               ( 1UL << 16 )
#define DMABMR_RDP_32           ( 32UL << 17 )
#define DMABMR_USP              ( 1UL << 23 )
#define DMABMR_AAB              ( 1UL << 25 )
/* DMASR (write 1 to clear) */
#define DMASR_TBUS              ( 1UL << 2 )
#define DMASR_RBUS              ( 1UL << 7 )
/* DMAOMR */
#define DMAOMR_SR               ( 1UL << 1 )
#define DMAOMR_ST               ( 1UL << 13 )
#define DMAOMR_FTF              ( 1UL << 20 )
#define DMAOMR_TSF              ( 1UL << 21 )
#define DMAOMR_RSF              ( 1UL << 25 )

/* RCC, RMII selection */
#if defined( NET_STM32_F1 )
#define RCC_CFGR                REG( NET_STM32_RCC_BASE, 0x04 )
#define RCC_AHBENR              REG( NET_STM32_RCC_BASE, 0x14 )
#define RCC_AHBRSTR             REG( NET_STM32_RCC_BASE, 0x28 )
#define RCC_ETH_CLOCKS          ( ( 1UL << 14 ) | ( 1UL << 15 ) | ( 1UL << 16 ) )   /* ETHMACEN, ETHMACTXEN, ETHMACRXEN */
#define RCC_ETH_RESET           ( 1UL << 14 )                                       /* ETHMACRST */
#define RCC_CFGR_MCO_MASK       ( 0xFUL << 24 )
#define RCC_CFGR_MCO_SYSCLK     ( 0x4UL << 24 )
#define AFIO_MAPR               REG( NET_STM32_AFIO_BASE, 0x04 )
#define AFIO_MAPR_MII_RMII_SEL  ( 1UL << 23 )
#else
#define RCC_CFGR                REG( NET_STM32_RCC_BASE, 0x08 )
#define RCC_AHB1RSTR            REG( NET_STM32_RCC_BASE, 0x10 )
#define RCC_AHB1ENR             REG( NET_STM32_RCC_BASE, 0x30 )
#define RCC_APB2ENR             REG( NET_STM32_RCC_BASE, 0x44 )
#define RCC_ETH_CLOCKS          ( ( 1UL << 25 ) | ( 1UL << 26 ) | ( 1UL << 27 ) )   /* ETHMACEN, ETHMACTXEN, ETHMACRXEN */
#define RCC_ETH_RESET           ( 1UL << 25 )                                       /* ETHMACRST */
#define RCC_APB2ENR_SYSCFGEN    ( 1UL << 14 )
#define RCC_CFGR_MCO1_MASK      ( ( 0x3UL << 21 ) | ( 0x7UL << 24 ) )
#define RCC_CFGR_MCO1_PLL       ( 0x3UL << 21 )
#define RCC_CFGR_MCO1PRE_DIV( n ) ( ( 0x4UL | ( ( uint32_t )( n ) - 2UL ) ) << 24 )  /* n = 2..5 */
#define SYSCFG_PMC              REG( NET_STM32_SYSCFG_BASE, 0x04 )
#define SYSCFG_PMC_MII_RMII_SEL ( 1UL << 23 )
#endif

/* Cortex-M7 data cache (F7) */
#define SCB_CCR                 REG( NET_STM32_SCB_BASE, 0xD14 )
#define SCB_CCR_DC              ( 1UL << 16 )
#define SCB_DCIMVAC             REG( NET_STM32_SCB_BASE, 0xF5C )   /* invalidate by address */
#define SCB_DCCMVAC             REG( NET_STM32_SCB_BASE, 0xF68 )   /* clean by address */

/* --------------------------------------------------------- Descriptors --- */

/* TDES0 / RDES0 */
#define DES0_OWN                ( 1UL << 31 )
#define TDES0_LS                ( 1UL << 29 )
#define TDES0_FS                ( 1UL << 28 )
#define TDES0_TCH               ( 1UL << 20 )
#define RDES0_FL( d )           ( ( ( d ) >> 16 ) & 0x3FFFUL )   /* frame length, CRC included */
#define RDES0_ES                ( 1UL << 15 )
#define RDES0_FS                ( 1UL << 9 )
#define RDES0_LS                ( 1UL << 8 )
/* RDES1 */
#define RDES1_RCH               ( 1UL << 14 )

#define BUF_SIZE                1536u           /* full frame, multiple of 32 */
#define CRC_SIZE                4u

/* One descriptor per 32-byte cache line. */
typedef struct
{
    volatile uint32_t des0;
    volatile uint32_t des1;
    volatile uint32_t des2;     /* buffer */
    volatile uint32_t des3;     /* next descriptor (chained) */
    uint32_t pad[ 4 ];
} dcpt_t;

static dcpt_t rx_dcpt[ NET_STM32_RX_BUFFERS ] __attribute__(( aligned( 32 ) ));
static dcpt_t tx_dcpt[ NET_STM32_TX_BUFFERS ] __attribute__(( aligned( 32 ) ));
static uint8_t rx_buf[ NET_STM32_RX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 32 ) ));
static uint8_t tx_buf[ NET_STM32_TX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 32 ) ));

#define ADDR( p )               ( ( uint32_t )( uintptr_t )( p ) )

/* Bounded waits on hardware flags. NET_STM32_POLL_HOOK() runs in every wait:
 * empty here, the host unit test uses it to play the hardware. */
#define WAIT_LOOPS              200000ul
#ifndef NET_STM32_POLL_HOOK
#define NET_STM32_POLL_HOOK()   ( ( void )0 )
#endif

/* ---------------------------------------------------------------- State --- */

static struct
{
    net_stm32_cfg_t cfg;
    net_phy_t phy;
    uint32_t mdc_range;
    uint8_t rx_next;
    uint8_t tx_next;
    bool link;
} eth;

/* ---------------------------------------------------------------- Cache --- */

#if defined( NET_STM32_F7 )
static bool dcache_on( void )
{
    return 0 != ( SCB_CCR & SCB_CCR_DC );
}

static void barrier( void )
{
#if defined( __arm__ )
    __asm__ volatile ( "dsb 0xF\n\tisb 0xF" ::: "memory" );
#endif
}

static void dcache_clean( const volatile void *p, uint32_t len )
{
    if ( dcache_on() )
    {
        for ( uintptr_t a = ( uintptr_t )p & ~( uintptr_t )31; a < ( uintptr_t )p + len; a += 32 )
        {
            SCB_DCCMVAC = ( uint32_t )a;
        }
        barrier();
    }
}

static void dcache_invalidate( const volatile void *p, uint32_t len )
{
    if ( dcache_on() )
    {
        for ( uintptr_t a = ( uintptr_t )p & ~( uintptr_t )31; a < ( uintptr_t )p + len; a += 32 )
        {
            SCB_DCIMVAC = ( uint32_t )a;
        }
        barrier();
    }
}
#else
#define dcache_clean( p, len )      ( ( void )( p ), ( void )( len ) )
#define dcache_invalidate( p, len ) ( ( void )( p ), ( void )( len ) )
#endif

/* ------------------------------------------------------------- Helpers --- */

/* Write a MAC register twice with a pause: successive writes to the same MAC
 * register may otherwise be lost (STM32F4/F7 errata, "Successive write
 * operations to the same register might not be fully taken into account"). */
static void mac_write( volatile uint32_t *reg, uint32_t value )
{
    *reg = value;
    ( void )*reg;
    Delay_ms( 1 );
    *reg = value;
}

/* MDC clock range (MACMIIAR.CR) from HCLK (the core clock): MDC <= 2.5 MHz. */
static uint32_t mdc_range( uint32_t hclk_khz )
{
#if !defined( NET_STM32_F1 )
    if ( hclk_khz >= 150000u )
    {
        return 4;   /* HCLK/102 */
    }
    if ( hclk_khz >= 100000u )
    {
        return 1;   /* HCLK/62 */
    }
#endif
    if ( hclk_khz >= 60000u )
    {
        return 0;   /* HCLK/42 */
    }
    if ( hclk_khz >= 35000u )
    {
        return 3;   /* HCLK/26 */
    }
    return 2;       /* HCLK/16 */
}

/* ----------------------------------------------------------------- MDIO --- */

static int32_t mdio_wait( void )
{
    for ( uint32_t i = 0; i < WAIT_LOOPS; i++ )
    {
        NET_STM32_POLL_HOOK();
        if ( !( ETH->MACMIIAR & MACMIIAR_MB ) )
        {
            return 0;
        }
    }
    return -1;
}

static uint32_t mdio_command( uint8_t addr, uint8_t reg )
{
    return ( ( uint32_t )( addr & 0x1F ) << MACMIIAR_PA_POS ) | ( ( uint32_t )( reg & 0x1F ) << MACMIIAR_MR_POS ) |
           ( eth.mdc_range << MACMIIAR_CR_POS ) | MACMIIAR_MB;
}

static int32_t mdio_read( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value )
{
    ( void )ctx;
    if ( mdio_wait() )
    {
        return -1;
    }
    ETH->MACMIIAR = mdio_command( addr, reg );
    int32_t err = mdio_wait();
    *value = ( uint16_t )ETH->MACMIIDR;
    return err;
}

static int32_t mdio_write( void *ctx, uint8_t addr, uint8_t reg, uint16_t value )
{
    ( void )ctx;
    if ( mdio_wait() )
    {
        return -1;
    }
    ETH->MACMIIDR = value;
    ETH->MACMIIAR = mdio_command( addr, reg ) | MACMIIAR_MW;
    return mdio_wait();
}

/* --------------------------------------------------- Pins and clocks --- */

#if defined( NET_STM32_F1 )
/* F1: outputs are alternate function push-pull, inputs are floating inputs. */
#define CFG_OUT ( GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_OTYPE_PP | GPIO_CFG_SPEED_MAX )
#define CFG_IN  ( GPIO_CFG_DIGITAL_INPUT )
#define AF_ETH  0
#define AF_MCO  0
#else
#define CFG_OUT ( GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_OTYPE_PP | GPIO_CFG_PULL_NO | GPIO_CFG_SPEED_MAX )
#define CFG_IN  CFG_OUT
#define AF_ETH  11
#define AF_MCO  0
#endif

static void pins_init( void )
{
    module_struct module;
    uint8_t n = 0;

#define PIN( name, af, config ) do { module.pins[ n ] = VALUE( ( name ), ( af ) ); module.configs[ n ] = ( config ); n++; } while ( 0 )
    PIN( GPIO_PA1, AF_ETH, CFG_IN );                        /* REF_CLK */
    PIN( GPIO_PA2, AF_ETH, CFG_OUT );                       /* MDIO */
    PIN( GPIO_PA7, AF_ETH, CFG_IN );                        /* CRS_DV */
    PIN( GPIO_PC1, AF_ETH, CFG_OUT );                       /* MDC */
    PIN( GPIO_PC4, AF_ETH, CFG_IN );                        /* RXD0 */
    PIN( GPIO_PC5, AF_ETH, CFG_IN );                        /* RXD1 */
#if defined( GPIO_PG11 ) && defined( GPIO_PG13 ) && defined( GPIO_PG14 )
    if ( NET_STM32_TX_PINS_PG11_PG13_PG14 == eth.cfg.tx_pins )
    {
        PIN( GPIO_PG11, AF_ETH, CFG_OUT );                  /* TX_EN */
        PIN( GPIO_PG13, AF_ETH, CFG_OUT );                  /* TXD0 */
        PIN( GPIO_PG14, AF_ETH, CFG_OUT );                  /* TXD1 */
    }
    else
#endif
    {
        /* Packages without port G (e.g. STM32F107, 100-pin F4/F7) only have these. */
        PIN( GPIO_PB11, AF_ETH, CFG_OUT );                  /* TX_EN */
        PIN( GPIO_PB12, AF_ETH, CFG_OUT );                  /* TXD0 */
        PIN( GPIO_PB13, AF_ETH, CFG_OUT );                  /* TXD1 */
    }
    if ( NET_STM32_REF_CLOCK_MCO == eth.cfg.ref_clock )
    {
        PIN( GPIO_PA8, AF_MCO, CFG_OUT );                   /* MCO1: PHY reference clock */
    }
#undef PIN
    module.pins[ n ] = GPIO_MODULE_STRUCT_END;
    module.configs[ n ] = GPIO_MODULE_STRUCT_END;
    module.gpio_remap = 0;          /* F1: Ethernet pins not remapped */
    hal_ll_gpio_module_struct_init( &module, true );
}

/* PHY reference clock on MCO1 and RMII mode; done while the MAC is off. */
static void clock_and_mode_init( void )
{
#if defined( NET_STM32_F1 )
    if ( NET_STM32_REF_CLOCK_MCO == eth.cfg.ref_clock )
    {
        RCC_CFGR = ( RCC_CFGR & ~RCC_CFGR_MCO_MASK ) | RCC_CFGR_MCO_SYSCLK;
    }
    AFIO_MAPR |= AFIO_MAPR_MII_RMII_SEL;            /* AFIO clock: enabled by the GPIO layer */
#else
    if ( NET_STM32_REF_CLOCK_MCO == eth.cfg.ref_clock )
    {
        uint8_t div = eth.cfg.mco_div;
        if ( div < 2 || div > 5 )
        {
            div = 2;
        }
        RCC_CFGR = ( RCC_CFGR & ~RCC_CFGR_MCO1_MASK ) | RCC_CFGR_MCO1_PLL | RCC_CFGR_MCO1PRE_DIV( div );
    }
    RCC_APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    ( void )RCC_APB2ENR;
    SYSCFG_PMC |= SYSCFG_PMC_MII_RMII_SEL;
#endif
}

static void mac_clocks_and_reset( void )
{
#if defined( NET_STM32_F1 )
    RCC_AHBENR |= RCC_ETH_CLOCKS;
    ( void )RCC_AHBENR;
    RCC_AHBRSTR |= RCC_ETH_RESET;
    RCC_AHBRSTR &= ~RCC_ETH_RESET;
#else
    RCC_AHB1ENR |= RCC_ETH_CLOCKS;
    ( void )RCC_AHB1ENR;
    RCC_AHB1RSTR |= RCC_ETH_RESET;
    RCC_AHB1RSTR &= ~RCC_ETH_RESET;
#endif
}

/* ------------------------------------------------------------- Driver --- */

static void descriptors_init( void )
{
    for ( uint8_t i = 0; i < NET_STM32_RX_BUFFERS; i++ )
    {
        rx_dcpt[ i ].des1 = RDES1_RCH | BUF_SIZE;
        rx_dcpt[ i ].des2 = ADDR( rx_buf[ i ] );
        rx_dcpt[ i ].des3 = ADDR( &rx_dcpt[ ( i + 1 ) % NET_STM32_RX_BUFFERS ] );
        rx_dcpt[ i ].des0 = DES0_OWN;
    }
    for ( uint8_t i = 0; i < NET_STM32_TX_BUFFERS; i++ )
    {
        tx_dcpt[ i ].des0 = TDES0_TCH;
        tx_dcpt[ i ].des1 = 0;
        tx_dcpt[ i ].des2 = ADDR( tx_buf[ i ] );
        tx_dcpt[ i ].des3 = ADDR( &tx_dcpt[ ( i + 1 ) % NET_STM32_TX_BUFFERS ] );
    }
    dcache_clean( rx_dcpt, sizeof( rx_dcpt ) );
    dcache_clean( tx_dcpt, sizeof( tx_dcpt ) );
    eth.rx_next = 0;
    eth.tx_next = 0;
}

static void mac_set_mode( const net_phy_mode_t *mode )
{
    uint32_t cr = ETH->MACCR & ~( MACCR_FES | MACCR_DM );
    if ( mode->speed_100 )
    {
        cr |= MACCR_FES;
    }
    if ( mode->full_duplex )
    {
        cr |= MACCR_DM;
    }
    mac_write( &ETH->MACCR, cr );
}

static int32_t stm32_init( void *ctx, const uint8_t *mac )
{
    ( void )ctx;

    /* 1. Pins, PHY reference clock and RMII mode, then the MAC clocks and reset. */
    pins_init();
    clock_and_mode_init();
    if ( HAL_PIN_NC != eth.cfg.phy_reset )
    {
        digital_out_t rst;
        if ( DIGITAL_OUT_SUCCESS == digital_out_init( &rst, eth.cfg.phy_reset ) )
        {
            digital_out_low( &rst );
            Delay_ms( 1 );
            digital_out_high( &rst );
            Delay_ms( 10 );
        }
    }
    mac_clocks_and_reset();

    /* 2. DMA software reset: completes only with the PHY's reference clock. */
    ETH->DMABMR |= DMABMR_SR;
    uint32_t i = 0;
    while ( NET_STM32_POLL_HOOK(), ETH->DMABMR & DMABMR_SR )
    {
        if ( ++i >= WAIT_LOOPS )
        {
            return -2;      /* no RMII reference clock: check the PHY clock (ref_clock / mco_div) */
        }
    }

    /* 3. PHY over MDIO. */
    eth.mdc_range = mdc_range( FOSC_KHZ_VALUE );
    eth.phy.ctx = NULL;
    eth.phy.addr = eth.cfg.phy_addr;
    eth.phy.read = mdio_read;
    eth.phy.write = mdio_write;
    if ( net_phy_init( &eth.phy ) )
    {
        return -1;
    }

    /* 4. MAC: 100 Mbit/s full duplex until the PHY reports the negotiated mode. */
    mac_write( &ETH->MACCR, MACCR_FES | MACCR_DM );
    mac_write( &ETH->MACFFR, MACFFR_PAM );
    mac_write( &ETH->MACFCR, 0 );
    ETH->MACA0HR = ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 );
    ETH->MACA0LR = ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 ) | ( ( uint32_t )mac[ 2 ] << 16 ) |
                   ( ( uint32_t )mac[ 3 ] << 24 );

    /* 5. DMA: rings, burst settings, store and forward (whole frames). */
    descriptors_init();
    ETH->DMATDLAR = ADDR( &tx_dcpt[ 0 ] );
    ETH->DMARDLAR = ADDR( &rx_dcpt[ 0 ] );
    ETH->DMABMR = DMABMR_AAB | DMABMR_USP | DMABMR_RDP_32 | DMABMR_FB | DMABMR_PBL_32;
    ETH->DMAIER = 0;
    mac_write( &ETH->DMAOMR, DMAOMR_RSF | DMAOMR_TSF );

    /* 6. Start: transmitter, flush its FIFO, DMA transmit, receiver, DMA receive. */
    mac_write( &ETH->MACCR, ETH->MACCR | MACCR_TE );
    ETH->DMAOMR |= DMAOMR_FTF;
    for ( i = 0; ( i < WAIT_LOOPS ) && ( ETH->DMAOMR & DMAOMR_FTF ); i++ )
    {
        NET_STM32_POLL_HOOK();
    }
    mac_write( &ETH->DMAOMR, ETH->DMAOMR | DMAOMR_ST );
    mac_write( &ETH->MACCR, ETH->MACCR | MACCR_RE );
    mac_write( &ETH->DMAOMR, ETH->DMAOMR | DMAOMR_SR );
    eth.link = false;
    return 0;
}

static int32_t stm32_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    ( void )ctx;
    if ( ( len == 0 ) || ( len > BUF_SIZE ) )
    {
        return -1;
    }
    dcpt_t *d = &tx_dcpt[ eth.tx_next ];
    for ( uint32_t i = 0; ; i++ )
    {
        NET_STM32_POLL_HOOK();
        dcache_invalidate( d, sizeof( *d ) );
        if ( !( d->des0 & DES0_OWN ) )
        {
            break;
        }
        if ( i >= WAIT_LOOPS )
        {
            return -1;      /* the DMA still owns the descriptor: transmitter stuck */
        }
    }
    memcpy( tx_buf[ eth.tx_next ], frame, len );
    dcache_clean( tx_buf[ eth.tx_next ], len );
    d->des1 = len;
    d->des0 = DES0_OWN | TDES0_FS | TDES0_LS | TDES0_TCH;
    dcache_clean( d, sizeof( *d ) );

    /* Resume the transmit DMA if it ran out of descriptors. */
    if ( ETH->DMASR & DMASR_TBUS )
    {
        ETH->DMASR = DMASR_TBUS;
    }
    ETH->DMATPDR = 0;
    eth.tx_next = ( uint8_t )( ( eth.tx_next + 1 ) % NET_STM32_TX_BUFFERS );
    return 0;
}

static int32_t stm32_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    ( void )ctx;
    int32_t result = 0;

    /* At most one pass over the ring per call. */
    for ( uint8_t pass = 0; ( pass < NET_STM32_RX_BUFFERS ) && ( result <= 0 ); pass++ )
    {
        dcpt_t *d = &rx_dcpt[ eth.rx_next ];
        dcache_invalidate( d, sizeof( *d ) );
        uint32_t des0 = d->des0;
        if ( des0 & DES0_OWN )
        {
            break;          /* nothing (more) received */
        }

        uint32_t len = RDES0_FL( des0 );
        bool whole = ( des0 & RDES0_FS ) && ( des0 & RDES0_LS ) && !( des0 & RDES0_ES );
        if ( whole && ( len >= 14u + CRC_SIZE ) )
        {
            len -= CRC_SIZE;
            if ( len > size )
            {
                len = size;
            }
            dcache_invalidate( rx_buf[ eth.rx_next ], len );
            memcpy( buf, rx_buf[ eth.rx_next ], len );
            result = ( int32_t )len;
        }
        /* Errored, runt or over several buffers (cannot happen with 1536-byte
         * buffers): dropped. Give the descriptor back. */
        d->des0 = DES0_OWN;
        dcache_clean( d, sizeof( *d ) );
        eth.rx_next = ( uint8_t )( ( eth.rx_next + 1 ) % NET_STM32_RX_BUFFERS );
    }

    /* Resume the receive DMA if it ran out of descriptors. */
    if ( ETH->DMASR & DMASR_RBUS )
    {
        ETH->DMASR = DMASR_RBUS;
        ETH->DMARPDR = 0;
    }
    return result;
}

static bool stm32_link_up( void *ctx )
{
    ( void )ctx;
    net_phy_mode_t mode;
    bool up = net_phy_link( &eth.phy, &mode );
    if ( up && !eth.link )
    {
        mac_set_mode( &mode );
    }
    eth.link = up;
    return up;
}

/* ---------------------------------------------------------------- API --- */

void net_stm32_cfg_setup( net_stm32_cfg_t *cfg )
{
#if defined( NET_STM32_TX_PG )
    cfg->tx_pins = NET_STM32_TX_PINS_PG11_PG13_PG14;
#else
    cfg->tx_pins = NET_STM32_TX_PINS_PB11_PB12_PB13;
#endif
    cfg->ref_clock = NET_STM32_REF_CLOCK_MCO;
#if defined( NET_STM32_F2 )
    cfg->mco_div = 2;       /* 100 MHz PLL / 2 */
#elif defined( NET_STM32_F4 )
    cfg->mco_div = 3;       /* 150 MHz PLL / 3 */
#elif defined( NET_STM32_F7 )
    cfg->mco_div = 4;       /* 200 MHz PLL / 4 */
#else
    cfg->mco_div = 0;       /* F1: MCO = system clock */
#endif
    cfg->phy_reset = HAL_PIN_NC;
    cfg->phy_addr = NET_PHY_ADDR_AUTO;
}

void net_driver_stm32( net_driver_t *drv, const net_stm32_cfg_t *cfg )
{
    eth.cfg = *cfg;
    drv->ctx = NULL;
    drv->init = stm32_init;
    drv->send = stm32_send;
    drv->receive = stm32_receive;
    drv->link_up = stm32_link_up;
}

const net_phy_t *net_driver_stm32_phy( void )
{
    return &eth.phy;
}

// ------------------------------------------------------------------------- END
