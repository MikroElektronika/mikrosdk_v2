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

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvtracegroup Firmware Trace Hooks
 * @brief Firmware Trace Hooks API Reference.
 * @details The drivers report transfers and pin changes to these hooks; the MikroSDK.Trace
 * library implements them. Applications do not call them.
 * @{
 */

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

/**
 * @brief 1-Wire operations of #drv_trace_one_wire.
 */
typedef enum
{
    DRV_TRACE_ONE_WIRE_RESET = 0,        /*!< Reset pulse; an error means no presence pulse. */
    DRV_TRACE_ONE_WIRE_READ_ROM = 1,     /*!< Read ROM (0x33): the ROM address read. */
    DRV_TRACE_ONE_WIRE_SKIP_ROM = 2,     /*!< Skip ROM (0xCC), no data. */
    DRV_TRACE_ONE_WIRE_MATCH_ROM = 3,    /*!< Match ROM (0x55): the ROM address written. */
    DRV_TRACE_ONE_WIRE_SEARCH_FIRST = 4, /*!< Search ROM (0xF0), first device: its ROM address. */
    DRV_TRACE_ONE_WIRE_SEARCH_NEXT = 5,  /*!< Search ROM, next device: its ROM address. */
    DRV_TRACE_ONE_WIRE_WRITE = 6,        /*!< Bytes written. */
    DRV_TRACE_ONE_WIRE_READ = 7          /*!< Bytes read. */
} drv_trace_one_wire_op_t;

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
 * @brief Asks a fault hook only when the trace library is linked; 0 otherwise.
 */
#define DRV_TRACE_FAULT( call ) ( drv_trace_present && ( call ) )

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
 * (spi_master_t). The chip select of the transfer is the one #drv_trace_spi_cs last reported
 * as selected.
 */
void drv_trace_spi( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                    const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start );

/**
 * @brief Chip select driven by spi_master_select_device() or spi_master_deselect_device().
 * @param[in] chip_select Chip select pin.
 * @param[in] selected 1 for select, 0 for deselect.
 * @param[in] level Pin level written, after the chip select polarity.
 */
void drv_trace_spi_cs( pin_name_t chip_select, uint8_t selected, uint8_t level );

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
 * @return The level the read gives: @p level, or the level of an injected fault holding the
 * pin (see #drv_trace_fault_i2c).
 */
uint8_t drv_trace_gpio_in( const void *obj, uint8_t level );

/**
 * @brief Analog input read.
 * @details Called only for successful reads. Raw counts and voltages of one driver object are
 * kept apart, so that the units of a lane never mix.
 * @param[in] obj Analog input driver object (analog_in_t).
 * @param[in] pin Analog input pin.
 * @param[in] is_voltage 1 for analog_in_read_voltage(), 0 for analog_in_read().
 * @param[in] value Value read: volts, or the raw count.
 */
void drv_trace_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float value );

/**
 * @brief 1-Wire operation finished.
 * @param[in] obj 1-Wire driver object (one_wire_t).
 * @param[in] pin 1-Wire data pin.
 * @param[in] op Operation, see #drv_trace_one_wire_op_t.
 * @param[in] buf Bytes written or read (a ROM address for the ROM operations), NULL when none.
 * @param[in] len Number of bytes.
 * @param[in] result Driver result, 0 on success.
 * @param[in] start Time of the operation start, from #drv_trace_now.
 */
void drv_trace_one_wire( const void *obj, pin_name_t pin, uint8_t op, const uint8_t *buf, size_t len,
                         err_t result, uint32_t start );

/**
 * @brief I2C transfer about to start.
 * @details Fault injection: NECTO Studio makes a device stop answering, a bus read a fixed
 * value, a pin stick at a level, to show how the application copes. The debugger writes the
 * faults to the trace library while the program is stopped; the drivers ask these hooks
 * whether one applies to a call. The trace marks the calls a fault changed.
 * @param[in] obj I2C Master driver object (i2c_master_t).
 * @return 1 when the device at the address of @p obj is not to answer: the driver then fails
 * the transfer without starting it, as for a NACK.
 */
uint8_t drv_trace_fault_i2c( const void *obj );

/**
 * @brief SPI transfer finished: the bytes read are replaced while MISO is held stuck.
 * @details See #drv_trace_fault_i2c.
 * @param[in] obj SPI Master driver object (spi_master_t).
 * @param[in,out] read_buf Bytes read, NULL when none.
 * @param[in] read_len Number of bytes read.
 */
void drv_trace_fault_spi( const void *obj, uint8_t *read_buf, size_t read_len );

/**
 * @brief Analog input about to be read.
 * @details See #drv_trace_fault_i2c.
 * @param[in] obj Analog input driver object (analog_in_t).
 * @param[in] pin Analog input pin.
 * @param[in] is_voltage 1 for analog_in_read_voltage(), 0 for analog_in_read().
 * @param[out] value The value the read is to give: volts, or the raw count.
 * @return 1 when the value is forced: the driver then gives @p value without reading.
 */
uint8_t drv_trace_fault_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float *value );

/**
 * @brief 1-Wire operation about to start.
 * @details See #drv_trace_fault_i2c.
 * @param[in] obj 1-Wire driver object (one_wire_t).
 * @param[in] pin 1-Wire data pin.
 * @return 1 when no device is to answer on the pin: the driver then skips the operation, as
 * on an empty bus.
 */
uint8_t drv_trace_fault_one_wire( const void *obj, pin_name_t pin );

#endif

/*! @} */ // drvtracegroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_TRACE_H_
// ------------------------------------------------------------------------- END
