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
 * \file  log.h
 */
#ifndef _API_LOG_LOG_H_
#define _API_LOG_LOG_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "plot.h"
#include "drv_uart.h"
#include <stdarg.h>

/*! \addtogroup apigroup
 *  @{
 */

/*! \addtogroup loggroup Logger Library
 *  @{
 */

/*!
 * \brief Return values.
 */
typedef enum
{
    LOG_SUCCESS = 0,  /*!< Success. */
    LOG_ERROR = (-1)  /*!< Error. */
} log_err_t;

/*!
 * \brief Log level values
 */
typedef enum
{
    LOG_LEVEL_DEBUG   = 0x00,
    LOG_LEVEL_INFO    = 0x01,
    LOG_LEVEL_WARNING = 0x02,
    LOG_LEVEL_ERROR   = 0x03,
    LOG_LEVEL_FATAL   = 0x04
} log_level_t;

/*!
 * \brief LOG context structure.
 */
typedef struct
{
    uart_t uart;
    log_level_t log_level;
} log_t;

/*!
 * \brief LOG init configuration structure.
 */
typedef struct
{
    hal_pin_name_t rx_pin;
    hal_pin_name_t tx_pin;
    uint32_t baud;
    bool is_interrupt;
    log_level_t level;
} log_cfg_t;

/*!
 * \brief LOG MAP to the USB UART configuration
 * NOTE If USB_UART_RX and USB_UART_TX are not defined
 *      (defined as HAL_PIN_NC) define them manually.
 *      Pins are defined as Pxy where:
 *        - `x` represents port name ( A, B, C ... )
 *        - `y` represents pin ( 1,2,3...15...31 )
 *      Example:
 *        #define USB_UART_RX GPIO_PA14
 *        #define USB_UART_TX GPIO_PC0
 */
#define LOG_MAP_USB_UART(cfg) \
    cfg.rx_pin = USB_UART_RX; \
    cfg.tx_pin = USB_UART_TX; \
    cfg.baud = 115200; \
    cfg.is_interrupt = true; \
    cfg.level = LOG_LEVEL_DEBUG;

/*!
 * \brief LOG MAP to the MikroBUS configuration
 */
#define LOG_MAP_MIKROBUS(cfg, mikrobus) \
    cfg.rx_pin = MIKROBUS(mikrobus, MIKROBUS_RX); \
    cfg.tx_pin = MIKROBUS(mikrobus, MIKROBUS_TX); \
    cfg.baud = 115200; \
    cfg.is_interrupt = true; \
    cfg.level = LOG_LEVEL_DEBUG;

/*!
 * \brief TRACE function used in CycloneTCP library.
 * \details Shall be defined only for toolchains that have this library.
 */
#if defined(gcc_arm_none_eabi) || defined(mchp_xc32)
#define TRACE_PRINTF(...) osSuspendAllTasks(), log_printf(&console, __VA_ARGS__), osResumeAllTasks()
#endif

/**
 * @brief Initializes LOG module.
 *
 * Initializes LOG driver. This function needs to be
 * called before other driver functions.
 *
 * @param[in] log LOG context object.
 * @param[in] cfg LOG configuration structure.
 *
 * @return Returns a value from @ref log_err_t.
 */
log_err_t log_init ( log_t *log, log_cfg_t *cfg );

/**
 * @brief Printf function.
 *
 * This function uses to be a print message on the UART.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_printf ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief Discards all characters from the output and input buffer.
 *
 * @param[in] log LOG context object.
 */
void log_clear ( log_t *log );

/**
 * @brief Reads at most \p size bytes of data from the device into \p buffer.
 *
 * @param[in] log LOG context object.
 * @param[out] rx_data_buf Array to place read data in.
 * @param[in] max_len Maximal length
 *
 * @return err_t Returns the number of bytes that were actually read,
 * or -1 if an error occurred or no data read.
 */
int8_t log_read ( log_t *log, uint8_t *rx_data_buf, uint8_t max_len );

/**
 * @brief INFO printf function.
 *
 * This function uses to be a print message on the UART.
 * This function uses the prefix [INFO] and check for log level
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_info ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief ERROR printf function.
 *
 * This function uses to be a print message on the UART.
 * This function uses the prefix [ERROR] and check for log level
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_error ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief FATAL printf function.
 *
 * This function uses to be a print message on the UART.
 * This function uses the prefix [FATAL] and check for log level
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_fatal ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief DEBUG printf function.
 *
 * This function uses to be a print message on the UART.
 * This function uses the prefix [DEBUG] and check for log level
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_debug ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief WARNING printf function.
 *
 * This function uses to be a print message on the UART.
 * This function uses the prefix [WARNING] and check for log level
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_warning ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief Printf function with a variable prefix.
 *
 * This function uses to be a print message on the UART.
 * This function uses a variable prefix.
 *
 * @param[in] log LOG context object.
 * @param[in] prefix  Prefix.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_log ( log_t *log, char * prefix, const code char * __generic_ptr f, ... );

/*! @} */ // loggroup
/*! @} */ // apigroup

#ifdef __cplusplus
}
#endif
#endif // _API_LOG_LOG_H_
// ------------------------------------------------------------------------- END
