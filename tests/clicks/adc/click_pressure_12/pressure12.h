/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2023 MikroElektronika d.o.o.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for Pressure 12 Click driver.
 *
 * \addtogroup pressure12 Pressure 12 Click Driver
 * @{
 */


#ifndef PRESSURE12_H
#define PRESSURE12_H

#include "drv_analog_in.h"
#include "pin_connections.h"

// -------------------------------------------------------------- PUBLIC MACROS

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PRESSURE12_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules

    analog_in_t adc;

} pressure12_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t an_pin;

    // Config variables

    analog_in_resolution_t resolution;   /** ADC Resolution */
    float vref;                          /** Reference Voltage */

} pressure12_cfg_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg Click configuration structure.
 *
 * @description This function initializes click configuration structure to init
 * state.
 * @note All used pins will be set to unconnected state.
 */
void pressure12_cfg_setup ( pressure12_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 *
 * @return See #err_t definition of data type.
 *            0  - Success,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
err_t pressure12_init ( pressure12_t *ctx, pressure12_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_out ADC value on the pin.
 *
 * @return See #err_t definition of data type.
 *
 * @description This function reads ADC value on the pin.
 */
err_t pressure12_read_pin_adc ( pressure12_t *ctx, uint16_t *data_out );

/**
 * @brief Generic function for read voltage.
 *
 * @param ctx Click object.
 * @param data_out Voltage value on the pin [V].
 *
 * @return See #err_t definition of data type.
 *
 * @description This function reads voltage value on the pin.
 */
err_t pressure12_read_pin_voltage ( pressure12_t *ctx, float *data_out );

/**
 * @brief Get pressure function.
 *
 * @param ctx Click object.
 * @param data_out Pressure value [mBar].
 *
 * @return See #err_t definition of data type.
 *
 * @description This function calculates pressure value detected on the
 * Pressure 12 click board.
 */
err_t pressure12_get_pressure ( pressure12_t *ctx, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
