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
 * @file sdspi_physical_drive.ch
 * @brief SD SPI Physical Drive.
 */

#include "sdspi_physical_drive.h"
#include "sd_common.h"
#include "pd_common.h"
#include "stdint.h"
#include "string.h"
#include "delays.h"

#define SDSPI_DATA_BLOCK_SIZE                  (512)
#define SDSPI_CRC_BUFFER_SIZE                  (2)
#define SDSPI_80_CLOCK_CYCLES                  (10)

#define SDSPI_STATUS_OK                        (0x00)
#define SDSPI_ERROR_BUSY_TIMEOUT               (0x81)

#define SDSPI_R1_VALID_MASK                    (0x80)
#define SDSPI_R1_NO_RESPONSE                   (0xFF)
#define SDSPI_R1_NO_ERRORS                     (0x00)
#define SDSPI_R1_IN_IDLE_STATE                 (0x01)
#define SDSPI_R1_ERASE_RESET                   (0x02)
#define SDSPI_R1_ILLEGAL_COMMAND               (0x04)
#define SDSPI_R1_COM_CRC_ERROR                 (0x08)
#define SDSPI_R1_ERASE_SEQUENCE_ERROR          (0x10)
#define SDSPI_R1_ADDRESS_ERROR                 (0x20)
#define SDSPI_R1_PARAMETER_ERROR               (0x40)

#define SDSPI_OCR_CSS_MASK                     (0x40000000)

#define SDSPI_CMD_PACKET_SIZE                  (6)
#define SDSPI_CMD_DEFAULT_ARGUMENT             (0x00000000)
#define SDSPI_CMD8_ARGUMENT                    (0x000001AA)
#define SDSPI_ACMD41_V1_ARGUMENT               SDSPI_CMD_DEFAULT_ARGUMENT
#define SDSPI_ACMD41_V2_ARGUMENT               SDSPI_OCR_CSS_MASK
#define SDSPI_CMD16_ARGUMENT                   (0x00000200)

#define SDSPI_TIMEOUT_CMD                      (9)                             // Documentation defines this as 8 bytes(clock cycles) max, but our old MMC lib uses 100. Value is empirically selected, but it should not be below 9
#define SDSPI_TIMEOUT_ACMD41                   (40000)                         // empirical value, subject to possible changes
#define SDSPI_TIMEOUT_CMD0_RETRIES             (35)                            // Sometimes it can take the card 30 CMD0 retries until it enters idle state, the chosen value is empirical and may be changed in the future
#define SDSPI_TIMEOUT_DATA_TOKEN_NAC           (40000)                         // empirical value, subject to possible changes
#define SDSPI_TIMEOUT_WAIT_BUSY                ((uint32_t)0xFFFFFFFF)

#define SDSPI_DATA_TOKEN_NOT_RECEIVED          (1)
#define SDSPI_DATA_TOKEN_RECEIVED              (0)
#define SDSPI_DATA_TOKEN_START_BLOCK           (0xFE)
#define SDSPI_DATA_TOKEN_CMD9                  SDSPI_DATA_TOKEN_START_BLOCK
#define SDSPI_DATA_TOKEN_CMD17                 SDSPI_DATA_TOKEN_START_BLOCK
#define SDSPI_DATA_TOKEN_CMD18                 SDSPI_DATA_TOKEN_START_BLOCK
#define SDSPI_DATA_TOKEN_CMD24                 SDSPI_DATA_TOKEN_START_BLOCK
#define SDSPI_DATA_TOKEN_CMD25_START           (0xFC)
#define SDSPI_DATA_TOKEN_CMD25_STOP            (0xFD)

#define SDSPI_READY                            (0xFF)
#define SDSPI_FILL_DATA_BUFFER                 (0xFF)
#define DATA_RESPONSE_MASK                     (0x1F)
#define DATA_RESPONSE_ACCEPTED                 (0x05)

#define CARD_NOT_INITIALIZED                   (0)
#define CARD_INITIALIZED                       (1)
#define CARD_NOT_READY                         (1)
#define CARD_READY                             (0)

#define SDSPI_CSD_REGISTER_SIZE                (16)
#define SDSPI_CSD_TAAC_VALUE_VER23             (0x0E)
#define SDSPI_CSD_TAAC_START_BIT               (112)
#define SDSPI_CSD_TAAC_END_BIT                 (119)
#define SDSPI_CSD_CSIZE_START_BIT_VER2         (48)
#define SDSPI_CSD_CSIZE_END_BIT_VER2           (69)

#define SDSPI_25MHZ_CLOCK                      (25000000)
#define SDSPI_100KHZ_CLOCK                     (100000)
#define SDSPI_1MHZ_STEP                        (1000000)

typedef uint8_t r1_response_t;
typedef uint8_t sdspi_command_t;
typedef struct {
    r1_response_t r1;
    uint32_t optional_bytes;
} response_t;

static void sdspi_select_device(sdspi_physical_drive_t * sd);
static void sdspi_deselect_device(sdspi_physical_drive_t * sd);
static void sdspi_wait(spi_master_t * spi, uint8_t count);
static uint8_t sdspi_wait_until_ready(spi_master_t * spi);
static uint8_t sdspi_wait_for_token(sdspi_physical_drive_t * sd, uint8_t token);
static r1_response_t sdspi_send_command(sdspi_physical_drive_t * sd, sdspi_command_t cmd, uint32_t arg);
static void sdspi_get_response_to_command(sdspi_physical_drive_t * sd, sdspi_command_t cmd, uint32_t arg,   response_t * response);
static void sdspi_power_up_card(sdspi_physical_drive_t * sdspi);
static int sdspi_go_idle(sdspi_physical_drive_t * sdspi);
static int sdspi_send_interface_condition(sdspi_physical_drive_t * sdspi);
static void sdspi_unidle(sdspi_physical_drive_t * sd);
static int sdspi_init_card(sdspi_physical_drive_t * sd);
static int sdspi_read_csd(sdspi_physical_drive_t* sd, uint8_t * csd_reg_data);
static uint32_t sdspi_get_csd_bitfield(uint8_t * csd, uint8_t fist_bit, uint8_t last_bit);

static pd_status_t sdspi_init(sdspi_physical_drive_t * const ptr_this);
static pd_status_t sdspi_read(sdspi_physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size);
static pd_status_t sdspi_write(sdspi_physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size);
static pd_status_t sdspi_trim(sdspi_physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size);

#ifdef __XC8
static physical_drive_vector_table_t sdspi_vtable = {
    (pd_status_t (*)(physical_drive_t * const ptr_this))&sdspi_init,
    (pd_status_t (*)(physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size))&sdspi_read,
    (pd_status_t (*)(physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size))&sdspi_write,
    (pd_status_t (*)(physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size))0 // TODO function under construction
};
#endif

static void sdspi_select_device(sdspi_physical_drive_t * sdspi)
{
    uint8_t fill_data_buffer = SDSPI_FILL_DATA_BUFFER;

    spi_master_write(&sdspi->spi, &fill_data_buffer, 1);
    if (CARD_NOT_INITIALIZED == sdspi->is_initialized) {
        Delay_10us();   // helps to prevent racing condition on fast MCUs , during initialization when SPI clock is still slow
    }
    digital_out_low(&sdspi->cs);
}

static void sdspi_deselect_device(sdspi_physical_drive_t * sdspi)
{
    uint8_t fill_data_buffer = SDSPI_FILL_DATA_BUFFER;

    spi_master_write(&sdspi->spi, &fill_data_buffer, 1);
    if (CARD_NOT_INITIALIZED == sdspi->is_initialized) {
        Delay_10us();   // helps to prevent racing condition on fast MCUs , during initialization when SPI clock is still slow
    }
    digital_out_high(&sdspi->cs);
}

static void sdspi_wait(spi_master_t * spi, uint8_t count)
{
    uint8_t buffer = SDSPI_FILL_DATA_BUFFER;

    while (count--) {
        spi_master_write(spi, &buffer, 1);
    }
}

static uint8_t sdspi_wait_for(spi_master_t * spi, uint8_t token_response, uint32_t timeout)
{
    uint8_t response;

    do {
        timeout--;
        spi_master_read(spi, &response, 1);
    } while ((token_response != response) && (timeout > 0));

    return token_response == response ? SDSPI_STATUS_OK : 1;
}

// waits until sd card is ready to receive new command
static uint8_t sdspi_wait_until_ready(spi_master_t * spi)
{
    return sdspi_wait_for(spi, SDSPI_READY, SDSPI_TIMEOUT_WAIT_BUSY);
}

static uint8_t sdspi_wait_for_token(sdspi_physical_drive_t * sdspi, uint8_t token)
{
    return sdspi_wait_for(&sdspi->spi, token, SDSPI_TIMEOUT_DATA_TOKEN_NAC);
}

// sends command via spi and wait for response for some timeout value,
// function returns the valid response, or invalid in case of timeout
static r1_response_t sdspi_send_command(sdspi_physical_drive_t * sdspi, sdspi_command_t cmd, uint32_t arg)
{
    r1_response_t response = SDSPI_R1_NO_RESPONSE;
    char command_packet[SDSPI_CMD_PACKET_SIZE];
    uint8_t cmd_timeout = SDSPI_TIMEOUT_CMD;

    command_packet[0] = cmd | 0x40;
    command_packet[1] = arg >> 24;
    command_packet[2] = arg >> 16;
    command_packet[3] = arg >> 8;
    command_packet[4] = arg >> 0;

    // crc is not used, and is ignored by the card
    switch (cmd) {
        case SD_CMD0_GO_IDLE_STATE:
            command_packet[5] = 0x95;
            break;
        case SD_CMD8_SEND_IF_COND:
            command_packet[5] = 0x87;
            break;
        default:
            command_packet[5] = SDSPI_FILL_DATA_BUFFER;
            break;
    }

    spi_master_write(&sdspi->spi, command_packet, SDSPI_CMD_PACKET_SIZE);

    // The received byte immediately following CMD12 is a stuff byte,
    // it should be discarded prior to receive the response of the CMD12.
    // http://elm-chan.org/docs/mmc/mmc_e.html
    // confirmed by logic analyzer
    if (SD_CMD12_STOP_TRANSMISSION == cmd){
        spi_master_read(&sdspi->spi, &response, 1);
    }

    // wait until valid R1 response is received, for at least 9 clock cycles
    do {
        cmd_timeout--;
        spi_master_read(&sdspi->spi, &response, 1);
    } while ((response & SDSPI_R1_VALID_MASK) && cmd_timeout);

    return response;
}

static void sdspi_get_response_to_command(sdspi_physical_drive_t * sdspi, sdspi_command_t cmd, uint32_t arg,  response_t * response)
{
    uint8_t response_buffer[4];
    response->r1 = SDSPI_R1_NO_RESPONSE;
    response->optional_bytes = 0;
    uint8_t buffer[2] = {SDSPI_FILL_DATA_BUFFER, SDSPI_FILL_DATA_BUFFER};

    // CMD12 is only used in multi-block read operation at which point the device is already selected by read operation itself
    // During reading operation when CMD12 needs to be issued, the card cannot be busy either, so there is no need to check if the card is ready
    if (SD_CMD12_STOP_TRANSMISSION != cmd) {
        // select the device
        sdspi_select_device(sdspi);
        // During initialization, until the CMD0_GO_IDLE_STATE command is sent, card will signal busy,
        // CMD0_GO_IDLE_STATE must be sent anyway to force card to enter idle state
        if (cmd != SD_CMD0_GO_IDLE_STATE) {
            // wait for card to be ready for new command
            if (CARD_NOT_READY == sdspi_wait_until_ready(&sdspi->spi)) {
                // error: timeout, card is busy
                sdspi_deselect_device(sdspi);
                return;
            }
        }
        else {
            spi_master_write(&sdspi->spi, &buffer, 2);     // some SD Cards on dsPIC do not respond to CMD0 command without sending fill byte first
        }
    }

    // send CMD55_APP_CMD first, in the case that command is app-cmd, then the regular command code, otherwise, just send the regular command code
    switch (cmd) {
        case SD_ACMD23_SET_WR_BLK_ERASE_COUNT:
        case SD_ACMD41_SD_SEND_OP_COND:
            sdspi_send_command(sdspi ,SD_CMD55_APP_CMD, 0);
        default:
            response->r1 = sdspi_send_command(sdspi, cmd, arg);
    }

    if (SDSPI_R1_NO_RESPONSE == response->r1) {
        // error: card did not respond
        sdspi_deselect_device(sdspi);
        return;
    }
    // "in idle state" error, is not treated as an error, because it is expected after cmd0

    // when an illegal command is detected, the card does not send other response bytes
    if (response->r1 & SDSPI_R1_ILLEGAL_COMMAND) {
        // error: illegal command received
        // if illegal command is detected after cmd8 during initialization, the card is not supported
        if (SD_CMD8_SEND_IF_COND == cmd) {
            sdspi->card_type = CT_UNSUPPORTED_CARD;
        }
        sdspi_deselect_device(sdspi);
        return;
    }

    // When CRC error is detected, card does not send other response bytes
    // CRC errors are ignored, because CRC is ignored by the card

    // no need to check for other errors

    // reading other response bytes if needed, and deselecting the device
    switch (cmd) {
        case SD_CMD8_SEND_IF_COND:         // read 4 byte response and deselect
        case SD_CMD58_READ_OCR:
            spi_master_read(&sdspi->spi, response_buffer, 4);
            response->optional_bytes = (uint32_t)response_buffer[0] << 24;
            response->optional_bytes |= (uint32_t)response_buffer[1] << 16;
            response->optional_bytes |= (uint32_t)response_buffer[2] << 8;
            response->optional_bytes |= (uint32_t)response_buffer[3] << 0;
            sdspi_deselect_device(sdspi);
            break;
        case SD_CMD12_STOP_TRANSMISSION:   // R1b response requires waiting until busy signal is cleared by the card
            if (CARD_NOT_READY == sdspi_wait_until_ready(&sdspi->spi)) {
                // error: timeout, card is busy
                sdspi_deselect_device(sdspi);
                response->r1 = SDSPI_R1_NO_RESPONSE;
                return;
            }
            sdspi_deselect_device(sdspi);
            break;
        case SD_CMD9_SEND_CSD:             // read and write commands do not need deselect, deselecting device will be done in read and write functions
        case SD_CMD17_READ_SINGLE_BLOCK:
        case SD_CMD18_READ_MULTIPLE_BLOCK:
        case SD_CMD24_WRITE_BLOCK:
        case SD_CMD25_WRITE_MULTIPLE_BLOCK:
            break;
        default:                           // deselect
            sdspi_deselect_device(sdspi);
            break;
    }
}

static void sdspi_power_up_card(sdspi_physical_drive_t * sdspi)
{
    // after supply voltage reached above 2.2 volts, wait for one millisecond at least
    Delay_1ms();

    // 74+ cycles of dummy clock with CS asserted low is needed to enter native mode and DI set high
    sdspi_deselect_device(sdspi);
    sdspi_wait(&sdspi->spi, SDSPI_80_CLOCK_CYCLES);
    // card will signal busy from now on, until CMD0_GO_IDLE_STATE command is sent
}

static int sdspi_go_idle(sdspi_physical_drive_t * sdspi)
{
    response_t response;
    uint8_t counter = SDSPI_TIMEOUT_CMD0_RETRIES;

    do {
        counter--;
        sdspi_get_response_to_command(sdspi, SD_CMD0_GO_IDLE_STATE, SDSPI_CMD_DEFAULT_ARGUMENT, &response);
    } while ((SDSPI_R1_IN_IDLE_STATE != response.r1) && (counter > 0));
    // if card did not return R1_IN_IDLE_STATE after several retries, card unsupported, abort initialization
    if (SDSPI_R1_IN_IDLE_STATE != response.r1) {
        sdspi->card_type = CT_UNSUPPORTED_CARD;
        return PDS_GENERAL_ERROR;
    }

    return PDS_OK;
}

static int sdspi_send_interface_condition(sdspi_physical_drive_t * sdspi)
{
    response_t response;

    sdspi_get_response_to_command(sdspi, SD_CMD8_SEND_IF_COND, SDSPI_CMD8_ARGUMENT, &response);
    // if 0x1AA mismatch happened, card is unsupported and initialization should abort
    if ((SDSPI_R1_IN_IDLE_STATE == response.r1) && (SDSPI_CMD8_ARGUMENT != response.optional_bytes)) {
        sdspi->card_type = CT_UNSUPPORTED_CARD;
        return PDS_GENERAL_ERROR;
    }

    return PDS_OK;
}

static void sdspi_unidle(sdspi_physical_drive_t * sdspi)
{
    response_t response;
    uint32_t counter = SDSPI_TIMEOUT_ACMD41;
    uint32_t acmd41_argument = CT_UNSUPPORTED_CARD == sdspi->card_type ? SDSPI_ACMD41_V1_ARGUMENT : SDSPI_ACMD41_V2_ARGUMENT;
    uint32_t cmd1_argument = SDSPI_CMD_DEFAULT_ARGUMENT;

    do {
        sdspi_get_response_to_command(sdspi, SD_ACMD41_SD_SEND_OP_COND, acmd41_argument, &response);
    } while ((SDSPI_R1_NO_ERRORS != response.r1) && (counter > 0));

    if (SDSPI_R1_NO_ERRORS == response.r1) {
        if (CT_UNSUPPORTED_CARD == sdspi->card_type) {
            sdspi->card_type = CT_SD_VER1X_SC;
        }
    }
    else {
        if (CT_UNSUPPORTED_CARD == sdspi->card_type) {
            do {
                sdspi_get_response_to_command(sdspi, SD_CMD1_SEND_OP_COND, cmd1_argument, &response);
            } while ((SDSPI_R1_NO_ERRORS != response.r1) && (counter > 0));

            if (SDSPI_R1_NO_ERRORS == response.r1) {
                sdspi->card_type = CT_MMC;
            }
            else {
                sdspi->card_type = CT_UNSUPPORTED_CARD;
            }
        }
        else {
            sdspi->card_type = CT_UNSUPPORTED_CARD;
        }
    }
}

static int sd_spi_init_card(sdspi_physical_drive_t * sdspi)
{
    response_t response;
    int status;

    sdspi_power_up_card(sdspi);    // card will signal busy from now on, until CMD0_GO_IDLE_STATE command is sent

    status = sdspi_go_idle(sdspi);
    if (PDS_OK != status) {
        // error: could not enter idle state
        return PDS_GENERAL_ERROR;
    }

    // send interface condition to the card and check if the card can operate in the supplied voltage range
    status = sdspi_send_interface_condition(sdspi);
    if (PDS_OK != status) {
        return PDS_GENERAL_ERROR;
    }

    // exit idle state, and try to determine card type
    sdspi_unidle(sdspi);

    // determine the card type if it is not already, and set block length if needed
    switch (sdspi->card_type) {
        case CT_NO_CARD:        // card type needs to be determined
            sdspi_get_response_to_command(sdspi, SD_CMD58_READ_OCR, SDSPI_CMD_DEFAULT_ARGUMENT, &response);
            if (SDSPI_R1_NO_ERRORS == response.r1) {
                #ifdef  __MIKROC_AI_FOR_DSPIC__
                if ((response.optional_bytes & SDSPI_OCR_CSS_MASK) > 0) {
                #else
                if (response.optional_bytes & SDSPI_OCR_CSS_MASK) {
                #endif
                    sdspi->card_type = CT_SD_VER2X_HC_XC;
                    break;
                }
                else {
                    sdspi->card_type = CT_SD_VER2X_SC;
                }
            }
        case CT_SD_VER1X_SC:    // if card type is MMC od SDver1 set block length to 512 bytes, for consistent block length
        case CT_MMC:
            sdspi_get_response_to_command(sdspi, SD_CMD16_SET_BLOCKLEN, SDSPI_CMD16_ARGUMENT, &response);
            if (SDSPI_R1_NO_ERRORS == response.r1) {
                break;
            }
        default:                // if everything works as intended, the program should never get here
            sdspi->card_type = CT_UNSUPPORTED_CARD;
            return PDS_GENERAL_ERROR;
    }

    return PDS_OK;
}

static int sdspi_read_csd(sdspi_physical_drive_t * sdspi, uint8_t * csd_reg_data)
{
    response_t response;
    uint8_t crc_buffer[SDSPI_CRC_BUFFER_SIZE];

    if ((CT_NO_CARD == sdspi->card_type) || (CT_UNSUPPORTED_CARD == sdspi->card_type)) {
        // error: card not initialized
        return PDS_GENERAL_ERROR;
    }

    sdspi_get_response_to_command(sdspi, SD_CMD9_SEND_CSD, SDSPI_CMD_DEFAULT_ARGUMENT, &response);
    if (SDSPI_R1_NO_ERRORS != response.r1) {
        // error: command failed
        return PDS_GENERAL_ERROR;
    }

    if (SDSPI_DATA_TOKEN_RECEIVED == sdspi_wait_for_token(sdspi, SDSPI_DATA_TOKEN_START_BLOCK)) {
        spi_master_read(&sdspi->spi, csd_reg_data, SDSPI_CSD_REGISTER_SIZE);    // read data
        spi_master_read(&sdspi->spi, crc_buffer, SDSPI_CRC_BUFFER_SIZE);        // read crc and discard
        sdspi_deselect_device(sdspi);
        return PDS_OK;
    }
    else {
        // error: reading failed
        sdspi_deselect_device(sdspi);
        return PDS_GENERAL_ERROR;
    }
}

static uint32_t sdspi_get_csd_bitfield(uint8_t * csd, uint8_t fist_bit, uint8_t last_bit)
{
    uint8_t i;
    uint32_t bit_field = 0;
    uint8_t bit_field_start_bit = 127 - fist_bit;
    uint8_t bit_field_end_bit = 127 - last_bit;
    uint8_t bit_field_start_byte = bit_field_start_bit >> 3;
    uint8_t bit_field_end_byte = bit_field_end_bit >> 3;
    uint8_t bit_field_size = (((bit_field_start_bit - bit_field_end_bit) + 1) >> 3) + 1;
    uint8_t mask = 0xFF;
    uint8_t shift;

    if (bit_field_size == 1) {
        mask = mask >> (8 - bit_field_size);
    }
    for (i = bit_field_start_byte; i >= bit_field_end_byte; i--) {
        if ((i < bit_field_start_byte) && (i > bit_field_end_byte)) {
            bit_field |= (uint32_t)(csd[i]) << (((bit_field_size - 1) - (i - bit_field_end_byte)) * 8);
        }
        else if (i == bit_field_start_byte) {
            shift = 7 - (bit_field_start_bit & 0x7);
            bit_field |= (csd[i] & (mask << shift)) >> shift;
        }
        else if (i == bit_field_end_byte) {
            shift = bit_field_end_bit & 0x7;
            bit_field |= (uint32_t)(csd[i] & (mask >> shift)) << ((bit_field_size - 1) * 8);
        }
    }

    return bit_field;
}

static pd_status_t sdspi_init(sdspi_physical_drive_t * const ptr_this)
{
    uint8_t csd[SDSPI_CSD_REGISTER_SIZE];

    uint32_t c_size;
    uint32_t taac;
    uint32_t spi_speed = SDSPI_25MHZ_CLOCK;
    uint32_t spi_speed_step = SDSPI_1MHZ_STEP;

    if (CARD_NOT_INITIALIZED == ptr_this->is_initialized) {  // This check is needed in order to not just avoid double initialization, and subsequent bugs
        if (PDS_OK != sd_spi_init_card(ptr_this)) {
            // card initialization failed
            return PDS_GENERAL_ERROR;
        }
    }

    // this is needed in order to set to maximum SPI frequency value to is equal or lower to 25MHz
    while (1) {
        spi_master_set_speed(&ptr_this->spi, spi_speed);
        spi_speed -= spi_speed_step;
        if (PDS_OK == sdspi_read_csd(ptr_this, csd)) {
            taac = sdspi_get_csd_bitfield(csd, SDSPI_CSD_TAAC_START_BIT, SDSPI_CSD_TAAC_END_BIT);
            if (SDSPI_CSD_TAAC_VALUE_VER23 == taac) { // this only works on SDHC
                break;
            }
        }
    }

    c_size = sdspi_get_csd_bitfield(csd, SDSPI_CSD_CSIZE_START_BIT_VER2, SDSPI_CSD_CSIZE_END_BIT_VER2); // this is only valid for HC cards
    ptr_this->base.sector_count = (c_size + 1) << 10;  // (C_SIZE + 1) * 1024 / TODO this is only valid for HC and XC cards
    ptr_this->is_initialized = CARD_INITIALIZED;

    return PDS_OK;
}

static pd_status_t sdspi_read(sdspi_physical_drive_t * const ptr_this, void * buf, unsigned long long addr, unsigned long long size)
{
    response_t response;
    uint8_t crc_buffer[2];
    uint32_t address = CT_SD_VER2X_HC_XC != ptr_this->card_type ? addr : addr/SDSPI_DATA_BLOCK_SIZE;
    uint32_t block_count = size/SDSPI_DATA_BLOCK_SIZE;
    uint32_t counter = block_count;
    sdspi_command_t cmd_read = block_count > 1 ? SD_CMD18_READ_MULTIPLE_BLOCK : SD_CMD17_READ_SINGLE_BLOCK;
    uint8_t * buffer_address = (uint8_t *)buf;

    if (CARD_NOT_INITIALIZED == ptr_this->is_initialized) {
        // error: cannot read uninitialized card
        return PDS_GENERAL_ERROR;
    }

    // notify card to prepare data for reading
    sdspi_get_response_to_command(ptr_this, cmd_read, address, &response);
    // checking for errors
    if (response.r1 != SDSPI_R1_NO_ERRORS ) {
        // error: command failed
        return PDS_GENERAL_ERROR;
    }

    // read data sent by the card
    do {
        // wait for data token
        if (SDSPI_DATA_TOKEN_RECEIVED == sdspi_wait_for_token(ptr_this, SDSPI_DATA_TOKEN_START_BLOCK)) {
            spi_master_read(&ptr_this->spi, buffer_address, SDSPI_DATA_BLOCK_SIZE);    // read data
            spi_master_read(&ptr_this->spi, crc_buffer, 2);                            // read crc and discard it
            counter--;                                                                 // decrease remaining block counter
            buffer_address += SDSPI_DATA_BLOCK_SIZE;                                   // prepare new bock buffer address
        }
        else { // if data token was never received
            sdspi_deselect_device(ptr_this);
            return PDS_GENERAL_ERROR;
        }
    } while (counter >= 1);

    // in the case of multup-block reading, reading needs to be stopped by stop transmission command
    if (SD_CMD18_READ_MULTIPLE_BLOCK == cmd_read) {
        sdspi_get_response_to_command(ptr_this, SD_CMD12_STOP_TRANSMISSION, SDSPI_CMD_DEFAULT_ARGUMENT, &response);
        if (response.r1 != SDSPI_R1_NO_ERRORS) {
            // error: faile to stop multi block writing
            sdspi_deselect_device(ptr_this);
            return PDS_GENERAL_ERROR;
        }
    }
    // in case of one block reading, just deselect the device
    else {
        sdspi_deselect_device(ptr_this);
    }

    return PDS_OK;
}

static pd_status_t sdspi_write(sdspi_physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size)
{
    uint8_t data_response = 0;
    response_t response;
    uint8_t crc_buffer[2] = {SDSPI_FILL_DATA_BUFFER, SDSPI_FILL_DATA_BUFFER};
    uint32_t address = CT_SD_VER2X_HC_XC != ptr_this->card_type ? addr : addr/SDSPI_DATA_BLOCK_SIZE;
    uint32_t block_count = size/SDSPI_DATA_BLOCK_SIZE;
    uint32_t counter = block_count;
    sdspi_command_t cmd_write = block_count > 1 ? SD_CMD25_WRITE_MULTIPLE_BLOCK : SD_CMD24_WRITE_BLOCK;
    const uint8_t * __generic_ptr buffer_address = (const uint8_t * __generic_ptr)buffer;
    uint8_t token = block_count > 1 ? SDSPI_DATA_TOKEN_CMD25_START : SDSPI_DATA_TOKEN_CMD24;

    if (CARD_NOT_INITIALIZED == ptr_this->is_initialized) {
        // error: cannot read uninitialized card
        return PDS_GENERAL_ERROR;
    }

    // in the case of multi-block write, for speed optimization purposes, card needs to be notified how many blocks need to be pre-erased
    if (block_count > 1) {
        sdspi_get_response_to_command(ptr_this, SD_ACMD23_SET_WR_BLK_ERASE_COUNT, block_count, &response);
        if (SDSPI_R1_NO_ERRORS != response.r1) {
            // error: command failed
            return PDS_GENERAL_ERROR;
        }
    }

    // notify card to prepare to write
    sdspi_get_response_to_command(ptr_this, cmd_write, address, &response);
    // checking for errors
    if (SDSPI_R1_NO_ERRORS != response.r1) {
        // error: command failed
        return PDS_GENERAL_ERROR;
    }

    // send data to the card
    do {
        spi_master_write(&ptr_this->spi, &token, 1);                                // sending data token start
        spi_master_write(&ptr_this->spi, buffer_address, SDSPI_DATA_BLOCK_SIZE);    // sending data block
        spi_master_write(&ptr_this->spi, crc_buffer, 2);                            // sending 2 byte crc
        spi_master_read(&ptr_this->spi, &data_response, 1);                         // read data response
        if (DATA_RESPONSE_ACCEPTED == (data_response & DATA_RESPONSE_MASK)) {       // if data was accepted
            if (CARD_NOT_READY == sdspi_wait_until_ready(&ptr_this->spi)) {         // wait until busy signal is cleared
                // error: timeout, card is busy
                sdspi_deselect_device(ptr_this);
                return PDS_GENERAL_ERROR;
            }
            counter--;                                                              // decrease remaining block counter
            buffer_address += SDSPI_DATA_BLOCK_SIZE;                                // prepare new bock buffer address
        }
        else { // if data was rejected by the card
            sdspi_deselect_device(ptr_this);
            return PDS_GENERAL_ERROR;
        }
    } while (counter >= 1);

    // if multi-block write was used, send data stop token to notify card that writing is over
    if (block_count > 1) {
        token = SDSPI_DATA_TOKEN_CMD25_STOP;
        spi_master_write(&ptr_this->spi, &token, 1);                                // send data token stop
        if (CARD_NOT_READY == sdspi_wait_until_ready(&ptr_this->spi)) {             // wait until busy signal is cleared
                // error: timeout, card is busy
                sdspi_deselect_device(ptr_this);
                return PDS_GENERAL_ERROR;
            }
    }
    sdspi_deselect_device(ptr_this);

    return PDS_OK;
}

static pd_status_t sdspi_trim(sdspi_physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size)
{
    uint8_t r1_response;
    uint32_t response;
    uint8_t crc_buffer[2] = {SDSPI_FILL_DATA_BUFFER, SDSPI_FILL_DATA_BUFFER};

    if (CARD_NOT_INITIALIZED == ptr_this->is_initialized) {
        // error: card is not initialized
        return PDS_GENERAL_ERROR;
    }

    // TODO finish this function

    return PDS_OK;
}

static void sdspi_bus_init(sdspi_physical_drive_t * sd, sdspi_config_t * config)
{
    spi_master_config_t spi_cfg;

    digital_out_init(&sd->cs, config->spi_cs);

    spi_cfg.default_write_data = SDSPI_FILL_DATA_BUFFER; // DI line must be kept high, during DO reading, important for spi_master_read(...) function
    spi_cfg.sck   = config->spi_sck;
    spi_cfg.miso  = config->spi_miso;
    spi_cfg.mosi  = config->spi_mosi;
    spi_cfg.speed = SDSPI_100KHZ_CLOCK;
    spi_cfg.mode = SPI_MASTER_MODE_0;

    spi_master_open(&sd->spi, &spi_cfg);
    spi_master_set_default_write_data(&sd->spi, spi_cfg.default_write_data);
    spi_master_set_mode(&sd->spi, spi_cfg.mode);
    spi_master_set_speed(&sd->spi, spi_cfg.speed);
}

pd_status_t sdspi_physical_drive_init(sdspi_physical_drive_t * sdspi, sdspi_config_t * config)
{
    #ifndef __XC8
    static physical_drive_vector_table_t sdspi_vtable = {
        (pd_status_t (*)(physical_drive_t * const ptr_this))&sdspi_init,
        (pd_status_t (*)(physical_drive_t * const ptr_this, void * buffer, unsigned long long addr, unsigned long long size))&sdspi_read,
        (pd_status_t (*)(physical_drive_t * const ptr_this, const void * __generic_ptr buffer, unsigned long long addr, unsigned long long size))&sdspi_write,
        (pd_status_t (*)(physical_drive_t * const ptr_this, unsigned long long addr, unsigned long long size))0 // TODO function under construction
    };
    #endif
    pd_status_t res;

    // validate config struct
    if (!config) {
        // error: no valid configuration provided
        return PDS_GENERAL_ERROR;
    }

    res = physical_drive_validate_drive(&sdspi->base);
    if (res != PDS_OK) {
        // error: physical drive is either nullptr or is not initialized
        return res;
    }

    memset(&sdspi->spi, 0, sizeof(spi_master_t));
    memset(&sdspi->cs, 0, sizeof(digital_out_t));

    sdspi->base.vtptr = &sdspi_vtable;
    physical_drive_base_init(&sdspi->base);
    sdspi->base.type = PD_TYPE_SDSPI;
    sdspi->base.erase_block_size = 1;
    sdspi->base.sector_size = SDSPI_DATA_BLOCK_SIZE;

    sdspi->card_type = CT_NO_CARD;
    sdspi->is_initialized = CARD_NOT_INITIALIZED;

    sdspi_bus_init(sdspi, config);

    return PDS_OK;
}
