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
** a written agreement between you and The mikroElektronika Company.
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
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_dma_irq.c
 * @brief DMA HAL LOW LEVEL stream interrupt handlers (STM32F2/F4/F7).
 *
 * Kept apart from hal_ll_dma.c on purpose: this object is only linked when
 * hal_ll_dma_register_irq_handler() is used, so applications that do not use
 * DMA interrupts (or define their own DMAx_StreamY_IRQHandler) are unaffected.
 */

#include "hal_ll_dma.h"
#include "hal_ll_core_defines.h"

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Enabled events per stream, owned by hal_ll_dma.c. */
extern uint8_t hal_ll_dma_irq_events[ DMA_NUM_OF_MODULES ][ DMA_NUM_OF_STREAMS ];

static hal_ll_dma_isr_t hal_ll_dma_irq_handlers[ DMA_NUM_OF_MODULES ][ DMA_NUM_OF_STREAMS ];
static void *hal_ll_dma_irq_contexts[ DMA_NUM_OF_MODULES ][ DMA_NUM_OF_STREAMS ];

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/*!< @brief Flag access by module/stream, implemented in hal_ll_dma.c. */
uint8_t hal_ll_dma_get_status_raw( uint8_t module, uint8_t stream );
void hal_ll_dma_clear_status_raw( uint8_t module, uint8_t stream, uint8_t events );

/**
 * @brief Common stream interrupt body.
 * @details Clears the stream's enabled events that are pending, then calls
 *          the registered callback with them.
 * @param[in] module DMA module number.
 * @param[in] stream DMA stream number.
 * @return Nothing.
 */
static void hal_ll_dma_irq_dispatch( uint8_t module, uint8_t stream );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_register_irq_handler( hal_ll_dma_t *obj, hal_ll_dma_isr_t handler, void *context ) {
    if ( !obj || ( obj->module >= DMA_NUM_OF_MODULES ) || ( obj->stream >= DMA_NUM_OF_STREAMS ) )
        return HAL_LL_DMA_ERROR;

    hal_ll_dma_irq_contexts[ obj->module ][ obj->stream ] = context;
    hal_ll_dma_irq_handlers[ obj->module ][ obj->stream ] = handler;

    return HAL_LL_DMA_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_dma_irq_dispatch( uint8_t module, uint8_t stream ) {
    uint8_t events = hal_ll_dma_get_status_raw( module, stream ) & hal_ll_dma_irq_events[ module ][ stream ];

    hal_ll_dma_clear_status_raw( module, stream, events );

    if ( events && hal_ll_dma_irq_handlers[ module ][ stream ] )
        hal_ll_dma_irq_handlers[ module ][ stream ]( hal_ll_dma_irq_contexts[ module ][ stream ], events );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS

#define HAL_LL_DMA_STREAM_IRQ_HANDLER( _name, _vector, _module, _stream ) \
    void MARK_AS_IRQ_HANDLER _name( void ) MIKROC_IV( _vector ) { \
        hal_ll_dma_irq_dispatch( _module, _stream ); \
    }

HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream0_IRQHandler, 27, 0, 0 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream1_IRQHandler, 28, 0, 1 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream2_IRQHandler, 29, 0, 2 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream3_IRQHandler, 30, 0, 3 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream4_IRQHandler, 31, 0, 4 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream5_IRQHandler, 32, 0, 5 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream6_IRQHandler, 33, 0, 6 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA1_Stream7_IRQHandler, 63, 0, 7 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream0_IRQHandler, 72, 1, 0 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream1_IRQHandler, 73, 1, 1 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream2_IRQHandler, 74, 1, 2 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream3_IRQHandler, 75, 1, 3 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream4_IRQHandler, 76, 1, 4 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream5_IRQHandler, 84, 1, 5 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream6_IRQHandler, 85, 1, 6 )
HAL_LL_DMA_STREAM_IRQ_HANDLER( DMA2_Stream7_IRQHandler, 86, 1, 7 )

// ------------------------------------------------------------------------- END
