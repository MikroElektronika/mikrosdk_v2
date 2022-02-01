/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2022 MikroElektronika d.o.o.
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
 * \brief This file contains API for Thermo 2 Click driver.
 *
 * \addtogroup thermo2 Thermo 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _THERMO_2_H_
#define _THERMO_2_H_

#include "drv_digital_out.h"
#include "drv_one_wire.h"
#include "drv_uart.h"
#include "conversions.h"

// -------------------------------------------------------------- PUBLIC MACROS
#define THERMO_2_MAP_MIKROBUS( cfg, mikrobus ) \
cfg.data_pin = MIKROBUS( mikrobus, MIKROBUS_PWM );

#define THERMO_2_LOOKUP_TABLE_ELEMENTS      ( 11 )
#define THERMO_2_RESOLUTION_ERROR           ( 126 )

#define THERMO_2_CMD_CONVERT_TEMPERATURE    ( 0x44 )
#define THERMO_2_CMD_WRITE_SCRATCHPAD       ( 0x4E )
#define THERMO_2_CMD_READ_SCRATCHPAD        ( 0xBE )
#define THERMO_2_CMD_COPY_SCRATCHPAD        ( 0x48 )
#define THERMO_2_CMD_RECALL_SCRATCHPAD      ( 0xB8 )

typedef enum {
    THERMO_2_RESOLUTION_12_BIT = 0,
    THERMO_2_RESOLUTION_11_BIT,
    THERMO_2_RESOLUTION_10_BIT,
    THERMO_2_RESOLUTION_9_BIT,

    THERMO_2_DEFAULT_RESOLUTION = THERMO_2_RESOLUTION_12_BIT
} thermo_2_resolution_t;


// Function declaration for temperature conversion.
float thermo_2_convert_temperature( uint16_t raw_temperature_value, thermo_2_resolution_t resolution_value );

#endif  // _THERMO_2_H_
/*! @} */
// ------------------------------------------------------------------------- END
