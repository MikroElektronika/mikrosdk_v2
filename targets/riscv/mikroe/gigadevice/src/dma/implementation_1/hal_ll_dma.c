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

#include "hal_ll_rcu.h"
#include "hal_ll_dma.h"
#include "hal_ll_gpio.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief DMA interrupt definitions. */
#define HAL_LL_DMA_IT_FT ((uint32_t)(1U << 1))
#define HAL_LL_DMA_IT_HT ((uint32_t)(1U << 2))
#define HAL_LL_DMA_IT_ET ((uint32_t)(1U << 3))
#define HAL_LL_DMA_IT_CLEAR_MASK (0x0FUL)

/*!< @brief DMA SCR register masks. */
#define HAL_LL_DMA_CHCTL_PRIORITY_VERY_HIGH_MASK 0x3000
#define HAL_LL_DMA_CHCTL_PRIORITY_HIGH_MASK 0x2000
#define HAL_LL_DMA_CHCTL_PRIORITY_MEDIUM_MASK 0x1000
#define HAL_LL_DMA_CHCTL_PRIORITY_LOW_MASK 0x0000
#define HAL_LL_DMA_CHCTL_CMEN_MASK 0x0020
#define HAL_LL_DMA_CHCTL_PWIDTH_BYTE_MASK 0x0000
#define HAL_LL_DMA_CHCTL_PWIDTH_HALFWORD_MASK 0x0100
#define HAL_LL_DMA_CHCTL_PWIDTH_WORD_MASK 0x0200
#define HAL_LL_DMA_MWIDTH_BYTE_MASK 0x0000
#define HAL_LL_DMA_MWIDTH_HALFWORD_MASK 0x0400
#define HAL_LL_DMA_MWIDTH_WORD_MASK 0x0800
#define HAL_LL_DMA_MNAGA_MASK 0x0080
#define HAL_LL_DMA_PNAGA_MASK 0x0040
#define HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY_MASK 0x4000
#define HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH_MASK 0x0010
#define HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY_MASK 0x0000
#define HAL_LL_DMA_CHCTL_PWIDTH_MASK 0x0300
#define HAL_LL_DMA_CHCTL_MWIDTH_MASK 0x0c00
#define HAL_LL_DMA_CHCTL_PRIO_MASK 0x3000
#define HAL_LL_DMA_CHCTL_EN_BIT (0)
#define HAL_LL_DMA_CHCTL_FTFIE_BIT (1)
#define HAL_LL_DMA_CHCTL_HTFIE_BIT (2)
#define HAL_LL_DMA_CHCTL_ERRIE_BIT (3)
#define HAL_LL_DMA_CHCTL_DIR_BIT (4)
#define HAL_LL_DMA_CHCTL_CMEN_BIT (5)
#define HAL_LL_DMA_CHCTL_PNAGA_BIT (6)
#define HAL_LL_DMA_CHCTL_MNAGA_BIT (7)
#define HAL_LL_DMA_CHCTL_M2M_BIT (14)

#define DMA1_BASE ( 0x40020000UL )
#define DMA2_BASE ( 0x40020400UL )
#define CCR_BASE_OFFSET (0x08U)
#define STREAM_BASE_OFFSET (0x14U)
#define HAL_LL_DMA1_CLOCK_BIT (0)
#define HAL_LL_DMA1_CLOCK_BASE ((uint32_t)RCU_AHBEN)
#define HAL_LL_DMA1_STREAM_BASE (DMA1_BASE + CCR_BASE_OFFSET)
#define HAL_LL_DMA2_CLOCK_BIT (1)
#define HAL_LL_DMA2_CLOCK_BASE ((uint32_t)RCU_AHBEN)
#define HAL_LL_DMA2_STREAM_BASE (DMA2_BASE + CCR_BASE_OFFSET)
#define HAL_LL_SYSCLK_BASE RCU_AHBEN
#define HAL_LL_PWRCLK_BASE RCU_APB1EN
#define HAL_LL_PWRCLK_BIT 28

/*!< @brief Clock enable macros. */
#define _HAL_LL_ENABLE_CLOCK_PWR_ (*HAL_LL_PWRCLK_BASE |= 1UL << HAL_LL_PWRCLK_BIT)

/*!< @brief DMA module enable macro. */
#define HAL_LL_DMA_MODULE_ENABLE(_x) (_x->cr |= 1U << HAL_LL_DMA_CHCTL_EN_BIT)

/*!< @brief DMA module disable macro. */
#define HAL_LL_DMA_MODULE_DISABLE(_x) (_x->cr &= ~(1U << HAL_LL_DMA_CHCTL_EN_BIT))

/*!< @brief Default timeout value to wait when checking if module is disabled/enabled. */
#define DEFAULT_TIMEOUT_VALUE (0xFFFFU)

// ----------------------------------------------------------- PRIVATE TYPEDEFS

/*!< @brief DMA HW register structure. */
typedef struct dma_handle
{
    volatile uint32_t cr;     /*!< DMA stream control register. */
    volatile uint32_t cnt;    /*!< DMA stream counter register. */
    volatile uint32_t par;    /*!< DMA stream peripheral address register. */
    volatile uint32_t mar;    /*!< DMA stream memory 0 address register. */
} dma_handle_t;

/*!< @brief DMA HW ISR register structure. */
typedef struct dma_isr_registers
{
    volatile uint32_t isr;   /*!< DMA interrupt status register */
    volatile uint32_t ifcr;  /*!< DMA interrupt flag clear register */
} dma_isr_registers_t;

/*!< @brief DMA HW clock settings structure. */
typedef struct
{
    uint8_t clock_bit;
    hal_ll_base_addr_t clock_base;
} dma_clock_t;

/*!< @brief DMA control settings structure. */
typedef struct
{
    dma_clock_t clock;
    hal_ll_base_addr_t stream_base;
} dma_control_struct_t;

// ------------------------------------------------------------------ VARIABLES

static const dma_control_struct_t dma_controller[ DMA_NUM_OF_MODULES ] =
{
    {
        // DMA1 streams 1-7
        { HAL_LL_DMA1_CLOCK_BIT, HAL_LL_DMA1_CLOCK_BASE }, HAL_LL_DMA1_STREAM_BASE
    },
    {
        // DMA2 streams 1-5
        { HAL_LL_DMA2_CLOCK_BIT, HAL_LL_DMA2_CLOCK_BASE }, HAL_LL_DMA2_STREAM_BASE
    }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Gets current stream address.
 * @details Returns stream address based on @ref module value and
 *          desired @ref stream value.
 * @param[in] module DMA module number.
 * @param[in] stream DMA stream number.
 * @return hal_ll_base_addr_t stream base register address.
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
 * @brief Initializes DMA module.
 * @details Initializes DMA module, stream to
 *          values from @ref config structure.
 * @param[in] dma_obj DMA object.
 * @param[in] dma DMA HW handle.
 * @param[in] config DMA configuration structure.
 * @return hal_ll_err_t Returns initialization state, either success or fail.
 */
static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *dma_obj, dma_handle_t *dma, hal_ll_dma_config_t config );

/**
 * @brief Gets DMA module state.
 * @details Checks if current DMA module stream has been stopped.
 *          Waits for defined @ref DEFAULT_TIMEOUT_VALUE number of cycles
 *          before jumping out of loop and returning @ref HAL_LL_DMA_ERROR.
 * @param[in] dma DMA HW handle.
 * @return hal_ll_err_t Returns success or fail.
 */
static inline hal_ll_err_t hal_ll_dma_is_module_disabled( dma_handle_t *dma );

/**
 * @brief Gets DMA channel.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref channel.
 * @param[in] channel DMA channel number.
 * @return uint32_t Returns actual HW register value based on @ref channel.
 */
static inline uint32_t hal_ll_dma_get_reg_value_channel( uint8_t channel );

/**
 * @brief Gets DMA direction.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref direction.
 * @param[in] direction DMA channel direction.
 *                      Refer to @hal_ll_dma_direction_t for possible values.
 * @return uint8_t Returns actual HW register value based on @ref direction.
 */
static inline uint16_t hal_ll_dma_get_reg_value_direction( hal_ll_dma_direction_t direction );

/**
 * @brief Gets DMA peripheral address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA channel peripheral address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc );

/**
 * @brief Gets DMA memory address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA channel memory address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_src_inc( bool set_inc );

/**
 * @brief Gets DMA memory address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA channel memory address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static inline uint16_t hal_ll_dma_get_reg_value_source_size( hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA peripheral address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA channel peripheral address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static inline uint16_t hal_ll_dma_get_reg_value_destination_size( hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA mode value.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref mode.
 * @param[in] mode DMA mode for object channel.
 *                 Refer to @ref hal_ll_dma_mode_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref mode.
 */
static inline uint16_t hal_ll_dma_get_reg_value_mode( hal_ll_dma_mode_t mode );

/**
 * @brief Gets DMA priority value.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref priority.
 * @param[in] priority DMA priority for object channel.
 *                     Refer to @ref hal_ll_dma_priority_t for possible values.
 * @return uint32_t Returns actual HW register value based on @ref priority.
 */
static inline uint32_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;

    // Enable PWRCLK.
    _HAL_LL_ENABLE_CLOCK_PWR_;

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

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new mode.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.mode = mode;
    // Disable module first.
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle) );
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
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle) );
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
    HAL_LL_DMA_MODULE_DISABLE( ((dma_handle_t *)obj->handle) );
    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    uint8_t ndtr_divisor;

    // This parameter is not relevant on this architecture.
    (void)src_mem_type;

    // Configure DMA Stream data length.
    switch ( obj->config.data_align_destination ) {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            ndtr_divisor = obj->config.data_align_destination;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            ndtr_divisor = 2;
            break;

        default:
            return HAL_LL_DMA_ERROR;
    }
    dma->cnt = transfer_size >> ndtr_divisor;

    // Memory to Peripheral.
    if ( HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH == obj->config.direction ) {
        // Configure DMA stream destination address.
        dma->par = addr_dst;
        // Configure DMA stream source address.
        dma->mar = addr_src;
    } else {  // Peripheral to Memory.
        // Configure DMA stream source address.
        dma->par = addr_src;
        // Configure DMA stream destination address.
        dma->mar = addr_dst;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj ) {
    HAL_LL_DMA_MODULE_ENABLE( ((dma_handle_t *)obj->handle) );
    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    uint16_t timeout = DEFAULT_TIMEOUT_VALUE;

    if( HAL_LL_DMA_MODE_CIRCULAR == obj->config.mode )
        return HAL_LL_DMA_ERROR;

    while(dma->cnt) {
        if (0 == timeout--)
            return HAL_LL_DMA_ERROR;
    }

    HAL_LL_DMA_MODULE_DISABLE( dma );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    dma_handle_t *dma = (dma_handle_t *)obj->handle;

    // Calculate DMA base and stream number.
    dma_isr_registers_t *regs = (dma_isr_registers_t *)(dma_controller[obj->module].stream_base - CCR_BASE_OFFSET);

    // Disable all the transfer interrupts.
    dma->cr &= ~(HAL_LL_DMA_CHCTL_FTFIE_BIT | HAL_LL_DMA_CHCTL_HTFIE_BIT | HAL_LL_DMA_CHCTL_ERRIE_BIT);

    // Disable the stream.
    HAL_LL_DMA_MODULE_DISABLE( dma );

    // Wait for bit to be cleared.
    status = hal_ll_dma_is_module_disabled( dma );

    // Clear all interrupt flags at correct offset within the register.
    if ( HAL_LL_DMA_SUCCESS == status )
        regs->ifcr = HAL_LL_DMA_IT_CLEAR_MASK << ( obj->channel * 4);

    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_base_addr_t hal_ll_dma_get_stream_address( uint8_t module, uint8_t stream ) {
    return ((hal_ll_base_addr_t)dma_controller[module].stream_base + (hal_ll_base_addr_t)(STREAM_BASE_OFFSET * (stream)));
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

static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *obj, dma_handle_t *dma, hal_ll_dma_config_t config ) {
    volatile uint32_t tmp = 0UL;
    // Check if user entered invalid data aka HAL_LL_DMA_DATA_ALIGN_BYTES_3
    if ( HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_source || HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_destination ) {
        return HAL_LL_DMA_ERROR;
    }

    // Disable the peripheral first.
    HAL_LL_DMA_MODULE_DISABLE(dma);

    // Wait for bit to be cleared.
    if ( HAL_LL_DMA_ERROR == hal_ll_dma_is_module_disabled( dma ) )
        return HAL_LL_DMA_ERROR;

    // Get the CR register value.
    tmp = dma->cr;

    // Clear CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, CT and DBM bits.
    tmp &= ((uint32_t)~(HAL_LL_DMA_CHCTL_EN_BIT | HAL_LL_DMA_CHCTL_FTFIE_BIT | HAL_LL_DMA_CHCTL_HTFIE_BIT | \
                        HAL_LL_DMA_CHCTL_ERRIE_BIT | HAL_LL_DMA_CHCTL_DIR_BIT | HAL_LL_DMA_CHCTL_CMEN_BIT | \
                        HAL_LL_DMA_CHCTL_PNAGA_BIT | HAL_LL_DMA_CHCTL_MNAGA_BIT | HAL_LL_DMA_CHCTL_M2M_BIT | \
                        HAL_LL_DMA_CHCTL_PWIDTH_MASK | HAL_LL_DMA_CHCTL_MWIDTH_MASK | HAL_LL_DMA_CHCTL_PRIO_MASK ));

    // BEGIN Prepare the DMA stream configuration.
    // Set desired direction value.
    tmp |= hal_ll_dma_get_reg_value_direction(config.direction);
    // Set desired memory increment settings.
    tmp |= hal_ll_dma_get_reg_value_src_inc(config.src_inc);
    tmp |= hal_ll_dma_get_reg_value_dst_inc(config.dst_inc);
    // Set desired data size settings.
    tmp |= hal_ll_dma_get_reg_value_source_size(config.data_align_source);
    tmp |= hal_ll_dma_get_reg_value_destination_size(config.data_align_destination);
    // Set desired mode.
    tmp |= hal_ll_dma_get_reg_value_mode(config.mode);
    // Finally, set desired priority.
    tmp |= hal_ll_dma_get_reg_value_priority(config.priority);

    // And then write to DMA stream CR register.
    dma->cr = tmp;

    return HAL_LL_DMA_SUCCESS;
}

static inline hal_ll_err_t hal_ll_dma_is_module_disabled( dma_handle_t *dma ) {
    uint16_t timeout = DEFAULT_TIMEOUT_VALUE;

    while((dma->cr & (1U << HAL_LL_DMA_CHCTL_EN_BIT)) != 0) {
        if (0 == timeout--)
            return HAL_LL_DMA_ERROR;
    }

    return HAL_LL_DMA_SUCCESS;
}

static inline uint16_t hal_ll_dma_get_reg_value_direction( hal_ll_dma_direction_t direction ) {
    volatile uint16_t direction_set = (uint8_t)HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY;

    switch (direction)
    {
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY:
            direction_set = HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY_MASK;
            break;
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH:
            direction_set = HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH_MASK;
            break;
        case HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY:
            direction_set = HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY_MASK;
            break;

        default:
            break;
    }

    return (uint16_t)direction_set;
}

static inline uint16_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc ) {
    return (uint16_t)((set_inc) ? (HAL_LL_DMA_PNAGA_MASK) : (0));
}

static inline uint16_t hal_ll_dma_get_reg_value_src_inc( bool set_inc ) {
    return (uint16_t)((set_inc) ? (HAL_LL_DMA_MNAGA_MASK) : (0));
}

static inline uint16_t hal_ll_dma_get_reg_value_source_size( hal_ll_dma_data_align_t align ) {
    volatile uint16_t align_set = (uint16_t)HAL_LL_DMA_DATA_ALIGN_BYTES_1;

    switch (align)
    {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            align_set = HAL_LL_DMA_MWIDTH_BYTE_MASK;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            align_set = HAL_LL_DMA_MWIDTH_HALFWORD_MASK;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            align_set = HAL_LL_DMA_MWIDTH_WORD_MASK;
            break;

        default:
            break;
    }

    return (uint16_t)align_set;
}

static inline uint16_t hal_ll_dma_get_reg_value_destination_size( hal_ll_dma_data_align_t align ) {
    volatile uint16_t align_set = (uint16_t)HAL_LL_DMA_DATA_ALIGN_BYTES_1;

    switch (align)
    {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            align_set = HAL_LL_DMA_CHCTL_PWIDTH_BYTE_MASK;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            align_set = HAL_LL_DMA_CHCTL_PWIDTH_HALFWORD_MASK;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            align_set = HAL_LL_DMA_CHCTL_PWIDTH_WORD_MASK;
            break;

        default:
            break;
    }

    return (uint16_t)align_set;
}

static inline uint16_t hal_ll_dma_get_reg_value_mode( hal_ll_dma_mode_t mode ) {
    return (uint16_t)((mode) ? (HAL_LL_DMA_CHCTL_CMEN_MASK) : (0));
}

static inline uint32_t hal_ll_dma_get_reg_value_priority( hal_ll_dma_priority_t priority ) {
    volatile uint32_t priority_set = (uint32_t)HAL_LL_DMA_PRIORITY_LOW;

    switch (priority)
    {
        case HAL_LL_DMA_PRIORITY_LOW:
            priority_set = HAL_LL_DMA_CHCTL_PRIORITY_LOW_MASK;
            break;
        case HAL_LL_DMA_PRIORITY_MEDIUM:
            priority_set = HAL_LL_DMA_CHCTL_PRIORITY_MEDIUM_MASK;
            break;
        case HAL_LL_DMA_PRIORITY_HIGH:
            priority_set = HAL_LL_DMA_CHCTL_PRIORITY_HIGH_MASK;
            break;
        case HAL_LL_DMA_PRIORITY_VERY_HIGH:
            priority_set = HAL_LL_DMA_CHCTL_PRIORITY_VERY_HIGH_MASK;
            break;

        default:
            break;
    }

    return (uint32_t)priority_set;
}

// ------------------------------------------------------------------------- END
