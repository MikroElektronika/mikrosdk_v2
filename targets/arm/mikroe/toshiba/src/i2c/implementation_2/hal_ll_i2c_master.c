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
 * @brief I2C master HAL LOW LEVEL layer implementation for I2C Interface Version A (EI2C).
 *
 * Used by TMPM4L devices. Transfer procedures follow RM "I2C Interface Version A (EI2C)",
 * chapter 5.1 Data Transfer Procedure.
 */
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_cg.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M (1000000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT (10000)

#define GPIO_CFG_I2C_SCL (GPIO_CFG_CR |\
                          GPIO_CFG_IE |\
                          GPIO_CFG_OD |\
                          GPIO_CFG_PULL_UP)

#define GPIO_CFG_I2C_SDA (GPIO_CFG_CR |\
                          GPIO_CFG_IE |\
                          GPIO_CFG_OD |\
                          GPIO_CFG_PULL_UP)

/*!< @brief CGFSYSENB bits for EI2C channels */
#define HAL_LL_CG_I2C0_BIT              (10)
#define HAL_LL_CG_I2C1_BIT              (11)

/*!< @brief [I2CxARST] */
#define HAL_LL_I2C_ARST_SWRES_10        (0x02UL)
#define HAL_LL_I2C_ARST_SWRES_01        (0x01UL)

/*!< @brief [I2CxAEN] */
#define HAL_LL_I2C_AEN_I2CM_MASK        (0x01UL)

/*!< @brief [I2CxACR0] */
#define HAL_LL_I2C_ACR0_DNF_POS         (12)
#define HAL_LL_I2C_ACR0_DNF_MASK        (0x7UL << HAL_LL_I2C_ACR0_DNF_POS)
#define HAL_LL_I2C_ACR0_NFSEL_MASK      (0x800UL)
#define HAL_LL_I2C_ACR0_NACKE_MASK      (0x04UL)
#define HAL_LL_I2C_ACR0_ALE_MASK        (0x01UL)

/*!< @brief [I2CxACR1] */
#define HAL_LL_I2C_ACR1_ACKWAIT_MASK    (0x10UL)
#define HAL_LL_I2C_ACR1_ACKSEL_MASK     (0x08UL)
#define HAL_LL_I2C_ACR1_SP_MASK         (0x04UL)
#define HAL_LL_I2C_ACR1_RS_MASK         (0x02UL)
#define HAL_LL_I2C_ACR1_ST_MASK         (0x01UL)

/*!< @brief [I2CxASR0] */
#define HAL_LL_I2C_ASR0_MST_MASK        (0x08UL)
#define HAL_LL_I2C_ASR0_BB_MASK         (0x02UL)
#define HAL_LL_I2C_ASR0_ACKF_MASK       (0x01UL)

/*!< @brief [I2CxASR1] - read: flag, write 1: clear flag */
#define HAL_LL_I2C_ASR1_AL_MASK         (0x80UL)
#define HAL_LL_I2C_ASR1_NACK_MASK       (0x40UL)
#define HAL_LL_I2C_ASR1_RBF_MASK        (0x20UL)
#define HAL_LL_I2C_ASR1_TBE_MASK        (0x10UL)
#define HAL_LL_I2C_ASR1_TEND_MASK       (0x08UL)
#define HAL_LL_I2C_ASR1_SPCF_MASK       (0x04UL)
#define HAL_LL_I2C_ASR1_RSCF_MASK       (0x02UL)
#define HAL_LL_I2C_ASR1_STCF_MASK       (0x01UL)
#define HAL_LL_I2C_ASR1_CLEAR_ALL       (0x3FFFUL)

/*!< @brief [I2CxAPM] */
#define HAL_LL_I2C_APM_SDA_MASK         (0x02UL)
#define HAL_LL_I2C_APM_SCL_MASK         (0x01UL)

/*!< @brief [I2CxAPRS] PRS[5:0] = divider - 1, divider 1..64 */
#define HAL_LL_I2C_APRS_DIV_MAX         (64)
/*!< @brief [I2CxASCL] */
#define HAL_LL_I2C_ASCL_SCLL_POS        (8)
#define HAL_LL_I2C_ASCL_MAX             (255)
/*!< @brief [I2CxACR0] DNF[2:0] = number of PRSCK cycles - 1 */
#define HAL_LL_I2C_DNF_CYCLES_MAX       (8)
/*!< @brief Minimum noise filter time in picoseconds, RM 3.3.1 (1) */
#define HAL_LL_I2C_DNF_MIN_PS           (50000UL)

// I2C transfer modes
#define HAL_LL_I2C_WRITE                (0x00U)
#define HAL_LL_I2C_READ                 (0x01U)

/*!< @brief EI2C register structure */
typedef struct {
    uint32_t arst;    /* 0x0000  I2C reset register                */
    uint32_t aen;     /* 0x0004  I2C bus enable register           */
    uint32_t acr0;    /* 0x0008  I2C control register 0            */
    uint32_t acr1;    /* 0x000C  I2C control register 1            */
    uint32_t adbrt;   /* 0x0010  Transmission data buffer          */
    uint32_t adbrr;   /* 0x0014  Reception data buffer             */
    uint32_t asr0;    /* 0x0018  Status register 0                 */
    uint32_t asr1;    /* 0x001C  Status register 1 (W1C flags)     */
    uint32_t aprs;    /* 0x0020  Prescaler clock setting           */
    uint32_t ascl;    /* 0x0024  SCL width setting                 */
    uint32_t aar1;    /* 0x0028  1st target address                */
    uint32_t aar2;    /* 0x002C  2nd target address                */
    uint32_t aie;     /* 0x0030  Interrupt/DMA setting             */
    uint32_t apm;     /* 0x0034  Bus pin monitor                   */
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;
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
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_master_timeout_t;

/*!< @brief Enum containing predefined module standard speed values */
typedef enum {
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;

/*!< @brief I2C-bus timing in nanoseconds for one speed mode */
typedef struct {
    uint32_t t_low;      /* Minimum SCL LOW time  */
    uint32_t t_high;     /* Minimum SCL HIGH time */
    uint32_t t_rise_fall; /* tr + tf used by RM 3.3.1 (2) for the given speed */
} hal_ll_i2c_timing_t;

// ------------------------------------------------------------------ VARIABLES
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef I2C_MODULE_0
    {HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
     HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
     HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0}
};

/*!< @brief I2C-bus specification minimums per speed mode (standard, fast, fast-plus) */
static const hal_ll_i2c_timing_t hal_ll_i2c_timing[] = {
    { 4700, 4000, 1300 },
    { 1300,  600,  600 },
    {  500,  260,  240 }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Full I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I2C pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I2C is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

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
 * Maps pin names and alternate function values for
 * I2C SCL and SDA pins.
 *
 * @param[in]  module_index I2C HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCL and SDA map index values
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list );

/**
  * @brief  Waits until I2C bus is free.
  *
  * Polls [I2CxASR0]<BB> and waits until bus is free.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Waits for [I2CxASR1] status flags.
  *
  * Polls [I2CxASR1] until any of the flags from mask or <AL> is set.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  mask - [I2CxASR1] flags to wait for.
  * @return uint32_t [I2CxASR1] value, or 0 on timeout.
  */
static uint32_t hal_ll_i2c_master_wait_status( hal_ll_i2c_hw_specifics_map_t *map, uint32_t mask );

/**
  * @brief  Generates STOP condition and releases the bus.
  *
  * Requests STOP condition, releases clock stretch caused by
  * <TEND> or <NACK> and waits for STOP condition detection.
  * Module is re-initialized if STOP condition is not detected.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Generates START condition and sends target address.
  *
  * Generates START condition (or Repeated START condition if module is
  * currently controlling the bus) and writes target address with
  * direction bit to transmission buffer.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  restart - Generate Repeated START condition.
  * @param[in]  direction - HAL_LL_I2C_WRITE or HAL_LL_I2C_READ.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map, bool restart, uint8_t direction );

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
  * @brief  Set I2C speed registers based on clock and bit rate.
  *
  * Sets [I2CxAPRS], [I2CxASCL] and [I2CxACR0]<DNF> so that SCL LOW and HIGH
  * widths satisfy I2C-bus specification minimums for selected speed mode.
  *
  * @param[in]  *map - I2C hardware context.
  * @return uint32_t [I2CxACR0]<DNF> field value to be used.
  */
static uint32_t hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buf - Pointer to data buffer.
  * @param[in]  len_read_data - Number of data to be read.
  * @param[in]  mode - End mode.
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
  * @param[in]  mode - End mode.
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
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                    write_data_buf,
                                                    len_write_data,
                                                    HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                   read_data_buf,
                                                   len_read_data,
                                                   HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
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

        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint32_t hal_ll_i2c_master_wait_status( hal_ll_i2c_hw_specifics_map_t *map, uint32_t mask ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint32_t status;

    while ( !( ( status = read_reg( &hal_ll_hw_reg->asr1 ) ) & ( mask | HAL_LL_I2C_ASR1_AL_MASK ) ) ) {
        if ( !time_counter-- ) {
            return 0;
        }
    }

    return status;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // STOP request is valid only in controller mode, RM 4.2.4
    if ( read_reg_bits( &hal_ll_hw_reg->asr0, HAL_LL_I2C_ASR0_MST_MASK ) ) {
        set_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_SP_MASK );

        // Release clock stretch caused by transfer end or NACK detection, RM 5.1.2
        write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_TEND_MASK | HAL_LL_I2C_ASR1_NACK_MASK );

        if ( !hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_SPCF_MASK ) ) {
            // Bus is stuck, reset the module to recover
            hal_ll_i2c_hw_init( map );
            return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    }

    // For next communication, clear the flags
    write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
    clear_reg( &hal_ll_hw_reg->acr1 );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map, bool restart, uint8_t direction ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint32_t status;
    uint32_t condition_flag;

    if ( restart ) {
        // Module waits after the last transmitted byte (<TEND> = 1), RM 5.1.3
        set_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_RS_MASK );
        write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_TEND_MASK );
        condition_flag = HAL_LL_I2C_ASR1_RSCF_MASK;
    } else {
        if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_wait_for_idle( map ) ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }

        write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
        clear_reg( &hal_ll_hw_reg->acr1 );

        set_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_ST_MASK );
        condition_flag = HAL_LL_I2C_ASR1_STCF_MASK;
    }

    status = hal_ll_i2c_master_wait_status( map, condition_flag );
    if ( !status ) {
        hal_ll_i2c_hw_init( map );
        return HAL_LL_I2C_MASTER_TIMEOUT_START;
    }
    if ( status & HAL_LL_I2C_ASR1_AL_MASK ) {
        write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
    }

    // Clear START/Repeated START detection flag, then set target address to release clock stretch
    write_reg( &hal_ll_hw_reg->asr1, condition_flag );
    write_reg( &hal_ll_hw_reg->adbrt, ( map->address << 1 ) | direction );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t err;
    uint32_t status;

    if ( HAL_LL_I2C_MASTER_SUCCESS != ( err = hal_ll_i2c_master_start( map, false, HAL_LL_I2C_WRITE ) ) ) {
        return err;
    }

    // Target address acknowledge sets <TBE>, RM 5.1.2
    status = hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_TBE_MASK |
                                                 HAL_LL_I2C_ASR1_TEND_MASK |
                                                 HAL_LL_I2C_ASR1_NACK_MASK );

    for ( size_t i = 0; ; i++ ) {
        if ( !status ) {
            hal_ll_i2c_master_stop( map );
            return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
        if ( status & HAL_LL_I2C_ASR1_AL_MASK ) {
            write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
            return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
        }
        if ( ( status & HAL_LL_I2C_ASR1_NACK_MASK ) ||
             read_reg_bits( &hal_ll_hw_reg->asr0, HAL_LL_I2C_ASR0_ACKF_MASK ) ) {
            hal_ll_i2c_master_stop( map );
            return HAL_LL_I2C_MASTER_ERROR;
        }

        if ( i == len_write_data ) {
            break;
        }

        // Writing data clears <TBE>, clearing <TEND> releases clock stretch if transfer had ended
        write_reg( &hal_ll_hw_reg->adbrt, write_data_buf[i] );
        if ( status & HAL_LL_I2C_ASR1_TEND_MASK ) {
            write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_TEND_MASK );
        }

        // Data is not pre-loaded, so the module waits with <TEND> = 1 after each acknowledged byte
        status = hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_TEND_MASK | HAL_LL_I2C_ASR1_NACK_MASK );
    }

    // For WRITE_THEN_READ mode, module stays in WAIT state for Repeated START condition
    if ( HAL_LL_I2C_MASTER_END_MODE_STOP == mode ) {
        return hal_ll_i2c_master_stop( map );
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter;
    hal_ll_err_t err;
    uint32_t status;

    if ( !len_read_data ) {
        return ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) ? hal_ll_i2c_master_stop( map ) : HAL_LL_I2C_MASTER_SUCCESS;
    }

    if ( HAL_LL_I2C_MASTER_SUCCESS != ( err = hal_ll_i2c_master_start( map,
                                                                       HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode,
                                                                       HAL_LL_I2C_READ ) ) ) {
        return err;
    }

    // Insert WAIT before each ACK, so that ACK/NACK can be selected per byte, RM 5.1.3
    set_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_ACKWAIT_MASK );

    // Check target address acknowledge
    status = hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_TBE_MASK |
                                                 HAL_LL_I2C_ASR1_RBF_MASK |
                                                 HAL_LL_I2C_ASR1_NACK_MASK );
    if ( !status ) {
        hal_ll_i2c_master_stop( map );
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }
    if ( status & HAL_LL_I2C_ASR1_AL_MASK ) {
        write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
    }
    if ( ( status & HAL_LL_I2C_ASR1_NACK_MASK ) ||
         read_reg_bits( &hal_ll_hw_reg->asr0, HAL_LL_I2C_ASR0_ACKF_MASK ) ) {
        hal_ll_i2c_master_stop( map );
        return HAL_LL_I2C_MASTER_ERROR;
    }

    for ( size_t i = 0; i < len_read_data; i++ ) {
        status = hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_RBF_MASK );
        if ( !status ) {
            hal_ll_i2c_master_stop( map );
            return HAL_LL_I2C_MASTER_TIMEOUT_READ;
        }
        if ( status & HAL_LL_I2C_ASR1_AL_MASK ) {
            write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
            return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
        }

        // Reading the buffer clears <RBF>
        read_data_buf[i] = ( uint8_t )read_reg( &hal_ll_hw_reg->adbrr );

        // <ACKSEL> may be written only while SCL is held low, RM 4.2.4
        time_counter = map->timeout;
        while ( read_reg_bits( &hal_ll_hw_reg->apm, HAL_LL_I2C_APM_SCL_MASK ) ) {
            if ( !time_counter-- ) {
                hal_ll_i2c_master_stop( map );
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        if ( i == ( len_read_data - 1 ) ) {
            // Last byte: NACK response with STOP request, writing <ACKSEL> releases clock stretch
            set_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_SP_MASK | HAL_LL_I2C_ACR1_ACKSEL_MASK );
        } else {
            // ACK response, writing <ACKSEL> releases clock stretch
            clear_reg_bits( &hal_ll_hw_reg->acr1, HAL_LL_I2C_ACR1_ACKSEL_MASK );
        }
    }

    if ( !hal_ll_i2c_master_wait_status( map, HAL_LL_I2C_ASR1_SPCF_MASK ) ) {
        hal_ll_i2c_hw_init( map );
        return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
    }

    // For next communication, clear the flags
    write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );
    clear_reg( &hal_ll_hw_reg->acr1 );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_I2C_SCL;
        module.configs[1] = GPIO_CFG_I2C_SDA;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;
    // SCL and SDA could have different alternate function settings,
    // hence save both AF values
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
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_1M ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        }
    }
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) /
                                        ( sizeof( hal_ll_i2c_master_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) /
                                        ( sizeof( hal_ll_i2c_master_handle_register_t ));

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
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( read_reg_bits( &hal_ll_hw_reg->asr0, HAL_LL_I2C_ASR0_BB_MASK ) ) {
        if ( !time_counter-- ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static uint32_t hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    const hal_ll_i2c_timing_t *timing;

    /*
     * RM 3.3.1 Serial Clock, digital noise filter (<NFSEL> = 0):
     *   tHIGH = ( SCLH + 3 + ( DNF + 1 ) ) * PRSCK period
     *   tLOW  = ( SCLL + 3 + ( DNF + 1 ) ) * PRSCK period
     *   PRSCK period = ( PRS + 1 ) / fsys
     *   50ns / ( DNF + 1 ) <= PRSCK period <= tHIGH(min) / ( DNF + 2 )
     */
    CG_ClocksTypeDef cg;
    CG_GetClocksFrequency( &cg );
    uint32_t fsys_khz = cg.CG_FSYSM_Frequency / 1000;
    uint32_t fsys_period_ps = 1000000000UL / fsys_khz;

    // Speed is one of 100K, 400K or 1M, tolerate calculated (real) speed stored from previous init
    uint32_t target = map->speed ? map->speed : HAL_LL_I2C_MASTER_SPEED_100K;
    if ( target <= ( HAL_LL_I2C_MASTER_SPEED_100K * 2 ) ) {
        timing = &hal_ll_i2c_timing[ HAL_LL_I2C_MASTER_SPEED_STANDARD ];
    } else if ( target <= ( HAL_LL_I2C_MASTER_SPEED_400K + HAL_LL_I2C_MASTER_SPEED_400K / 2 ) ) {
        timing = &hal_ll_i2c_timing[ HAL_LL_I2C_MASTER_SPEED_FULL ];
    } else {
        timing = &hal_ll_i2c_timing[ HAL_LL_I2C_MASTER_SPEED_FAST ];
    }

    uint32_t t_low_ps  = timing->t_low * 1000UL;
    uint32_t t_high_ps = timing->t_high * 1000UL;
    uint32_t prs_div = 1, dnf_cycles = 1, scll = HAL_LL_I2C_ASCL_MAX, sclh = HAL_LL_I2C_ASCL_MAX;
    uint32_t prsck_ps = fsys_period_ps;

    // Use the fastest prescaler clock for which SCL widths fit into [I2CxASCL]
    for ( prs_div = 1; prs_div <= HAL_LL_I2C_APRS_DIV_MAX; prs_div++ ) {
        prsck_ps = fsys_period_ps * prs_div;

        // Noise filter should cover at least 50ns, but PRSCK * ( DNF + 2 ) must not exceed tHIGH
        dnf_cycles = ( HAL_LL_I2C_DNF_MIN_PS + prsck_ps - 1 ) / prsck_ps;
        if ( dnf_cycles > HAL_LL_I2C_DNF_CYCLES_MAX ) {
            dnf_cycles = HAL_LL_I2C_DNF_CYCLES_MAX;
        }
        while ( ( dnf_cycles > 1 ) && ( ( prsck_ps * ( dnf_cycles + 1 ) ) > t_high_ps ) ) {
            dnf_cycles--;
        }

        uint32_t low_cycles  = ( t_low_ps + prsck_ps - 1 ) / prsck_ps;
        uint32_t high_cycles = ( t_high_ps + prsck_ps - 1 ) / prsck_ps;
        scll = ( low_cycles > ( 3 + dnf_cycles + 1 ) ) ? ( low_cycles - 3 - dnf_cycles ) : 1;
        sclh = ( high_cycles > ( 3 + dnf_cycles ) ) ? ( high_cycles - 3 - dnf_cycles ) : 0;

        if ( ( scll <= HAL_LL_I2C_ASCL_MAX ) && ( sclh <= HAL_LL_I2C_ASCL_MAX ) ) {
            break;
        }
    }

    if ( prs_div > HAL_LL_I2C_APRS_DIV_MAX ) {
        prs_div = HAL_LL_I2C_APRS_DIV_MAX;
        scll = HAL_LL_I2C_ASCL_MAX;
        sclh = HAL_LL_I2C_ASCL_MAX;
    }

    write_reg( &hal_ll_hw_reg->aprs, prs_div - 1 );
    write_reg( &hal_ll_hw_reg->ascl, ( scll << HAL_LL_I2C_ASCL_SCLL_POS ) | sclh );

    // Update the speed with the real value, tr and tf as in RM 3.3.1 (2)
    uint32_t period_ns = ( ( ( scll + 3 + dnf_cycles ) + ( sclh + 3 + dnf_cycles ) ) * prsck_ps ) / 1000UL +
                         timing->t_rise_fall;
    map->speed = 1000000000UL / period_ns;

    return ( dnf_cycles - 1 ) << HAL_LL_I2C_ACR0_DNF_POS;
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_cg_base_handle_t  *hal_ll_cg_reg = (hal_ll_cg_base_handle_t *) HAL_LL_CG_BASE_ADDR;
    uint16_t time_counter = map->timeout;

    switch ( map->module_index ) {
        #ifdef I2C_MODULE_0
        case hal_ll_i2c_module_num( I2C_MODULE_0 ):
            set_reg_bit( &hal_ll_cg_reg->fsysenb, HAL_LL_CG_I2C0_BIT );  // Enable clock for EI2C0 module
            break;
        #endif
        #ifdef I2C_MODULE_1
        case hal_ll_i2c_module_num( I2C_MODULE_1 ):
            set_reg_bit( &hal_ll_cg_reg->fsysenb, HAL_LL_CG_I2C1_BIT );  // Enable clock for EI2C1 module
            break;
        #endif

        default:
            break;
    }

    // Software reset is asserted by the successive writes of 10 -> 01, RM 4.2.1
    write_reg( &hal_ll_hw_reg->arst, HAL_LL_I2C_ARST_SWRES_10 );
    write_reg( &hal_ll_hw_reg->arst, HAL_LL_I2C_ARST_SWRES_01 );

    // Device initialization, RM 5.1.1
    clear_reg( &hal_ll_hw_reg->aen );
    write_reg( &hal_ll_hw_reg->asr1, HAL_LL_I2C_ASR1_CLEAR_ALL );

    uint32_t acr0_dnf = hal_ll_i2c_calculate_speed( map );

    // Interrupts and DMA requests are not used
    clear_reg( &hal_ll_hw_reg->aie );

    // Digital noise filter, NACK detection at transmission and Arbitration Lost detection
    write_reg( &hal_ll_hw_reg->acr0, acr0_dnf | HAL_LL_I2C_ACR0_NACKE_MASK | HAL_LL_I2C_ACR0_ALE_MASK );
    clear_reg( &hal_ll_hw_reg->acr1 );

    // Check that I2C-bus is free before enabling pin control
    while ( ( read_reg( &hal_ll_hw_reg->apm ) & ( HAL_LL_I2C_APM_SCL_MASK | HAL_LL_I2C_APM_SDA_MASK ) ) !=
            ( HAL_LL_I2C_APM_SCL_MASK | HAL_LL_I2C_APM_SDA_MASK ) ) {
        if ( !time_counter-- ) {
            break;
        }
    }

    write_reg( &hal_ll_hw_reg->aen, HAL_LL_I2C_AEN_I2CM_MASK );
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_hw_init( map );
}

// ------------------------------------------------------------------------- END
