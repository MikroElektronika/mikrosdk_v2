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
 * @file  hal_dma.c
 * @brief This file contains all the functions prototypes for the DMA library.
 */

#include "hal_dma.h"
#include "hal_ll_dma.h"

/*!< @brief Sets module, stream and channel to first free one. */
#define set_module_stream_and_channel_default() obj->module = i; \
                                                obj->stream = j; \
                                                obj->channel = k;

/*!< @brief Sets module, stream and channel to user defined values. */
#define set_module_stream_and_channel() obj->module = config->module; \
                                        obj->stream = config->stream; \
                                        obj->channel = config->channel;

/**
 * @brief Local static global handler.
 *   + DMA_NUM_OF_MODULES defined per MCU.
 *   + DMA_NUM_OF_STREAMS defined per MCU.
 *   + DMA_NUM_OF_CHANNELS defined per MCU.
 */
static hal_dma_channel_t dma_channels = {0};

/**
 * @brief Checks if desired stream and channel are available on current MCU.
 */
static inline bool check_limit( hal_dma_t *obj )
{
    return (((obj->config.stream < DMA_NUM_OF_STREAMS) && (obj->config.stream != 0xFF) && \
             (obj->config.channel < DMA_NUM_OF_CHANNELS) && (obj->config.channel != 0xFF)) ? (true) : (false));
}

void hal_dma_configure_default( hal_dma_config_t *config )
{
    if ( config ) {
        /**
         * Fill all values to default ones.
         * Leave only channel as UNINITIALIZED.
         */
        config->module = 0xFF;
        config->stream = 0xFF;
        config->channel = 0xFF;
        config->direction = HAL_DMA_DIRECTION_DEFAULT;
        config->mode = HAL_DMA_MODE_DEFAULT;
        config->priority = HAL_DMA_PRIORITY_DEFAULT;

        /**
         * Set memory values to default ones.
         */
        config->source_inc = false;
        config->data_align_source = HAL_DMA_DATA_ALIGN_DEFAULT;
        config->burst_size_source = HAL_DMA_BURST_SIZE_INCREMENT_DEFAULT;

        /**
         * Set peripheral values to default ones.
         */
        config->destination_inc = false;
        config->data_align_destination = HAL_DMA_DATA_ALIGN_DEFAULT;
        config->burst_size_destination = HAL_DMA_BURST_SIZE_INCREMENT_DEFAULT;

        /**
         * Set transfer values to default ones.
         */
        config->addr_src = 0;
        config->addr_dst = 0;
        config->transfer_length = 0;
    }
}

void hal_dma_get_channels( hal_dma_channel_t *channels )
{
    if ( channels ) {
        /*!< Used to check which channels are available. */
        memcpy( channels, dma_channels, sizeof(hal_dma_channel_t) );
    }
}

err_t hal_dma_open( hal_dma_t *obj, hal_dma_config_t *config )
{
    err_t status = HAL_DMA_ERROR;
    bool channel_found = false;

    if ( obj ) {
        if ( !obj->allocated ) {
            /**
             * First copy the config structure contents
             * to object handle.
             */
            hal_dma_config_t *p_config = &obj->config;
            memcpy( p_config, config, sizeof( hal_dma_config_t ) );

            /* Then check if stream and channel are within limits. */
            if ( check_limit( obj ) ) {
                if ( 0xFF == config->module ) {
                    for ( int i = 0; i < DMA_NUM_OF_MODULES; i++ ) {
                        if ( 0xFF == config->stream ) {
                            for ( int j = 0; j < DMA_NUM_OF_STREAMS; j++ ) {
                                if ( 0xFF == config->channel ) {
                                    for ( int k = 0; k < DMA_NUM_OF_CHANNELS; k++ ) {
                                        if ( !dma_channels[i][j][k] ) {
                                            /**
                                            * If default channel is set,
                                            * iterate through maximum number of channels
                                            * for current stream and settle for first that
                                            * hasn't been allocated yet.
                                            */
                                            set_module_stream_and_channel_default();
                                            status = HAL_DMA_SUCCESS;
                                            channel_found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        if ( channel_found )
                            break;
                    }
                } else {
                    /*!< Allocate user desired channel. */
                    set_module_stream_and_channel();
                    status = HAL_DMA_SUCCESS;
                }
            }
        }
    }

    /**
     * If last status was a success proceed with module
     * hardware initialization.
     */
    if ( HAL_DMA_SUCCESS == status ) {
        obj->allocated = true;
        obj->initialized = false;

        /*!< Set stream/channel as allocated. */
        dma_channels[obj->module][obj->stream][obj->channel] = HAL_DMA_STATE_ALLOCATED;

        status = hal_ll_dma_init( (hal_ll_dma_t *)obj );
        if ( HAL_DMA_SUCCESS == status ) {
            obj->initialized = true;
        }
    }

    /**
     * If it reaches here, invalid pointers have
     * been passed to API.
     */
    return status;
}

err_t hal_dma_set_mode( hal_dma_t *obj, hal_dma_mode_t mode )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /**
             * Abort any transfer before continuing.
             * Set dma mode - normal or circular.
             */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( obj );
                status = hal_ll_dma_set_mode( (hal_ll_dma_t *)obj, (hal_ll_dma_mode_t)mode );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.mode = mode;
                }
            }
        }
    }

    return status;
}

err_t hal_dma_set_direction( hal_dma_t *obj, hal_dma_direction_t direction )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /**
             * Abort any transfer before continuing.
             * Set dma direction.
             * M2M/M2P/P2M/P2P
             */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( obj );
                status = hal_ll_dma_set_direction( (hal_ll_dma_t *)obj, (hal_ll_dma_direction_t)direction );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.direction = direction;
                }
            }
        }
    }

    return status;
}

err_t hal_dma_set_priority( hal_dma_t *obj, hal_dma_priority_t priority )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /**
             * Abort any transfer before continuing.
             * Set priority of currently active channel.
             */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( obj );
                status = hal_ll_dma_set_priority( (hal_ll_dma_t *)obj, (hal_ll_dma_priority_t)priority );
                if ( HAL_LL_DMA_SUCCESS == status ) {
                    // Map new value to object.
                    obj->config.priority = priority;
                }
            }
        }
    }

    return status;
}

err_t hal_dma_set_transfer_config( hal_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_dma_source_memory_region_t src_mem_type )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            obj->config.addr_src = addr_src;
            obj->config.addr_dst = addr_dst;
            obj->config.transfer_length = transfer_size;
            /**
             * Abort any transfer before continuing.
             * Configure the transfer type using
             * standard HAL config APIs.
             */
            if ( obj->initialized ) {
                (void)hal_dma_transfer_abort( obj );

                status = HAL_DMA_SUCCESS;
                status |= hal_dma_set_mode( obj, obj->config.mode );
                status |= hal_dma_set_direction( obj, obj->config.direction );
                status |= hal_dma_set_priority( obj, obj->config.priority );

                status |= hal_ll_dma_set_parameters( (hal_ll_dma_t *)obj, addr_src, addr_dst, transfer_size, (hal_ll_dma_source_memory_region_t)src_mem_type );
            }
        }
    }

    return status;
}

err_t hal_dma_transfer_start( hal_dma_t *obj )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Initialize transfer. */
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_start( (hal_ll_dma_t *)obj );
            }
        }
    }

    return status;
}

err_t hal_dma_transfer_stop( hal_dma_t *obj )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Stop transfer. */
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_stop( (hal_ll_dma_t *)obj );
            }
        }
    }

    return status;
}

err_t hal_dma_transfer_abort( hal_dma_t *obj )
{
    err_t status = HAL_DMA_ERROR;

    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Abort any ongoing transfer. */
            if ( obj->initialized ) {
                status = hal_ll_dma_transfer_abort( (hal_ll_dma_t *)obj );
            }
        }
    }

    return status;
}

err_t hal_dma_close( hal_dma_t *obj )
{
    if ( obj ) {
        if ( obj->allocated ) {
            /*!< Abort any ongoing transfer. */
            (void)hal_dma_transfer_abort( obj );
            if ( obj->initialized ) {
                hal_ll_dma_deinit( (hal_ll_dma_t *)obj );
            }

            /*!< Reset current stream channel handle to HAL_DMA_STATE_FREE. */
            dma_channels[obj->module][obj->stream][obj->channel] = HAL_DMA_STATE_FREE;

            /*!< Reset all data to 0. */
            memset(obj, 0, sizeof(hal_dma_t));
        }
    }

    return HAL_DMA_SUCCESS;
}

// ------------------------------------------------------------------------- END
