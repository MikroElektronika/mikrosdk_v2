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
 * @file  mikrobus_id.h
 * @brief Implements mikroBUS specific ID's.
 */

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _MIKROBUS_ID_H_
#define _MIKROBUS_ID_H_

/**
 * @brief Enumerates available mikroBUS socket IDs mapped to platform-specific constants.
 *
 * @details This enum provides symbolic names for each mikroBUS socket available on the target platform.
 * Each value is conditionally included based on whether the corresponding `MIKROBUS_x` macro is defined,
 * allowing the enum to adapt to different hardware configurations.
 *
 * The values themselves are mapped directly to the `MIKROBUS_x` constants defined elsewhere in the system,
 * typically representing internal identifiers used for pin mapping or peripheral configuration.
 *
 * The values are usually defined in respective `board.h` file.
 */
typedef enum mikrobus_id {
    #ifdef MIKROBUS_1
    /**
     * @brief mikroBUS socket 1 identifier.
     */
    MIKROBUS_ID_1 = MIKROBUS_1,
    #endif

    #ifdef MIKROBUS_2
    /**
     * @brief mikroBUS socket 2 identifier.
     */
    MIKROBUS_ID_2 = MIKROBUS_2,
    #endif

    #ifdef MIKROBUS_3
    /**
     * @brief mikroBUS socket 3 identifier.
     */
    MIKROBUS_ID_3 = MIKROBUS_3,
    #endif

    #ifdef MIKROBUS_4
    /**
     * @brief mikroBUS socket 4 identifier.
     */
    MIKROBUS_ID_4 = MIKROBUS_4,
    #endif

    #ifdef MIKROBUS_5
    /**
     * @brief mikroBUS socket 5 identifier.
     */
    MIKROBUS_ID_5 = MIKROBUS_5,
    #endif
    MIKROBUS_ID_NONE = 0xFF
} mikrobus_id_t;

#ifdef __cplusplus
}
#endif

#endif // _MIKROBUS_ID_H_
// ------------------------------------------------------------------------- END
