/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_pps.c
 * @brief This file contains low level HAL PPS function definitions.
 */

#include "hal_ll_pps_port.h"

hal_ll_pps_err_t hal_ll_pps_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num, hal_ll_gpio_direction_t direction, hal_ll_pps_functionality_t pps_func, hal_ll_pps_module_index_t module_num, bool hal_ll_state ) {
    bool hal_ll_pps_lock_status = false;
    // First, unlock sequence
    if ( ( false != HAL_LL_CFGCON_ADDRESS ) && check_reg_bit( HAL_LL_CFGCON_ADDRESS, HAL_LL_IOLOCK_BIT ) ) {
        hal_ll_pps_lock_unlock( HAL_LL_PPS_UNLOCK );
        hal_ll_pps_lock_status = true;
    }

    // Second, map functions to adequate pins
    if ( direction == HAL_LL_GPIO_DIGITAL_INPUT ) {
        if ( hal_ll_pps_map_input( port_name, pin_num, pps_func, module_num, hal_ll_state ) != HAL_LL_PPS_SUCCESS )
            return HAL_LL_PPS_PIN_ERROR;
    } else if ( direction == HAL_LL_GPIO_DIGITAL_OUTPUT ) {
        if ( hal_ll_pps_map_output( port_name, pin_num, pps_func, module_num, hal_ll_state ) != HAL_LL_PPS_SUCCESS )
            return HAL_LL_PPS_PIN_ERROR;
    }

    // Finally, lock sequence
    if ( hal_ll_pps_lock_status ) {
        hal_ll_pps_lock_unlock( HAL_LL_PPS_LOCK );
    }

    // If it gets to this point, return success msg
    return HAL_LL_PPS_SUCCESS;
}
// ------------------------------------------------------------------------- END
