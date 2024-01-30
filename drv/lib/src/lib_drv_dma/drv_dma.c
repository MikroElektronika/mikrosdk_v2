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
 * @file  drv_dma.c
 * @brief DMA driver implementation.
 */

#include "drv_dma.h"

void dma_configure_default( dma_config_t *config )
{
    if ( config ) {
        /**
         * Fill all values to default ones.
         * Leave only channel as UNINITIALIZED.
         */
        config->module = 0xFF;
        config->stream = 0xFF;
        config->channel = 0xFF;
        config->direction = DMA_DIRECTION_DEFAULT;
        config->mode = DMA_MODE_DEFAULT;
        config->priority = DMA_PRIORITY_DEFAULT;

        /**
         * Set memory values to default ones.
         */
        config->src_inc = false;
        config->data_align_source = DMA_DATA_ALIGN_DEFAULT;
        config->burst_size_source = DMA_BURST_SIZE_INCREMENT_DEFAULT;

        /**
         * Set peripheral values to default ones.
         */
        config->dst_inc = false;
        config->data_align_destination = DMA_DATA_ALIGN_DEFAULT;
        config->burst_size_destination = DMA_BURST_SIZE_INCREMENT_DEFAULT;

        /**
         * Set transfer values to default ones.
         */
        config->addr_src = 0;
        config->addr_dst = 0;
        config->transfer_length = 0;
    }
}

void dma_get_channels( dma_channel_t *channels )
{
    if ( channels ) {
        /*!< Used to check which channels are available. */
        hal_dma_get_channels( channels );
    }
}

err_t dma_open( dma_t *obj, dma_config_t *config )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( !obj->allocated ) {
            /*!< Allocate and initialize DMA object. */
            status = hal_dma_open( (hal_dma_t *)obj, (hal_dma_config_t *)config );
        }
    }

    return status;
}

err_t dma_set_mode( dma_t *obj, dma_mode_t mode )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Set dma mode - normal/circular etc. */
            status = hal_dma_set_mode( (hal_dma_t *)obj, (hal_dma_mode_t)mode );
        }
    }

    return status;
}

err_t dma_set_direction( dma_t *obj, dma_direction_t direction )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /**
             * Set DMA direction:
             *     M2M/M2P/P2M/P2P
             */
            status = hal_dma_set_direction( (hal_dma_t *)obj, (hal_dma_direction_t)direction );
        }
    }

    return status;
}

err_t dma_set_priority( dma_t *obj, dma_priority_t priority )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Set priority of currently active channel. */
            status = hal_dma_set_priority( (hal_dma_t *)obj, (hal_dma_priority_t)priority );
        }
    }

    return status;
}

err_t dma_set_transfer_config( dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, dma_source_memory_region_t src_mem_type )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Configure the transfer type. */
            status = hal_dma_set_transfer_config( (hal_dma_t *)obj, addr_src, addr_dst, transfer_size, (hal_dma_source_memory_region_t)src_mem_type );
        }
    }

    return status;
}

err_t dma_transfer_start( dma_t *obj )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Initialize transfer. */
            status = hal_dma_transfer_start( (hal_dma_t *)obj );
        }
    }

    return status;
}

err_t dma_transfer_stop( dma_t *obj )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Stop transfer. */
            status = hal_dma_transfer_stop( (hal_dma_t *)obj );
        }
    }

    return status;
}

err_t dma_transfer_abort( dma_t *obj )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Abort transfer. */
            status = hal_dma_transfer_abort( (hal_dma_t *)obj );
        }
    }

    return status;
}

err_t dma_close( dma_t *obj )
{
    err_t status = DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Reset everything to default or uninitialized values. */
            status = hal_dma_close( (hal_dma_t *)obj );
        }
    }

    return status;
}


// ------------------------------------------------------------------------- END
