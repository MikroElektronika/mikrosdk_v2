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
 * @file  callbacks_default.c
 * @brief TinyUSB default callback routines.
 * @details Defined as weak so the user defined routine can take over.
 */

#include "tusb.h"

//--------------------------------------------------------------------+
// Unused callbacks defined for sake of HID library
//--------------------------------------------------------------------+

#ifdef __HAS_DEVICE__
#if CFG_TUD_HID==1
// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
TU_ATTR_WEAK uint8_t const * tud_hid_descriptor_report_cb(uint8_t itf)
{
    // TODO not Implemented
    (void) itf;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
TU_ATTR_WEAK void tud_hid_set_report_cb(uint8_t itf,
                                        uint8_t report_id,
                                        hid_report_type_t report_type,
                                        uint8_t const* buffer,
                                        uint16_t bufsize
                                       )
{
    // TODO not Implemented
    (void) itf;
    (void) report_id;
    (void) report_type;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
TU_ATTR_WEAK uint16_t tud_hid_get_report_cb(uint8_t itf,
                                            uint8_t report_id,
                                            hid_report_type_t report_type,
                                            uint8_t* buffer,
                                            uint16_t reqlen
                                           )
{
    // TODO not Implemented
    (void) itf;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}
#endif
#if CFG_TUD_MSC==1
TU_ATTR_WEAK int32_t tud_msc_read10_cb (uint8_t lun, uint32_t lba,
                                        uint32_t offset, void* buffer,
                                        uint32_t bufsize
                                       )
{
    // TODO not implemented
    (void) lun;
    (void) lba;
    (void) offset;
    (void) buffer;
    (void) bufsize;

    return 0;
}

TU_ATTR_WEAK int32_t tud_msc_write10_cb (uint8_t lun, uint32_t lba,
                                         uint32_t offset, uint8_t* buffer,
                                         uint32_t bufsize
                                        )
{
    // TODO not implemented
    (void) lun;
    (void) lba;
    (void) offset;
    (void) buffer;
    (void) bufsize;

    return 0;
}

TU_ATTR_WEAK void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor_id[8],
                                     uint8_t product_id[16], uint8_t product_rev[4]
                                    )
{
    // TODO not implemented
    (void) lun;
    (void) vendor_id;
    (void) product_id;
    (void) product_rev;
}

TU_ATTR_WEAK bool tud_msc_test_unit_ready_cb(uint8_t lun) {
    // TODO not implemented
    (void) lun;

    return false;
}

TU_ATTR_WEAK void tud_msc_capacity_cb(uint8_t lun, uint32_t* block_count, uint16_t* block_size) {
    // TODO not implemented
    (void) lun;
    (void) block_count;
    (void) block_size;
}

TU_ATTR_WEAK int32_t tud_msc_scsi_cb (uint8_t lun, uint8_t const scsi_cmd[16], void* buffer, uint16_t bufsize) {
    // TODO not implemented
    (void) lun;
    (void) scsi_cmd;
    (void) buffer;
    (void) bufsize;

    return 0;
}
#endif
#if (CFG_TUD_ECM_RNDIS==1) || (CFG_TUD_NCM==1)
TU_ATTR_WEAK bool tud_network_recv_cb(const uint8_t *src, uint16_t size) {
    // TODO not implemented
    (void) src;
    (void) size;

    return false;
}

TU_ATTR_WEAK uint16_t tud_network_xmit_cb(uint8_t *dst, void *ref, uint16_t arg) {
    // TODO not implemented
    (void) dst;
    (void) ref;
    (void) arg;

    return 0;
}

TU_ATTR_WEAK void tud_network_init_cb(void) {
    // TODO not implemented
}

// TODO not implemented
TU_ATTR_WEAK uint8_t tud_network_mac_address[6] = { 0 };

TU_ATTR_WEAK void tud_network_link_state_cb(bool state) {
    // TODO not implemented
    (void) state;
}
#endif
#if CFG_TUD_DFU==1
TU_ATTR_WEAK uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state) {
    // TODO not implemented
    (void) alt;
    (void) state;

    return 0;
}

TU_ATTR_WEAK void tud_dfu_download_cb (
                                        uint8_t alt, uint16_t block_num,
                                        uint8_t const *data, uint16_t length
                                      )
{
    // TODO not implemented
    (void) alt;
    (void) block_num;
    (void) data;
    (void) length;
}

TU_ATTR_WEAK void tud_dfu_manifest_cb(uint8_t alt) {
    // TODO not implemented
    (void) alt;
}
#endif
#if CFG_TUD_DFU_RUNTIME==1
TU_ATTR_WEAK void tud_dfu_runtime_reboot_to_dfu_cb(void) {
    // TODO not implemented
}
#endif
#if CFG_TUD_USBTMC==1
    #if (CFG_TUD_USBTMC_ENABLE_488)
    TU_ATTR_WEAK usbtmc_response_capabilities_488_t const * tud_usbtmc_get_capabilities_cb(void) {
        // TODO not implemented
    }
    #else
    TU_ATTR_WEAK usbtmc_response_capabilities_t const * tud_usbtmc_get_capabilities_cb(void) {
        // TODO not implemented
    }
    #endif
TU_ATTR_WEAK void tud_usbtmc_open_cb(uint8_t interface_id) {
    // TODO not implemented
    (void) interface_id;
}

TU_ATTR_WEAK bool tud_usbtmc_msgBulkOut_start_cb(usbtmc_msg_request_dev_dep_out const * msgHeader) {
    // TODO not implemented
    (void) msgHeader;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_msg_data_cb( void *data, size_t len, bool transfer_complete) {
    // TODO not implemented
    (void) data;
    (void) len;
    (void) transfer_complete;

    return false;
}

TU_ATTR_WEAK void tud_usbtmc_bulkOut_clearFeature_cb(void) {
    // TODO not implemented
}

TU_ATTR_WEAK bool tud_usbtmc_msgBulkIn_request_cb(usbtmc_msg_request_dev_dep_in const * request) {
    // TODO not implemented
    (void) request;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_msgBulkIn_complete_cb(void) {
    // TODO not implemented
    return false;
}

TU_ATTR_WEAK void tud_usbtmc_bulkIn_clearFeature_cb(void) {
    // TODO not implemented
}

TU_ATTR_WEAK bool tud_usbtmc_initiate_abort_bulk_in_cb(uint8_t *tmcResult) {
    // TODO not implemented
    (void) tmcResult;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_initiate_abort_bulk_out_cb(uint8_t *tmcResult) {
    // TODO not implemented
    (void) tmcResult;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_initiate_clear_cb(uint8_t *tmcResult) {
    // TODO not implemented
    (void) tmcResult;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_check_abort_bulk_in_cb(usbtmc_check_abort_bulk_rsp_t *rsp) {
    // TODO not implemented
    (void) rsp;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_check_abort_bulk_out_cb(usbtmc_check_abort_bulk_rsp_t *rsp) {
    // TODO not implemented
    (void) rsp;

    return false;
}

TU_ATTR_WEAK bool tud_usbtmc_check_clear_cb(usbtmc_get_clear_status_rsp_t *rsp) {
    // TODO not implemented

}

TU_ATTR_WEAK uint8_t tud_usbtmc_get_stb_cb(uint8_t *tmcResult) {
    // TODO not implemented
    (void) tmcResult;

    return 0;
}
#endif
#if (CFG_TUD_ECM_RNDIS==1) || (CFG_TUD_NCM==1)

#endif
TU_ATTR_WEAK void rndis_class_set_handler(uint8_t *data, int size) {
    // TODO not implemented
    (void) data;
    (void) size;
}
#endif

#ifdef __HAS_HOST__
    // TODO
#endif

// ------------------------------------------------------------------------- END
