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
 * @file  drv_dma.c
 * @brief DMA driver implementation.
 */

#include "drv_dma.h"

#if !DRV_TO_HAL
extern hal_dma_channel_t dma_channels;
#endif

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
        #if DRV_TO_HAL
        hal_dma_get_channels( channels );
        #else
        memcpy( channels, dma_channels, sizeof(hal_dma_channel_t) );
        #endif
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
            #if DRV_TO_HAL
            status = hal_dma_set_mode( (hal_dma_t *)obj, (hal_dma_mode_t)mode );
            #else
            /**
            * Abort any transfer before continuing.
            * Set dma mode - normal or circular.
            */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( (hal_dma_t *)obj );
                status = hal_ll_dma_set_mode( (hal_ll_dma_t *)obj, (hal_ll_dma_mode_t)mode );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.mode = mode;
                }
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_set_direction( (hal_dma_t *)obj, (hal_dma_direction_t)direction );
            #else
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( (hal_dma_t *)obj );
                status = hal_ll_dma_set_direction( (hal_ll_dma_t *)obj, (hal_ll_dma_direction_t)direction );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.direction = direction;
                }
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_set_priority( (hal_dma_t *)obj, (hal_dma_priority_t)priority );
            #else
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( (hal_dma_t *)obj );
                status = hal_ll_dma_set_priority( (hal_ll_dma_t *)obj, (hal_ll_dma_priority_t)priority );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.priority = priority;
                }
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_set_transfer_config( (hal_dma_t *)obj, addr_src, addr_dst, transfer_size, (hal_dma_source_memory_region_t)src_mem_type );
            #else
            obj->config.addr_src = addr_src;
            obj->config.addr_dst = addr_dst;
            obj->config.transfer_length = transfer_size;
            /**
             * Abort any transfer before continuing.
             * Configure the transfer type using
             * standard HAL config APIs.
             */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( (hal_dma_t *)obj );

                status = HAL_DMA_SUCCESS;
                status |= hal_dma_set_mode( (hal_dma_t *)obj, (hal_dma_mode_t)obj->config.mode );
                status |= hal_dma_set_direction( (hal_dma_t *)obj, (hal_dma_direction_t)obj->config.direction );
                status |= hal_dma_set_priority( (hal_dma_t *)obj, (hal_dma_priority_t)obj->config.priority );

                status |= hal_ll_dma_set_parameters( (hal_ll_dma_t *)obj, addr_src, addr_dst, transfer_size, (hal_ll_dma_source_memory_region_t)src_mem_type );
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_transfer_start( (hal_dma_t *)obj );
            #else
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_start( (hal_ll_dma_t *)obj );
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_transfer_stop( (hal_dma_t *)obj );
            #else
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_stop( (hal_ll_dma_t *)obj );
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_transfer_abort( (hal_dma_t *)obj );
            #else
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_abort( (hal_ll_dma_t *)obj );
            }
            #endif
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
            #if DRV_TO_HAL
            status = hal_dma_close( (hal_dma_t *)obj );
            #else
            /*!< Abort any ongoing transfer. */
            (void)hal_dma_transfer_abort( (hal_dma_t *)obj );
            if ( obj->initialized ) {
                hal_ll_dma_deinit( (hal_ll_dma_t *)obj );
            }

            /*!< Reset current stream channel handle to HAL_DMA_STATE_FREE. */
            dma_channels[obj->module][obj->stream][obj->channel] = HAL_DMA_STATE_FREE;

            /*!< Reset all data to 0. */
            memset(obj, 0, sizeof(hal_dma_t));

            status = DMA_SUCCESS;
            #endif
        }
    }

    return status;
}


// ------------------------------------------------------------------------- END
