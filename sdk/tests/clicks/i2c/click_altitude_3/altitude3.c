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
 */

#include "altitude3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void read_otp ( altitude3_t *ctx, uint16_t *out_data );

static void calc_conv_const ( uint32_t *p_pa, float *p_lut, float *out_data );

static void drv_read_9 ( altitude3_t *ctx, uint8_t *data_buf );

static uint8_t calculate_crc( uint8_t *data_buf, size_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void altitude3_cfg_setup ( altitude3_cfg_t *cfg )
{
    // Communication gpio pins

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = ALTITUDE3_SLAVE_ADDR;
    cfg->update_check_cfg = 0;
}

ALTITUDE3_RETVAL altitude3_init ( altitude3_t *ctx, altitude3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->update_check = cfg->update_check_cfg;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ALTITUDE3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return ALTITUDE3_OK;
}

void altitude3_default_cfg ( altitude3_t *ctx )
{
    uint8_t dummy;

    altitude3_soft_reset( ctx );
    Delay_100ms();
    altitude3_get_data( ctx, dummy );
}

void altitude3_generic_write ( altitude3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

void altitude3_generic_read ( altitude3_t *ctx, uint8_t *reg_buf, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, reg_buf, 2, data_buf, len );
}

uint8_t altitude3_measurement_mode ( altitude3_t *ctx, uint16_t mode_cmd )
{
    uint8_t ret_val;
    uint8_t temp_data[ 2 ];

    if ( ( mode_cmd == ALTITUDE3_LOW_POWER_T_FIRST ) ||
         ( mode_cmd == ALTITUDE3_NORMAL_T_FIRST ) ||
         ( mode_cmd == ALTITUDE3_LOW_NOISE_T_FIRST ) ||
         ( mode_cmd == ALTITUDE3_ULTRA_LOW_NOISE_T_FIRST ) )
    {
        ret_val = ALTITUDE3_T_FIRST_ORDER;
    }
    else if ( ( mode_cmd == ALTITUDE3_LOW_POWER_P_FIRST ) ||
              ( mode_cmd == ALTITUDE3_NORMAL_P_FIRST ) ||
              ( mode_cmd == ALTITUDE3_LOW_NOISE_P_FIRST ) ||
              ( mode_cmd == ALTITUDE3_ULTRA_LOW_NOISE_P_FIRST ) )
    {
        ret_val = ALTITUDE3_P_FIRST_ORDER;
    }
    else
    {
        return ALTITUDE3_ERROR;
    }

    temp_data[ 0 ] = mode_cmd >> 8;
    temp_data[ 1 ] = mode_cmd;

    altitude3_generic_write( ctx, temp_data[ 0 ], &temp_data[ 1 ], 1 );

    return ret_val;
}

void altitude3_soft_reset ( altitude3_t *ctx )
{
    uint8_t temp_data[ 2 ];

    temp_data[ 0 ] = 0x80;
    temp_data[ 1 ] = 0x5D;

    altitude3_generic_write( ctx, temp_data[ 0 ], &temp_data[ 1 ], 1 );

    ctx->update_check = 0;
}

uint8_t altitude3_read_adc_results ( altitude3_t *ctx, uint8_t read_order, int16_t *temperature, uint32_t *pressure )
{
    uint8_t temp_data[ 9 ];
    uint8_t temp_indx;
    uint8_t press_indx;

    i2c_master_read( &ctx->i2c, temp_data, 9 );

    if ( read_order == ALTITUDE3_T_FIRST_ORDER )
    {
        temp_indx = 0;
        press_indx = 3;
    }
    else if ( read_order == ALTITUDE3_P_FIRST_ORDER )
    {
        press_indx = 0;
        temp_indx = 6;
    }
    else
    {
        return ALTITUDE3_ERROR;
    }

    if ( calculate_crc( &temp_data[ temp_indx ], 2 ) != temp_data[ temp_indx + 2 ] )
    {
        return ALTITUDE3_ERROR;
    }
    else
    {
        *temperature = temp_data[ temp_indx ];
        *temperature <<= 8;
        *temperature |= temp_data[ temp_indx + 1 ];
    }

    if ( calculate_crc( &temp_data[ press_indx ], 2 ) != temp_data[ press_indx + 2 ] )
    {
        return ALTITUDE3_ERROR;
    }
    else
    {
        *pressure = temp_data[ press_indx ];
        *pressure <<= 8;
        *pressure |= temp_data[ press_indx + 1 ];
        *pressure <<= 8;
    }

    if ( calculate_crc( &temp_data[ press_indx + 3 ], 2 ) != temp_data[ press_indx + 3 + 2 ] )
    {
        return ALTITUDE3_ERROR;
    }
    else
    {
        *pressure |= temp_data[ press_indx + 3 ];
    }

    return ALTITUDE3_OK;
}

void altitude3_init_cfg ( altitude3_t *ctx, altitude3_param_t *s )
{
    uint16_t otp_data[ 4 ];
    uint8_t cnt;

    read_otp( ctx, otp_data );

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        s->sensor_const[ cnt ] = otp_data[ cnt ];
    }

    s->p_pa_calib[ 0 ] = 45000;
    s->p_pa_calib[ 1 ] = 80000;
    s->p_pa_calib[ 2 ] = 105000;
    s->lut_lower = 3.5 * 1048576.0;
    s->lut_upper = 11.5 * 1048576.0;
    s->quadr_factor = 1.0 / 16777216.0;
    s->offst_factor = 2048;
    s->min_delay_us = 100000;
}

uint8_t altitude3_get_data ( altitude3_t *ctx, uint8_t read_order )
{
    int16_t temp;
    uint32_t press;
    uint8_t error_check;
    static altitude3_param_t otp_param;
    int16_t volatile t;
    float s1;
    float sbuff[ 3 ];
    float abc_const[ 3 ];
    float res;

    if ( ctx->update_check == 0 )
    {
        altitude3_init_cfg( ctx, &otp_param );
        ctx->update_check = 1;

        return ALTITUDE3_INITIALIZED;
    }

    error_check = altitude3_read_adc_results( ctx, read_order, &temp, &press );

    if ( error_check == ALTITUDE3_ERROR )
    {
        return error_check;
    }

    t = ( int16_t )( temp - 32768 );
    s1 = otp_param.sensor_const[ 0 ];
    s1 *= t;
    s1 *= t;
    s1 *= otp_param.quadr_factor;
    s1 += otp_param.lut_lower;
    sbuff[ 0 ] = s1;
    res = otp_param.offst_factor;
    res *= otp_param.sensor_const[ 3 ];
    s1 = otp_param.sensor_const[ 1 ];
    s1 *= t;
    s1 *= t;
    s1 *= otp_param.quadr_factor;
    s1 += res;
    sbuff[ 1 ] = s1;
    s1 = otp_param.sensor_const[ 2 ];
    s1 *= t;
    s1 *= t;
    s1 *= otp_param.quadr_factor;
    s1 += otp_param.lut_upper;
    sbuff[ 2 ] = s1;

    calc_conv_const( otp_param.p_pa_calib, sbuff, abc_const );

    res =- 45.0 + 175.0/65536.0 * temp;
    ctx->sens_data.temperature = res;

    res = abc_const[ 2 ];
    res += ( double ) press;
    res = abc_const[ 1 ] / res;
    res += abc_const[ 0 ];
    res /= 100;
    ctx->sens_data.pressure = res;

    res = ctx->sens_data.pressure / 1013.96;
    res = pow( res, 0.19022 );
    res = 1.0 - res;
    s1 = ctx->sens_data.temperature;
    s1 += 273.15;
    s1 /= 0.0065;
    res *= s1;
    ctx->sens_data.altitude = res;

    return error_check;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void read_otp ( altitude3_t *ctx, uint16_t *out_data )
{
    uint8_t addr;
    uint8_t temp_data[ 4 ];
    uint8_t cnt;

    addr = 0xC5;
    temp_data[ 0 ] = 0x95;
    temp_data[ 1 ] = 0x00;
    temp_data[ 2 ] = 0x66;
    temp_data[ 3 ] = 0x9C;

    altitude3_generic_write( ctx, addr, temp_data, 4 );
    Delay_10ms( );

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        temp_data[ 0 ] = 0xC7;
        temp_data[ 1 ] = 0xF7;

        altitude3_generic_read( ctx, temp_data, temp_data, 3 );
        Delay_1ms( );

        out_data[ cnt ] = temp_data[ 0 ];
        out_data[ cnt ] <<= 8;
        out_data[ cnt ] |= temp_data[ 1 ];
    }
}

static void calc_conv_const ( uint32_t *p_pa, float *p_lut, float *out_data )
{
    float tmp;
    float c;
    float b;
    float a;

    c = ( float )( p_lut[ 0 ] * p_lut[ 1 ] * ( int32_t )( p_pa[ 0 ] - p_pa[ 1 ] ) );
    c += ( float )( p_lut[ 2 ] * p_lut[ 0 ] * ( int32_t )( p_pa[ 2 ] - p_pa[ 0 ] ) );
    c += ( float )( p_lut[ 1 ] * p_lut[ 2 ] * ( int32_t )( p_pa[ 1 ] - p_pa[ 2 ] ) );
    tmp = ( float )( p_lut[ 2 ] * ( int32_t )( p_pa[ 0 ] - p_pa[ 1 ] ) );
    tmp += ( float )( p_lut[ 1 ] * ( int32_t )( p_pa[ 2 ] - p_pa[ 0 ] ) );
    tmp += ( float )( p_lut[ 0 ] * ( int32_t )( p_pa[ 1 ] - p_pa[ 2 ] ) );
    c /= tmp;

    a = ( float )( p_pa[ 0 ] * p_lut[ 0 ] );
    a -= ( float )( p_pa[ 1 ] * p_lut[ 1 ] );
    a -= ( float )( ( int32_t )( p_pa[ 1 ] - p_pa[ 0 ] ) * c );
    a /= ( float )( p_lut[ 0 ] - p_lut[ 1 ] );

    b = ( float )( p_pa[ 0 ] - a );
    b *= ( float )( p_lut[ 0 ] + c );

    out_data[ 2 ] = c;
    out_data[ 1 ] = b;
    out_data[ 0 ] = a;
}

static void drv_read_9 ( altitude3_t *ctx, uint8_t *data_buf )
{

}

static uint8_t calculate_crc( uint8_t *data_buf, size_t len )
{
    uint8_t crc = 0xFF;
    size_t i, j;

    for ( i = 0; i < len; i++ )
    {
        crc ^= data_buf[ i ];
        for ( j = 0; j < 8; j++ )
        {
            if ( ( crc & 0x80 ) != 0 )
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x31 );
            else
                crc <<= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
