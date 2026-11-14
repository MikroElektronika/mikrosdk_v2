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
 * @file  hal_dma_irq.c
 * @brief DMA HAL interrupt callback registration.
 *
 * Separate from hal_dma.c so that the low level interrupt handlers it pulls in
 * are only linked into applications that register a DMA callback.
 */

#include "hal_dma.h"
#include "hal_ll_dma.h"

err_t hal_dma_register_irq_handler( hal_dma_t *obj, hal_dma_isr_t handler, void *context )
{
    err_t status = HAL_DMA_ERROR;

    #ifdef HAL_LL_DMA_EXT_SUPPORTED
    if ( obj && obj->allocated && obj->initialized ) {
        status = hal_ll_dma_register_irq_handler( (hal_ll_dma_t *)obj, (hal_ll_dma_isr_t)handler, context );
    }
    #else
    (void)obj;
    (void)handler;
    (void)context;
    #endif

    return status;
}

// ------------------------------------------------------------------------- END
