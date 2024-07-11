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
 * @file sd_common.h
 * @brief SD Card Common.
 */

#ifndef _SD_COMMON_H_
#define _SD_COMMON_H_

/**
 * @defgroup sd_card_commands_group SD Commands
 * @ingroup physical_drive_data_group
 * @brief SD Card Commands.
 * @{
 */

/**
 * @brief Resets the SD memory card
 */
#define SD_CMD0_GO_IDLE_STATE               ((uint8_t)0)

/**
 * @brief Sends host capacity support information and activates the card's initialization process.
 */
#define SD_CMD1_SEND_OP_COND                ((uint8_t)1)

/**
 * @brief Sends SD Memory Card interface condition.
 * @details Sends SD Memory Card interface condition that includes host supply voltage information
 *          and asks accessed card whether card can operate in supplied voltage range.
 */
#define SD_CMD8_SEND_IF_COND                ((uint8_t)8)

/**
 * @brief Asks the selected card to send its card specific data (CSD).
 */
#define SD_CMD9_SEND_CSD                    ((uint8_t)9)

/**
 * @brief Asks the selected card to send its card identification (CID).
 */
#define SD_CMD10_SEND_CID                   ((uint8_t)10)

/**
 * @brief Forces the card to stop transmission in Multiple Block Read Operation.
 */
#define SD_CMD12_STOP_TRANSMISSION          ((uint8_t)12)

/**
 * @brief Sets block length of SDSC Card.
 */
#define SD_CMD16_SET_BLOCKLEN               ((uint8_t)16)

/**
 * @brief Reads a block of data.
 */
#define SD_CMD17_READ_SINGLE_BLOCK          ((uint8_t)17)

/**
 * @brief Continuously transfers data blocks from card to host until interrupted by @ref SD_CMD12_STOP_TRANSMISSION command.
 */
#define SD_CMD18_READ_MULTIPLE_BLOCK        ((uint8_t)18)

/**
 * @brief Writes a block of data.
 */
#define SD_CMD24_WRITE_BLOCK                ((uint8_t)24)

/**
 * @brief Continuously writes blocks of data until @c Stop @c Tran tokens is sent.
 */
#define SD_CMD25_WRITE_MULTIPLE_BLOCK       ((uint8_t)25)

/**
 * @brief Defines to the card that the next command is and application specific command.
 */
#define SD_CMD55_APP_CMD                    ((uint8_t)55)

/**
 * @brief Reads the OCR register of the card.
 */
#define SD_CMD58_READ_OCR                   ((uint8_t)58)

/**
 * @brief Set the number of write blocks to be pre-erased before writing.
 */
#define SD_ACMD23_SET_WR_BLK_ERASE_COUNT    ((uint8_t)23)

/**
 * @brief Send host capacity support information and activates the card's initialization process.
 */
#define SD_ACMD41_SD_SEND_OP_COND           ((uint8_t)41)

/*! @} */ // sd_card_commands_group

#endif // !_SD_COMMON_H_
