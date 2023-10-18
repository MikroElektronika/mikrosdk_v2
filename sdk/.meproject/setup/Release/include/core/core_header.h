/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
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
 * @file  core_header.h
 * @brief Mikroe GD32VF103 chip series core header implementation.
 */

#ifndef __MIKROC_CORE_LIB_H__
#define __MIKROC_CORE_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ADDRESS_RCU_CTL 0x40021000 
#define VALUE_RCU_CTL 0x1080001 
#define ADDRESS_RCU_CFG0 0x40021004 
#define VALUE_RCU_CFG0 0x20A84402 
#define ADDRESS_RCU_BDCTL 0x40021020 
#define VALUE_RCU_BDCTL 0x0 
#define ADDRESS_RCU_RSTSCK 0x40021024 
#define VALUE_RCU_RSTSCK 0x0 
#define ADDRESS_RCU_CFG1 0x4002102C 
#define VALUE_RCU_CFG1 0x6600 
#define ADDRESS_RCU_DSV 0x40021034 
#define VALUE_RCU_DSV 0x3 
#define FOSC_KHZ_VALUE 108000 
#define GD32VF103VBT6 


#ifdef __cplusplus
}
#endif

#endif // __MIKROC_CORE_LIB_H__
