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
 * @file  hal_ll_dma.c
 * @brief DMA HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_rcc.h"
#include "hal_ll_dma.h"
#include "hal_ll_gpio.h"

// ------------------------------------------------------------- PRIVATE MACROS

// /*!< @brief DMA SCR register masks. */
#define HAL_LL_DMAMUX_ENABLE_MASK (0x80U)
#define HAL_LL_DMA_ERQ_CLEAR_MASK (0x0000U)
#define HAL_LL_DMAMUX_CLEAR_MASK (0x00U)
#define HAL_LL_DMA_TCD_SOFF_NO_INCREMENT (0x0000U)
#define HAL_LL_DMA_TCD_SOFF_BYTE (0x0001U)
#define HAL_LL_DMA_TCD_SOFF_HALF_WORD (0x0002U)
#define HAL_LL_DMA_TCD_SOFF_WORD (0x0004U)
#define HAL_LL_DMA_TCD_DOFF_NO_INCREMENT (0x0000U)
#define HAL_LL_DMA_TCD_DOFF_BYTE (0x0001U)
#define HAL_LL_DMA_TCD_DOFF_HALF_WORD (0x0002U)
#define HAL_LL_DMA_TCD_DOFF_WORD (0x0004U)
#define HAL_LL_DMA_TCD_ATTR_SSIZE_BYTE (0x0000U)
#define HAL_LL_DMA_TCD_ATTR_SSIZE_HALF_WORD (0x0100U)
#define HAL_LL_DMA_TCD_ATTR_SSIZE_WORD (0x0200U)
#define HAL_LL_DMA_TCD_ATTR_DSIZE_BYTE (0x0000U)
#define HAL_LL_DMA_TCD_ATTR_DSIZE_HALF_WORD (0x0001U)
#define HAL_LL_DMA_TCD_ATTR_DSIZE_WORD (0x0002U)
#define HAL_LL_DMA_TCD_CSR_START_BIT (0)
#define HAL_LL_DMA_TCD_CSR_DREQ_BIT (3)
#define HAL_LL_DMA_TCD_CLEAR_MASK_BYTE (0x00)
#define HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD (0x0000)
#define HAL_LL_DMA_TCD_CLEAR_MASK_WORD (0x00000000)

#define HAL_LL_DMA_BASE (0x40008000UL)
#define HAL_LL_DMA_CR_BASE ((uint32_t)HAL_LL_DMA_BASE)
#define HAL_LL_DMA_CHPRIO_BASE ((uint32_t)HAL_LL_DMA_BASE + 0x100UL)
#define HAL_LL_DMA_TCD_BASE ((uint32_t)HAL_LL_DMA_BASE + (uint32_t)0x1000UL)
#define HAL_LL_DMAMUX_BASE (0x40021000UL)
#define HAL_LL_SCR_BASE_OFFSET (0x10U)
#define HAL_LL_STREAM_BASE_OFFSET (0x18U)
/*!< @brief Clock bases and bit locations and stream bases. */
#define HAL_LL_DMA_TCD_BASE_OFFSET 0x1000
#define HAL_LL_DMA_TCD_REG_MULTIPLIER 32
#define HAL_LL_DMA_CLOCK_BIT (1)
#define HAL_LL_DMA_CLOCK_BASE ((uint32_t)_SIM_SCGC7)
#define HAL_LL_DMAMUX_CLOCK_BIT (1)
#define HAL_LL_DMAMUX_CLOCK_BASE ((uint32_t)_SIM_SCGC6)
#define HAL_LL_SYSCLK_BASE _RCC_APB2ENR
#define HAL_LL_SYSCLK_BIT 14

/*!< @brief DMA module enable macro. */
#define HAL_LL_DMA_MODULE_ENABLE(_x,_y) (_x->erq |= 1U << _y->stream)

/*!< @brief DMA module disable macro. */
#define HAL_LL_DMA_MODULE_DISABLE(_x,_y) (_x->erq &= ~(1U << _y->stream))

/*!< @brief Default timeout value to wait when checking if module is disabled/enabled. */
#define DEFAULT_TIMEOUT_VALUE (0xFFFFU)

// ----------------------------------------------------------- PRIVATE TYPEDEFS
/*!< @brief DMA TCD HW register structure. */
typedef struct
{
    uint32_t saddr;     /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    uint16_t soff;      /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    uint16_t attr;      /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    uint32_t nbytes;    /**< TCD Minor Byte Count (Minor Loop Disabled), array offset: 0x1008, array step: 0x20 */
    int      slast;     /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    uint32_t daddr;     /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    uint16_t doff;      /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    uint16_t citer;     /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
    int      dlast_sga; /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    uint16_t csr;       /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    uint16_t biter;     /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
} dma_tcd_t;

/*!< @brief DMA HW register structure. */
typedef struct
{
    uint8_t dchpri;  /**< Channel n Priority Register, offset: 0x100 */
} dma_chpro_t;

/*!< @brief DMAMUX HW register structure. */
typedef struct
{
    uint8_t chcfg;
} dmamux_t;

/*!< @brief DMA HW register structure. */
typedef struct dma_handle
{
    uint32_t cr;           /**< Control Register, offset: 0x0 */
    uint32_t es;           /**< Error Status Register, offset: 0x4 */
    uint8_t reserved_0[4];
    uint32_t erq;          /**< Enable Request Register, offset: 0xC */
    uint8_t reserved_1[4];
    uint32_t eei;          /**< Enable Error Interrupt Register, offset: 0x14 */
    uint8_t ceei;          /**< Clear Enable Error Interrupt Register, offset: 0x18 */
    uint8_t seei;          /**< Set Enable Error Interrupt Register, offset: 0x19 */
    uint8_t cerq;          /**< Clear Enable Request Register, offset: 0x1A */
    uint8_t serq;          /**< Set Enable Request Register, offset: 0x1B */
    uint8_t cdne;          /**< Clear DONE Status Bit Register, offset: 0x1C */
    uint8_t ssrt;          /**< Set START Bit Register, offset: 0x1D */
    uint8_t cerr;          /**< Clear Error Register, offset: 0x1E */
    uint8_t cint;          /**< Clear Interrupt Request Register, offset: 0x1F */
    uint8_t reserved_2[4];
    uint32_t dint;          /**< Interrupt Request Register, offset: 0x24 */
    uint8_t reserved[4];
    uint32_t err;          /**< Error Register, offset: 0x2C */
    uint8_t reserved_4[4];
    uint32_t hrs;          /**< Hardware Request Status Register, offset: 0x34 */
} dma_handle_t;

/*!< @brief DMA HW ISR register structure. */
typedef struct dma_isr_registers
{
    volatile uint32_t isr;       /*!< DMA interrupt status register */
    volatile uint32_t reserved0;
    volatile uint32_t ifcr;      /*!< DMA interrupt flag clear register */
} dma_isr_registers_t;

/*!< @brief DMA HW clock settings structure. */
typedef struct
{
    uint8_t clock_bit;
    hal_ll_base_addr_t clock_base;
} dma_clock_t;

/*!< @brief DMAMUX HW clock settings structure. */
typedef struct
{
    uint8_t mux_bit;
    hal_ll_base_addr_t mux_base;
} dma_mux_t;

/*!< @brief DMA control settings structure. */
typedef struct
{
    dma_clock_t clock;
    hal_ll_base_addr_t stream_base;
} dma_control_struct_t;

/*!< @brief DMAMUX control settings structure. */
typedef struct
{
    dma_mux_t dmamux;
    hal_ll_base_addr_t dmamux_base;
} dmamux_control_struct_t;

// ------------------------------------------------------------------ VARIABLES

static const dma_control_struct_t dma_controller[ DMA_NUM_OF_MODULES ] =
{
    {
        // DMA1 Streams 1-16
        { HAL_LL_DMA_CLOCK_BIT, HAL_LL_DMA_CLOCK_BASE }, HAL_LL_DMA_BASE
    }

};

static const dmamux_control_struct_t dmamux_controller[ DMA_NUM_OF_MODULES ] =
{
    {
        // DMA1 Streams 1-16
        { HAL_LL_DMAMUX_CLOCK_BIT, HAL_LL_DMAMUX_CLOCK_BASE }, HAL_LL_DMAMUX_BASE
    }

};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Gets current stream address.
 * @details Returns stream address based on @ref module value and
 *          desired @ref stream value.
 * @param[in] module DMA module number.
 * @param[in] stream DMA stream number.
 * @return hal_ll_base_addr_t Stream base register address.
 */
static hal_ll_base_addr_t hal_ll_dma_get_stream_address( uint8_t module, uint8_t stream );

/**
 * @brief Sets current module clock.
 * @details If @ref state is @b true, enables DMA module clock.
 *          If @ref state is @b false, disables DMA module clock.
 * @param[in] dma_obj DMA object.
 * @param[in] state Desired state.
 *              - @b true
 *              - @b false
 * @return Nothing.
 */
static void hal_ll_dma_clock_set( hal_ll_dma_t *dma_obj, bool state );

/**
 * @brief Sets current module clock.
 * @details If @ref state is @b true, enables DMA module clock.
 *          If @ref state is @b false, disables DMA module clock.
 * @param[in] dma_obj DMA object.
 * @param[in] state Desired state.
 *              - @b true
 *              - @b false
 * @return Nothing.
 */
static void hal_ll_dmamux_clock_set( hal_ll_dma_t *dma_obj, bool state );

/**
 * @brief Initializes DMA module.
 * @details Initializes DMA module, stream and channel to
 *          values from @ref config structure.
 * @param[in] dma_obj DMA object.
 * @param[in] dma DMA HW handle.
 * @param[in] config DMA configuration structure.
 * @return hal_ll_err_t Returns initialization state, either success or fail.
 */
static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *dma_obj, dma_handle_t *dma, hal_ll_dma_config_t config );

/**
 * @brief Gets DMA peripheral address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream peripheral address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc, hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA memory address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream memory address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_src_inc( bool set_inc, hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA memory address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA stream memory address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static uint16_t hal_ll_dma_get_reg_value_source_size( hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA peripheral address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA stream peripheral address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static uint16_t hal_ll_dma_get_reg_value_destination_size( hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA priority value.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref priority.
 * @param[in] priority DMA priority for object stream.
 *                     Refer to @ref hal_ll_dma_priority_t for possible values.
 * @return uint32_t Returns actual HW register value based on @ref priority.
 */
static inline uint8_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;

    // Enable current stream clock.
    hal_ll_dmamux_clock_set( obj, true );
    // Enable current stream clock.
    hal_ll_dma_clock_set( obj, true );

    // Initialize current stream.
    obj->handle = hal_ll_dma_get_stream_address( obj->module, obj->stream );
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 obj->config );

    if ( HAL_LL_DMA_SUCCESS != status ) {
        obj->handle = 0;  // If initialization failed, reset handle.
    }

    return status;
}

hal_ll_err_t hal_ll_dma_deinit( hal_ll_dma_t *obj ) {
    // First abort current transfer.
    if ( HAL_LL_DMA_SUCCESS != hal_ll_dma_transfer_abort( obj ) )
        return HAL_LL_DMA_ERROR;
    // Finally, disable module clock.
    hal_ll_dma_clock_set( obj, false );
    // Enable current stream clock.
    hal_ll_dmamux_clock_set( obj, false );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new mode.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.mode = mode;
    // Disable module first.
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle), obj );
    // Try to set new mode.
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_direction( hal_ll_dma_t *obj, hal_ll_dma_direction_t direction ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new direction.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.direction = direction;
    // Disable module first.
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle),obj );
    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_priority( hal_ll_dma_t *obj, hal_ll_dma_priority_t priority ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new priority.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.priority = priority;
    // Disable module first.
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle), obj );
    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    dmamux_t * mux = (dmamux_t*)dmamux_controller[obj->module].dmamux_base + obj->stream;
    dma_tcd_t * tcd = (dma_tcd_t*)(obj->handle + ( HAL_LL_DMA_TCD_BASE_OFFSET + ( HAL_LL_DMA_TCD_REG_MULTIPLIER * obj->stream )));

    // Disable the peripheral first.
    HAL_LL_DMA_MODULE_DISABLE(dma, obj);

    // Minor loop byte count: how many bytes to transfer in each service request.
    tcd->nbytes = obj->config.data_align_destination + 1;

    // Number of major loops.
    tcd->biter = transfer_size / ( obj->config.data_align_destination + 1 );
    // Number of major loops.
    tcd->citer = transfer_size / ( obj->config.data_align_destination + 1 );

    // Set reset value for source and destination addresses.
    if (obj->config.mode == HAL_LL_DMA_MODE_CIRCULAR){
        tcd->slast = -transfer_size;
    } else {
        tcd->slast = 0;
    }

    tcd->dlast_sga = 0;

    // Set source and destination addresses.
    tcd->saddr = addr_src;
    tcd->daddr = addr_dst;

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj ) {
    dma_tcd_t * tcd = (dma_tcd_t*)( obj->handle + ( HAL_LL_DMA_TCD_BASE_OFFSET + ( HAL_LL_DMA_TCD_REG_MULTIPLIER * obj->stream )));

    // Start dma transfer
    HAL_LL_DMA_MODULE_ENABLE( ((dma_handle_t *)obj->handle), obj );
    // If normal mode, disable request once major loop is completed
    if ( HAL_LL_DMA_MODE_NORMAL == obj->config.mode ) {
        tcd->csr = 0x1 << HAL_LL_DMA_TCD_CSR_DREQ_BIT;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj ) {
    dma_tcd_t * tcd = (dma_tcd_t*)( obj->handle + ( HAL_LL_DMA_TCD_BASE_OFFSET + ( HAL_LL_DMA_TCD_REG_MULTIPLIER * obj->stream )));

    // Stop request, once major loop count reaches 0 transfer is stoped.
    tcd->csr = 0x1 << HAL_LL_DMA_TCD_CSR_DREQ_BIT;

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;

    // Disable the stream.
    HAL_LL_DMA_MODULE_DISABLE( dma, obj );

    return HAL_LL_DMA_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_base_addr_t hal_ll_dma_get_stream_address( uint8_t module, uint8_t stream ) {
    return ((hal_ll_base_addr_t)dma_controller[module].stream_base);
}

static void hal_ll_dma_clock_set( hal_ll_dma_t *obj, bool state ) {
    if ( state ) {
        set_reg_bit( (uint32_t *)dma_controller[obj->module].clock.clock_base,
                     dma_controller[obj->module].clock.clock_bit );
    } else {
        clear_reg_bit( (uint32_t *)dma_controller[obj->module].clock.clock_base,
                       dma_controller[obj->module].clock.clock_bit );
    }
}

static void hal_ll_dmamux_clock_set( hal_ll_dma_t *obj, bool state ) {
    if ( state ) {
        set_reg_bit( (uint32_t *)dmamux_controller[obj->module].dmamux.mux_base,
                     dmamux_controller[obj->module].dmamux.mux_bit );
    } else {
        clear_reg_bit( (uint32_t *)dmamux_controller[obj->module].dmamux.mux_base,
                     dmamux_controller[obj->module].dmamux.mux_bit );
    }
}

static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *obj, dma_handle_t *dma, hal_ll_dma_config_t config ) {
    volatile uint32_t tmp = 0UL;

    // Check if user entered invalid data aka HAL_LL_DMA_DATA_ALIGN_BYTES_3
    if ( HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_source || HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_destination ) {
        return HAL_LL_DMA_ERROR;
    }

    dmamux_t * mux = (dmamux_t*)dmamux_controller[obj->module].dmamux_base + obj->stream;
    dma_tcd_t * tcd = (dma_tcd_t *)( obj->handle + ( HAL_LL_DMA_TCD_BASE_OFFSET + ( HAL_LL_DMA_TCD_REG_MULTIPLIER * obj->stream )));
    // TODO: chprio for now doesn't do anything. Left for future release.
    // Issue: All streams need to have unique priority set.
    // dma_chpro_t * chprio = (dma_chpro_t*)(obj->handle +(0x100 + ( obj->stream + 1)));

    // Disable the peripheral first.
    HAL_LL_DMA_MODULE_DISABLE(dma, obj);

    mux->chcfg = HAL_LL_DMAMUX_CLEAR_MASK;

    // Map DMA channel(source) to stream.
    mux->chcfg = HAL_LL_DMAMUX_ENABLE_MASK | obj->channel;

    // Clear TCD registers
    tcd->csr = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;
    tcd->saddr = HAL_LL_DMA_TCD_CLEAR_MASK_WORD;
    tcd->daddr = HAL_LL_DMA_TCD_CLEAR_MASK_WORD;
    tcd->soff = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;
    tcd->doff = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;
    tcd->nbytes = HAL_LL_DMA_TCD_CLEAR_MASK_WORD;
    tcd->attr = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;
    tcd->citer = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;
    tcd->biter = HAL_LL_DMA_TCD_CLEAR_MASK_HALF_WORD;

    // TODO: this checks if channel can do m2m transfer
    if(!config.direction && config.channel<58)
        return HAL_LL_DMA_ERROR;

    // Set increment offset for source and destination adresses.
    tcd->soff |= hal_ll_dma_get_reg_value_src_inc(config.src_inc, config.data_align_source);
    tcd->doff |= hal_ll_dma_get_reg_value_dst_inc(config.dst_inc, config.data_align_destination);
    // Set source and destination size.
    tcd->attr |= hal_ll_dma_get_reg_value_source_size(config.data_align_source);
    tcd->attr |= hal_ll_dma_get_reg_value_destination_size(config.data_align_destination);

    // PRIORITY
    // TODO: For future release.
    // chprio->dchpri |= hal_ll_dma_get_reg_value_priority(config.priority);

    return HAL_LL_DMA_SUCCESS;
}

static inline uint16_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc, hal_ll_dma_data_align_t align ) {
    if(set_inc) {
        switch (align)
        {
            case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
                // Source address increment. Data is 1 byte.
                return  HAL_LL_DMA_TCD_DOFF_BYTE;
                break;
            case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
                // Source address increment. Data is halfword.
                return HAL_LL_DMA_TCD_DOFF_HALF_WORD;
                break;
            case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
                // Source address increment. Data is word.
                return HAL_LL_DMA_TCD_DOFF_WORD;
                break;

            default:
                break;
        }
    }
    return HAL_LL_DMA_TCD_DOFF_NO_INCREMENT;
}

static inline uint16_t hal_ll_dma_get_reg_value_src_inc( bool set_inc, hal_ll_dma_data_align_t align ) {
    if(set_inc) {
        switch (align)
        {
            case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
                // Source address increment. Data is 1 byte.
                return  HAL_LL_DMA_TCD_SOFF_BYTE;
                break;
            case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
                // Source address increment. Data is halfword.
                return HAL_LL_DMA_TCD_SOFF_HALF_WORD;
                break;
            case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
                // Source address increment. Data is word.
                return HAL_LL_DMA_TCD_SOFF_WORD;
                break;

            default:
                break;
            }
    }
    return HAL_LL_DMA_TCD_SOFF_NO_INCREMENT;
}

static uint16_t hal_ll_dma_get_reg_value_source_size( hal_ll_dma_data_align_t align ) {
    switch (align)
    {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Source address increment. Data is 1 byte.
            return HAL_LL_DMA_TCD_ATTR_SSIZE_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Source and destination data width specification.
            return HAL_LL_DMA_TCD_ATTR_SSIZE_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Source address increment. Data is word.
            return HAL_LL_DMA_TCD_ATTR_SSIZE_WORD;
            break;

        default:
            break;
    }
    return HAL_LL_DMA_TCD_ATTR_SSIZE_BYTE;
}

static uint16_t hal_ll_dma_get_reg_value_destination_size( hal_ll_dma_data_align_t align ) {
    switch (align)
    {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Source address increment. Data is 1 byte.
            return HAL_LL_DMA_TCD_ATTR_DSIZE_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Source address increment. Data is halfowrd.
            return HAL_LL_DMA_TCD_ATTR_DSIZE_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Source address increment. Data is word.
            return HAL_LL_DMA_TCD_ATTR_DSIZE_WORD;
            break;

        default:
            break;
    }
    return HAL_LL_DMA_DATA_ALIGN_BYTES_1;
}

//TODO For future release
static inline uint8_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority ) {
    // volatile uint8_t priority_set = (uint8_t)HAL_LL_DMA_PRIORITY_LOW;
    // switch (priority)
    // {
    //     case HAL_LL_DMA_PRIORITY_LOW:
    //         return 0;
    //         // priority_set = HAL_LL_DMA_SCR_PL_LOW_MASK;
    //         break;
    //     case HAL_LL_DMA_PRIORITY_MEDIUM:
    //         return 0xf;
    //         // priority_set = HAL_LL_DMA_SCR_PL_MEDIUM_MASK;
    //         break;
    //     case HAL_LL_DMA_PRIORITY_HIGH:
    //         return 0xa;
    //         // priority_set = HAL_LL_DMA_SCR_PL_HIGH_MASK;
    //         break;
    //     case HAL_LL_DMA_PRIORITY_VERY_HIGH:
    //         return 0xf;
    //         // priority_set = HAL_LL_DMA_SCR_PL_VERYHIGH_MASK;
    //         break;

    //     default:
    //         break;
    // }
    return 1;
}

// ------------------------------------------------------------------------- END
