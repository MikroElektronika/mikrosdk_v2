/****************************************************************************
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file buzz.c
 * @brief BUZZ Click Driver.
 */

#include "buzz.h"

void buzz_cfg_setup ( buzz_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->pwm = HAL_PIN_NC;

	cfg->dev_pwm_freq = BUZZ_DEF_FREQ;
}

err_t buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg ) {
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return PWM_SUCCESS;

}

err_t buzz_set_duty_cycle ( buzz_t *ctx, float duty_cycle ) {
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t buzz_pwm_stop ( buzz_t *ctx ) {
    return pwm_stop( &ctx->pwm );
}

err_t buzz_pwm_start ( buzz_t *ctx ) {
    return pwm_start( &ctx->pwm );
}
void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint16_t level, uint16_t duration ) {
    pwm_set_freq( &ctx->pwm, freq );
    ctx->pwm_freq = freq;
    buzz_pwm_start( ctx );
    buzz_set_duty_cycle( ctx, level / 1000.0 );

    while ( duration )
    {
        Delay_1ms( );
        duration--;
    }
    buzz_pwm_stop( ctx );
}

// ------------------------------------------------------------------------- END
