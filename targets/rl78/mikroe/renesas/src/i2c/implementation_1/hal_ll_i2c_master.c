/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_per.h"
#include "hal_ll_pior.h"
#include "delays.h"
#include "mcu.h"
#include <stdbool.h>

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting the 1st SFR area (IICAn/IICSn/IICFn) */
#define hal_ll_i2c_get_base_struct(_handle) ((volatile hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting the 2nd SFR area (IICCTLn0/1, IICWLn/H, SVAn) */
#define hal_ll_i2c_get_ctrl_struct(_handle) ((volatile hal_ll_i2c_ctrl_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

/*!< @brief Volatile register accessor, the bit control macros don't add volatile themselves. */
#define hal_ll_i2c_reg8(_addr)          ( ( volatile uint8_t * )( _addr ) )

/*!< @brief Register addresses outside of the IICA blocks. */
#define HAL_LL_I2C_PER0_ADDR            ( 0xF00F0UL )
#define HAL_LL_I2C_PRR0_ADDR            ( 0xF00F1UL )

/*!< @brief IICA0 2nd SFR area and INTIICA0 flag/mask (IICAIF0 = IF1L.3, IICAMK0 = MK1L.3). */
#define HAL_LL_I2C0_CTRL_BASE_ADDR      ( 0xF0230UL ) // IICCTL00
#define HAL_LL_I2C0_IF_ADDR             ( 0xFFFE2UL ) // IF1L
#define HAL_LL_I2C0_MK_ADDR             ( 0xFFFE6UL ) // MK1L
#define HAL_LL_I2C0_INT_BIT             ( 3 )

/*!< @brief IICA1 2nd SFR area and INTIICA1 flag/mask (IICAIF1 = IF2H.7, IICAMK1 = MK2H.7). */
#define HAL_LL_I2C1_CTRL_BASE_ADDR      ( 0xF0238UL ) // IICCTL10
#define HAL_LL_I2C1_IF_ADDR             ( 0xFFFD1UL ) // IF2H
#define HAL_LL_I2C1_MK_ADDR             ( 0xFFFD5UL ) // MK2H
#define HAL_LL_I2C1_INT_BIT             ( 7 )

/*!< @brief PIOR12 routes IICA0 (bits 1:0) and IICA1 (bits 3:2). */
#define HAL_LL_I2C_PIOR_REG             ( 12 )
#define hal_ll_i2c_pior_shift(_index)   ( ( _index ) << 1 )
#define HAL_LL_I2C_PIOR_WIDTH           ( 2 )

/*!< @brief IICCTLn0 bits */
#define HAL_LL_I2C_IICCTL0_IICE         (7)
#define HAL_LL_I2C_IICCTL0_LREL         (6)
#define HAL_LL_I2C_IICCTL0_WREL         (5)
#define HAL_LL_I2C_IICCTL0_SPIE         (4)
#define HAL_LL_I2C_IICCTL0_WTIM         (3)
#define HAL_LL_I2C_IICCTL0_ACKE         (2)
#define HAL_LL_I2C_IICCTL0_STT          (1)
#define HAL_LL_I2C_IICCTL0_SPT          (0)

/*!< @brief IICSn bits (read-only) */
#define HAL_LL_I2C_IICS_MSTS            (7)
#define HAL_LL_I2C_IICS_ALD             (6)
#define HAL_LL_I2C_IICS_EXC             (5)
#define HAL_LL_I2C_IICS_COI             (4)
#define HAL_LL_I2C_IICS_TRC             (3)
#define HAL_LL_I2C_IICS_ACKD            (2)
#define HAL_LL_I2C_IICS_STD             (1)
#define HAL_LL_I2C_IICS_SPD             (0)

/*!< @brief IICFn bits */
#define HAL_LL_I2C_IICF_STCF            (7)
#define HAL_LL_I2C_IICF_IICBSY          (6)
#define HAL_LL_I2C_IICF_STCEN           (1)
#define HAL_LL_I2C_IICF_IICRSV          (0)

/*!< @brief IICCTLn1 bits */
#define HAL_LL_I2C_IICCTL1_WUP          (7)
#define HAL_LL_I2C_IICCTL1_SVADIS       (6)
#define HAL_LL_I2C_IICCTL1_CLD          (5)
#define HAL_LL_I2C_IICCTL1_DAD          (4)
#define HAL_LL_I2C_IICCTL1_SMC          (3)
#define HAL_LL_I2C_IICCTL1_DFC          (2)
#define HAL_LL_I2C_IICCTL1_PRS          (0)

/*!< @brief Address byte R/W bit */
#define HAL_LL_I2C_DIRECTION_WRITE      (0)
#define HAL_LL_I2C_DIRECTION_READ       (1)

/*!< @brief fMCK must not exceed 20 MHz, PRSn = 1 selects fCLK/2 above that. */
#define HAL_LL_I2C_FMCK_MAX_HZ          (20000000UL)
#define HAL_LL_I2C_MCU_CLOCK_HZ         ( ( uint32_t )Get_Fosc_kHz() * 1000UL )
/*!< @brief tR + tF of SCLAn, board dependent (pull-ups, bus capacitance). */
#define HAL_LL_I2C_RISE_FALL_TIME_S     (0.0000003f)
#define HAL_LL_I2C_IICWLH_MAX           (255.0f)

/*!< @brief Supported bit-rates */
#define HAL_LL_I2C_MASTER_SPEED_100K    (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K    (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M      (1000000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT   (10000)

/*!< @brief I2C register structure - 1st SFR area (IICAn/IICSn/IICFn) */
typedef struct {
    uint8_t iica;   /*!< IICAn - shift register */
    uint8_t iics;   /*!< IICSn - status register, read-only */
    uint8_t iicf;   /*!< IICFn - flag register */
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C register structure - 2nd SFR area (IICCTLn0/1, IICWLn/H, SVAn) */
typedef struct {
    uint8_t iicctl0; /*!< IICCTLn0 - start/stop trigger, ACK/wait control */
    uint8_t iicctl1; /*!< IICCTLn1 - speed mode, digital filter, clock divider */
    uint8_t iicwl;   /*!< IICWLn - SCL low-level width */
    uint8_t iicwh;   /*!< IICWHn - SCL high-level width */
    uint8_t sva;     /*!< SVAn - own slave address */
} hal_ll_i2c_ctrl_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;      /*!< Must stay first, see hal_ll_get_specifics(). */
    hal_ll_base_addr_t ctrl_base;
    hal_ll_base_addr_t if_reg;    /*!< IFxx register holding IICAIFn */
    hal_ll_base_addr_t mk_reg;    /*!< MKxx register holding IICAMKn */
    uint8_t int_bit;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct {
    uint32_t pin_scl;
    uint32_t pin_sda;
} hal_ll_i2c_pin_id;

/*!< @brief I2C end mode selection values */
typedef enum {
    HAL_LL_I2C_MASTER_END_MODE_RESTART = 0,
    HAL_LL_I2C_MASTER_END_MODE_STOP,
    HAL_LL_I2C_MASTER_WRITE_THEN_READ
} hal_ll_i2c_master_end_mode_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I2C_MASTER_SUCCESS = 0,
    HAL_LL_I2C_MASTER_WRONG_PINS,
    HAL_LL_I2C_MASTER_MODULE_ERROR,

    HAL_LL_I2C_MASTER_ERROR = (-1)
} hal_ll_i2c_master_err_t;

/*!< @brief I2C timeout error values */
typedef enum {
    HAL_LL_I2C_MASTER_TIMEOUT_START = 1300,
    HAL_LL_I2C_MASTER_TIMEOUT_STOP,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_INIT,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE,
    HAL_LL_I2C_MASTER_NACK
} hal_ll_i2c_master_timeout_t;

/*!< @brief Enum containing predefined module standard speed values */
typedef enum {
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ VARIABLES
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef I2C_MODULE_0
    {HAL_LL_I2C0_BASE_ADDR, HAL_LL_I2C0_CTRL_BASE_ADDR, HAL_LL_I2C0_IF_ADDR, HAL_LL_I2C0_MK_ADDR, HAL_LL_I2C0_INT_BIT,
     hal_ll_i2c_module_num( I2C_MODULE_0 ), {{HAL_LL_PIN_NC, 0}, {HAL_LL_PIN_NC, 0}},
     HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDR, HAL_LL_I2C1_CTRL_BASE_ADDR, HAL_LL_I2C1_IF_ADDR, HAL_LL_I2C1_MK_ADDR, HAL_LL_I2C1_INT_BIT,
     hal_ll_i2c_module_num( I2C_MODULE_1 ), {{HAL_LL_PIN_NC, 0}, {HAL_LL_PIN_NC, 0}},
     HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, 0,
     HAL_LL_MODULE_ERROR, {{HAL_LL_PIN_NC, 0}, {HAL_LL_PIN_NC, 0}}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable or disable the I2C hardware module.
  *
  * Supplies/removes the IICAn clock (PER0) and releases IICAn from reset (PRR0).
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - true to enable, false to disable.
  * @return None
  */
static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Sets IICFn, SVAn and the transfer clock while IICEn = 0.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Full I2C module initialization procedure.
  *
  * Follows the single-master initial setting flow (R01UH1082 Figure 20-28):
  * clock, pins as inputs, transfer clock, IICEn = 1, pins as outputs.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I2C pin alternate function state.
  *
  * Routes SCLAn/SDAAn through PIOR12 and leaves both pins in input mode,
  * so they never drive the bus while IICEn = 0.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
  * @brief  Configure SCL and SDA with the same GPIO configuration.
  *
  * @param[in]  *map   - Object specific context handler.
  * @param[in]  config - GPIO_CFG_DIGITAL_INPUT or GPIO_CFG_DIGITAL_OUTPUT.
  * @return None
  */
static void hal_ll_i2c_master_set_pins_config( hal_ll_i2c_hw_specifics_map_t *map, uint32_t config );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_i2c_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_i2c_hw_specifics_map_t Map address.
  */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Check if pins are adequate.
  *
  * Checks scl and sda pins the user has passed with pre-defined
  * pins in scl and sda maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  scl - SCL pre-defined pin name.
  * @param[in]  sda - SDA pre-defined pin name.
  * @param[in]  *index_list - Index list address
  * @return hal_ll_pin_name_t Module index based on pins.
  */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * @param[in]  module_index I2C HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCL and SDA map index values
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list );

/**
  * @brief  Waits until the bus is released (IICBSYn = 0).
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Polls a register bit until it is set or the timeout expires.
  *
  * @param[in]  *map - Object specific context handler, timeout of 0 waits forever.
  * @param[in]  *reg - Register to poll.
  * @param[in]  bit  - Bit position.
  * @return bool true if the bit got set, false on timeout.
  */
static bool hal_ll_i2c_master_wait_for_bit( hal_ll_i2c_hw_specifics_map_t *map, volatile uint8_t *reg, uint8_t bit );

/**
  * @brief  Waits for INTIICAn and clears its request flag.
  *
  * With WTIMn = 1 the flag is set on the 9th clock falling edge (after ACK),
  * with WTIMn = 0 on the 8th, and on stop condition detection (SPIEn = 1).
  *
  * @param[in]  *map - Object specific context handler.
  * @return bool true if the interrupt occurred, false on timeout.
  */
static bool hal_ll_i2c_master_wait_for_interrupt( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Generates a start, or a restart when called during a master wait.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Generates a stop condition and waits for it on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sends the slave address with the R/W bit and checks for ACK.
  *
  * @param[in]  *map      - Object specific context handler.
  * @param[in]  direction - HAL_LL_I2C_DIRECTION_WRITE or HAL_LL_I2C_DIRECTION_READ.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_send_address( hal_ll_i2c_hw_specifics_map_t *map, uint8_t direction );

/**
  * @brief  Get adequate I2C bit-rate value.
  *
  * Returns one of pre-defined bit-rate values,
  * or the closest bit-rate based on bit_rate
  * value passed to the function.
  *
  * @param[in]  bit_rate - I2C bit rate.
  * @return uint32_t Adequate bit-rate value.
  *
  * HAL_LL_I2C_MASTER_SPEED_100K -- 100Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_400K -- 400Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_1M -- 1Mbit/s
  */
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
  * @brief  Set IICCTLn1, IICWLn and IICWHn based on fCLK and bit rate.
  *
  * Must be called while IICEn = 0.
  *
  * @param[in]  *map - I2C hardware context.
  */
static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buf - Pointer to data buffer.
  * @param[in]  len_read_data - Number of data to be read.
  * @param[in]  mode - HAL_LL_I2C_MASTER_WRITE_THEN_READ issues a restart
  *                    instead of waiting for a free bus.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode );

/**
  * @brief  Perform a write on the I2C bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buf - Pointer to data buffer.
  * @param[in]  len_write_data - Number of data to be written.
  * @param[in]  mode - HAL_LL_I2C_MASTER_WRITE_THEN_READ keeps the bus
  *                    (no stop) so the read can restart.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl,
                                                hal_ll_pin_name_t sda,
                                                hal_ll_i2c_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( (hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_scl.pin_name != scl) ||
         (hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_sda.pin_name != sda) )
    {
        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false );

        hal_ll_i2c_master_map_pins( pin_check_result, index_list );

        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle =
            ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    low_level_handle->init_ll_state = false;
    hal_ll_i2c_hw_specifics_map_local->speed = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
        hal_ll_i2c_hw_specifics_map_local->address = addr;
    }
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                              read_data_buf,
                                              len_read_data,
                                              HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                               write_data_buf,
                                               len_write_data,
                                               HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle,
                                                uint8_t *write_data_buf,
                                                size_t len_write_data,
                                                uint8_t *read_data_buf,
                                                size_t len_read_data ) {
    hal_ll_err_t status;

    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    status = hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                 write_data_buf,
                                                 len_write_data,
                                                 HAL_LL_I2C_MASTER_WRITE_THEN_READ );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                              read_data_buf,
                                              len_read_data,
                                              HAL_LL_I2C_MASTER_WRITE_THEN_READ );
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_i2c_master_handle ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        // Pins back to input first, with IICEn = 0 the output latch (0) would hold the bus low.
        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );
        clear_reg_bit( &hal_ll_i2c_get_ctrl_struct( hal_ll_i2c_hw_specifics_map_local->ctrl_base )->iicctl0,
                       HAL_LL_I2C_IICCTL0_IICE );
        hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_local, false );

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t status;

    status = hal_ll_i2c_master_wait_for_idle( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    status = hal_ll_i2c_master_start( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    status = hal_ll_i2c_master_send_address( map, HAL_LL_I2C_DIRECTION_WRITE );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        hal_ll_i2c_master_stop( map );
        return status;
    }

    for ( size_t i = 0; i < len_write_data; i++ ) {
        // Writing IICAn also releases the wait from the previous byte.
        write_reg( &hal_ll_hw_reg->iica, write_data_buf[i] );

        if ( !hal_ll_i2c_master_wait_for_interrupt( map ) ) {
            hal_ll_i2c_master_stop( map );
            return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }

        if ( !check_reg_bit( &hal_ll_hw_reg->iics, HAL_LL_I2C_IICS_ACKD ) ) {
            hal_ll_i2c_master_stop( map );
            return HAL_LL_I2C_MASTER_NACK;
        }
    }

    // Bus is kept in the 9th clock wait, read_bare_metal() generates the restart.
    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) {
        return HAL_LL_I2C_MASTER_SUCCESS;
    }

    return hal_ll_i2c_master_stop( map );
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );
    hal_ll_err_t status;

    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        status = hal_ll_i2c_master_wait_for_idle( map );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    }

    status = hal_ll_i2c_master_start( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) {
            hal_ll_i2c_master_stop( map );
        }
        return status;
    }

    status = hal_ll_i2c_master_send_address( map, HAL_LL_I2C_DIRECTION_READ );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        hal_ll_i2c_master_stop( map );
        return status;
    }

    if ( !len_read_data ) {
        return hal_ll_i2c_master_stop( map );
    }

    // Wait after the 8th clock (WTIMn = 0) so ACKEn can still be changed before the 9th.
    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_ACKE );
    clear_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WTIM );
    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WREL );

    for ( size_t i = 0; i < len_read_data; i++ ) {
        if ( !hal_ll_i2c_master_wait_for_interrupt( map ) ) {
            status = HAL_LL_I2C_MASTER_TIMEOUT_READ;
            break;
        }

        read_data_buf[i] = read_reg( &hal_ll_hw_reg->iica );

        if ( i == ( len_read_data - 1 ) ) {
            // NACK the last byte, wait moves back to the 9th clock so the stop can follow.
            clear_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_ACKE );
            set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WTIM );
            set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WREL );

            if ( !hal_ll_i2c_master_wait_for_interrupt( map ) ) {
                status = HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        } else {
            set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WREL );
        }
    }

    // Restore the transmit defaults set in hal_ll_i2c_init().
    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_WTIM );
    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_ACKE );

    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        hal_ll_i2c_master_stop( map );
        return status;
    }

    return hal_ll_i2c_master_stop( map );
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );
    uint16_t time_counter = map->timeout;

    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_STT );

    // STDn = 1 once the (re)start is on the bus, STCFn = 1 if it was refused (IICRSVn = 1).
    while ( !check_reg_bit( &hal_ll_hw_reg->iics, HAL_LL_I2C_IICS_STD ) ) {
        if ( check_reg_bit( &hal_ll_hw_reg->iicf, HAL_LL_I2C_IICF_STCF ) ) {
            return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
        }
        if ( map->timeout ) {
            if ( !time_counter-- ) {
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
            }
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );

    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_SPT );

    if ( !hal_ll_i2c_master_wait_for_bit( map, &hal_ll_hw_reg->iics, HAL_LL_I2C_IICS_SPD ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
    }

    // Drop the INTIICAn request raised by the stop condition (SPIEn = 1).
    clear_reg_bit( hal_ll_i2c_reg8( map->if_reg ), map->int_bit );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_send_address( hal_ll_i2c_hw_specifics_map_t *map, uint8_t direction ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    clear_reg_bit( hal_ll_i2c_reg8( map->if_reg ), map->int_bit );
    write_reg( &hal_ll_hw_reg->iica, ( map->address << 1 ) | direction );

    if ( !hal_ll_i2c_master_wait_for_interrupt( map ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_START;
    }

    if ( !check_reg_bit( &hal_ll_hw_reg->iics, HAL_LL_I2C_IICS_ACKD ) ) {
        return HAL_LL_I2C_MASTER_NACK;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static bool hal_ll_i2c_master_wait_for_bit( hal_ll_i2c_hw_specifics_map_t *map, volatile uint8_t *reg, uint8_t bit ) {
    uint16_t time_counter = map->timeout;

    while ( !check_reg_bit( reg, bit ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- ) {
                return false;
            }
        }
    }

    return true;
}

static bool hal_ll_i2c_master_wait_for_interrupt( hal_ll_i2c_hw_specifics_map_t *map ) {
    if ( !hal_ll_i2c_master_wait_for_bit( map, hal_ll_i2c_reg8( map->if_reg ), map->int_bit ) ) {
        return false;
    }

    clear_reg_bit( hal_ll_i2c_reg8( map->if_reg ), map->int_bit );

    return true;
}

static void hal_ll_i2c_master_set_pins_config( hal_ll_i2c_hw_specifics_map_t *map, uint32_t config ) {
    module_struct module;

    module.pins[0] = map->pins.pin_scl.pin_name;
    module.pins[1] = map->pins.pin_sda.pin_name;
    module.pins[2] = GPIO_MODULE_STRUCT_END;

    module.configs[0] = config;
    module.configs[1] = config;
    module.configs[2] = GPIO_MODULE_STRUCT_END;

    hal_ll_gpio_module_struct_init( &module, true );
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    if ( ( map->pins.pin_scl.pin_name != HAL_LL_PIN_NC ) && ( map->pins.pin_sda.pin_name != HAL_LL_PIN_NC ) ) {
        if ( hal_ll_state ) {
            // One PIOR12 field routes both SCLAn and SDAAn.
            hal_ll_pior_set_field( HAL_LL_I2C_PIOR_REG, hal_ll_i2c_pior_shift( map->module_index ),
                                   HAL_LL_I2C_PIOR_WIDTH, map->pins.pin_scl.pin_af );
        }

        // Input in both cases, the pins only become outputs once IICEn = 1 (see hal_ll_i2c_init()).
        hal_ll_i2c_master_set_pins_config( map, GPIO_CFG_DIGITAL_INPUT );
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins.
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;

    // SCL and SDA could have different alternate function settings,
    // hence save both AF values.
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        }
    }
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle ==
                 hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size =
            ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size =
            ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t scl_index;
    uint16_t sda_index;

    if ( (HAL_LL_PIN_NC == scl) || (HAL_LL_PIN_NC == sda) ) {
        return HAL_LL_PIN_NC;
    }

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[ scl_index ].pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[ sda_index ].pin == sda ) {
                    if ( hal_ll_i2c_scl_map[ scl_index ].module_index ==
                                hal_ll_i2c_sda_map[ sda_index ].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;

                        // Map module number to map index
                        for ( uint8_t map_member = 0; map_member < I2C_MODULE_COUNT + 1; map_member++  ) {
                            if ( hal_ll_i2c_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                                hal_ll_module_id = map_member;
                                break;
                            }
                        }

                        // Map pin names
                        index_list[hal_ll_module_id].pin_scl = scl_index;
                        index_list[hal_ll_module_id].pin_sda = sda_index;

                        // Check if module is taken
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_i2c_master_handle ) {
                            return hal_ll_module_id;
                        } else if ( I2C_MODULE_COUNT == ++index_counter ) {
                            return --index_counter;
                        }
                    }
                }
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( check_reg_bit( &hal_ll_hw_reg->iicf, HAL_LL_I2C_IICF_IICBSY ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- ) {
                return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
            }
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );
    uint32_t fclk = HAL_LL_I2C_MCU_CLOCK_HZ;
    uint32_t fmck = fclk;
    uint8_t iicctl1 = 0;
    float wl_frac, wh_frac, wl, wh;

    if ( fclk > HAL_LL_I2C_FMCK_MAX_HZ ) {
        fmck = fclk / 2;
        iicctl1 |= ( 1 << HAL_LL_I2C_IICCTL1_PRS );
    }

    // Duty cycle per mode, R01UH1082 20.4.2.
    if ( map->speed >= HAL_LL_I2C_MASTER_SPEED_1M ) {
        wl_frac = 0.50f;
        wh_frac = 0.50f;
        iicctl1 |= ( 1 << HAL_LL_I2C_IICCTL1_SMC ) | ( 1 << HAL_LL_I2C_IICCTL1_DFC );
    } else if ( map->speed >= HAL_LL_I2C_MASTER_SPEED_400K ) {
        wl_frac = 0.52f;
        wh_frac = 0.48f;
        iicctl1 |= ( 1 << HAL_LL_I2C_IICCTL1_SMC ) | ( 1 << HAL_LL_I2C_IICCTL1_DFC );
    } else {
        wl_frac = 0.47f;
        wh_frac = 0.53f;
    }

    write_reg( &hal_ll_ctrl_reg->iicctl1, iicctl1 );

    // Fractional parts are rounded up.
    wl = ( wl_frac / (float)map->speed ) * (float)fmck + 0.999f;
    wh = ( ( wh_frac / (float)map->speed ) - HAL_LL_I2C_RISE_FALL_TIME_S ) * (float)fmck + 0.999f;

    if ( wl > HAL_LL_I2C_IICWLH_MAX ) {
        wl = HAL_LL_I2C_IICWLH_MAX;
    }
    if ( wh > HAL_LL_I2C_IICWLH_MAX ) {
        wh = HAL_LL_I2C_IICWLH_MAX;
    } else if ( wh < 1.0f ) {
        wh = 1.0f;
    }

    write_reg( &hal_ll_ctrl_reg->iicwl, (uint8_t)wl );
    write_reg( &hal_ll_ctrl_reg->iicwh, (uint8_t)wh );
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );

    // IICCTLn1, IICWLn/IICWHn, SVAn and IICFn setup bits may only be written while IICEn = 0.
    clear_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_IICE );

    hal_ll_i2c_calculate_speed( map );

    write_reg( &hal_ll_ctrl_reg->sva, 0x00 );

    // STCENn = 1: start allowed right after IICEn = 1 without detecting a stop first (single master).
    // IICRSVn = 1: no reservation, a refused start shows up as STCFn = 1 instead of waiting silently.
    write_reg( &hal_ll_hw_reg->iicf, ( 1 << HAL_LL_I2C_IICF_STCEN ) | ( 1 << HAL_LL_I2C_IICF_IICRSV ) );
}

static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    #ifdef I2C_MODULE_1
    uint8_t per0_bit = ( hal_ll_i2c_module_num( I2C_MODULE_1 ) == map->module_index ) ?
                       PER0_IICA1EN_POS : PER0_IICA0EN_POS;
    #else
    uint8_t per0_bit = PER0_IICA0EN_POS;
    #endif

    if ( hal_ll_state ) {
        // IICAnRES shares the PER0 bit position in PRR0.
        clear_reg_bit( hal_ll_i2c_reg8( HAL_LL_I2C_PRR0_ADDR ), per0_bit );
        set_reg_bit( hal_ll_i2c_reg8( HAL_LL_I2C_PER0_ADDR ), per0_bit );
    } else {
        clear_reg_bit( hal_ll_i2c_reg8( HAL_LL_I2C_PER0_ADDR ), per0_bit );
    }
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_i2c_ctrl_handle_t *hal_ll_ctrl_reg = hal_ll_i2c_get_ctrl_struct( map->ctrl_base );

    hal_ll_i2c_master_module_enable( map, true );

    // Polled operation, keep INTIICAn masked and use only its request flag.
    set_reg_bit( hal_ll_i2c_reg8( map->mk_reg ), map->int_bit );

    // Release the pins before IICEn = 0, otherwise the output latch (0) pulls the bus low.
    hal_ll_i2c_master_alternate_functions_set_state( map, true );

    hal_ll_i2c_hw_init( map );

    // ACKEn = WTIMn = SPIEn = 1, then IICEn = 1.
    write_reg( &hal_ll_ctrl_reg->iicctl0, ( 1 << HAL_LL_I2C_IICCTL0_ACKE ) |
                                          ( 1 << HAL_LL_I2C_IICCTL0_WTIM ) |
                                          ( 1 << HAL_LL_I2C_IICCTL0_SPIE ) );
    set_reg_bit( &hal_ll_ctrl_reg->iicctl0, HAL_LL_I2C_IICCTL0_IICE );

    // IICAn owns the pins now, output mode with latch 0 lets it drive them (N-ch open drain).
    hal_ll_i2c_master_set_pins_config( map, GPIO_CFG_DIGITAL_OUTPUT );

    clear_reg_bit( hal_ll_i2c_reg8( map->if_reg ), map->int_bit );
}

// ------------------------------------------------------------------------- END
