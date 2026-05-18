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
 * @file  hal_ll_i3c.c
 * @brief I3C HAL LOW LEVEL layer implementation.
 */

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_i3c.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i3c_get_base_struct(_handle) ((hal_ll_i3c_base_handle_t *)_handle)

/*!< @brief Macros defining bit location. */
#define HAL_LL_I3C_SCR_TEIE         (2)

/*!< @brief I2C register structure */
typedef struct {
    uint32_t prts;
    uint32_t cectl;
    uint32_t bctl;
    uint32_t msdvad;
    uint32_t reserved1;
    uint32_t rstctl;
    uint32_t prsst;
    uint32_t reserved2[2];
    uint32_t inst;
    uint32_t inste;
    uint32_t inie;
    uint32_t instfc;
    uint32_t reserved3;
    uint32_t dvct;
    uint32_t reserved4[4];
    uint32_t ibinctl;
    uint32_t reserved5;
    uint32_t bfctl;
    uint32_t svctl;
    uint32_t reserved6[2];
    uint32_t refckctl;
    uint32_t stdbr;
    uint32_t extbr;
    uint32_t bfrecdt;
    uint32_t bavlcdt;
    uint32_t bidlcdt;
    uint32_t outctl;
    uint32_t inctl;
    uint32_t tmoctl;
    uint32_t reserved7;
    uint32_t wuctl;
    uint32_t reserved8;
    uint32_t ackctl;
    uint32_t scstrctl;
    uint32_t reserved9[2];
    uint32_t scstlctl;
    uint32_t reserved10[3];
    uint32_t svtdlg0;
    uint32_t reserved11[23];
    uint32_t stctl;
    uint32_t atctl;
    uint32_t attrg;
    uint32_t atccnte;
    uint32_t reserved12[4];
    uint32_t cndctl;
    uint32_t reserved13[3];
    uint32_t ncmdqp;
    uint32_t nrspqp;
    uint32_t ntdtbp0;
    uint32_t reserved14[8];
    uint32_t nibiqp;
    uint32_t nrsqp;
    uint32_t hcmdqp;
    uint32_t hrspqp;
    uint32_t htdtbp;
    uint32_t nqthctl;
    uint32_t ntbthctl0;
    uint32_t reserved15[10];
    uint32_t nrqthctl;
    uint32_t hqthctl;
    uint32_t htbthctl;
    uint32_t reserved16;
    uint32_t bst;
    uint32_t bste;
    uint32_t bie;
    uint32_t bstfc;
    uint32_t ntst;
    uint32_t ntste;
    uint32_t ntie;
    uint32_t ntstfc;
    uint32_t reserved17[4];
    uint32_t htst;
    uint32_t htste;
    uint32_t htie;
    uint32_t htstfc;
    uint32_t bcst;
    uint32_t svst;
    uint32_t wust;
    uint32_t mrccpt;
    uint32_t reserved18;
    uint32_t datbas0;
    uint32_t reserved19;
    uint32_t datbas1;
    uint32_t reserved20;
    uint32_t datbas2;
    uint32_t reserved21;
    uint32_t datbas3;
    uint32_t reserved22;
    uint32_t datbas4;
    uint32_t reserved23;
    uint32_t datbas5;
    uint32_t reserved24;
    uint32_t datbas6;
    uint32_t reserved25;
    uint32_t datbas7;
    uint32_t reserved26[16];
    uint32_t exdatbas;
    uint32_t reserved27[3];
    uint32_t sdatbas0;
    uint32_t sdatbas1;
    uint32_t sdatbas2;
    uint32_t reserved28[5];
    uint32_t msdct0;
    uint32_t msdct1;
    uint32_t msdct2;
    uint32_t msdct3;
    uint32_t msdct4;
    uint32_t msdct5;
    uint32_t msdct6;
    uint32_t msdct7;
    uint32_t reserved29[12];
    uint32_t svdct;
    uint32_t sdctpidl;
    uint32_t sdctpidh;
    uint32_t reserved30;
    uint32_t svdvad0;
    uint32_t svdvad1;
    uint32_t svdvad2;
    uint32_t reserved31[5];
    uint32_t csecmd;
    uint32_t ceactst;
    uint32_t cmwlg;
    uint32_t cmrlg;
    uint32_t cetstmd;
    uint32_t cgdvst;
    uint32_t cmdspw;
    uint32_t cmdspr;
    uint32_t cmdspt;
    uint32_t cetsm;
    uint32_t cetss;
    uint32_t cghdrcap;
    uint32_t bitcnt;
    uint32_t reserved32[4];
    uint32_t nqstlv;
    uint32_t ndbstlv0;
    uint32_t reserved33[9];
    uint32_t nrsqstlv;
    uint32_t hqstlv;
    uint32_t hdbstlv;
    uint32_t prstdbg;
    uint32_t mserrcnt;
    uint32_t reserved34[3];
    uint32_t sc1cpt;
    uint32_t sc2cpt;
} hal_ll_i3c_base_handle_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I3C_SUCCESS = 0,
    HAL_LL_I3C_WRONG_PINS,
    HAL_LL_I3C_MODULE_ERROR,

    HAL_LL_I3C_ERROR = (-1)
} hal_ll_i3c_err_t;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize I3C module in I2C Master mode on hardware level.
  *
  * Initializes I3C module in I2C Master mode on hardware level,
  * based on beforehand set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i3c_i2c_hw_init( hal_ll_i3c_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I3C pin alternate function state to work in I2C Master mode.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I3C is to work in I2C Master mode.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i3c_i2c_alternate_functions_set_state( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state );

/**
  * @brief  Set I3C speed registers based on clock and requested bit rate.
  *
  * Calculates and sets the I3C bit rate by configuring the SPBR register,
  * based on the PCLK clock and desired speed.
  *
  * @param[in]  base     Base address for the module in use.
  * @param[in]  speed    Requested bitrate value.
  * @param[in]  i3c_mode I3C mode in use.
  * @return None
  */
static void hal_ll_i3c_i2c_calculate_speed( uint32_t base, uint32_t speed, hal_ll_i3c_mode_t i3c_mode );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_i3c_i2c_write_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_i3c_i2c_end_mode_t mode ) {
    hal_ll_i3c_base_handle_t *hal_ll_hw_reg = hal_ll_i3c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;


    return HAL_LL_I3C_SUCCESS;
}

hal_ll_err_t hal_ll_i3c_i2c_read_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_i3c_i2c_end_mode_t mode ) {
    hal_ll_i3c_base_handle_t *hal_ll_hw_reg = hal_ll_i3c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = 0xFF;
    uint8_t dummy_read = 0;

    return HAL_LL_I3C_SUCCESS;
}

void hal_ll_i3c_module_enable( hal_ll_i3c_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef I3C_MODULE_0
        case ( hal_ll_i3c_module_num( I3C_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS )) :
                                        ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS ));
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_i3c_i2c_init( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    // Enable I3C peripheral
    hal_ll_i3c_module_enable( map, true );

    hal_ll_i3c_i2c_alternate_functions_set_state( map, true );

    hal_ll_i3c_i2c_hw_init( map );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_i3c_i2c_alternate_functions_set_state( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[1] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_i3c_i2c_calculate_speed( uint32_t base, uint32_t speed, hal_ll_i3c_mode_t i3c_mode ) {
    hal_ll_i3c_base_handle_t *hal_ll_hw_reg = hal_ll_i3c_get_base_struct( base );

    uint8_t best_cks = 0, best_brr = 0;
    double best_error = 100.0;

    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );

}

static void hal_ll_i3c_i2c_hw_init( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    hal_ll_i3c_base_handle_t *hal_ll_hw_reg = hal_ll_i3c_get_base_struct( map->base );

}

// ------------------------------------------------------------------------- END
