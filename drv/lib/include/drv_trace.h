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
 * @file  drv_trace.h
 * @brief Firmware trace hooks of the driver layer.
 *
 * @details The drivers report each transfer and pin change to these hooks. The library
 * versions do nothing; the MikroSDK.Trace library replaces them when it is linked
 * (see trace.h). A project that does not use the trace only pays an empty call per transfer.
 *
 * Flattened GPIO macros (FLATTEN_ME_LEVEL_HIGH) are expanded in the application, so they
 * call the hooks only when the application defines MIKROSDK_TRACE.
 */

#ifndef _DRV_TRACE_H_
#define _DRV_TRACE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>
#include "drv_name.h"

/**
 * @brief Trace hooks are compiled in.
 * @details Weak symbols are needed to let the trace library replace the empty hooks;
 * toolchains without them get no hooks at all.
 */
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__XC8) && !defined(__MIKROC_AI__)
#define DRV_TRACE_ENABLED 1
#define DRV_TRACE_WEAK __attribute__((weak))
#else
#define DRV_TRACE_ENABLED 0
#endif

/**
 * @brief Transfer kinds of #drv_trace_i2c and #drv_trace_spi.
 */
typedef enum
{
    DRV_TRACE_OP_WRITE = 0,
    DRV_TRACE_OP_READ = 1,
    DRV_TRACE_OP_WRITE_THEN_READ = 2,
    DRV_TRACE_OP_TRANSFER = 3 /*!< Full duplex: the same number of bytes written and read. */
} drv_trace_op_t;

#if DRV_TRACE_ENABLED

/**
 * @brief 1 when the MikroSDK.Trace library is linked, 0 otherwise.
 * @details The drivers define it weak as 0, the library as 1. Every hook call is behind it, so
 * firmware without the trace pays one load and a branch per call, not an empty call.
 */
extern const volatile uint8_t drv_trace_present;

/**
 * @brief Calls a hook only when the trace library is linked.
 */
#define DRV_TRACE( ... ) do { if ( drv_trace_present ) { __VA_ARGS__; } } while ( 0 )

/**
 * @brief Start time of a transfer for its hook; 0 without the trace library.
 */
#define DRV_TRACE_NOW() ( drv_trace_present ? drv_trace_now() : 0 )

/**
 * @brief Current trace time, in ticks of the trace time base.
 * @details Taken before a transfer starts, so that the record carries its start time.
 */
uint32_t drv_trace_now( void );

/**
 * @brief I2C transfer finished.
 * @param[in] obj I2C Master driver object (i2c_master_t).
 * @param[in] op Transfer kind, see #drv_trace_op_t.
 * @param[in] write_buf Bytes written, NULL when none.
 * @param[in] write_len Number of bytes written.
 * @param[in] read_buf Bytes read, NULL when none.
 * @param[in] read_len Number of bytes read.
 * @param[in] result Driver result, 0 on success.
 * @param[in] start Time of the transfer start, from #drv_trace_now.
 */
void drv_trace_i2c( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                    const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start );

/**
 * @brief SPI transfer finished.
 * @details Same parameters as #drv_trace_i2c; @p obj is the SPI Master driver object
 * (spi_master_t). Chip select is not part of the record: it is driven outside the driver.
 */
void drv_trace_spi( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                    const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start );

/**
 * @brief UART data written or read.
 * @details With interrupts or DMA the driver only queues the data: the duration is then the
 * time to queue it, not the time on the line.
 * @param[in] obj UART driver object (uart_t).
 * @param[in] is_tx 1 for data written, 0 for data read.
 * @param[in] buf Data.
 * @param[in] len Number of bytes the driver reported written or read.
 * @param[in] start Time of the call start, from #drv_trace_now.
 */
void drv_trace_uart( const void *obj, uint8_t is_tx, const uint8_t *buf, size_t len, uint32_t start );

/**
 * @brief GPIO pin initialized.
 * @param[in] obj Digital output or input driver object.
 * @param[in] pin Pin name.
 * @param[in] is_output 1 for digital_out, 0 for digital_in.
 */
void drv_trace_gpio_init( const void *obj, pin_name_t pin, uint8_t is_output );

/**
 * @brief Output pin about to be written.
 * @details Called before the write, so that flattened macros keep the value of the write.
 * @param[in] obj Digital output driver object (digital_out_t).
 * @param[in] level New level.
 */
void drv_trace_gpio_out( const void *obj, uint8_t level );

/**
 * @brief Input pin read.
 * @param[in] obj Digital input driver object (digital_in_t).
 * @param[in] level Level read.
 * @return @p level, so that the hook can wrap the read in an expression.
 */
uint8_t drv_trace_gpio_in( const void *obj, uint8_t level );

#endif

#ifdef __cplusplus
}
#endif

#endif // _DRV_TRACE_H_
// ------------------------------------------------------------------------- END
