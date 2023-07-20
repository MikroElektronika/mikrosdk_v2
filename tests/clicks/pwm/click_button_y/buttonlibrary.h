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
 * \brief This file contains API for Button library Click driver.
 *
 * \addtogroup buttonlibrary Button library Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUTTONLIBRARY_H
#define BUTTONLIBRARY_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"
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
#define BUTTONLIBRARY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUTTONLIBRARY_RETVAL  uint8_t

#define BUTTONLIBRARY_OK           0x00
#define BUTTONLIBRARY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BUTTONLIBRARY_DEF_FREQ     500
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
    // Input pins

    digital_in_t int_pin;

    // Modules

    pwm_t pwm;

    // ctx variable

    uint16_t pwm_period;
    uint32_t pwm_freq;

} buttonlibrary_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t pwm;

    // Additional gpio pins

    pin_name_t int_pin;

    // static variable

    uint32_t dev_pwm_freq;

} buttonlibrary_cfg_t;

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
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void buttonlibrary_cfg_setup ( buttonlibrary_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buttonlibrary Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUTTONLIBRARY_RETVAL buttonlibrary_init ( buttonlibrary_t *ctx, buttonlibrary_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void buttonlibrary_set_duty_cycle ( buttonlibrary_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void buttonlibrary_pwm_stop ( buttonlibrary_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void buttonlibrary_pwm_start ( buttonlibrary_t *ctx );

/**
 * @brief Get button state function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the digital signal from the INT pin which tells us whether
 *              the button has been pressed or not.
 */
uint8_t buttonlibrary_get_button_state ( buttonlibrary_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUTTONLIBRARY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------- END
