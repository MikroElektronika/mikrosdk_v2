/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file pd_common.h
 * @brief Physical Drive.
 */

#ifndef _PD_COMMON_H_
#define _PD_COMMON_H_

#define PHYSICAL_DRIVE_VALIDATE_UNINITIALIZATION  ((uint8_t)0)
#define PHYSICAL_DRIVE_VALIDATE_INITIALIZATION    ((uint8_t)1)

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @ingroup physical_drive_data_group
 *
 * @brief Physical Drive Vector Table
 *
 * @details A table of function pointers, used used by @ref physical_drive_t struct,
 *          in order to call up correct functions for the particular implementation of the physical drive.
 */
struct physical_drive_vector_table {
    pd_status_t (*init)(physical_drive_t * const ptr_this);
    pd_status_t (*read)(physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size);
    pd_status_t (*write)(physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size);
    pd_status_t (*trim)(physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size); // TODO under construction
};

typedef uint8_t physical_drive_validation_t;

void physical_drive_base_init(physical_drive_t * physical_drive);

pd_status_t physical_drive_validate_drive(physical_drive_t * const physical_drive);

#ifdef __cplusplus
}
#endif

#endif // !_PD_COMMON_H_
