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

#include "hal_ll_dma.h"

// ------------------------------------------------------------- PRIVATE MACROS

#pragma ReentrancyCheck OFF hal_ll_dma_transfer_start

#define HAL_LL_DMA_CON0_XIP_POSITION                ((uint8_t)0)
#define HAL_LL_DMA_CON0_XIP_MASK                    ((uint8_t)0x1 << HAL_LL_DMA_CON0_XIP_POSITION)
#define HAL_LL_DMA_CON0_XIP                         HAL_LL_DMA_CON0_XIP_MASK
#define HAL_LL_DMA_CON0_AIRQEN_POSITION             ((uint8_t)2)
#define HAL_LL_DMA_CON0_AIRQEN_MASK                 ((uint8_t)0x1 << HAL_LL_DMA_CON0_AIRQEN_POSITION)
#define HAL_LL_DMA_CON0_AIRQEN                      HAL_LL_DMA_CON0_AIRQEN_MASK
#define HAL_LL_DMA_CON0_DGO_POSITION                ((uint8_t)5)
#define HAL_LL_DMA_CON0_DGO_MASK                    ((uint8_t)0x1 << HAL_LL_DMA_CON0_DGO_POSITION)
#define HAL_LL_DMA_CON0_DGO                         HAL_LL_DMA_CON0_DGO_MASK
#define HAL_LL_DMA_CON0_SIRQEN_POSITION             ((uint8_t)6)
#define HAL_LL_DMA_CON0_SIRQEN_MASK                 ((uint8_t)0x1 << HAL_LL_DMA_CON0_SIRQEN_POSITION)
#define HAL_LL_DMA_CON0_SIRQEN                      HAL_LL_DMA_CON0_SIRQEN_MASK
#define HAL_LL_DMA_CON0_EN_POSITION                 ((uint8_t)7)
#define HAL_LL_DMA_CON0_EN_MASK                     ((uint8_t)0x1 << HAL_LL_DMA_CON0_EN_POSITION)
#define HAL_LL_DMA_CON0_EN                          HAL_LL_DMA_CON0_EN_MASK

#define HAL_LL_DMA_CON1_SSTP_POSITION               ((uint8_t)0)
#define HAL_LL_DMA_CON1_SSTP_MASK                   ((uint8_t)0x1 << HAL_LL_DMA_CON1_SSTP_POSITION)
#define HAL_LL_DMA_CON1_SSTP                        HAL_LL_DMA_CON1_SSTP_MASK
#define HAL_LL_DMA_CON1_SMODE_POSITION              ((uint8_t)1)
#define HAL_LL_DMA_CON1_SMODE_MASK                  ((uint8_t)0x3 << HAL_LL_DMA_CON1_SMODE_POSITION)
#define HAL_LL_DMA_CON1_SMODE_STATIC                ((uint8_t)0x0)
#define HAL_LL_DMA_CON1_SMODE_INCREMENT             ((uint8_t)0x1 << HAL_LL_DMA_CON1_SMODE_POSITION)
#define HAL_LL_DMA_CON1_SMODE_DECREMENT             ((uint8_t)0x2 << HAL_LL_DMA_CON1_SMODE_POSITION)
#define HAL_LL_DMA_CON1_SMR_POSITION                ((uint8_t)3)
#define HAL_LL_DMA_CON1_SMR_MASK                    ((uint8_t)0x3 << HAL_LL_DMA_CON1_SMR_POSITION)
#define HAL_LL_DMA_CON1_SMR_SFR_GPR                 ((uint8_t)0x0)
#define HAL_LL_DMA_CON1_SMR_PFM                     ((uint8_t)0x1 << HAL_LL_DMA_CON1_SMR_POSITION)
#define HAL_LL_DMA_CON1_SMR_EEPROM                  ((uint8_t)0x2 << HAL_LL_DMA_CON1_SMR_POSITION)
#define HAL_LL_DMA_CON1_DSTP_POSITION               ((uint8_t)5)
#define HAL_LL_DMA_CON1_DSTP_MASK                   ((uint8_t)0x1 << HAL_LL_DMA_CON1_DSTP_POSITION)
#define HAL_LL_DMA_CON1_DSTP                        HAL_LL_DMA_CON1_DSTP_MASK
#define HAL_LL_DMA_CON1_DMODE_POSITION              ((uint8_t)6)
#define HAL_LL_DMA_CON1_DMODE_MASK                  ((uint8_t)0x3 << HAL_LL_DMA_CON1_DMODE_POSITION)
#define HAL_LL_DMA_CON1_DMODE_STATIC                ((uint8_t)0x0)
#define HAL_LL_DMA_CON1_DMODE_INCREMENT             ((uint8_t)0x1 << HAL_LL_DMA_CON1_DMODE_POSITION)
#define HAL_LL_DMA_CON1_DMODE_DECREMENT             ((uint8_t)0x2 << HAL_LL_DMA_CON1_DMODE_POSITION)

#define HAL_LL_DMA_INTCON0_GIE_POSITION             ((uint8_t)7)
#define HAL_LL_DMA_INTCON0_GIE_MASK                 ((uint8_t)0x1 << HAL_LL_DMA_INTCON0_GIE_POSITION)
#define HAL_LL_DMA_INTCON0_GIE                      HAL_LL_DMA_INTCON0_GIE_MASK

#define HAL_LL_DMA_PIR_DMASCINTIF_POSITION          ((uint8_t)4)
#define HAL_LL_DMA_PIR_DMASCINTIF_MASK              ((uint8_t)0x1 << HAL_LL_DMA_PIR_DMASCINTIF_POSITION)
#define HAL_LL_DMA_PIR_DMASCINTIF                   HAL_LL_DMA_PIR_DMASCINTIF_MASK
#define HAL_LL_DMA_PIR_DMADCINTIF_POSITION          ((uint8_t)5)
#define HAL_LL_DMA_PIR_DMADCINTIF_MASK              ((uint8_t)0x1 << HAL_LL_DMA_PIR_DMADCINTIF_POSITION)
#define HAL_LL_DMA_PIR_DMADCINTIF                   HAL_LL_DMA_PIR_DMADCINTIF_MASK
#define HAL_LL_DMA_PIR_DMAORIF_POSITION             ((uint8_t)6)
#define HAL_LL_DMA_PIR_DMAORIF_MASK                 ((uint8_t)0x1 << HAL_LL_DMA_PIR_DMAORIF_POSITION)
#define HAL_LL_DMA_PIR_DMAORIF                      HAL_LL_DMA_PIR_DMAORIF_MASK
#define HAL_LL_DMA_PIR_DMAAIF_POSITION              ((uint8_t)7)
#define HAL_LL_DMA_PIR_DMAAIF_MASK                  ((uint8_t)0x1 << HAL_LL_DMA_PIR_DMAAIF_POSITION)
#define HAL_LL_DMA_PIR_DMAAIF                       HAL_LL_DMA_PIR_DMAAIF_MASK
#define HAL_LL_DMA_PIR_MASK                         (HAL_LL_DMA_PIR_DMASCINTIF | HAL_LL_DMA_PIR_DMADCINTIF | HAL_LL_DMA_PIR_DMAORIF | HAL_LL_DMA_PIR_DMAAIF)

#define HAL_LL_DMA_BUS_ARBITER_PRIORITY_UNLOCKED    (0x00)
#define HAL_LL_DMA_BUS_ARBITER_PRIORITY_LOCKED      (0x01)
#define HAL_LL_DMA_BUS_ARBITER_PRIORITY_MAX_NO      (7)
#define HAL_LL_DMA_DMA_BASE_ADDRESS                 (0x00E8)
#define HAL_LL_DMA_BUS_ARBITER_BASE_ADDRESS         (0x00B4)
#define HAL_LL_DMA_INTCON0_BASE_ADDRESS             (0x04D6)
#define HAL_LL_DMA_BSR_BASE_ADDRESS                 (0x04E0)

#define HAL_LL_DMA_INTCON0                          *hal_ll_dma_intcon0
#define HAL_LL_DMA_BSR                              *hal_ll_dma_bsr

/*!< @brief DMA module disable macro. */
#define HAL_LL_DMA_MODULE_DISABLE(_x)              (_x->con0 &= ~HAL_LL_DMA_CON0_EN)
/*!< @brief DMA module enable macro. */
#define HAL_LL_DMA_MODULE_ENABLE(_x)               (_x->con0 |= HAL_LL_DMA_CON0_EN)
/*!< @brief Stop DMA transfer macro. */
#define HAL_LL_DMA_STOP_TRANSFER(_x)               (_x->con0 &= ~(HAL_LL_DMA_CON0_DGO | HAL_LL_DMA_CON0_SIRQEN))
/*!< @brief Disable the DMA module trigger source macro. */
#define HAL_LL_DMA_DISABLE_TRIGGER_SOURCE(_x)      (_x->con0 &= ~HAL_LL_DMA_CON0_SIRQEN)


// ----------------------------------------------------------- PRIVATE TYPEDEFS

/*!< @brief DMA HW register structure. */
typedef struct dma_handle
{
    volatile uint8_t select;
    volatile uint8_t buf;           /*!< DMA data buffer register. */
    volatile uint16_t dcnt;         /*!< DMA destination count register. */
    volatile uint16_t dptr;         /*!< DMA destination pointer register. */
    volatile uint16_t dsz;          /*!< DMA destination size register. */
    volatile uint16_t dsa;          /*!< DMA destination start address register. */
    volatile uint16_t scnt;         /*!< DMA destination count register. */
    volatile uint16_t sptr;         /*!< DMA source pointer register. */
    volatile uint8_t sptru;         /*!< DMA source pointer upper register. */
    volatile uint16_t ssz;          /*!< DMA source size register. */
    volatile uint16_t ssa;          /*!< DMA source start address register. */
    volatile uint8_t ssau;          /*!< DMA source start address upper register. */
    union {
        volatile uint16_t con;      /*!< DMA control register. */
        struct {
            volatile uint8_t con0;  /*!< DMA control 0 register. */
            volatile uint8_t con1;  /*!< DMA control 1 register. */
        };
    };
    volatile uint8_t airq;          /*!< DMA interrupt request source register. */
    volatile uint8_t sirq;          /*!< DMA abort request source register. */
} dma_handle_t;

/*!< @brief Bus arbiter structure. */
typedef struct hal_ll_dma_bus_arbiter_registers
{
    volatile uint8_t prlock;        /*!< Priority lock register */
    volatile uint8_t scanpr;        /*!< Scanner priority register */
    volatile uint8_t dma1pr;        /*!< DMA1 priority register */
    volatile uint8_t dma2pr;        /*!< DMA2 priority register */
    volatile uint8_t dma3pr;        /*!< DMA1 priority register */
    volatile uint8_t dma4pr;        /*!< DMA2 priority register */
    volatile uint8_t dma5pr;        /*!< DMA1 priority register */
    volatile uint8_t dma6pr;        /*!< DMA2 priority register */
    uint16_t reserved;
    volatile uint8_t mainpr;        /*!< Main routine priority register */
    volatile uint8_t ispr;          /*!< ISR priority register */
} hal_ll_dma_bus_arbiter_registers_t;


// ------------------------------------------------------------------ VARIABLES

static volatile hal_ll_base_addr_t * const hal_ll_dma = HAL_LL_DMA_DMA_BASE_ADDRESS;

static volatile hal_ll_base_addr_t * const hal_ll_dma_intcon0 = HAL_LL_DMA_INTCON0_BASE_ADDRESS;

static volatile hal_ll_base_addr_t * const hal_ll_dma_bsr = HAL_LL_DMA_BSR_BASE_ADDRESS;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Unlocks MCU bus arbiter priorities.
 * @details Unlocks MCU bus arbiter priority registers,
 *          thus blocking DMA access to the system bus.
 * @return Nothing.
 */
static inline void hal_ll_dma_bus_arbiter_priority_unlock();

/**
 * @brief Locks MCU bus arbiter priorities.
 * @details Locks MCU bus arbiter priority registers,
 *          thus allowing DMA access to the system bus.
 * @return Nothing.
 */
static inline void hal_ll_dma_bus_arbiter_priority_lock();

/**
 * @brief Clears DMA interrupt flags.
 * @details Clears DMA module active interrupt flags.
 * @param[in] obj DMA object.
 * @return Nothing.
 */
static void hal_ll_dma_clear_interrupt_flags( hal_ll_dma_t *obj );


/**
 * @brief Set the desired DMA module priority.
 * @details Set the desired DMA module priority, in bus arbiter and lock priorities.
 *          If some other module has the desired priority, its priority will be set to,
 *          the current DMA module priority.
 * @param[in] config DMA configuration structure.
 * @return Nothing.
 */
static void hal_ll_dma_set_bus_arbiter_priority( hal_ll_dma_config_t * config );

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
 * @brief Enable the DMA module.
 * @details Enables the DMA module specified by the @ref dma_obj structure.
 * @param[in] dma_obj DMA object.
 * @return Nothing.
 */
static inline void hal_ll_dma_enable_module( hal_ll_dma_t *obj );

/**
 * @brief Gets DMA source address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream source address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_source_inc( bool set_inc );

/**
 * @brief Gets DMA destination address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream destination address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint16_t hal_ll_dma_get_reg_value_destination_inc( bool set_inc );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;

    // Initialize DMA module.
    obj->handle = ( handle_t )HAL_LL_DMA_DMA_BASE_ADDRESS;
    status = hal_ll_dma_init_hw( obj,
                                ( dma_handle_t * )obj->handle,
                                 obj->config );

    if ( HAL_LL_DMA_SUCCESS != status ) {
        obj->handle = 0;  // If initialization failed, reset handle.
    }

    return status;
}

hal_ll_err_t hal_ll_dma_deinit( hal_ll_dma_t *obj ) {
    dma_handle_t * dma = (dma_handle_t *)obj->handle;

    // Select the correct DMA module for subsequent operations.
    dma->select = obj->config.module;

    // Disable the DMA module.
    HAL_LL_DMA_MODULE_DISABLE( dma );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new mode.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.mode = mode;

    // Try to set new mode.
    status = hal_ll_dma_init_hw( obj,
                                ( dma_handle_t * )obj->handle,
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
                                ( dma_handle_t * )obj->handle,
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
                                ( dma_handle_t * )obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type ) {
    dma_handle_t * dma = (dma_handle_t *)obj->handle;
    hal_ll_dma_config_t cfg = obj->config;

    // Select the correct DMA module for subsequent operations.
    dma->select = obj->config.module;

    // Disable module first.
    HAL_LL_DMA_MODULE_DISABLE( dma );

    // Clear source memory region control bits and set upper address byte.
    dma->con1 &= ~HAL_LL_DMA_CON1_SMR_MASK;
    switch ( src_mem_type ) {
        case HAL_LL_DMA_SOURCE_MEMORY_REGION_PFM:        // Program flash memory region
            dma->con1 |= HAL_LL_DMA_CON1_SMR_PFM;
            dma->ssau = (uint8_t)( ( addr_src >> 16 ) && 0xFF );
            break;
        case HAL_LL_DMA_SOURCE_MEMORY_REGION_DEEPROM:    // Data EEPROM memory region
            dma->con1 |= HAL_LL_DMA_CON1_SMR_EEPROM;
            dma->ssau = (uint8_t)( ( addr_src >> 16 ) && 0xFF );
            break;
        case HAL_LL_DMA_SOURCE_MEMORY_REGION_RAM:        // No need to set anything in DMAxCON1 register.
            dma->ssau = 0;
            break;

        default:
            return HAL_LL_DMA_ERROR;        // Invalid selection.
    }

    // Configure DMA source address.
    dma->ssa = (uint16_t)( addr_src & 0xFFFF );
    // Configure DMA destination address.
    dma->dsa = (uint16_t)( addr_dst & 0xFFFF );

    // Configure source and destination sizes, depending on direction.
    switch ( cfg.direction ) {
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY:
            dma->ssz = cfg.transfer_length;
            dma->dsz = cfg.transfer_length;
            // TODO consider what happens if addresses are not from GPR section.
            break;
        case HAL_LL_DMA_DIRECTION_MEMORY_TO_PERIPH:
            dma->ssz = cfg.transfer_length;
            dma->dsz = cfg.data_align_destination + 1;
            if ( HAL_LL_DMA_MODE_NORMAL == cfg.mode ) {
                dma->con1 |= HAL_LL_DMA_CON1_SSTP;
            }
            // TODO consider what happens if peripheral address is not SFR or if source address is not GPR.
            break;
        case HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY:
            dma->ssz = cfg.data_align_source + 1;
            dma->dsz = cfg.transfer_length;
            if ( HAL_LL_DMA_MODE_NORMAL == cfg.mode ) {
                dma->con1 |= HAL_LL_DMA_CON1_DSTP;
            }
            // TODO consider what happens if peripheral address is not GPR or if source address is not SFR.
            break;
        case HAL_LL_DMA_DIRECTION_PERIPH_TO_PERIPH:
            if ( cfg.data_align_destination == cfg.data_align_source ) {
                dma->ssz = cfg.data_align_source + 1;
                dma->dsz = cfg.data_align_destination + 1;
                break;
            }
            // In P2P mode source and destination must be of the same size.
            // TODO consider what happens if address are not from SFR space

        default:
           return HAL_LL_DMA_ERROR;
    }

    // Enable DMA module.
    HAL_LL_DMA_MODULE_ENABLE( dma );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    uint8_t tmp = 0;

    // Select the correct DMA module for subsequent operations.
    dma->select = obj->config.module;

    tmp = dma->con0;

    // In case of circular mode or a direction includes at least one peripheral,
    // for the purposes of synchronization DMA start is performed using SIRQEN control bit.
    // This allows the peripheral to start DMA transmission when it is ready.
    if ( ( HAL_LL_DMA_MODE_CIRCULAR == obj->config.mode ) ||
         ( HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY != obj->config.direction ) ) {
        tmp |= HAL_LL_DMA_CON0_SIRQEN;
    }
    tmp |= HAL_LL_DMA_CON0_DGO;

    // Write appropriate start command into DMA control0 register.
    dma->con0 = tmp;

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj ) {
    dma_handle_t * dma = (dma_handle_t *)obj->handle;
    volatile uint16_t * transfer_remaining_count;
    uint16_t transfer_completed;

    // No point in stopping circular transfer.
    if ( HAL_LL_DMA_MODE_CIRCULAR == obj->config.mode ) {
        return HAL_LL_DMA_ERROR;
    }

    // Select the correct DMA module for subsequent operations.
    dma->select = obj->config.module;

    // Determine total transfer size and how much still needs to be sent before transfer completes.
    transfer_remaining_count = ( dma->scnt > dma->dcnt ) ? &dma->scnt : &dma->dcnt;
    transfer_completed = ( dma->ssz > dma->dsz ) ? dma->ssz : dma->dsz;


    // Wait until transfer has completed.
    while ( *transfer_remaining_count != transfer_completed );
    // Once transfer has completed it will be stopped by the hardware automatically by clearing DGO bit.

    /* Note: Once the DMA message is complete, it may be desirable to disable
     *       the trigger source to prevent overrun or under run of data.
     */
    HAL_LL_DMA_DISABLE_TRIGGER_SOURCE( dma );

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj ) {
    dma_handle_t * dma = (dma_handle_t *)obj->handle;

    // Select the correct DMA module for subsequent operations.
    dma->select = obj->config.module;

    // Stop DMA Transfer by clearing DGO and SIRQEN bits.
    HAL_LL_DMA_STOP_TRANSFER( dma );

    // Clear DMA module interrupt flags.
    hal_ll_dma_clear_interrupt_flags( obj );

    return HAL_LL_DMA_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static inline void hal_ll_dma_bus_arbiter_priority_unlock() {
    uint8_t bsr_backup = HAL_LL_DMA_BSR;    // Save  BANK.
    // TODO what about WREG?

    /* Note: To unlock PRLOCK register (and block the DMA access to the system bus)
     *       special sequence should be followed:
     *       PRLOCK = 0x55;
     *       PRLOCK = 0xAA;
     *       PRLOCK &= ~(0x01);
     *       This special unlocking sequence must be performed with
     *       specific assembly instructions. To avoid possibility
     *       of compiler generating different instructions
     *       for the unlocking sequence, unlocking is implemented in assembly.
     *       The PRLOCK register address is 0x00B4.
     */
    asm {
        MOVLW    0x55         // Move 0x55 to WREG.
        MOVLB    0x00         // Set bank to 39. PRLOCK BANK.
        MOVWF    0xB4         // Write WREG(0x55) to PRLOCK.
        MOVLW    0xAA         // Move 0xAA to WREG.
        MOVWF    0xB4         // Write WREG(0xAA) to PRLOCK.
        BCF      0xB4, 0      // Clear bit 0 in PRLOCK.
    };
    HAL_LL_DMA_BSR = bsr_backup;            // Restore BANK.
}

static inline void hal_ll_dma_bus_arbiter_priority_lock() {
    uint8_t bsr_backup = HAL_LL_DMA_BSR;    // Save BANK.
    // TODO what about WREG?

    /* Note: To lock PRLOCK (and allow the DMA access to the system bus)
     *       special sequence should be followed:
     *       PRLOCK = 0x55;
     *       PRLOCK = 0xAA;
     *       PRLOCK |= 0x01;
     *       This special locking sequence must be performed with
     *       specific assembly instructions. To avoid possibility
     *       of compiler generating different instructions
     *       for the locking sequence, locking is implemented in assembly.
     *       The PRLOCK register address is 0x00B4.
     */
    asm {
        MOVLW    0x55         // Move 0x55 to WREG.
        MOVLB    0x00         // Set bank to 39. PRLOCK BANK.
        MOVWF    0xB4         // Write WREG(0x55) to PRLOCK.
        MOVLW    0xAA         // Move 0xAA to WREG.
        MOVWF    0xB4         // Write WREG(0xAA) to PRLOCK.
        BSF      0xB4, 0      // Set bit 0 in PRLOCK.
    };
    HAL_LL_DMA_BSR = bsr_backup;            // Restore BANK.
}

static void hal_ll_dma_clear_interrupt_flags( hal_ll_dma_t *obj ) {
    switch (obj->module) {
        #ifdef DMA_MODULE_1
        case DMA_MODULE_1:
            *(uint8_t *)HAL_LL_PIR2_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
        #ifdef DMA_MODULE_2
        case DMA_MODULE_2:
            *(uint8_t *)HAL_LL_PIR6_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
        #ifdef DMA_MODULE_3
        case DMA_MODULE_3:
            *(uint8_t *)HAL_LL_PIR10_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
        #ifdef DMA_MODULE_4
        case DMA_MODULE_4:
            *(uint8_t *)HAL_LL_PIR11_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
        #ifdef DMA_MODULE_5
        case DMA_MODULE_5:
            *(uint8_t *)HAL_LL_PIR12_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
        #ifdef DMA_MODULE_6
        case DMA_MODULE_6:
            *(uint8_t *)HAL_LL_PIR13_ADDRESS &= ~HAL_LL_DMA_PIR_MASK;
            break;
        #endif
    }
}

static void hal_ll_dma_set_bus_arbiter_priority( hal_ll_dma_config_t * config ) {
    uint8_t tmp = 0;
    hal_ll_dma_bus_arbiter_registers_t * bus_arbiter = (hal_ll_dma_bus_arbiter_registers_t *)HAL_LL_DMA_BUS_ARBITER_BASE_ADDRESS;
    volatile uint8_t * current_dmapr_reg = ( (uint8_t *)&bus_arbiter->dma1pr + config->module );
    uint8_t desired_dmapr = ( HAL_LL_DMA_BUS_ARBITER_PRIORITY_MAX_NO - ( config->priority << 1 ) );  // This conversion will never allow DMA to preempt ISR

    // Save INTCON0 register state.
    tmp = HAL_LL_DMA_INTCON0;

    // Disable global interrupts.
    HAL_LL_DMA_INTCON0 &= ~HAL_LL_DMA_INTCON0_GIE;

    // If the new priority is different then the old one.
    if ( *current_dmapr_reg != desired_dmapr ) {
        // If PRLOCK is active, unlock the bus arbiter priorities.
        if ( HAL_LL_DMA_BUS_ARBITER_PRIORITY_LOCKED == bus_arbiter->prlock ) {
            hal_ll_dma_bus_arbiter_priority_unlock();
        }

        // Set desired DMA priority in bus arbiter.
        *current_dmapr_reg = desired_dmapr;
    }

    // If the bus arbiters priority lock is not active.
    if ( HAL_LL_DMA_BUS_ARBITER_PRIORITY_UNLOCKED == bus_arbiter->prlock ) {
        // Lock the bus arbiter priorities and allow DMA access to the system bus.
        hal_ll_dma_bus_arbiter_priority_lock();
    }

    // Revert INTCON0 register state.
    HAL_LL_DMA_INTCON0 = tmp;
}

static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *obj, dma_handle_t *dma, hal_ll_dma_config_t config ) {
    uint16_t tmp = 0;

    // Enable DMA module in case it was disabled.
    hal_ll_dma_enable_module( obj );

    // Select the correct DMA module for subsequent operations.
    dma->select = config.module;

    // Disable the peripheral first.
    HAL_LL_DMA_MODULE_DISABLE( dma );

    // Set DMA module priority.
    hal_ll_dma_set_bus_arbiter_priority( &config );

    // Get the CON0 register value.
    tmp = dma->con;

    // Clear DGO, AIRQEN, SIRQEN, DMODE, SSTP, DSTP, SMR, and SMODE bits.
    tmp &= ~ ( ( (uint16_t)( HAL_LL_DMA_CON0_DGO_MASK   | HAL_LL_DMA_CON0_AIRQEN | HAL_LL_DMA_CON0_SIRQEN ) | \
                 (uint16_t)( HAL_LL_DMA_CON1_DMODE_MASK | HAL_LL_DMA_CON1_SSTP   | HAL_LL_DMA_CON1_DSTP   | \
                               HAL_LL_DMA_CON1_SMODE_MASK ) << 8 ) );

    // BEGIN Prepare the DMA configuration.
    // Set desired memory increment settings.
    tmp |= hal_ll_dma_get_reg_value_source_inc( config.src_inc );
    tmp |= hal_ll_dma_get_reg_value_destination_inc( config.dst_inc );
    // Check validity of desired data size settings.
    if ( ( HAL_LL_DMA_DATA_ALIGN_BYTES_4 == config.data_align_source ) || \
         ( HAL_LL_DMA_DATA_ALIGN_BYTES_4 == config.data_align_destination ) ) {
        return HAL_LL_DMA_ERROR;
    }
    // Check validity of desired burst transfer settings. PIC18 DMA does not have burst mode.
    if ( ( HAL_LL_DMA_BURST_SIZE_INCREMENT_1 != config.burst_size_source ) || \
         ( HAL_LL_DMA_BURST_SIZE_INCREMENT_1 != config.burst_size_destination ) ) {
        return HAL_LL_DMA_ERROR;
    }
    // Configure desired mode.
    if ( HAL_LL_DMA_MODE_NORMAL == config.mode ) {
        if ( HAL_LL_DMA_DIRECTION_PERIPH_TO_MEMORY == config.direction ) {
            // In P2M direction, destination/memory must stop the transmission, because its message size is larger.
            tmp |= ( (uint16_t)HAL_LL_DMA_CON1_DSTP << 8 );
        } else {
            // In P2P and M2M directions. it does not matter whether source or destination stop signal is used, because both are of the same size.
            // In M2P direction, source/memory must stop the transmission, because its message size is larger.
            tmp |= ( (uint16_t)HAL_LL_DMA_CON1_SSTP << 8);
        }
    }
    // If SIRQEN is 1, and the appropriate SIRQ/channel is sending requests, it will be in circular mode by default

    // Set the desired IRQ source/channel for synchronization purposes.
    dma->sirq = config.channel;

    // Configure the DMA module.
    dma->con = tmp;

    // Enable the peripheral.
    HAL_LL_DMA_MODULE_ENABLE( dma );

    return HAL_LL_DMA_SUCCESS;
}

static inline void hal_ll_dma_enable_module( hal_ll_dma_t *obj ) {
    *(uint8_t *)HAL_LL_PMD8_ADDRESS &= ~( 0x01 << obj->config.module );
}

static inline uint16_t hal_ll_dma_get_reg_value_source_inc( bool set_inc ) {
    return ( ( set_inc ) ? ( (uint16_t)HAL_LL_DMA_CON1_SMODE_INCREMENT << 8 ) : (uint16_t)HAL_LL_DMA_CON1_SMODE_STATIC );
}

static inline uint16_t hal_ll_dma_get_reg_value_destination_inc( bool set_inc ) {
    return ( ( set_inc ) ? ( (uint16_t)HAL_LL_DMA_CON1_DMODE_INCREMENT << 8 ) : (uint16_t)HAL_LL_DMA_CON1_SMODE_STATIC );
}

// ------------------------------------------------------------------------- END
