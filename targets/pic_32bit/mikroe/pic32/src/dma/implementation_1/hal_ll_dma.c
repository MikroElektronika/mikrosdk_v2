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
 * @file  hal_ll_dma.c
 * @brief DMA HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_dma.h"

// ------------------------------------------------------------- PRIVATE MACROS

// DMA Addressees.
#ifdef PIC32MXxx
#define HAL_LL_DMA_BASE_ADDRESS                (0xBF883000)
#endif
#ifdef PIC32MZxx
#define HAL_LL_DMA_BASE_ADDRESS                (0xBF811000)
#endif
#define HAL_LL_DMA_STREAM_BASE_OFFSET          (0x60)
#define HAL_LL_DMA_STREAM_STREAM_OFFSET        (0xC0)
#define HAL_LL_DMA_STREAM_BASE_ADDRESS         (HAL_LL_DMA_BASE_ADDRESS + HAL_LL_DMA_STREAM_BASE_OFFSET)

// DMACON control and status bits.
#define HAL_LL_DMA_CON_SUSPEND_POSITION        (12)
#define HAL_LL_DMA_CON_SUSPEND_MASK            (0x1UL << HAL_LL_DMA_CON_SUSPEND_POSITION)
#define HAL_LL_DMA_CON_SUSPEND                 HAL_LL_DMA_CON_SUSPEND_MASK
#define HAL_LL_DMA_CON_ON_POSITION             (15)
#define HAL_LL_DMA_CON_ON_MASK                 (0x1UL << HAL_LL_DMA_CON_ON_POSITION)
#define HAL_LL_DMA_CON_ON                      HAL_LL_DMA_CON_ON_MASK

// DCHxCON control and status bits.
#define HAL_LL_DMA_DCHCON_CHPRI_POSITION       (0)
#define HAL_LL_DMA_DCHCON_CHPRI_MASK           (0x3UL << HAL_LL_DMA_DCHCON_CHPRI_POSITION)
#define HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_0     (0)
#define HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_1     (0x1UL << HAL_LL_DMA_DCHCON_CHPRI_POSITION)
#define HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_2     (0x2UL << HAL_LL_DMA_DCHCON_CHPRI_POSITION)
#define HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_3     (0x3UL << HAL_LL_DMA_DCHCON_CHPRI_POSITION)
#define HAL_LL_DMA_DCHCON_CHEDET_POSITION      (2)
#define HAL_LL_DMA_DCHCON_CHEDET_MASK          (0x1UL << HAL_LL_DMA_DCHCON_CHEDET_POSITION)
#define HAL_LL_DMA_DCHCON_CHEDET               HAL_LL_DMA_DCHCON_CHEDET_MASK
#define HAL_LL_DMA_DCHCON_CHAEN_POSITION       (4)
#define HAL_LL_DMA_DCHCON_CHAEN_MASK           (0x1UL << HAL_LL_DMA_DCHCON_CHAEN_POSITION)
#define HAL_LL_DMA_DCHCON_CHAEN                HAL_LL_DMA_DCHCON_CHAEN_MASK
#define HAL_LL_DMA_DCHCON_CHCHN_POSITION       (5)
#define HAL_LL_DMA_DCHCON_CHCHN_MASK           (0x1UL << HAL_LL_DMA_DCHCON_CHCHN_POSITION)
#define HAL_LL_DMA_DCHCON_CHCHN                HAL_LL_DMA_DCHCON_CHCHN_MASK
#define HAL_LL_DMA_DCHCON_CHAED_POSITION       (6)
#define HAL_LL_DMA_DCHCON_CHAED_MASK           (0x1UL << HAL_LL_DMA_DCHCON_CHAED_POSITION)
#define HAL_LL_DMA_DCHCON_CHAED                HAL_LL_DMA_DCHCON_CHAED_MASK
#define HAL_LL_DMA_DCHCON_CHEN_POSITION        (7)
#define HAL_LL_DMA_DCHCON_CHEN_MASK            (0x1UL << HAL_LL_DMA_DCHCON_CHEN_POSITION)
#define HAL_LL_DMA_DCHCON_CHEN                 HAL_LL_DMA_DCHCON_CHEN_MASK
#define HAL_LL_DMA_DCHCON_CHCHNS_POSITION      (8)
#define HAL_LL_DMA_DCHCON_CHCHNS_MASK          (0x1UL << HAL_LL_DMA_DCHCON_CHCHNS_POSITION)
#define HAL_LL_DMA_DCHCON_CHCHNS               HAL_LL_DMA_DCHCON_CHCHNS_MASK
#ifdef HAL_LL_DMA_DCHCON_CHBUSY_AVAILABLE
    #define HAL_LL_DMA_DCHCON_CHBUSY_POSITION      (9)
    #define HAL_LL_DMA_DCHCON_CHBUSY_MASK          (0x1UL << HAL_LL_DMA_DCHCON_CHBUSY_POSITION)
    #define HAL_LL_DMA_DCHCON_CHBUSY               HAL_LL_DMA_DCHCON_CHBUSY_MASK
#endif

// DCHxECON control and status bits.
#define HAL_LL_DMA_DCHECON_AIRQEN_POSITION     (3)
#define HAL_LL_DMA_DCHECON_AIRQEN_MASK         (0x1UL << HAL_LL_DMA_DCHECON_AIRQEN_POSITION)
#define HAL_LL_DMA_DCHECON_AIRQEN              HAL_LL_DMA_DCHECON_AIRQEN_MASK
#define HAL_LL_DMA_DCHECON_SIRQEN_POSITION     (4)
#define HAL_LL_DMA_DCHECON_SIRQEN_MASK         (0x1UL << HAL_LL_DMA_DCHECON_SIRQEN_POSITION)
#define HAL_LL_DMA_DCHECON_SIRQEN              HAL_LL_DMA_DCHECON_SIRQEN_MASK
#define HAL_LL_DMA_DCHECON_PATEN_POSITION      (5)
#define HAL_LL_DMA_DCHECON_PATEN_MASK          (0x1UL << HAL_LL_DMA_DCHECON_PATEN_POSITION)
#define HAL_LL_DMA_DCHECON_PATEN               HAL_LL_DMA_DCHECON_PATEN_MASK
#define HAL_LL_DMA_DCHECON_CABORT_POSITION     (6)
#define HAL_LL_DMA_DCHECON_CABORT_MASK         (0x1UL << HAL_LL_DMA_DCHECON_CABORT_POSITION)
#define HAL_LL_DMA_DCHECON_CABORT              HAL_LL_DMA_DCHECON_CABORT_MASK
#define HAL_LL_DMA_DCHECON_CFORCE_POSITION     (7)
#define HAL_LL_DMA_DCHECON_CFORCE_MASK         (0x1UL << HAL_LL_DMA_DCHECON_CFORCE_POSITION)
#define HAL_LL_DMA_DCHECON_CFORCE              HAL_LL_DMA_DCHECON_CFORCE_MASK
#define HAL_LL_DMA_DCHECON_CHSIRQ_POSITION     (8)
#define HAL_LL_DMA_DCHECON_CHSIRQ_MASK         (0xFFUL << HAL_LL_DMA_DCHECON_CHSIRQ_POSITION)
#define HAL_LL_DMA_DCHECON_CHAIRQ_POSITION     (16)
#define HAL_LL_DMA_DCHECON_CHAIRQ_MASK         (0xFFUL << HAL_LL_DMA_DCHECON_CHAIRQ_POSITION)

// DCHxINT control and status bits.
#define HAL_LL_DMA_DCHINT_CHERIF_POSITION       (0)
#define HAL_LL_DMA_DCHINT_CHERIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHERIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHERIF                HAL_LL_DMA_DCHINT_CHERIF_MASK
#define HAL_LL_DMA_DCHINT_CHTAIF_POSITION       (1)
#define HAL_LL_DMA_DCHINT_CHTAIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHTAIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHTAIF                HAL_LL_DMA_DCHINT_CHTAIF_MASK
#define HAL_LL_DMA_DCHINT_CHCCIF_POSITION       (2)
#define HAL_LL_DMA_DCHINT_CHCCIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHCCIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHCCIF                HAL_LL_DMA_DCHINT_CHCCIF_MASK
#define HAL_LL_DMA_DCHINT_CHBCIF_POSITION       (3)
#define HAL_LL_DMA_DCHINT_CHBCIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHBCIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHBCIF                HAL_LL_DMA_DCHINT_CHBCIF_MASK
#define HAL_LL_DMA_DCHINT_CHDHIF_POSITION       (4)
#define HAL_LL_DMA_DCHINT_CHDHIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHDHIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHDHIF                HAL_LL_DMA_DCHINT_CHDHIF_MASK
#define HAL_LL_DMA_DCHINT_CHDDIF_POSITION       (5)
#define HAL_LL_DMA_DCHINT_CHDDIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHDDIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHDDIF                HAL_LL_DMA_DCHINT_CHDDIF_MASK
#define HAL_LL_DMA_DCHINT_CHSHIF_POSITION       (6)
#define HAL_LL_DMA_DCHINT_CHSHIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHSHIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHSHIF                HAL_LL_DMA_DCHINT_CHSHIF_MASK
#define HAL_LL_DMA_DCHINT_CHSDIF_POSITION       (7)
#define HAL_LL_DMA_DCHINT_CHSDIF_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHSDIF_POSITION)
#define HAL_LL_DMA_DCHINT_CHSDIF                HAL_LL_DMA_DCHINT_CHSDIF_MASK
#define HAL_LL_DMA_DCHINT_CHERIE_POSITION       (16)
#define HAL_LL_DMA_DCHINT_CHERIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHERIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHERIE                HAL_LL_DMA_DCHINT_CHERIE_MASK
#define HAL_LL_DMA_DCHINT_CHTAIE_POSITION       (17)
#define HAL_LL_DMA_DCHINT_CHTAIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHTAIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHTAIE                HAL_LL_DMA_DCHINT_CHTAIE_MASK
#define HAL_LL_DMA_DCHINT_CHCCIE_POSITION       (18)
#define HAL_LL_DMA_DCHINT_CHCCIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHCCIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHCCIE                HAL_LL_DMA_DCHINT_CHCCIE_MASK
#define HAL_LL_DMA_DCHINT_CHBCIE_POSITION       (19)
#define HAL_LL_DMA_DCHINT_CHBCIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHBCIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHBCIE                HAL_LL_DMA_DCHINT_CHBCIE_MASK
#define HAL_LL_DMA_DCHINT_CHDHIE_POSITION       (20)
#define HAL_LL_DMA_DCHINT_CHDHIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHDHIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHDHIE                HAL_LL_DMA_DCHINT_CHDHIE_MASK
#define HAL_LL_DMA_DCHINT_CHDDIE_POSITION       (21)
#define HAL_LL_DMA_DCHINT_CHDDIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHDDIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHDDIE                HAL_LL_DMA_DCHINT_CHDDIE_MASK
#define HAL_LL_DMA_DCHINT_CHSHIE_POSITION       (22)
#define HAL_LL_DMA_DCHINT_CHSHIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHSHIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHSHIE                HAL_LL_DMA_DCHINT_CHSHIE_MASK
#define HAL_LL_DMA_DCHINT_CHSDIE_POSITION       (23)
#define HAL_LL_DMA_DCHINT_CHSDIE_MASK           (0x1UL << HAL_LL_DMA_DCHINT_CHSDIE_POSITION)
#define HAL_LL_DMA_DCHINT_CHSDIE                HAL_LL_DMA_DCHINT_CHSDIE_MASK
#define HAL_LL_DMA_DCHINT_IE                    (HAL_LL_DMA_DCHINT_CHERIE | HAL_LL_DMA_DCHINT_CHTAIE | \
                                                 HAL_LL_DMA_DCHINT_CHCCIE | HAL_LL_DMA_DCHINT_CHBCIE | \
                                                 HAL_LL_DMA_DCHINT_CHDHIE | HAL_LL_DMA_DCHINT_CHDDIE | \
                                                 HAL_LL_DMA_DCHINT_CHSHIE | HAL_LL_DMA_DCHINT_CHSDIE)
#define HAL_LL_DMA_DCHINT_IF                    (HAL_LL_DMA_DCHINT_CHERIF | HAL_LL_DMA_DCHINT_CHTAIF | \
                                                 HAL_LL_DMA_DCHINT_CHCCIF | HAL_LL_DMA_DCHINT_CHBCIF | \
                                                 HAL_LL_DMA_DCHINT_CHDHIF | HAL_LL_DMA_DCHINT_CHDDIF | \
                                                 HAL_LL_DMA_DCHINT_CHSHIF | HAL_LL_DMA_DCHINT_CHSDIF)

/*!< @brief Macro used for checking transfer completion. */
#define HAL_LL_DMA_TRANSFER_DONE                transfer_complete_flag

/*!< @brief Macro used for checking if transfer size is valid (0-65535). */
#define HAL_LL_DMA_TRANSFER_SIZE_ILLEGAL        transfer_size >> 16

/*!< @brief DMA module enable macro. */
#define HAL_LL_DMA_MODULE_ENABLE(_x)            (_x->conset = HAL_LL_DMA_CON_ON)

/*!< @brief DMA module disable macro. */
#define HAL_LL_DMA_MODULE_DISABLE(_x)           (_x->conclr = HAL_LL_DMA_CON_ON)

/*!< @brief DMA stream enable macro. */
#define HAL_LL_DMA_STREAM_ENABLE(_x)            (_x->conset = HAL_LL_DMA_DCHCON_CHEN)

/*!< @brief DMA stream disable macro. */
#define HAL_LL_DMA_STREAM_DISABLE(_x)           (_x->conclr = HAL_LL_DMA_DCHCON_CHEN)

/*!< @brief DMA stream disable macro. */
#define HAL_LL_DMA_STREAM_ABORT(_x)             (_x->econset = HAL_LL_DMA_DCHECON_CABORT)

/*!< @brief Convert virtual memory address into physical one. */
#define VIRTUAL_TO_PHYSICAL(_x)                (((uint32_t)(_x)) & 0x1FFFFFFF)

// ----------------------------------------------------------- PRIVATE TYPEDEFS

/*!< @brief DMA controller HW register structure. */
typedef struct dma_handle
{
    volatile uint32_t con;             /*!< DMA controller control register. */
    volatile uint32_t conclr;          /*!< DMA controller control clear register. */
    volatile uint32_t conset;          /*!< DMA controller control set register. */
    volatile uint32_t coninv;          /*!< DMA controller control toggle register. */
    volatile uint32_t stat;            /*!< DMA status register. */
    uint32_t __unused1[3];
    volatile uint32_t addr;            /*!< DMA address register. */
} dma_handle_t;

/*!< @brief DMA stream HW register structure. */
typedef struct hal_ll_dma_stream_handle
{
    volatile uint32_t con;             /*!< DMA stream control register. */
    volatile uint32_t conclr;          /*!< DMA stream control clear register. */
    volatile uint32_t conset;          /*!< DMA stream control set register. */
    volatile uint32_t coninv;          /*!< DMA stream control toggle register. */
    volatile uint32_t econ;            /*!< DMA stream event control register. */
    volatile uint32_t econclr;         /*!< DMA stream event control clear register. */
    volatile uint32_t econset;         /*!< DMA stream event control set register. */
    volatile uint32_t econinv;         /*!< DMA stream event control toggle register. */
    volatile uint32_t intcr;           /*!< DMA stream interrupt control register. */
    volatile uint32_t intcrclr;        /*!< DMA stream interrupt control clear register. */
    volatile uint32_t intcrset;        /*!< DMA stream interrupt control set register. */
    volatile uint32_t intcrinv;        /*!< DMA stream interrupt control toggle register. */
    volatile uint32_t ssa;             /*!< DMA stream source start address register. */
    volatile uint32_t ssaclr;          /*!< DMA stream source start address clear register. */
    volatile uint32_t ssaset;          /*!< DMA stream source start address set register. */
    volatile uint32_t ssainv;          /*!< DMA stream source start address toggle register. */
    volatile uint32_t dsa;             /*!< DMA stream destination start address register. */
    volatile uint32_t dsaclr;          /*!< DMA stream destination start address clear register. */
    volatile uint32_t dsaset;          /*!< DMA stream destination start address set register. */
    volatile uint32_t dsainv;          /*!< DMA stream destination start address toggle register. */
    volatile uint32_t ssiz;            /*!< DMA stream source size register. */
    volatile uint32_t ssizclr;         /*!< DMA stream source size clear register. */
    volatile uint32_t ssizset;         /*!< DMA stream source size set register. */
    volatile uint32_t ssizinv;         /*!< DMA stream source size toggle register. */
    volatile uint32_t dsiz;            /*!< DMA stream destination size register. */
    volatile uint32_t dsizclr;         /*!< DMA stream destination size clear register. */
    volatile uint32_t dsizset;         /*!< DMA stream destination size set register. */
    volatile uint32_t dsizinv;         /*!< DMA stream destination size toggle register. */
    volatile uint32_t sptr;            /*!< DMA stream source pointer register. */
    uint32_t __unused1[3];
    volatile uint32_t dptr;            /*!< DMA stream destination pointer register. */
    uint32_t __unused2[3];
    volatile uint32_t csiz;            /*!< DMA stream cell size register. */
    // volatile uint32_t csizclr;         /*!< DMA stream cell size clear register. */
    // volatile uint32_t csizset;         /*!< DMA stream cell size set register. */
    // volatile uint32_t csizinv;         /*!< DMA stream cell size toggle register. */
    // volatile uint32_t cptr;            /*!< DMA stream cell pointer register. */
    // uint32_t __unused3[3];
    // volatile uint32_t dat;             /*!< DMA stream pattern data register. */
    // volatile uint32_t datclr;          /*!< DMA stream pattern data clear register. */
    // volatile uint32_t datset;          /*!< DMA stream pattern data set register. */
    // volatile uint32_t datinv;          /*!< DMA stream pattern data toggle register. */
} hal_ll_dma_stream_handle_t;

// ------------------------------------------------------------------ VARIABLES

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Gets current stream address.
 * @details Returns stream address based on desired @ref stream value.
 * @param[in] stream DMA stream number.
 * @return hal_ll_base_addr_t Stream base register address.
 */
static inline hal_ll_base_addr_t hal_ll_dma_get_stream_address( uint8_t stream );

/**
 * @brief Initializes DMA module.
 * @details Initializes DMA module, stream and channel to
 *          values from @ref config structure.
 * @param[in] dma_obj DMA object.
 * @param[in] dma DMA HW handle.
 * @param[in] config DMA configuration structure.
 * @return hal_ll_err_t Returns initialization state, either success or failure.
 */
static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *dma_obj, hal_ll_dma_stream_handle_t *dma_stream, hal_ll_dma_config_t config );

/**
 * @brief Gets DMA channel.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref channel.
 * @param[in] channel DMA channel number.
 * @return uint32_t Returns actual HW register value based on @ref channel.
 */
static inline uint32_t hal_ll_dma_get_reg_value_channel( uint8_t channel );

/**
 * @brief Gets DMA priority value.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref priority.
 * @param[in] priority DMA priority for object stream.
 *                     Refer to @ref hal_ll_dma_priority_t for possible values.
 * @return uint32_t Returns actual HW register value based on @ref priority.
 */
static inline uint32_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority );

/**
 * @brief Disables all DMA stream interrupts and clears their flags.
 * @details Disables all DMA stream interrupts and clears their flags.
 * @param[in] dma_stream DMA stream number.
 */
static inline void hal_ll_dma_clear_interrupt_flags( hal_ll_dma_stream_handle_t * dma_stream );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;

    // Initialize the current stream.
    obj->handle = hal_ll_dma_get_stream_address( obj->stream );
    status = hal_ll_dma_init_hw( obj,
                                (hal_ll_dma_stream_handle_t *)obj->handle,
                                 obj->config );

    if ( HAL_LL_DMA_SUCCESS != status ) {
        obj->handle = 0;  // If initialization failed, reset handle.
    }

    return status;
}

hal_ll_err_t hal_ll_dma_deinit( hal_ll_dma_t *obj ) {
    uint8_t index = 0;
    hal_ll_dma_stream_handle_t * dma_stream;

    // Check if the DMA stream is enabled
    while (index < DMA_NUM_OF_STREAMS) {
        dma_stream = ( hal_ll_dma_stream_handle_t * )hal_ll_dma_get_stream_address( index );
        if ( HAL_LL_DMA_DCHCON_CHEN & dma_stream->con ) {
            // If an enabled stream was found, exit.
            return HAL_LL_DMA_SUCCESS;
        }
        ++index;
    }

    // If no stream is enabled, disable the DMA module.
    HAL_LL_DMA_MODULE_DISABLE( ( ( dma_handle_t * )HAL_LL_DMA_BASE_ADDRESS ) );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new mode.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.mode = mode;

    // Try to set new mode.
    status = hal_ll_dma_init_hw( obj,
                                ( hal_ll_dma_stream_handle_t * )obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_direction( hal_ll_dma_t *obj, hal_ll_dma_direction_t direction ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new direction.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.direction = direction;

    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                ( hal_ll_dma_stream_handle_t * )obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_priority( hal_ll_dma_t *obj, hal_ll_dma_priority_t priority ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new priority.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.priority = priority;

    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                ( hal_ll_dma_stream_handle_t * )obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type ) {
    hal_ll_dma_stream_handle_t *dma_stream = ( hal_ll_dma_stream_handle_t * )obj->handle;
    hal_ll_dma_config_t cfg = obj->config;

    // Ignore src_mem_type. Only relevant on PIC18
    ( void )src_mem_type;

    // Check if the transfer size is valid.
    if ( HAL_LL_DMA_TRANSFER_SIZE_ILLEGAL ) {
        // Transfer size cannot be greater than 65535.
        return HAL_LL_DMA_ERROR;
    }

    HAL_LL_DMA_STREAM_DISABLE( dma_stream );

    // Configure DMA source address.
    dma_stream->ssa = VIRTUAL_TO_PHYSICAL( addr_src );
    // Configure DMA destination address.
    dma_stream->dsa = VIRTUAL_TO_PHYSICAL( addr_dst );

    // Configure source and destination sizes, depending on direction.
    switch ( cfg.direction ) {
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY:
            dma_stream->ssiz = cfg.transfer_length;
            dma_stream->dsiz = cfg.transfer_length;
            dma_stream->csiz = cfg.transfer_length;
            break;
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH:
            dma_stream->ssiz = cfg.transfer_length;
            dma_stream->dsiz = 1;
            dma_stream->csiz = 1;
            break;
        case HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY:
            dma_stream->ssiz = 1;
            dma_stream->dsiz = cfg.transfer_length;
            dma_stream->csiz = 1;
            break;
        case HAL_LL_DMA_DIRECTION_PERIPH_TO_PERIPH:
            dma_stream->ssiz = 1;
            dma_stream->dsiz = 1;
            dma_stream->csiz = 1;
            break;

        default:
           return HAL_LL_DMA_ERROR;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj ) {
    hal_ll_dma_stream_handle_t *dma_stream = ( hal_ll_dma_stream_handle_t * )obj->handle;
    uint8_t tmp = 0;

    // Enable the module is enough for transfer to start if triggered by hardware.
    HAL_LL_DMA_STREAM_ENABLE( dma_stream );

    // If using memory to memory direction, transfer needs to be forced.
    if ( HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY == obj->config.direction ) {
        dma_stream->econset = HAL_LL_DMA_DCHECON_CFORCE;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj ) {
    hal_ll_dma_stream_handle_t * dma_stream = ( hal_ll_dma_stream_handle_t * )obj->handle;
    uint32_t transfer_complete_flag = ( HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY == obj->config.direction ? \
                                        HAL_LL_DMA_DCHINT_CHDDIF : HAL_LL_DMA_DCHINT_CHSDIF );

    // No point in stopping circular mode transfer.
    if ( HAL_LL_DMA_MODE_CIRCULAR == obj->config.mode ) {
        return HAL_LL_DMA_ERROR;
    }

    // Wait until the transfer has been completed.
    while ( HAL_LL_DMA_TRANSFER_DONE != ( dma_stream->intcr & transfer_complete_flag ) );
    // The stream is automatically disabled by hardware by clearing CHEN bit (DCHxCON<7>) when the transfer completes.

    // TODO consider removing anything below as it is redundant.
    /* Note: Individual channels may be suspended using the CHEN bit (DCHxCON<7>). If a DMA transfer
     *       is in progress and the CHEN bit is cleared, the current transaction will be completed and further
     *       transactions on the channel will be suspended.
     */
    // TODO This is redundant, as when the transfer is finished, CHEN bit is cleared by hardware. It would be useful for pausing instead.
    HAL_LL_DMA_STREAM_DISABLE( dma_stream );

    /* Note: Depending on the device, when the channel is suspended by clearing the CHEN bit, the user
     *       application should poll the CHBUSY bit (DCHxCON<15>) to determine when the channel is
     *       completely suspended following completion of the current transaction
     */
    #ifdef HAL_LL_DMA_DCHCON_CHBUSY_AVAILABLE
    // TODO This is redundant, as when the transfer is finished, CHEN bit is cleared by hardware. It would be useful for pausing instead.
    while ( HAL_LL_DMA_DCHCON_CHBUSY & dma_stream->con );
    #endif

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj ) {
    hal_ll_dma_stream_handle_t * dma_stream = ( hal_ll_dma_stream_handle_t * )obj->handle;
    /* Note: The channel logic will be reset on any device Reset. The channel is also reset when the channel
     *       bit, CABORT (DCHxECON<6>), is set. This will turn off the channel bit, CHEN = 0, clear the
     *       Source and Destination Pointers, and reset the event detector. When the CABORT bit is set, the
     *       current transaction in progress
     */
    HAL_LL_DMA_STREAM_ABORT( dma_stream );

    // Clear all of the stream interrupt flags.
    hal_ll_dma_clear_interrupt_flags( dma_stream );

    return HAL_LL_DMA_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static inline uint32_t hal_ll_dma_get_stream_address( uint8_t stream ) {
    return ((hal_ll_base_addr_t)HAL_LL_DMA_STREAM_BASE_ADDRESS + (hal_ll_base_addr_t)(HAL_LL_DMA_STREAM_STREAM_OFFSET * stream));
}

static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *obj, hal_ll_dma_stream_handle_t *dma_stream, hal_ll_dma_config_t config ) {
    dma_handle_t * dma = ( dma_handle_t * )HAL_LL_DMA_BASE_ADDRESS;
    volatile uint32_t con_tmp = 0UL;
    volatile uint32_t econ_tmp = 0UL;

    /* Note: Every time we open some DMA, it should be confirmed that DMA module is on because this function
     *       will mostly focus on configuring DMA channel and not the module itself. and for the channel to function,
     *       module needs to be enabled.
     *       The DMA module should only be disabled if all of its channels are disabled.
     */
    /* Note: For clarification, in our driver, the functionality performed by PIC32 channel is called stream,
     *       and events that can trigger transmissions are called channels.
     */

    // Enable DMA module.
    HAL_LL_DMA_MODULE_ENABLE( dma );

    // Disable the DMA stream.
    HAL_LL_DMA_STREAM_DISABLE( dma_stream );

    // BEGIN Prepare the DMA Stream configuration.
    // Clear CHPRI, CHAEN, CHCHN, CHAED, and CHCHNS bits.
    dma_stream->conclr = ( HAL_LL_DMA_DCHCON_CHPRI_MASK | HAL_LL_DMA_DCHCON_CHAEN_MASK | \
                           HAL_LL_DMA_DCHCON_CHCHN_MASK | HAL_LL_DMA_DCHCON_CHAED_MASK | \
                           HAL_LL_DMA_DCHCON_CHCHNS_MASK );
    // Get the DCHxCON register value.
    con_tmp = dma_stream->con;
    // Clear AIRQEN, SIRQEN, PATEN, and CHSIRQ bits.
    dma_stream->econclr = ( HAL_LL_DMA_DCHECON_AIRQEN_MASK | HAL_LL_DMA_DCHECON_SIRQEN_MASK | \
                            HAL_LL_DMA_DCHECON_PATEN_MASK  | HAL_LL_DMA_DCHECON_CHSIRQ_MASK );
    // Get the DCHxECON register value.
    econ_tmp = dma_stream->econ;

    // Select the desired stream channel.
    econ_tmp |= hal_ll_dma_get_reg_value_channel( config.channel );

    // Set desired direction value.
    /* Note: PIC32 does not differentiate between memory and peripherals.
     *       Direction mode is still used to configure the rest of the stream properly.
     *       If the direction is anything but M2M and the mode is NORMAL, SIRQEN bit needs to be set.
     *       Additionally if mode CIRCULAR, then even in M2M direction SIRQEN needs to be set.
     */

    // There is only autoincrement mode. If end of the buffer is reached, pointers are reloaded.
    if ( ( false == config.src_inc ) || ( false == config.dst_inc ) ) {
        return HAL_LL_DMA_ERROR;
    }

    // Note: Data Alignment and Burst Transfer settings are not relevant on PIC32.

    // Set desired mode.
    /* Note: PIC32 does not differentiate between memory and peripherals.
     *       config.direction is still used to configure the rest of the stream properly.
     *       If the direction is anything but M2M and the mode is NORMAL, SIRQEN bit needs to be set.
     *       Additionally if mode CIRCULAR, then even in M2M direction SIRQEN needs to be set.
     */
     /* Note: PIC32 does not have circular mode, but config.mode is still used to
      *       configure the stream to functionally behave like it is in CIRCULAR mode.
      *       To achieve it SIRQEN and CHAEN bits need to be set as well as the CHSIRQ bitfield
      */
    if ( HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY != config.direction ) {
        econ_tmp |= HAL_LL_DMA_DCHECON_SIRQEN;
    }
    if ( HAL_LL_DMA_MODE_CIRCULAR == obj->config.mode ) {
        con_tmp |= HAL_LL_DMA_DCHCON_CHAEN;
        econ_tmp |= HAL_LL_DMA_DCHECON_SIRQEN;
    }

    // Finally set the desired priority.
    con_tmp |= hal_ll_dma_get_reg_value_priority(config.priority);

    // And then write to DMA Stream CON and ECON register.
    dma_stream->conset = con_tmp;
    dma_stream->econset = econ_tmp;
    // END Prepare the DMA Stream configuration.

    return HAL_LL_DMA_SUCCESS;
}

static inline uint32_t hal_ll_dma_get_reg_value_channel( uint8_t channel ) {
    return ( uint32_t )( channel << ( uint8_t )HAL_LL_DMA_DCHECON_CHSIRQ_POSITION );
}

static inline uint32_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority ) {
    uint32_t priority_set = HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_0;

    switch (priority)
    {
        case HAL_LL_DMA_PRIORITY_LOW:
            priority_set = HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_0;
            break;
        case HAL_LL_DMA_PRIORITY_MEDIUM:
            priority_set = HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_1;
            break;
        case HAL_LL_DMA_PRIORITY_HIGH:
            priority_set = HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_2;
            break;
        case HAL_LL_DMA_PRIORITY_VERY_HIGH:
            priority_set = HAL_LL_DMA_DCHCON_CHPRI_PRIORITY_3;
            break;

        default:
            break;
    }

    return (uint32_t)priority_set;
}

static inline void hal_ll_dma_clear_interrupt_flags( hal_ll_dma_stream_handle_t * dma_stream ) {
    dma_stream->intcrclr = ( uint32_t )( HAL_LL_DMA_DCHINT_IF );
}

// ------------------------------------------------------------------------- END
