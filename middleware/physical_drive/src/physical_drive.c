
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
 * @file physical_drive.c
 * @brief Physical Drive.
 */

#include "physical_drive.h"
#include "pd_common.h"

static pd_status_t pd_default_init(physical_drive_t * const ptr_this);
static pd_status_t pd_default_deinit(physical_drive_t * const ptr_this);
static pd_status_t pd_default_read(physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size);
static pd_status_t pd_default_write(physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size);
static pd_status_t pd_default_trim(physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size);

void physical_drive_base_init(physical_drive_t * pdrive_base)
{
    if (0 == pdrive_base->vtptr->init) {
        pdrive_base->vtptr->init = &pd_default_init;
    }
    if (0 == pdrive_base->vtptr->read) {
        pdrive_base->vtptr->read = &pd_default_read;
    }
    if (0 == pdrive_base->vtptr->write) {
        pdrive_base->vtptr->write = &pd_default_write;
    }
    if (0 == pdrive_base->vtptr->trim) {
        pdrive_base->vtptr->trim = &pd_default_trim;
    }

    pdrive_base->type = PD_TYPE_UNINITIALIZED;
    pdrive_base->sector_count = 0;
    pdrive_base->sector_size = 0;
    pdrive_base->erase_block_size = 0;
    pdrive_base->volumes = 0;
    pdrive_base->error = 0;
}

static pd_status_t pd_default_init(physical_drive_t * const ptr_this)
{
    return PDS_NOT_IMPLEMENTED;
}

static pd_status_t pd_default_deinit(physical_drive_t * const ptr_this)
{
    return PDS_NOT_IMPLEMENTED;
}

static pd_status_t pd_default_read(physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size)
{
    return PDS_NOT_IMPLEMENTED;
}

static pd_status_t pd_default_write(physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size)
{
    return PDS_NOT_IMPLEMENTED;
}

static pd_status_t pd_default_trim(physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size)
{
    return PDS_NOT_IMPLEMENTED;
}

pd_status_t physical_drive_validate_drive(physical_drive_t * const physical_drive)
{
    return physical_drive ? PDS_OK : PDS_GENERAL_ERROR;
}

pd_status_t physical_drive_init(physical_drive_t * physical_drive)
{
    pd_status_t res;

    res = physical_drive_validate_drive(physical_drive);
    if (res != PDS_OK) {
        // error: physical drive is either nullptr or is not initialized
        return res;
    }

    return physical_drive->vtptr->init(physical_drive);
}

pd_status_t physical_drive_read(physical_drive_t * physical_drive, void * buffer, unsigned long long addr, unsigned long long size)
{
    pd_status_t res;

    res = physical_drive_validate_drive(physical_drive);
    if (res != PDS_OK) {
        // error: physical drive is either nullptr or is not initialized
        return res;
    }

    // validate buffer
    if (!buffer) {
        // error: no valid buffer provided
        return PDS_GENERAL_ERROR;
    }

    return physical_drive->vtptr->read(physical_drive, buffer, addr, size);
}

pd_status_t physical_drive_write(physical_drive_t * physical_drive, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size)
{
    pd_status_t res;

    res = physical_drive_validate_drive(physical_drive);
    if (res != PDS_OK) {
        // error: physical drive is either nullptr or is not initialized
        return res;
    }

    // validate buffer
    if (!buffer) {
        // error: no valid buffer provided
        return PDS_GENERAL_ERROR;
    }

    return physical_drive->vtptr->write(physical_drive, buffer, addr, size);
}
