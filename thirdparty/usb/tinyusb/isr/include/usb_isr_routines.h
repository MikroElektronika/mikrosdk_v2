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
 * @file  usb_isr_routines.h
 * @brief Default MikroE USB ISR.
 */

#ifndef _USB_ISR_ROUTINES_
#define _USB_ISR_ROUTINES_

#ifdef __cplusplus
extern "C"{
#endif

#include "tusb_config.h"

/*!
 * @addtogroup api API
 * @{
 */

/*!
 * @addtogroup usb USB Tiny.
 * @brief MikroE USB HW init library.
 *
 * @details This library works with HW specific
 * interrupts.
 * @{
 */

#if defined(__PROJECT_MIKROSDK_MIKROE__) && (__USE_MIKROE_ISR__==1)
    // Always link following API.
    #pragma GCC push_options
    #pragma GCC optimize ("O0")
    /**
     * @brief Makes sure file is included in build.
     * @details Simple NOP to make sure GCC includes
     * source file in build output.
     * @param None
     * @return None
     */

    void usb_isr_include(void);
    /**
     * @brief USB ISR.
     * @details Default MikroE USB interrupt service routine.
     * @param None
     * @return None
     * @warning MUST be defined somewhere in code.
     */
    void define_usb_handler_here(void) __attribute__((interrupt));
    #pragma GCC pop_options
#endif

/*! @} */ // usb
/*! @} */ // api

#ifdef __cplusplus
}
#endif

#endif // _USB_ISR_ROUTINES_
// ------------------------------------------------------------------------- END
