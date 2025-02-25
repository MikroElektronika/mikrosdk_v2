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
 * @file  plot.h
 * @brief Implements plot functionality.
 */

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _PLOT_H_
#define _PLOT_H_

#include <cstdio.h>
#include <string.h>
#include "generic_pointer.h"

/*!
 * @addtogroup platform Platform
 * @{
 */

/*!
 * @addtogroup plot MikroE Plotter.
 * @brief MikroE Plotter library.
 *
 * @details This library uses a predefined template in order
 * to write data to NECTO Studio Chart GUI.
 * @{
 */

/**
 * @brief Maximum buffer size for plotter.
 * @warning Change at your own risk.
 */
#define PLOT_BUFF_SIZE 48U

/**
 * @brief Number of characters for plotter template message.
 */
#define PLOT_CHAR_NUM_TEMPLATE 13U

/**
 * @brief Macro used to check chart name length.
 * @warning Chart name length @b must @b not be greater than
 * @ref PLOT_BUFF_SIZE - @ref PLOT_CHAR_NUM_TEMPLATE.
 * @note By default, maximum chart name is limited to @b 35.
 */
#define check_name_length(_name)  ((PLOT_CHAR_NUM_TEMPLATE + strlen(_name)) > PLOT_BUFF_SIZE) ? \
                                  (printf_me("Chart name too long. Reduce by %u characters.\n", \
                                            (PLOT_CHAR_NUM_TEMPLATE + strlen(_name)) - PLOT_BUFF_SIZE)) : \
                                  (0)

/**
 * @brief Plot log API.
 * @details API used for logging values to plot.
 * @param[in] *name Application name.
 * @param[in] value Value to send to plot.
 * @return If successful, the total number of characters written is returned.
 * On failure, a negative number is returned.
 * @note Values can be any of the standard types used in C.
 * @warning @ref name must be within defined limit for chart name size.
 * Look at @ref check_name_length for more details.
 */
static inline int plot( const char * __generic_ptr name, double value ) {
    if (check_name_length(name) == 0) {
        return printf_me( "CH:|%s|%.3f|\n", name, value );
    }
}

/*! @} */ // plot
/*! @} */ // platform

#ifdef __cplusplus
}
#endif

#endif // _PLOT_H_
// ------------------------------------------------------------------------- END
