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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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

/*! \addtogroup apigroup
 *  @{
 */

/*! \addtogroup loggroup Logger Library
 *  @{
 */

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
    log_level_t log_level;
} log_t;

/*!
 * \brief LOG init configuration structure.
 */
typedef struct
{
    log_level_t level;
} log_cfg_t;

/*!
 * \brief LOG MAP to the USB UART configuration
 * \note Build compatibility only, not functional.
 */
#define LOG_MAP_USB_UART(cfg) cfg.level = LOG_LEVEL_DEBUG;

/*!
 * \brief LOG MAP to the MikroBUS configuration
 * \note Build compatibility only, not functional.
 */
#define LOG_MAP_MIKROBUS(cfg, mikrobus) cfg.level = LOG_LEVEL_DEBUG;

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
 */
void log_init ( log_t *log, log_cfg_t *cfg );

/**
 * @brief Printf function.
 *
 * This function is used to print a message on the std_out terminal.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_printf ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief Empty wrapper API.
 * @note Build compatibility only, not functional.
 *
 * @param[in] log LOG context object.
 */
void log_clear ( log_t *log );

/**
 * @brief Empty wrapper API.
 * @note Build compatibility only, not functional.
 *
 * @return 0
 */
int8_t log_read ( log_t *log, uint8_t *rx_data_buf, uint8_t max_len );

/**
 * @brief INFO printf function.
 *
 * This function is used print a message on the std_out terminal.
 * This function uses the prefix [INFO] and checks for log level.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_info ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief ERROR printf function.
 *
 * This function is used print a message on the std_out terminal.
 * This function uses the prefix [ERROR] and checks for log level.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_error ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief FATAL printf function.
 *
 * This function is used print a message on the std_out terminal.
 * This function uses the prefix [FATAL] and checks for log level.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_fatal ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief DEBUG printf function.
 *
 * This function is used print a message on the std_out terminal.
 * This function uses the prefix [DEBUG] and checks for log level.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_debug ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief WARNING printf function.
 *
 * This function is used print a message on the std_out terminal.
 * This function uses the prefix [WARNING] and checks for log level.
 *
 * @param[in] log LOG context object.
 * @param[in] *f  pointer to the string
 * @param[in] ... Other parameters
 */
void log_warning ( log_t *log, const code char * __generic_ptr f,... );

/**
 * @brief Printf function with a variable prefix.
 *
 * This function is used print a message on the std_out terminal.
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
