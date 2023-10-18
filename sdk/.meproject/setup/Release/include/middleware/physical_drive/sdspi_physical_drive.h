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
 * @file sdspi_physical_drive.h
 * @brief SD Card Physical Drive via SPI.
 */

#ifndef _SDSPI_PHYSICAL_DRIVE_H_
#define _SDSPI_PHYSICAL_DRIVE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "physical_drive.h"
#include "drv_spi_master.h"

/**
 * @brief SD Card Type Enumerator.
 * @details Indicate the type of the SD Card. It will be determined during the process of the SD Card initialization.
 */
typedef enum {
    CT_NO_CARD = -1,            /**< Initial value */
    CT_MMC = 0,                 /**< Multi Media Card */
    CT_SD_VER1X_SC = 1,         /**< Standard Capacity Version 1 SD memory card */
    CT_SD_VER2X_SC = 2,         /**< Standard Capacity Version 2 SD memory card */
    CT_SD_VER2X_HC_XC = 3,      /**< High or Extended Capacity SD memory card */
    CT_UNSUPPORTED_CARD = 4,    /**< SD Card is not supported */
} sdspi_card_type_t;

/**
 * @brief A Structure used for initialization of SD SPI Physical Drive.
 * @details It specifies what pins will be used for SPI communication with SD Card.
 */
typedef struct {
    pin_name_t spi_sck;     /**< Pins used for SPI Clock */
    pin_name_t spi_miso;    /**< Pins used as SPI MISO or SD Card Data Out */
    pin_name_t spi_mosi;    /**< Pins used as SPI MOSI or SD Card Data In */
    pin_name_t spi_cs;      /**< Pins used as Chip Select, for selecting the SD Card */
} sdspi_config_t;

/**
 * @ingroup physical_drive_data_group
 *
 * @brief SD SPI Physical Drive Data Structure.
 *
 * @details Manages communication with SD Card hardware memory module via SPI bus, using its vector table @c vtptr inside @c base structure,
 *          which points to functions that implement communication with SD Card hardware memory module via SPI bus.
 *          It also identifies and represents SD Card hardware memory module, by keeping all the relevant data about it.
 *          It is derived from @ref physical_drive_t structure.
 */
typedef struct {
    physical_drive_t base;          /**< Physical Drive base data structure. It It identifies and represents @c sdspi_physical_drive_t with physical drive API functions.*/
    spi_master_t spi;               /**< SPI Master data used for the purposes of communication with SD Card. */
    digital_out_t cs;               /**< Digital Out data used for the purposes of communication with SD Card. */
    sdspi_card_type_t card_type;    /**< SD Card type. See @ref sdspi_card_type_t enum. */
    bool is_initialized;             /**< Indicated whether SD Card hardware memory module is initialized */
} sdspi_physical_drive_t;

/**
 * @ingroup physical_drive_group
 *
 * @brief Initializes Physical Drive for SD Card communication via SPI bus.
 *
 * @details This API function will initialize the @c sd structure with data provided by the @c config structure,
 *          by initializing @c spi and @c cs, thus enabling the communication with SD Card via SPI bus.
 *          @c vtptr vector tables inside the physical drive @c base structure, will be initialized to point
 *          to functions that implement communication with SD Card via SPI bus.
 *          All other struct members are set to zeros.
 *
 * @post Physical drive @c sd is now ready to be used by the Physical Drive API functions.
 * SD Card hardware memory module should be initialized now by calling @ref physical_drive_init,
 */
pd_status_t sdspi_physical_drive_init(sdspi_physical_drive_t * sd, sdspi_config_t * config);

#ifdef __cplusplus
}
#endif

#endif // !_SDSPI_PHYSICAL_DRIVE_H_
