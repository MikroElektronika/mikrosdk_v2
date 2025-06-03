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

#include "hal_ll_rcc.h"
#include "hal_ll_dma.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief To ensure that the whole DMA channel control structure can fit into buffer after 1024 byte aligned address, the buffer must to be expanded by 1023 bytes. */
#define HAL_LL_DMA_BASE_ADDR                   (0x400FF000UL)
#define HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK     (0x3FFUL)

// RCGCDMA register definitions.
#define HAL_LL_DMA_SYSCTL_RCGCDMA              (*((volatile uint32_t *)0x400FE60C))
#define HAL_LL_DMA_SYSCTL_RCGCDMA_CLOCK_DMA    (0x1UL)

// PRDMA register definitions.
#define HAL_LL_DMA_SYSCTL_PRDMA                (*((volatile uint32_t *)0x400FEA0C))
#define HAL_LL_DMA_SYSCTL_PRDMA_DMA_READY      (0x1UL)

// FLASHDMAPP register definitions.
#define HAL_LL_DMA_FLASHPP                     (*((volatile uint32_t *)0x400FDFC0))
#define HAL_LL_DMA_FLASHPP_SIZE_POSITION       ((uint8_t)0)
#define HAL_LL_DMA_FLASHPP_SIZE_MASK           (0xFFFFUL << HAL_LL_DMA_FLASHPP_SIZE_POSITION)
#define HAL_LL_DMA_FLASHPP_DFA_POSITION        ((uint8_t)28)
#define HAL_LL_DMA_FLASHPP_DFA_MASK            (0x1UL << HAL_LL_DMA_FLASHPP_DFA_POSITION)
#define HAL_LL_DMA_FLASHPP_DFA                 HAL_LL_DMA_FLASHPP_DFA_MASK

// FLASHDMASZ register definitions.
#define HAL_LL_DMA_FLASHDMASZ                  (*((volatile uint32_t *)0x400FDFD0))
#define HAL_LL_DMA_FLASHDMASZ_SIZE_POSITION    ((uint8_t)0)
#define HAL_LL_DMA_FLASHDMASZ_SIZE_MASK        (0x3FFFFUL << HAL_LL_DMA_FLASHDMASZ_SIZE_POSITION)

// FLASHDMAST register definitions.
#define HAL_LL_DMA_FLASHDMAST                  (*((volatile uint32_t *)0x400FDFD4))
#define HAL_LL_DMA_FLASHDMAST_ADDR_POSITION    ((uint8_t)11)
#define HAL_LL_DMA_FLASHDMAST_ADDR_MASK        (0x3FFFFUL << HAL_LL_DMA_FLASHDMAST_ADDR_POSITION)

// DMASTAT register definitions.
#define HAL_LL_DMA_DMASTAT_MASTEN              (0x1UL)
// DMACFG register definitions.
#define HAL_LL_DMA_DMACFG_MASTEN               (0x1UL)
// DMASWREQ register definitions.
#define HAL_LL_DMA_SWREQ                       (0x1UL)
// DMAUSEBURSTCLR register definitions.
#define HAL_LL_DMA_USEBURSTCLR                 (0x1UL)
// DMAREQMASKCLR register definitions.
#define HAL_LL_DMA_REQMASKCLR                  (0x1UL)
// DMAENSET register definitions.
#define HAL_LL_DMA_ENASET                      (0x1UL)
// DMAENCLR register definitions.
#define HAL_LL_DMA_ENACLR                      (0x1UL)
// Mask used to check if the DMA stream is in use.
#define HAL_LL_DMA_STREAM_ENABLED_MASK         (0xFFFFFFFFUL)
// DMAALTCLR register definitions.
#define HAL_LL_DMA_ALTCLR                      (0x1UL)
// DMAPRIOSET register definitions.
#define HAL_LL_DMA_PRIOSET                     (0x1UL)
// DMAPRIOCLR register definitions.
#define HAL_LL_DMA_PRIOCLR                     (0x1UL)

// DMA Channel Control Word (DMACHTL) definitions.
#define HAL_LL_DMA_DMACHCTL_XFERMODE_MASK                         (0x7UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_STOP                         (0x0UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_BASIC                        (0x1UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_AUTO_REQUEST                 (0x2UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_PING_PONG                    (0x3UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_MEM_SCATTER_GATHER           (0x4UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_ALT_MEM_SCATTER_GATHER       (0x5UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_PERIPH_SCATTER_GATHER        (0x6UL)
#define HAL_LL_DMA_DMACHCTL_XFERMODE_ALT_PERIPH_SCATTER_GATHER    (0x7UL)
#define HAL_LL_DMA_DMACHTL_NXTUSEBURST_POSITION                   ((uint8_t)3)
#define HAL_LL_DMA_DMACHTL_NXTUSEBURST_MASK                       (0x1UL << HAL_LL_DMA_DMACHTL_NXTUSEBURST_POSITION)
#define HAL_LL_DMA_DMACHTL_NXTUSEBURST                            HAL_LL_DMA_DMACHTL_NXTUSEBURST_MASK
#define HAL_LL_DMA_DMACHTL_XFERSIZE_POSITION                      ((uint8_t)4)
#define HAL_LL_DMA_DMACHTL_XFERSIZE_MASK                          (0x3FFUL << HAL_LL_DMA_DMACHTL_XFERSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_ARBSIZE_POSITION                       ((uint8_t)14)
#define HAL_LL_DMA_DMACHTL_ARBSIZE_MASK                           (0xFUL << HAL_LL_DMA_DMACHTL_ARBSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCSIZE_POSITION                       ((uint8_t)24)
#define HAL_LL_DMA_DMACHTL_SRCSIZE_MASK                           (0x3UL << HAL_LL_DMA_DMACHTL_SRCSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCSIZE_BYTE                           (0x0UL)
#define HAL_LL_DMA_DMACHTL_SRCSIZE_HALF_WORD                      (0x1UL << HAL_LL_DMA_DMACHTL_SRCSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCSIZE_WORD                           (0x2UL << HAL_LL_DMA_DMACHTL_SRCSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCINC_POSITION                        ((uint8_t)26)
#define HAL_LL_DMA_DMACHTL_SRCINC_MASK                            (0x3UL << HAL_LL_DMA_DMACHTL_SRCINC_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCINC_BYTE                            (0x0UL)
#define HAL_LL_DMA_DMACHTL_SRCINC_HALF_WORD                       (0x1UL << HAL_LL_DMA_DMACHTL_SRCINC_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCINC_WORD                            (0x2UL << HAL_LL_DMA_DMACHTL_SRCINC_POSITION)
#define HAL_LL_DMA_DMACHTL_SRCINC_NO_INCREMENT                    (0x3UL << HAL_LL_DMA_DMACHTL_SRCINC_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTSIZE_POSITION                       ((uint8_t)28)
#define HAL_LL_DMA_DMACHTL_DSTSIZE_MASK                           (0x3UL << HAL_LL_DMA_DMACHTL_DSTSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTSIZE_BYTE                           (0x0UL)
#define HAL_LL_DMA_DMACHTL_DSTSIZE_HALF_WORD                      (0x1UL << HAL_LL_DMA_DMACHTL_DSTSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTSIZE_WORD                           (0x2UL << HAL_LL_DMA_DMACHTL_DSTSIZE_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTINC_POSITION                        ((uint8_t)30)
#define HAL_LL_DMA_DMACHTL_DSTINC_MASK                            (0x3UL << HAL_LL_DMA_DMACHTL_DSTINC_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTINC_BYTE                            (0x0UL)
#define HAL_LL_DMA_DMACHTL_DSTINC_HALF_WORD                       (0x1UL << HAL_LL_DMA_DMACHTL_DSTINC_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTINC_WORD                            (0x2UL << HAL_LL_DMA_DMACHTL_DSTINC_POSITION)
#define HAL_LL_DMA_DMACHTL_DSTINC_NO_INCREMENT                    (0x3UL << HAL_LL_DMA_DMACHTL_DSTINC_POSITION)

/*!< Read Only access. */
#ifdef __GNUC__
    #define _HAL_LL_DMA_RO                     volatile const
#else
    #define _HAL_LL_DMA_RO                     volatile
#endif
/*!< Read and Write access. */
#define _HAL_LL_DMA_RW                         volatile
/*!< Write Only access. */
#define _HAL_LL_DMA_WO                         volatile

/*!< @brief Macro use to determine if the DMA has access to flash memory */
#define HAL_LL_DMA_HAS_FLASH_ACCESS            (HAL_LL_DMA_FLASHPP & HAL_LL_DMA_FLASHPP_DFA)
/*!< @brief Macro use to determine the size of the flash memory */
#define HAL_LL_DMA_FLASH_SIZE                  ((HAL_LL_DMA_FLASHPP & HAL_LL_DMA_FLASHPP_SIZE_MASK) >> HAL_LL_DMA_FLASHPP_SIZE_POSITION)
/*!< @brief Macro use to validate appropriate DMA access to transfer buffers located in flash memory */
#define HAL_LL_DMA_FLASH_ACCESS_OK             HAL_LL_DMA_SUCCESS

/*!< @brief Clock enable macro. */
#define _HAL_LL_ENABLE_CLOCK_SYS_              (HAL_LL_DMA_SYSCTL_RCGCDMA |= HAL_LL_DMA_SYSCTL_RCGCDMA_CLOCK_DMA)
/*!< @brief Clock disable macro. */
#define _HAL_LL_DISABLE_CLOCK_SYS_             (HAL_LL_DMA_SYSCTL_RCGCDMA &= !HAL_LL_DMA_SYSCTL_RCGCDMA_CLOCK_DMA)

/*!< @brief DMA module enable macro. */
#define HAL_LL_DMA_MODULE_ENABLE               (dma->cfg |= HAL_LL_DMA_DMACFG_MASTEN)
/*!< @brief DMA module disable macro. */
#define HAL_LL_DMA_MODULE_DISABLE              (dma->cfg &= ~HAL_LL_DMA_DMACFG_MASTEN)
/*!< @brief DMA module usage status macro. */
#define HAL_LL_DMA_MODULE_UNUSED               (0x0UL)

/*!< @brief DMA stream enable macro. */
#define HAL_LL_DMA_STREAM_ENABLE(_stream)      (dma->ena_set |= HAL_LL_DMA_ENASET << _stream)
/*!< @brief DMA stream disable macro. */
#define HAL_LL_DMA_STREAM_DISABLE(_stream)     (dma->ena_clr |= HAL_LL_DMA_ENASET << _stream)

/*!< @brief Default timeout value to wait when checking if module is disabled/enabled. */
#define DEFAULT_TIMEOUT_VALUE                  (0xFFFFU)

// ----------------------------------------------------------- PRIVATE TYPEDEFS

/*!< @brief DMA HW channel control structure. */
typedef struct dma_ch_ctl_struct
{
    _HAL_LL_DMA_RW uint32_t src_endp; /*!< DMA channel source address end pointer. */
    _HAL_LL_DMA_RW uint32_t dst_endp; /*!< DMA channel destination address end pointer. */
    _HAL_LL_DMA_RW uint32_t ch_ctl;   /*!< DMA channel control word. */
                   uint32_t __unused1;
} dma_ch_ctl_struct_t;

/*!< @brief DMA HW register structure. */
typedef struct dma_handle
{
    _HAL_LL_DMA_RO uint32_t stat;              /*!< DMA status register. */
    _HAL_LL_DMA_WO uint32_t cfg;               /*!< DMA configuration register. */
    _HAL_LL_DMA_RW uint32_t ctl_base;          /*!< DMA channel control base pointer. */
    _HAL_LL_DMA_RO uint32_t alt_base;          /*!< DMA alternate channel control base pointer. */
    _HAL_LL_DMA_RO uint32_t wait_stat;         /*!< DMA channel wait-on request status register. */
    _HAL_LL_DMA_WO uint32_t sw_req;            /*!< DMA channel software request register. */
    _HAL_LL_DMA_RW uint32_t use_burst_set;     /*!< DMA channel useburst set register. */
    _HAL_LL_DMA_WO uint32_t use_burst_clr;     /*!< DMA channel useburst clear register. */
    _HAL_LL_DMA_RW uint32_t req_mask_set;      /*!< DMA channel request mask set register. */
    _HAL_LL_DMA_WO uint32_t req_mask_clr;      /*!< DMA channel request mask clear register. */
    _HAL_LL_DMA_RW uint32_t ena_set;           /*!< DMA channel enable set register. */
    _HAL_LL_DMA_WO uint32_t ena_clr;           /*!< DMA channel enable clear register. */
    _HAL_LL_DMA_RW uint32_t alt_set;           /*!< DMA channel primary alternate set register. */
    _HAL_LL_DMA_WO uint32_t alt_clr;           /*!< DMA channel primary alternate clear register */
    _HAL_LL_DMA_RW uint32_t prio_set;          /*!< DMA channel priority set register */
    _HAL_LL_DMA_WO uint32_t prio_clr;          /*!< DMA channel priority clear register */
                   uint32_t unused1[3];
    _HAL_LL_DMA_RW uint32_t err_clr;           /*!< DMA bus error clear register */
                   uint32_t unused2[300];
    _HAL_LL_DMA_RW uint32_t ch_asgn;           /*!< DMA channel assignment register */
                   uint32_t unused3[3];
    _HAL_LL_DMA_RW uint32_t ch_map[4];         /*!< DMA channel map select registers */
} dma_handle_t;

// ------------------------------------------------------------------ VARIABLES

/* Note: The channel control structure buffer is created with overhead of 1023 bytes to ensure that
 *       there is one address aligned/divisible with 1024 inside the buffer, and there are enough
 *       enough bytes needed for channel control structure (sizeof(dma_ch_ctl_struct_t) * DMA_NUM_OF_STREAMS),
 *       after this address.
 */
 /*!< @brief DMA HW channel control structure extended buffer */
static dma_ch_ctl_struct_t dma_ch_ctl_buffer[ ( ( ( sizeof( dma_ch_ctl_struct_t ) * DMA_NUM_OF_STREAMS ) << 1 )
                                                + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK )
                                              / sizeof( dma_ch_ctl_struct_t ) ];
/*!< @brief Pointer to 1024 byte aligned address inside dma_ch_ctl_buffer where actual channel control data will be stored */
static dma_ch_ctl_struct_t * dma_ch_ctl;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

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
 * @brief Sets DMA channel.
 * @details Sets appropriate value HW register for the desired @ref channel.
 * @param[in] dma DMA HW handle.
 * @param[in] stream DMA Stream number.
 * @param[in] channel DMA Channel number.
 * @return Nothing.
 */
static inline void hal_ll_dma_set_channel( dma_handle_t *dma, uint8_t stream, uint8_t channel );

/**
 * @brief Configures DMA access to FLASH memory.
 * @details If DMA has access to the flash memory, the function
 *          will configure the region in flash memory,
 *          where DMA read access is allowed, by setting the starting address and size
 *          starting from that address where reading is allowed.
 * @return Nothing.
 */
static void hal_ll_dma_configure_flash_access();

/**
 * @brief Gets DMA direction.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref direction.
 * @param[in] direction DMA stream direction.
 *                      Refer to @hal_ll_dma_direction_t for possible values.
 * @return uint8_t Returns actual HW register value based on @ref direction.
 */
static inline uint8_t hal_ll_dma_get_reg_value_direction( hal_ll_dma_direction_t direction );

/**
 * @brief Gets DMA peripheral address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream peripheral address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint32_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc, hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA memory address increment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref set_inc.
 * @param[in] set_inc DMA stream memory address increment.
 *                    Set to @b true in order to increment address.
 *                    Set to @b false in order to keep address the same.
 * @return uint16_t Returns actual HW register value based on @ref set_inc.
 */
static inline uint32_t hal_ll_dma_get_reg_value_src_inc( bool set_inc, hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA memory address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA stream memory address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static inline uint32_t hal_ll_dma_get_reg_value_src_size( hal_ll_dma_data_align_t align );

/**
 * @brief Gets DMA peripheral address alignment.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref align.
 * @param[in] align DMA stream peripheral address increment.
 *                  Refer to @ref hal_ll_dma_data_align_t for possible values.
 * @return uint16_t Returns actual HW register value based on @ref align.
 */
static inline uint32_t hal_ll_dma_get_reg_value_dst_size( hal_ll_dma_data_align_t align );

/**
 * @brief Sets DMA stream priority value.
 * @details Sets the appropriate value in HW register
 *          for desired @ref priority.
 * @param[in] dma DMA HW handle.
 * @param[in] stream DMA Stream number.
 * @param[in] priority DMA priority for object stream.
 *                     Refer to @ref hal_ll_dma_priority_t for possible values.
 * @return Nothing.
 */
static inline void hal_ll_dma_set_stream_priority( dma_handle_t *dma, uint8_t stream, hal_ll_dma_priority_t priority );

/**
 * @brief Gets DMA burst size value.
 * @details Returns appropriate value to be set in HW register
 *          for desired @ref burst_size.
 * @param[in] burst_size DMA burst size for channel.
 *                       Refer to @ref hal_ll_dma_burst_size_t for possible values.
 * @return uint32_t Returns actual HW register value based on @ref burst_size.
 */
static inline uint32_t hal_ll_dma_get_reg_value_burst_size( hal_ll_dma_burst_size_t burst_size );

/**
 * @brief Validates DMA flash memory access.
 * @details For transfer buffers stored in flash memory,
 *          validates that the DMA has access to flash memory.
 * @param[in] addr_src DMA source buffer address.
 * @param[in] addr_dst DMA destination buffer address.
 * @return hal_ll_err_t Returns DMA flash memory access status
 *         for transfer buffers stored in flash memory.
 */
static hal_ll_dma_err_t hal_ll_dma_check_flash_access( uint32_t addr_src, uint32_t addr_dst );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_dma_init( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;

    // Enable SYSCLK.
    _HAL_LL_ENABLE_CLOCK_SYS_;

    // Wait until the DMA module is ready for access.
    while ( !( HAL_LL_DMA_SYSCTL_PRDMA & HAL_LL_DMA_SYSCTL_PRDMA_DMA_READY) );

    obj->handle = HAL_LL_DMA_BASE_ADDR;
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 obj->config );

    if ( HAL_LL_DMA_SUCCESS != status ) {
        obj->handle = 0;  // If initialization failed, reset handle.
    }

    return status;
}

hal_ll_err_t hal_ll_dma_deinit( hal_ll_dma_t *obj ) {
    dma_handle_t * dma = (dma_handle_t *)obj->handle;
    // Disable module and module clock, only if all streams are disabled and inactive.
    if ( HAL_LL_DMA_MODULE_UNUSED == ( dma->ena_set & HAL_LL_DMA_STREAM_ENABLED_MASK ) ) {
        HAL_LL_DMA_MODULE_DISABLE;
        _HAL_LL_DISABLE_CLOCK_SYS_;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_set_mode( hal_ll_dma_t *obj, hal_ll_dma_mode_t mode ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    // Get new mode.
    hal_ll_dma_config_t cfg = obj->config;
    cfg.mode = mode;

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

    // Try to set new value.
    status = hal_ll_dma_init_hw( obj,
                                (dma_handle_t *)obj->handle,
                                 cfg );

    return status;
}

hal_ll_err_t hal_ll_dma_set_parameters( hal_ll_dma_t *obj, uint32_t addr_src, uint32_t addr_dst, size_t transfer_size, hal_ll_dma_source_memory_region_t src_mem_type ) {
    dma_handle_t *dma = ( dma_handle_t * )obj->handle;
    // Set pointer to 1024 byte aligned address inside dma_ch_ctl_buffer, where actual channel control structure data will be located.
    dma_ch_ctl = (dma_ch_ctl_struct_t *)( ( (uint32_t)dma_ch_ctl_buffer + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK ) & ~HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK );
    uint8_t transfer_size_shift_divisor = 2; // default value for HAL_LL_DMA_DATA_ALIGN_BYTES_4
    uint8_t stream = obj->config.stream;
    uint16_t endpoint_offset;

    // Memory type parameter is unused.
    (void)src_mem_type;

    // Configure DMA Stream data length.
    if ( HAL_LL_DMA_DATA_ALIGN_BYTES_4 != obj->config.data_align_destination ) {
        transfer_size_shift_divisor = obj->config.data_align_destination;
    }

    // If DMA transfer buffers are stored in flash memory, validate DMA access to the.
    if (HAL_LL_DMA_FLASH_ACCESS_OK != hal_ll_dma_check_flash_access( addr_src, addr_dst ) ) {
        // DMA does not have appropriate access to flash memory.
        return HAL_LL_DMA_ERROR;
    } else {  // Proceed with the DMA channel configuration.
        // Calculate the address offset of the last buffer item.
        endpoint_offset = transfer_size - ( 1 << transfer_size_shift_divisor );
        // Calculate the source data buffer inclusive endpoint.
        addr_src += obj->config.src_inc ? endpoint_offset : 0;
        // Calculate the destination data buffer inclusive endpoint.
        addr_dst += obj->config.dst_inc ? endpoint_offset : 0;
        // Recalculate the transfer size.
        transfer_size >>= transfer_size_shift_divisor;
        --transfer_size;

        // Write calculated endpoint addresses and transfer size into channel control structure.
        dma_ch_ctl[ stream ].ch_ctl |= (uint32_t)transfer_size << HAL_LL_DMA_DMACHTL_XFERSIZE_POSITION;
        dma_ch_ctl[ stream ].dst_endp |= addr_dst;
        dma_ch_ctl[ stream ].src_endp |= addr_src;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_start( hal_ll_dma_t *obj ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    // Set pointer to 1024 byte aligned address inside dma_ch_ctl_buffer, where actual channel control structure data will be located.
    dma_ch_ctl = (dma_ch_ctl_struct_t *)( ( (uint32_t)dma_ch_ctl_buffer + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK ) & ~HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK );
    uint8_t stream = obj->config.stream;

    // Enable the DMA stream.
    HAL_LL_DMA_STREAM_ENABLE( stream );
    // Transfer will start immediately after the channel periphery sends the request.
    if ( HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY == obj->config.direction ) {
        // in case of the M2M direction start transfer using software request.
        dma->sw_req = HAL_LL_DMA_SWREQ << stream;
    }

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_stop( hal_ll_dma_t *obj ) {
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    uint16_t timeout = DEFAULT_TIMEOUT_VALUE;
    // Set pointer to 1024 byte aligned address inside dma_ch_ctl_buffer, where actual channel control structure data will be located.
    dma_ch_ctl = (dma_ch_ctl_struct_t *)( ( (uint32_t)dma_ch_ctl_buffer + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK ) & ~HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK );

    // Wait until transfer completes.
    while ( dma_ch_ctl->ch_ctl & HAL_LL_DMA_DMACHCTL_XFERMODE_STOP ) {
        if (0 == timeout--) {
            // TODO consider forcing the stream to disable here.
            return HAL_LL_DMA_ERROR;
        }
    }
    // When transfer completes the DMA stream disables itself.

    return HAL_LL_DMA_SUCCESS;
}

hal_ll_err_t hal_ll_dma_transfer_abort( hal_ll_dma_t *obj ) {
    hal_ll_err_t status = HAL_LL_DMA_SUCCESS;
    dma_handle_t *dma = (dma_handle_t *)obj->handle;
    // Set pointer to 1024 byte aligned address inside dma_ch_ctl_buffer, where actual channel control structure data will be located.
    dma_ch_ctl = (dma_ch_ctl_struct_t *)( ( (uint32_t)dma_ch_ctl_buffer + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK ) & ~HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK );

    // Disable the stream.
    // Disabling the stream, just pauses it.
    HAL_LL_DMA_STREAM_DISABLE( obj->config.stream );
    // Stop transfer.
    dma_ch_ctl->ch_ctl &= HAL_LL_DMA_DMACHCTL_XFERMODE_STOP;

    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_err_t hal_ll_dma_init_hw( hal_ll_dma_t *obj, dma_handle_t *dma, hal_ll_dma_config_t config ) {
    // Set pointer to 1024 byte aligned address inside dma_ch_ctl_buffer, where actual channel control structure data will be located.
    dma_ch_ctl = (dma_ch_ctl_struct_t *)( ( (uint32_t)dma_ch_ctl_buffer + HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK ) & ~HAL_LL_DMA_MEMORY_ALLIGN_1024_MASK );
    uint8_t stream = config.stream;

    // Allow the DMA read access to the whole flash memory.
    hal_ll_dma_configure_flash_access();

    // Enable the DMA module.
    HAL_LL_DMA_MODULE_ENABLE;

    // Disable the DMA stream first.
    HAL_LL_DMA_STREAM_DISABLE( stream );

    // Set channel control structure address.
    dma->ctl_base = (uint32_t)dma_ch_ctl;
    // Configure DMA to use the primary channel control structure.
    dma->alt_clr = HAL_LL_DMA_ALTCLR << stream;
    // Allow both single and burst requests.
    dma->use_burst_clr = HAL_LL_DMA_USEBURSTCLR << stream;
    // Allow channel to send requests.
    dma->req_mask_clr = HAL_LL_DMA_REQMASKCLR << stream;
    // Set the desired channel.
    hal_ll_dma_set_channel( dma, stream, config.channel );
    // Set the desired priority.
    hal_ll_dma_set_stream_priority( dma, stream, config.priority );

    // Stream configuration.
    // Clear source endpoint address.
    dma_ch_ctl[ stream ].src_endp = 0;
    // Clear destination endpoint address.
    dma_ch_ctl[ stream ].dst_endp = 0;
    // Clear the stream control word.
    dma_ch_ctl[ stream ].ch_ctl = 0;

    // Set desired direction value.
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_direction( config.direction );
    // Set desired memory increment settings.
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_src_inc( config.src_inc, config.data_align_source );
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_dst_inc( config.dst_inc, config.data_align_source );

    // Set desired data size settings.
    if ( config.data_align_source != config.data_align_destination ) {
        // Source and Destination Data sizes must be equal.
        return HAL_LL_DMA_ERROR;
    }
    if ( ( HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_source ) || ( HAL_LL_DMA_DATA_ALIGN_BYTES_3 == config.data_align_destination ) ) {
        // Source and Destination Data sizes cannot be 3 bytes.
        return HAL_LL_DMA_ERROR;
    }
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_src_size( config.data_align_source );
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_dst_size( config.data_align_source );

    // Set desired burst transfer settings.
    if ( config.burst_size_source != config.burst_size_destination ) {
        // No multiple burst on TIVA.
        return HAL_LL_DMA_ERROR;
    }
    // TODO On TIVA burst size can go up to 1024. Consider adding more enums to cover all of them.
    dma_ch_ctl[ stream ].ch_ctl |= hal_ll_dma_get_reg_value_burst_size( config.burst_size_source );

    // Set desired mode.
    if ( HAL_LL_DMA_MODE_CIRCULAR == config.mode ) {
        // TODO Implement circular mode later, during DMA peripheral synthesis.
        /* NOTE: Channel control structure register do not posses the auto-reloading functionality,
         *       therefore they must be reloaded by software in interrupt routine.
         *       The DMA ISR is not used for this, instead the ISR form the peripheral that is using the DMA is used.
         */
        return HAL_LL_DMA_ERROR;
    }

    return HAL_LL_DMA_SUCCESS;
}

static inline void hal_ll_dma_set_channel( dma_handle_t *dma, uint8_t stream, uint8_t channel ) {
    dma->ch_map[ (uint8_t)( stream >> 3 ) ] |= (uint32_t)( channel << (uint8_t)( ( stream & 0x7 ) << 2 ) ) ;
}

static void hal_ll_dma_configure_flash_access() {
    // If DMA has access to flash memory.
    if ( HAL_LL_DMA_HAS_FLASH_ACCESS ) {
        // Clear the DMA flash access address, and at the same time indirectly set DMA starting access address to 0x00000000UL.
        HAL_LL_DMA_FLASHDMAST &= ~HAL_LL_DMA_FLASHDMAST_ADDR_MASK;
        // Clear DMA flash access size.
        HAL_LL_DMA_FLASHDMASZ &= ~HAL_LL_DMA_FLASHDMASZ_SIZE_MASK;
        // Set DMA access to whole flash memory.
        HAL_LL_DMA_FLASHDMASZ |= ( HAL_LL_DMA_FLASH_SIZE ) << HAL_LL_DMA_FLASHDMASZ_SIZE_POSITION;
    }
}

static inline uint8_t hal_ll_dma_get_reg_value_direction( hal_ll_dma_direction_t direction ) {
    volatile uint32_t direction_set = HAL_LL_DMA_DMACHCTL_XFERMODE_BASIC;

    // For M2M direction AUTO mode is used, and for all other directions, BASIC mode is used.
    if ( HAL_LL_DMA_DIRECTION_MEMORY_TO_MEMORY == direction ) {
        direction_set = HAL_LL_DMA_DMACHCTL_XFERMODE_AUTO_REQUEST;
    }

    return direction_set;
}

static inline uint32_t hal_ll_dma_get_reg_value_dst_inc( bool set_inc, hal_ll_dma_data_align_t align ) {
    volatile uint32_t dst_inc = HAL_LL_DMA_DMACHTL_DSTINC_NO_INCREMENT;

    if ( set_inc ) {
        switch ( align ) {
            case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Source address increment. Data is 1 byte.
            dst_inc = HAL_LL_DMA_DMACHTL_DSTINC_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Source address increment. Data is halfword.
            dst_inc = HAL_LL_DMA_DMACHTL_DSTINC_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Source address increment. Data is word.
            dst_inc = HAL_LL_DMA_DMACHTL_DSTINC_WORD;
            break;

        default:
            break;
        }
    }

    return dst_inc;
}

static inline uint32_t hal_ll_dma_get_reg_value_src_inc( bool set_inc, hal_ll_dma_data_align_t align ) {
    volatile uint32_t src_inc = HAL_LL_DMA_DMACHTL_SRCINC_NO_INCREMENT;

    if ( set_inc ) {
        switch ( align ) {
            case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Source address increment. Data is 1 byte.
            src_inc = HAL_LL_DMA_DMACHTL_SRCINC_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Source address increment. Data is halfword.
            src_inc = HAL_LL_DMA_DMACHTL_SRCINC_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Source address increment. Data is word.
            src_inc = HAL_LL_DMA_DMACHTL_SRCINC_WORD;
            break;

        default:
            break;
        }
    }

    return src_inc;
}

static inline uint32_t hal_ll_dma_get_reg_value_src_size( hal_ll_dma_data_align_t align ) {
    volatile uint32_t align_set;

    switch ( align ) {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Data is 1 byte.
            align_set =  HAL_LL_DMA_DMACHTL_SRCSIZE_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Data is halfword.
            align_set = HAL_LL_DMA_DMACHTL_SRCSIZE_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Data is word.
            align_set = HAL_LL_DMA_DMACHTL_SRCSIZE_WORD;
            break;

        default:
            break;
        }

    return align_set;
}

static inline uint32_t hal_ll_dma_get_reg_value_dst_size( hal_ll_dma_data_align_t align ) {
    volatile uint32_t align_set;

    switch ( align ) {
        case HAL_LL_DMA_DATA_ALIGN_BYTES_1:
            // Data is 1 byte.
            align_set =  HAL_LL_DMA_DMACHTL_DSTSIZE_BYTE;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_2:
            // Data is halfword.
            align_set = HAL_LL_DMA_DMACHTL_DSTSIZE_HALF_WORD;
            break;
        case HAL_LL_DMA_DATA_ALIGN_BYTES_4:
            // Data is word.
            align_set = HAL_LL_DMA_DMACHTL_DSTSIZE_WORD;
            break;

        default:
            break;
        }

    return align_set;
}

static inline void hal_ll_dma_set_stream_priority( dma_handle_t *dma, uint8_t stream, hal_ll_dma_priority_t priority ) {
    switch ( priority ) {
        case HAL_LL_DMA_PRIORITY_LOW:
        case HAL_LL_DMA_PRIORITY_MEDIUM:
            dma->prio_clr = HAL_LL_DMA_PRIOCLR << stream;
            break;
        case HAL_LL_DMA_PRIORITY_HIGH:
        case HAL_LL_DMA_PRIORITY_VERY_HIGH:
            dma->prio_set = HAL_LL_DMA_PRIOSET << stream;
            break;

        default:
            break;
    }
}

static inline uint32_t hal_ll_dma_get_reg_value_burst_size( hal_ll_dma_burst_size_t burst_size ) {
    return ((uint32_t)burst_size << HAL_LL_DMA_DMACHTL_ARBSIZE_POSITION);
}

static hal_ll_dma_err_t hal_ll_dma_check_flash_access( uint32_t addr_src, uint32_t addr_dst ) {
    uint32_t flash_memory_end = ( ( HAL_LL_DMA_FLASH_SIZE + 1 ) << 11 ) - 1;

    // Check whether destination address is in FLASH memory.
    if ( addr_dst <= flash_memory_end ) {
        // DMA does not have write access to FLASH memory.
        return HAL_LL_DMA_ERROR;
    }

    // Check whether source address is in FLASH memory.
    if ( addr_src <= flash_memory_end ) {
        if ( !HAL_LL_DMA_HAS_FLASH_ACCESS ) {
            // DMA does not have access to FLASH memory.
            return HAL_LL_DMA_ERROR;
        }
    }

    return HAL_LL_DMA_SUCCESS;
}

// ------------------------------------------------------------------------- END
