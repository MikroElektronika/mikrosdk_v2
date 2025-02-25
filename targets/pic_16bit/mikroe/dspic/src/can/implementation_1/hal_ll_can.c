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
 * @file  hal_ll_can.c
 * @brief CAN HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_can.h"
#include "hal_ll_gpio.h"
#include "hal_ll_can_pin_map.h"
#include "hal_ll_pps.h"

#ifdef __XC16__
// Note: Added for XC16 implementation.
#include "mcu.h"
#endif

/*!< @brief Local handle list */
static volatile hal_ll_can_handle_register_t hal_ll_module_state[CAN_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_can_get_module_state_address ((hal_ll_can_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_can_get_handle (hal_ll_can_handle_register_t *)hal_ll_can_get_module_state_address->hal_ll_can_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_can_get_base_struct(_handle) ((hal_ll_can_base_handle_t *)_handle)
#define hal_ll_can_get_buffer_base_struct(_handle) ((hal_ll_can_buffer_base_handle_t *)_handle)
#define hal_ll_can_get_filter_base_struct(_handle) ((hal_ll_can_filter_base_handle_t *)_handle)
#define hal_ll_can_get_rx_tx_memory_slot_struct(_handle) ((hal_ll_rx_tx_buffer_regs_t *)_handle)
#define hal_ll_can_get_dma_base_struct(_handle) ((hal_ll_dma_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_can_get_base_from_hal_handle ((hal_ll_can_hw_specifics_map_t *)((hal_ll_can_handle_register_t *)\
                                            (((hal_ll_can_handle_register_t *)(handle))->hal_ll_can_handle))->hal_ll_can_handle)->base
#define hal_ll_get_fosc_clock_value (Get_Fosc_kHz()/1000)
#define hal_ll_get_actual_baud_rate(temp) (1000000/temp)
#define hal_ll_can_get_brg_element_mask(element, offset) (((uint16_t)(element - 1)) << offset)
/*!< @brief Helper macro for getting values for filter mask registers */
#define hal_ll_can_get_rxmsid_value(mask_32) (((mask_32 & 0x000007FF) << 5U | (mask_32 & 0x18000000) >> 27U))
#define hal_ll_can_get_rxmeid_value(mask_32) (((mask_32 & 0x07FFF800) >> 11U))
#define hal_ll_can_set_bufpnt(offset,ptr,fifo) (fifo << ((offset - 1 * ptr) * 4))
#define hal_ll_can_set_msksel(msk,fifo) (msk << (fifo * 2))
#define hal_ll_can_get_bufpnt_num(filter_num) (filter_num/4)
#define hal_ll_can_get_msksel_num(filter_num) (filter_num/8)

/*!< @brief DMA constants and register bits and masks */
#define HAL_LL_DMA_CNT_CAN1_RX_INTERRUPT_MASK (34)
#define HAL_LL_DMA_CNT_CAN2_RX_INTERRUPT_MASK (55)
#define HAL_LL_DMA_CNT_CAN1_TX_INTERRUPT_MASK (70)
#define HAL_LL_DMA_CNT_CAN2_TX_INTERRUPT_MASK (71)
#define HAL_LL_DMA_CNT_DATA_BLOCK_SIZE        (0x0007)
#define HAL_LL_DMA_CON_RX_CONFIG_MASK         (0x0020)
#define HAL_LL_DMA_CON_TX_CONFIG_MASK         (0x2020)
#define HAL_LL_DMA_CON_RX_ENABLE_MASK         (0x8020)
#define HAL_LL_DMA_CON_TX_ENABLE_MASK         (0xA020)
#define HAL_LL_FCTRL_CONFIGURATION_MASK       (0xC01F)
/*!< @brief CAN baudrate constants and register bits and masks */
#define HAL_LL_CAN_BRG_PRESCALER_OFFSET       (0)
#define HAL_LL_CAN_BRG_PRSEG_OFFSET           (0)
#define HAL_LL_CAN_BRG_SJW_VALUE              (1)
#define HAL_LL_CAN_BRG_PSEG1_OFFSET           (3)
#define HAL_LL_CAN_BRG_SJW_OFFSET             (6)
#define HAL_LL_CAN_BRG_PSEG2_OFFSET           (8)
#define HAL_LL_CAN_BRG_MAX_PSEG1_VALUE        (8)
#define HAL_LL_CAN_BRG_MAX_PRSEG_VALUE        (8)
#define HAL_LL_CAN_BRG_MAX_PSEG2_VALUE        (8)
#define HAL_LL_CAN_BRG_CLOCK_SELECTION_BIT    (11)
#define HAL_LL_CAN_MAXIMUM_FREQUENCY          (40)
#define HAL_LL_CAN_BRG_MAX_PRESCALER_VALUE    (64)
#define HAL_LL_CAN_BRGCON2_SEG2PHTS_MASK      (0x80)
/*!< @brief CAN control and status register bits */
#define HAL_LL_CAN_CTRL_WIN_BIT               (0)
#define HAL_LL_CAN_TXREQ_BIT                  (3)
#define HAL_LL_CAN_CTRL_NORMAL_MASK           (0x000)
#define HAL_LL_CAN_CTRL_OP_NORMAL_MASK        (0x000)
#define HAL_LL_CAN_CTRL_OP_DISABLE_MASK       (0x020)
#define HAL_LL_CAN_CTRL_OP_LOOPBACK_MASK      (0x040)
#define HAL_LL_CAN_CTRL_OP_LISTENONLY_MASK    (0x060)
#define HAL_LL_CAN_CTRL_OP_CONFIG_MASK        (0x080)
#define HAL_LL_CAN_CTRL_OPMODE_MASK           (0x0E0)
#define HAL_LL_CAN_CTRL_OP_LISTENALL_MASK     (0x0E0)
#define HAL_LL_CAN_CTRL_DISABLE_MASK          (0x100)
#define HAL_LL_CAN_CTRL_LOOPBACK_MASK         (0x200)
#define HAL_LL_CAN_CTRL_LISTENONLY_MASK       (0x300)
#define HAL_LL_CAN_CTRL_CONFIG_MASK           (0x400)
#define HAL_LL_CAN_CTRL_REQOP_MASK            (0x700)
#define HAL_LL_CAN_MODE_LISTENALL_MASK        (0x700)
/*!< @brief CAN filter constants and register bits and masks */
#define HAL_LL_CAN_FILTER_MASK_COUNT          (3)
#define HAL_LL_FILTER_NUMBER                  (16)
/*!< @brief CAN transmit constatns, registers bits and masks */
#define HAL_LL_CAN_TX_FIFO_IDE_BIT            (0)
#define HAL_LL_CAN_TX_FIFO_SRR_BIT            (1)
#define HAL_LL_CAN_TX_FIFO_STDID_OFFSET       (2)
#define HAL_LL_CAN_TX_EID_EID_OFFSET          (7)
#define HAL_LL_CAN_TX_FIFO_RTR_BIT            (9)
#define HAL_LL_CAN_TX_DLC_EID_OFFSET          (11)
#define HAL_LL_CAN_TR01CON_CONFIG_MASK        (0x83)
#define HAL_LL_CAN_TX_FIFO_STDID_MASK         (0x7FF)
#define HAL_LL_CAN_TX_DLC_EID_MASK            (0x1F800UL)
#define HAL_LL_CAN_TX_EID_EID_MASK            (0x1FFE0000UL)
/*!< @brief CAN receive FIFO constants, register bits and masks */
#define HAL_LL_CAN_RX_SID_OFFSET              (2)
#define HAL_LL_CAN_RX_DLC_EID_OFFSET          (10)
#define HAL_LL_CAN_RX_EID_EID_OFFSET          (17)
#define HAL_LL_CAN_RX_DLC_DLC_MASK            (0x000F)
#define HAL_LL_CAN_RX_DLC_EID_MASK            (0xFC00)
#define HAL_LL_CAN_RX_SID_MASK                (0x1FFC)
/*!< @brief Byte offset macros */
#define HAL_LL_CAN_BYTE_OFFSET_1              (8U)
#define HAL_LL_CAN_BYTE_OFFSET_2              (16U)
/*!< @brief Helper macro for defining timout value */
#define HAL_LL_CAN_TIMEOUT_VALUE 10000UL

/*!< @brief CAN filter register structure used for storing configured filter masks. */
typedef struct
{
    uint32_t mask;
    uint8_t filter_to_mask_map;
    bool configured;
} hal_ll_can_hw_filter_mask_t;

/*!< @brief CAN hw specific structure. */
typedef struct
{
    hal_ll_base_addr_t base;
    hal_ll_base_addr_t alternate_base;
    hal_ll_base_addr_t dma_base;
    hal_ll_pin_name_t module_index;
    hal_ll_can_pins_t pins;
    hal_ll_can_mode_t mode;
    uint32_t frequency;
} hal_ll_can_hw_specifics_map_t;

/*!< @brief DMA channel registers structure. */
typedef struct
{
    hal_ll_base_addr_t con;         /* Control register. */
    hal_ll_base_addr_t req;         /* IRQ select register. */
    #ifdef dsPIC33FJ_FAMILY
    hal_ll_base_addr_t sta;         /* RAM start address offset register A. */
    hal_ll_base_addr_t stb;         /* RAM start address offset register B. */
    #elif defined dsPIC33EP_FAMILY
    hal_ll_base_addr_t stal;        /* RAM start address offset low register A. */
    hal_ll_base_addr_t stah;        /* RAM start address offset high register A. */
    hal_ll_base_addr_t stbl;        /* RAM start address offset low register B. */
    hal_ll_base_addr_t stbh;        /* RAM start address offset high register B. */
    #endif
    hal_ll_base_addr_t pad;         /* Peripheral address register. */
    hal_ll_base_addr_t cnt;         /* Transfer count register. */
} hal_ll_dma_regs;

/*!< @brief DMA hw register structure. */
typedef struct
{
    #ifdef dsPIC33FJ_FAMILY
    hal_ll_dma_regs dma_regs[8];    /* DMA channel registers. */
    hal_ll_base_addr_t cs0;         /* Controller status register 0. */
    hal_ll_base_addr_t cs1;         /* Controller status register 1. */
    hal_ll_base_addr_t dsadr;       /* Most recent DMA data space address register. */
    #elif defined dsPIC33EP_FAMILY
    hal_ll_dma_regs dma_regs[15];   /* DMA channel registers. */
    hal_ll_base_addr_t pwc;         /* Peripheral write collision status register. */
    hal_ll_base_addr_t rqc;         /* Request collision status register. */
    hal_ll_base_addr_t pps;         /* Ping-Pong status register. */
    hal_ll_base_addr_t lca;         /* Last channel active bit. */
    hal_ll_base_addr_t dsadrl;      /* Most recent DMA data space low address register. */
    hal_ll_base_addr_t dsadrh;      /* Most recent DMA data space high address register. */
    #endif
} hal_ll_dma_base_handle_t;

/*!< @brief CAN hw specific module values. */
typedef struct
{
    hal_ll_pin_name_t pin_tx;
    hal_ll_pin_name_t pin_rx;
} hal_ll_can_pin_id;

/*!< @brief CAN acceptance filter specific structure. */
typedef struct
{
    hal_ll_base_addr_t rxfsid;         /*!< Acceptance filter standard identifier. */
    hal_ll_base_addr_t rxfeid;         /*!< Acceptance filter extended identifier. */
} hal_ll_acceptance_filters_regs;

/*!< @brief CAN acceptance mask specific structure. */
typedef struct
{
    hal_ll_base_addr_t sid;        /*!< Acceptance filter mask standard id register. */
    hal_ll_base_addr_t eid;        /*!< Acceptance filter mask extended id register. */
} hal_ll_acceptance_mask_regs;

/*!< @brief CAN filter specific registers. */
typedef struct
{
    hal_ll_base_addr_t bufpnt[4];        /*!< Filter buffer pointer register. */
    hal_ll_base_addr_t __unused1[4];
    hal_ll_acceptance_mask_regs mask[3];
    hal_ll_base_addr_t __unused2[2];
    hal_ll_acceptance_filters_regs acceptance_filters[16];
} hal_ll_can_filter_base_handle_t;

/*!< @brief CAN FIFO specific registers. */
typedef struct
{
    hal_ll_base_addr_t sid;     /*!< Word 0 register. */
    hal_ll_base_addr_t eid;     /*!< Word 1 register. */
    hal_ll_base_addr_t dlc;     /*!< Word 2 register. */
    hal_ll_base_addr_t data0;   /*!< Word 3 register. */
    hal_ll_base_addr_t data1;   /*!< Word 4 register. */
    hal_ll_base_addr_t data2;   /*!< Word 5 register. */
    hal_ll_base_addr_t data3;   /*!< Word 6 register. */
    hal_ll_base_addr_t flhit;   /*!< Word 7 register. */
} hal_ll_rx_tx_buffer_regs_t;

/*!< CAN buffer configuration specific registers. */
typedef struct
{
    hal_ll_base_addr_t rxful1;          /*!< Receive buffer full register 1. */
    hal_ll_base_addr_t rxful2;          /*!< Receive buffer full register 2. */
    hal_ll_base_addr_t __unused1[2];
    hal_ll_base_addr_t rxovf1;          /*!< Receive buffer overflow register 1. */
    hal_ll_base_addr_t rxovf2;          /*!< Receive buffer overflow register 2. */
    hal_ll_base_addr_t __unused2[2];
    hal_ll_base_addr_t tr01con;         /*!< TX/RX buffer 0 control register. */
    hal_ll_base_addr_t tr23con;         /*!< TX/RX buffer 2 control register. */
    hal_ll_base_addr_t tr45con;         /*!< TX/RX buffer 4 control register. */
    hal_ll_base_addr_t tr67con;         /*!< TX/RX buffer 6 control register. */
    hal_ll_base_addr_t __unused3[4];
    hal_ll_base_addr_t rxd;             /*!< Receive data register. */
    hal_ll_base_addr_t txd;             /*!< Transmit data register. */
} hal_ll_can_buffer_base_handle_t;

/*!< @brief CAN hw register structure. */
typedef struct
{
    hal_ll_base_addr_t ctrl1;     /*!< Module control register 1. */
    hal_ll_base_addr_t ctrl2;     /*!< Module control register 2. */
    hal_ll_base_addr_t vec;       /*!< Interrupt code register. */
    hal_ll_base_addr_t fctrl;     /*!< FIFO control register. */
    hal_ll_base_addr_t fifo;      /*!< FIFO statis register. */
    hal_ll_base_addr_t intf;      /*!< Interrupt flag register. */
    hal_ll_base_addr_t inte;      /*!< Interrupt enable register. */
    hal_ll_base_addr_t ec;        /*!< Transmit/receive error count. */
    hal_ll_base_addr_t cfg1;      /*!< Baudrate configuration register 1. */
    hal_ll_base_addr_t cfg2;      /*!< Baudrate configuration register 2. */
    hal_ll_base_addr_t fen1;      /*!< Acceptance filter enable register. */
    hal_ll_base_addr_t __unused1;
    hal_ll_base_addr_t fmsksel[2];  /*!< Filter mask selection register. */
} hal_ll_can_base_handle_t;

/*!< @brief CAN hw specific error values. */
typedef enum
{
    HAL_LL_CAN_SUCCESS = 0,
    HAL_LL_CAN_WRONG_PINS,
    HAL_LL_CAN_MODULE_ERROR,

    HAL_LL_CAN_ERROR = (-1)
} hal_ll_can_err_t;
// ------------------------------------------------------------------ VARIABLES
/*!< @brief CAN hardware specific info */
static hal_ll_can_hw_specifics_map_t hal_ll_can_hw_specifics_map[] =
{
    #ifdef CAN_MODULE_1
    { HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_ALTERNATE_BASE_ADDRESS, HAL_LL_DMA_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_1 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 125000 },
    #endif
    #ifdef CAN_MODULE_2
    { HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_ALTERNATE_BASE_ADDRESS, HAL_LL_DMA_BASE_ADDRESS, hal_ll_can_module_num( CAN_MODULE_2 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 125000 },
    #endif
    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, HAL_LL_CAN_MODE_NORMAL, 125000 }
};


/*!< @brief Global handle variables used in functions */
static volatile hal_ll_can_handle_register_t *low_level_handle;
static volatile hal_ll_can_hw_specifics_map_t *hal_ll_can_hw_specifics_map_local;
/*!< @brief Global flag for initializing the filter. */
bool filter_funtion_default_config = true;
/*!< @brief Global variable for tracking the filter mask definition. */
hal_ll_can_hw_filter_mask_t hal_ll_can_filter_mask[3];
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Check if pins are adequate.
 *
 * Checks tx and rx pins the user has passed with pre-defined
 * pins in tx and rx maps. Take into consideration that module
 * index numbers have to be the same for both pins.
 *
 * @param[in]  tx_pin - TX pre-defined pin name.
 * @param[in]  rx_pin - RX pre-defined pin name.
 * @param[in]  *index_list - Index list address
 * @param[in]  *handle_map - HAL low level context object handle.
 * @return hal_ll_pin_name_t Module index based on pins.
 *
 * Returns pre-defined module index from pin maps, if pins
 * are adequate.
 */
static hal_ll_pin_name_t hal_ll_can_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                hal_ll_can_pin_id *index_list, hal_ll_can_handle_register_t *handle_map );

/**
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * CAN TX and RX pins.
 *
 * @param[in]  module_index CAN HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TX and RX map index values
 *                          and module number
 *
 * @return  None
 */
static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list );

/**
 * @brief Get local hardware specific map.
 *
 * Checks handle value and returns address of adequate
 * hal_ll_can_hw_specifics_map array index.
 *
 * @param[in]  handle - Object specific context handler.
 * @return hal_ll_can_hw_specifics_map_t Map address.
 *
 * Returns pre-defined map index address based on handle value,
 * if handle is adequate.
 */
static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
 * @brief Full CAN module initialization procedure.
 *
 * Initializes CAN module on hardware level, based on beforehand
 * set configuration and module handler. Sets control and filter registers.
 * Initializes module clock.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @param[in]  filter_config - CAN filter config structure.
 * @param[in]  default_config - CAN filter config flag.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config );

/**
 * @brief Calculates parameters for desired CAN frequency.
 *
 * Calculates adequate values to be written in CAN_BTR register
 * in order to set appropriate baud rate.
 *
 * @param[in]  map - Object specific context handler.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map );

/**
 * @brief Initialize CAN module on hardware level.
 *
 * Initializes CAN module on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config );

/**
 * @brief Configure CAN filter.
 *
 * Initializes CAN filter on hardware level, based on beforehand
 * set configuration and module handler.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  filter_config - CAN filter config structure.
 * @param[in]  default_config - CAN filter config flag.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config );

/**
 * @brief Configure DMA controller for CAN module.
 *
 * Configures DMA RAM for CAN buffers and DMA channel for ECAN reception.
 *
 * DMA0 channel is used for transmission (DMA RAM to peripheral)
 * DMA1 channel is used for reception (peripheral to DMA RAM)
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return None
 */
static void hal_ll_can_dma_configure( hal_ll_can_hw_specifics_map_t *map );

/**
 * @brief  Set PPS state.
 *
 * Sets adequate RPINRx and RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Set operation mode.
 *
 * Sets an operation mode requested by user.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  config - CAN config structure.
 * @return hal_ll_err_t Module specific values.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_can_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_can_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_can_pin_id index_list[CAN_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_can_check_pins( tx_pin, rx_pin, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_CAN_WRONG_PINS;
    };

    if (( hal_ll_can_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin ) ||
        ( hal_ll_can_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin ))
    {
        // Used only for chips that have CAN PPS pins.
        #if HAL_LL_CAN_PPS_ENABLED == true
        if ( HAL_LL_CAN_SUCCESS != hal_ll_pps_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], false ))
            return HAL_LL_CAN_WRONG_PINS;
        #endif

        hal_ll_can_map_pins( pin_check_result, &index_list );

        // Used only for chips that have CAN PPS pins.
        #if HAL_LL_CAN_PPS_ENABLED == true
        if ( HAL_LL_CAN_SUCCESS != hal_ll_pps_set_state( &hal_ll_can_hw_specifics_map[ pin_check_result ], true ))
            return HAL_LL_CAN_WRONG_PINS;
        #endif

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_can_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_can_handle;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_init( handle_t *handle, hal_ll_can_config_t *config,
                              hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_handle_register_t *hal_handle = (hal_ll_can_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_can_hw_specifics_map_local->module_index;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config ))
        return HAL_LL_CAN_ERROR;

    hal_ll_module_state[pin_check_result].hal_ll_can_handle = (handle_t *)&hal_ll_can_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_filter( handle_t *handle, hal_ll_can_config_t *config,
                                    hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    low_level_handle->init_ll_state = false;
    if ( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_local, filter_config, false ))
        return HAL_LL_CAN_ERROR;

    low_level_handle->init_ll_state = true;

    return HAL_LL_CAN_SUCCESS;
}

hal_ll_err_t hal_ll_can_set_frequency( handle_t *handle, hal_ll_can_config_t *config,
                                       hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    uint32_t original_frequency;
    hal_ll_err_t result;

    low_level_handle->init_ll_state = false;

    original_frequency = hal_ll_can_hw_specifics_map_local->frequency;

    hal_ll_can_hw_specifics_map_local->frequency = config->frequency;
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    // In case the desired frequency setting hasn't been achieved, there's no need to update the map.
    if( HAL_LL_CAN_SUCCESS != result )
        hal_ll_can_hw_specifics_map_local->frequency = original_frequency;

    low_level_handle->init_ll_state = true;

    return result;
}

hal_ll_err_t hal_ll_can_get_frequency( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    return hal_ll_can_hw_specifics_map_local->frequency;
}

hal_ll_err_t hal_ll_can_set_mode( handle_t *handle, hal_ll_can_config_t *config,
                                  hal_ll_can_filter_config_t *filter_config ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_err_t result;

    low_level_handle->init_ll_state = false;

    // NOTE: Changing mode won't result in an error, so saving the previous value is not needed.
    hal_ll_can_hw_specifics_map_local->mode = config->mode;
    result = hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_local, config, filter_config );

    low_level_handle->init_ll_state = true;

    return result;
}

hal_ll_err_t hal_ll_can_get_mode( handle_t *handle ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );

    return hal_ll_can_hw_specifics_map_local->mode;
}

hal_ll_err_t hal_ll_can_transmit( handle_t *handle, hal_ll_can_transmit_message_struct *transmit_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_can_get_module_state_address );
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( hal_ll_can_hw_specifics_map_local->base );
    hal_ll_can_buffer_base_handle_t *hal_ll_buffer_hw_reg = hal_ll_can_get_buffer_base_struct( hal_ll_can_hw_specifics_map_local->alternate_base );
    hal_ll_rx_tx_buffer_regs_t *CANMsgBuf = hal_ll_can_get_rx_tx_memory_slot_struct( HAL_LL_DMA_RAM_TX_ADDRESS );
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Use buffer registers.
    clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );

    // Clear the TX buffer.
    clear_reg( &CANMsgBuf->sid );
    clear_reg( &CANMsgBuf->eid );
    clear_reg( &CANMsgBuf->dlc );
    clear_reg( &CANMsgBuf->data0 );
    clear_reg( &CANMsgBuf->data1 );
    clear_reg( &CANMsgBuf->data2 );
    clear_reg( &CANMsgBuf->data3 );

    CANMsgBuf->sid = (( transmit_message->message.id & HAL_LL_CAN_TX_FIFO_STDID_MASK ) << HAL_LL_CAN_TX_FIFO_STDID_OFFSET );
    CANMsgBuf->dlc = (( transmit_message->message.id & HAL_LL_CAN_TX_DLC_EID_MASK ) >> HAL_LL_CAN_TX_DLC_EID_OFFSET );
    CANMsgBuf->eid = (( transmit_message->message.id & HAL_LL_CAN_TX_EID_EID_MASK ) >> HAL_LL_CAN_TX_EID_EID_OFFSET );

    // Set an appropriate frame format of the message.
    if ( HAL_LL_CAN_FRAME_FORMAT_STANDARD_11BITS == transmit_message->message.frame_format )
        clear_reg_bit( &CANMsgBuf->sid, HAL_LL_CAN_TX_FIFO_IDE_BIT );
    else
        set_reg_bit( &CANMsgBuf->sid, HAL_LL_CAN_TX_FIFO_IDE_BIT );

    // Set an appropriate frame type of the message.
    if ( HAL_LL_CAN_FRAME_TYPE_DATA == transmit_message->message.frame_format )
        clear_reg_bit( &CANMsgBuf->sid, HAL_LL_CAN_TX_FIFO_SRR_BIT );
    else {
        set_reg_bit( &CANMsgBuf->sid, HAL_LL_CAN_TX_FIFO_SRR_BIT );
        set_reg_bit( &CANMsgBuf->dlc, HAL_LL_CAN_TX_FIFO_RTR_BIT );
    }

    CANMsgBuf->dlc |= ( transmit_message->message.data_len );

    CANMsgBuf->data0 = ( transmit_message->message.message_data[1] << HAL_LL_CAN_BYTE_OFFSET_1 ) | transmit_message->message.message_data[0];
    CANMsgBuf->data1 = ( transmit_message->message.message_data[3] << HAL_LL_CAN_BYTE_OFFSET_1 ) | transmit_message->message.message_data[2];
    CANMsgBuf->data2 = ( transmit_message->message.message_data[5] << HAL_LL_CAN_BYTE_OFFSET_1 ) | transmit_message->message.message_data[4];
    CANMsgBuf->data3 = ( transmit_message->message.message_data[7] << HAL_LL_CAN_BYTE_OFFSET_1 ) | transmit_message->message.message_data[6];

    // Request transmission.
    set_reg_bit( &hal_ll_buffer_hw_reg->tr01con, HAL_LL_CAN_TXREQ_BIT );
    // Check if transmission is acknowledged.
    while ( check_reg_bit( &hal_ll_buffer_hw_reg->tr01con, HAL_LL_CAN_TXREQ_BIT )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

void hal_ll_can_transmission_stop( handle_t *handle ) {
    hal_ll_can_buffer_base_handle_t *hal_ll_buffer_hw_reg = hal_ll_can_get_buffer_base_struct( hal_ll_can_hw_specifics_map_local->alternate_base );

    if ( check_reg_bit( &hal_ll_buffer_hw_reg->tr01con, HAL_LL_CAN_TXREQ_BIT ))
        clear_reg_bit( &hal_ll_buffer_hw_reg->tr01con, HAL_LL_CAN_TXREQ_BIT );
}

hal_ll_err_t hal_ll_can_receive( handle_t *handle, hal_ll_can_receive_message_struct *receive_message ) {
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( hal_ll_can_hw_specifics_map_local->base );
    hal_ll_can_buffer_base_handle_t *hal_ll_buffer_hw_reg = hal_ll_can_get_buffer_base_struct( hal_ll_can_hw_specifics_map_local->alternate_base );
    uint8_t rx_fifo_num = receive_message->rx_fifo_number;
    uint16_t rx_fifo_address = HAL_LL_DMA_RAM_TX_ADDRESS + sizeof( hal_ll_rx_tx_buffer_regs_t ) * rx_fifo_num;
    hal_ll_rx_tx_buffer_regs_t *CANMsgBuf = hal_ll_can_get_rx_tx_memory_slot_struct( rx_fifo_address );
    uint32_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Use buffer registers.
    clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );

    // FIFO0 is used for transmission and FIFO31 is the highest RX FIFO.
    if (( HAL_LL_CAN_FILTER_FIFO0 == rx_fifo_num ) || ( HAL_LL_CAN_FILTER_FIFO31 < rx_fifo_num ))
        return HAL_LL_CAN_ERROR;

    if ( HAL_LL_CAN_FILTER_FIFO16 > rx_fifo_num ) {
        while ( !check_reg_bit( &hal_ll_buffer_hw_reg->rxful1, rx_fifo_num )) {
            if( 0 == timeout-- )
                return HAL_LL_CAN_ERROR;
        }
    } else {
        while ( !check_reg_bit( &hal_ll_buffer_hw_reg->rxful2, rx_fifo_num - 16 )) {
            if( 0 == timeout-- )
                return HAL_LL_CAN_ERROR;
        }
    }

    receive_message->message.id = ( CANMsgBuf->sid & HAL_LL_CAN_RX_SID_MASK ) >> HAL_LL_CAN_RX_SID_OFFSET;
    receive_message->message.id |= ( CANMsgBuf->dlc & HAL_LL_CAN_RX_DLC_EID_MASK ) << HAL_LL_CAN_RX_DLC_EID_OFFSET;
    receive_message->message.id |= CANMsgBuf->eid << HAL_LL_CAN_RX_EID_EID_OFFSET;
    receive_message->message.data_len = CANMsgBuf->dlc & HAL_LL_CAN_RX_DLC_DLC_MASK;
    receive_message->message.message_data[0] = CANMsgBuf->data0;
    receive_message->message.message_data[1] = CANMsgBuf->data0 >> HAL_LL_CAN_BYTE_OFFSET_1;
    receive_message->message.message_data[2] = CANMsgBuf->data1;
    receive_message->message.message_data[3] = CANMsgBuf->data1 >> HAL_LL_CAN_BYTE_OFFSET_1;
    receive_message->message.message_data[4] = CANMsgBuf->data2;
    receive_message->message.message_data[5] = CANMsgBuf->data2 >> HAL_LL_CAN_BYTE_OFFSET_1;
    receive_message->message.message_data[6] = CANMsgBuf->data3;
    receive_message->message.message_data[7] = CANMsgBuf->data3 >> HAL_LL_CAN_BYTE_OFFSET_1;

    // Clear RXFUL to allow CAN to load new messages.
    if ( HAL_LL_CAN_FILTER_FIFO16 > rx_fifo_num )
        clear_reg_bit( &hal_ll_buffer_hw_reg->rxful1, rx_fifo_num );
    else
        clear_reg_bit( &hal_ll_buffer_hw_reg->rxful2, rx_fifo_num - HAL_LL_CAN_BYTE_OFFSET_2 );

    return HAL_LL_CAN_SUCCESS;
}


hal_ll_err_t hal_ll_can_close( handle_t *handle ) {
    low_level_handle = hal_ll_can_get_handle;
    hal_ll_can_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_can_get_module_state_address);

    if( low_level_handle->hal_ll_can_handle != NULL ) {
        hal_ll_can_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.tx_pin.pin_pps = HAL_LL_PPS_FUNCTIONALITY_NONE;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_can_hw_specifics_map_local->pins.rx_pin.pin_pps = HAL_LL_PPS_FUNCTIONALITY_NONE;

        hal_ll_can_hw_specifics_map_local->frequency = 125000UL;

        low_level_handle->hal_ll_can_handle = NULL;
        low_level_handle->hal_drv_can_handle = NULL;

        low_level_handle->init_ll_state = false;

        return HAL_LL_CAN_SUCCESS;
    } else
        return HAL_LL_CAN_ERROR;
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_can_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                hal_ll_can_pin_id *index_list, hal_ll_can_handle_register_t *handle_map ) {
    static const uint16_t tx_map_size = ( sizeof( hal_ll_can_tx_map ) / sizeof( hal_ll_can_pin_map_t ) );
    static const uint16_t rx_map_size = ( sizeof( hal_ll_can_rx_map ) / sizeof( hal_ll_can_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t tx_index;
    uint16_t rx_index;

    if ( (HAL_LL_PIN_NC == tx_pin) || (HAL_LL_PIN_NC == rx_pin) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ )
    {
        if ( hal_ll_can_tx_map[ tx_index ].pin == tx_pin )
        {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ )
            {
                if ( hal_ll_can_rx_map[ rx_index ].pin == rx_pin )
                {
                    if ( hal_ll_can_tx_map[ tx_index ].base == hal_ll_can_rx_map[ rx_index ].base ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_can_tx_map[ tx_index ].module_index;

                        // Map pin names
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_can_handle ) {
                            return hal_ll_module_id;
                        } else if ( CAN_MODULE_COUNT == ++index_counter ) {
                            return --index_counter;
                        }
                    }
                }
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_can_map_pins( uint8_t module_index, hal_ll_can_pin_id *index_list ) {
    // Map new pins.
    hal_ll_can_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_can_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_can_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_can_rx_map[ index_list[module_index].pin_rx ].pin;
}

static hal_ll_can_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_can_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_can_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_can_get_base_from_hal_handle == hal_ll_can_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_can_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_can_hw_specifics_map[hal_ll_module_error];
}

static hal_ll_err_t hal_ll_can_bit_timing( hal_ll_can_hw_specifics_map_t *map ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint8_t sjw, prseg, prescaler, pseg1, pseg2;
    uint32_t baud_rate, actual_baud_rate;
    float tq, temp, can_clock;

    baud_rate = map->frequency;

    can_clock = hal_ll_get_fosc_clock_value;

    // CAN clock is half of Focs frequency for this implementation.
    #ifdef dsPIC33EP_FAMILY
    // ERRATA information - setting this bit will use Fosc/2 for CAN.
    set_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_BRG_CLOCK_SELECTION_BIT );
    #endif
    can_clock /= 2;

    // For dsPIC33/PIC24 MCUs maximum input CAN frequency is 40MHz
    if ( (float)HAL_LL_CAN_MAXIMUM_FREQUENCY < can_clock )
        return HAL_LL_CAN_ERROR;

    /*
     * Description: This code snippet searches for optimal parameters for configuring
     * the CAN bus baud rate on PIC18 microcontrollers, based on the provided parameters.
     *
     * Initial parameters:
     * - can_clock: CAN source clock frequency in Hz.
     * - baud_rate: Desired CAN bus baud rate.
     *
     * Calculated parameters:
     * - prescaler: The prescaler value to achieve the desired baud rate.
     * - pseg1, pseg2: Time segment values for configuring the CAN bus.
     *
     * Formulas used:
     * - can_clock = Fosc / 2 - input frequency to CAN module (MAX 40MHz for dsPIC33F and PIC24H)
     * - tq = 2 * prescaler / can_clock - time quanta
     * - actual_baud_rate = 1 / (tq * (sjw + prseg + pseg1 + pseg2)) - baud rate that we are trying to achieve
     */

    sjw = HAL_LL_CAN_BRG_SJW_VALUE;

    for( prescaler = 1; prescaler <= HAL_LL_CAN_BRG_MAX_PRESCALER_VALUE; prescaler++ ) {
        for( pseg1 = 1; pseg1 <= HAL_LL_CAN_BRG_MAX_PSEG1_VALUE; pseg1++ ) {
            for( pseg2 = 2; pseg2 <= HAL_LL_CAN_BRG_MAX_PSEG2_VALUE; pseg2++ ) {
                for ( prseg = 1; prseg <= HAL_LL_CAN_BRG_MAX_PRSEG_VALUE; prseg++ ) {
                    tq = 2 * prescaler;
                    tq /= can_clock;
                    temp = tq;
                    temp *= ( pseg1 + pseg2 + sjw + prseg );
                    actual_baud_rate = hal_ll_get_actual_baud_rate( temp );
                    if ( actual_baud_rate < baud_rate )
                        break;
                    if( actual_baud_rate == baud_rate ) {
                        // Exact match found
                        uint16_t prseg_val = hal_ll_can_get_brg_element_mask( prseg, HAL_LL_CAN_BRG_PRSEG_OFFSET );
                        uint16_t sjw_val = hal_ll_can_get_brg_element_mask( sjw, HAL_LL_CAN_BRG_SJW_OFFSET );
                        uint16_t pseg1_val = hal_ll_can_get_brg_element_mask( pseg1, HAL_LL_CAN_BRG_PSEG1_OFFSET );
                        uint16_t pseg2_val = hal_ll_can_get_brg_element_mask( pseg2, HAL_LL_CAN_BRG_PSEG2_OFFSET );
                        uint16_t prescaler_val = hal_ll_can_get_brg_element_mask( prescaler, HAL_LL_CAN_BRG_PRESCALER_OFFSET );

                        hal_ll_hw_reg->cfg1 = sjw_val | prescaler_val;
                        hal_ll_hw_reg->cfg2 = HAL_LL_CAN_BRGCON2_SEG2PHTS_MASK | pseg1_val | prseg_val | pseg2_val;

                        return HAL_LL_CAN_SUCCESS;
                    }
                }
            }
        }
        /*
        * Note: Setting parameters that result in a baud rate that differs from the desired value is not acceptable.
        *       If two devices communicate over CAN, their baud rates need to be exactly the same.
        */
    }

    // If this point was reached, baud rate wasn't set to the desired value and error is returned.
    return HAL_LL_CAN_ERROR;
}

static hal_ll_err_t hal_ll_can_module_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    hal_ll_can_buffer_base_handle_t *hal_ll_buffer_hw_reg = hal_ll_can_get_buffer_base_struct( map->alternate_base );
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    // Request configuration mode.
    set_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_CONFIG_MASK );
    // Wait until HW enters initialization mode.
    while( HAL_LL_CAN_CTRL_OP_CONFIG_MASK != ( hal_ll_hw_reg->ctrl1 & HAL_LL_CAN_CTRL_OPMODE_MASK )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    // Clear Device Filter Number bits.
    clear_reg( &hal_ll_hw_reg->ctrl2 );

    // Setup RX and TX control registers - CxCTRL1.WIN = 0
    clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );
    clear_reg( &hal_ll_buffer_hw_reg->rxful1 );
    clear_reg( &hal_ll_buffer_hw_reg->rxful2 );
    clear_reg( &hal_ll_buffer_hw_reg->rxovf1 );
    clear_reg( &hal_ll_buffer_hw_reg->rxovf2 );

    /*
     * Buffer 0 is used for TX with highest priority.
     * Buffers 1-7 are used for RX.
     */
    write_reg( &hal_ll_buffer_hw_reg->tr01con, HAL_LL_CAN_TR01CON_CONFIG_MASK );
    clear_reg( &hal_ll_buffer_hw_reg->tr23con );
    clear_reg( &hal_ll_buffer_hw_reg->tr45con );
    clear_reg( &hal_ll_buffer_hw_reg->tr67con );

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_filter_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_filter_config_t *filter_config, bool default_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    hal_ll_can_filter_base_handle_t *hal_ll_filter_hw_reg = hal_ll_can_get_filter_base_struct( map->alternate_base );
    uint8_t filter_number_pos = filter_config->can_filter_bank;
    uint8_t mask_sel_reg = hal_ll_can_get_msksel_num( filter_number_pos );
    uint8_t mask_num = 0, buffer_pointer = hal_ll_can_get_bufpnt_num( filter_number_pos );
    uint8_t filter_to_mask, filter_to_fifo = filter_config->can_filter_fifo;


    // Setup filters - CxCTRL1.WIN = 1.
    set_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );

    if ( filter_funtion_default_config ) {
        // These registers have undefined reset values, so they should be cleared first.
        for( uint8_t counter = 0; counter < HAL_LL_FILTER_NUMBER; counter++ ) {
            clear_reg( &hal_ll_filter_hw_reg->acceptance_filters[counter].rxfeid );
            clear_reg( &hal_ll_filter_hw_reg->acceptance_filters[counter].rxfsid );
        }
        // Set all masks to unconfigured state.
        while ( mask_num < HAL_LL_CAN_FILTER_MASK_COUNT ) {
            hal_ll_can_filter_mask[mask_num].configured = false;
            hal_ll_can_filter_mask[mask_num++].mask = 0x00000000ul;
        }
        // Disable all filters.
        clear_reg( &hal_ll_hw_reg->fen1 );

        // Switch to buffer registers.
        clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );
        filter_funtion_default_config = false;
        return HAL_LL_CAN_SUCCESS;
    }

    if ( default_config )
        return HAL_LL_CAN_SUCCESS;

    // dsPIC33 and PIC24 MCUs have only 16 filters and 32 FIFOs, FIFO0 is for TX.
    if (( HAL_LL_FILTER_NUMBER <= filter_number_pos ) || ( HAL_LL_CAN_FILTER_FIFO0 == filter_to_fifo ) ||
             ( HAL_LL_CAN_FILTER_FIFO31 < filter_to_fifo )) {
        // Switch to buffer registers.
        clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );
        return HAL_LL_CAN_ERROR;
    }

    /*
     * As dsPIC33 and PIC24 MCUs have only 3 filter masks in total, SW writes
     * first 3 unique filter masks and maps them to the filter numbers passed.
     * If user defines 4 unique filter masks and more, error will be returned.
     */
    while ( mask_num < HAL_LL_CAN_FILTER_MASK_COUNT ) {
        if ( hal_ll_can_filter_mask[mask_num].mask != filter_config->can_filter_mask_id ) {
            if ( hal_ll_can_filter_mask[mask_num].configured == false ) {
                hal_ll_filter_hw_reg->mask[mask_num].sid = hal_ll_can_get_rxmsid_value( filter_config->can_filter_mask_id );
                hal_ll_filter_hw_reg->mask[mask_num].eid = hal_ll_can_get_rxmeid_value( filter_config->can_filter_mask_id );
                hal_ll_can_filter_mask[mask_num].mask = filter_config->can_filter_mask_id;
                hal_ll_can_filter_mask[mask_num].configured = true;
                break;
            }
        } else {
            break;
        }
    }
    if ( HAL_LL_CAN_FILTER_MASK_COUNT == mask_num )
        // dsPIC MCUs only have 3 unique masks.
        return HAL_LL_CAN_ERROR;

    // Assign filter ID requested by user.
    hal_ll_filter_hw_reg->acceptance_filters[filter_number_pos].rxfsid = hal_ll_can_get_rxmsid_value( filter_config->can_filter_id );
    hal_ll_filter_hw_reg->acceptance_filters[filter_number_pos].rxfeid = hal_ll_can_get_rxmeid_value( filter_config->can_filter_id );

    set_reg_bits( &hal_ll_hw_reg->fmsksel[mask_sel_reg], hal_ll_can_set_msksel( mask_num, filter_number_pos ));

    set_reg_bits( &hal_ll_filter_hw_reg->bufpnt[buffer_pointer],
                   hal_ll_can_set_bufpnt( filter_number_pos, buffer_pointer, filter_to_fifo ));

    if ( HAL_LL_CAN_FILTER_ENABLE == filter_config->can_filter_enable )
        // Enable the filter requested by user.
        set_reg_bit( &hal_ll_hw_reg->fen1, filter_number_pos );
    else
        // Disable the filter requested by user.
        clear_reg_bit( &hal_ll_hw_reg->fen1, filter_number_pos );

    // Switch to buffer registers.
    clear_reg_bit( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_WIN_BIT );
}

static void hal_ll_can_dma_configure( hal_ll_can_hw_specifics_map_t *map ){
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    hal_ll_dma_base_handle_t *hal_ll_dma_hw_reg = hal_ll_can_get_dma_base_struct( map->dma_base );
    hal_ll_can_buffer_base_handle_t *hal_ll_buffer_hw_reg = hal_ll_can_get_buffer_base_struct( map->alternate_base );

    #ifdef dsPIC33EP_FAMILY
    DSRPAG = 1; // dsPIC33EP family uses far data space for DMA so this register should equal 1.
    #endif

    /*
     * Set the size of buffer in DMA RAM for 32 buffers (1 TX + 31 RX) and
     * configure FIFO Start Area bits (RX buffer) from the FIFO31 up to FIFO0.
     */
    write_reg( &hal_ll_hw_reg->fctrl, HAL_LL_FCTRL_CONFIGURATION_MASK );

    /*
     * DMA0 channel initialization for ECAN reception (ECAN to DMA RAM).
     * Set up Channel 0 for peripheral indirect addressing mode and select TX to peripheral.
     *
     * Read from peripheral address, write to DMA RAM address.
     * Initiate block transfer complete interrupt when all data has been moved.
     * Peripheral Indirect Addressing mode.
     * Continious, Ping-Pong modes disabled.
     */
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].con, HAL_LL_DMA_CON_RX_CONFIG_MASK );

    // Set up the address of the peripheral (CxRXD).
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].pad, (volatile uint16_t) &hal_ll_buffer_hw_reg->rxd );

    // Set the data block transfer size of 8.
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].cnt, HAL_LL_DMA_CNT_DATA_BLOCK_SIZE );

    // Automatic DMA RX initiation by DMA request.
    if ( HAL_LL_CAN1_BASE_ADDRESS == map->base)
        write_reg( &hal_ll_dma_hw_reg->dma_regs[0].req, HAL_LL_DMA_CNT_CAN1_RX_INTERRUPT_MASK );
    else
        write_reg( &hal_ll_dma_hw_reg->dma_regs[0].req, HAL_LL_DMA_CNT_CAN2_RX_INTERRUPT_MASK );

    // DPSRAM start address offset value FIFO1 is the first RX buffer.
    #ifdef dsPIC33FJ_FAMILY
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].sta, ( volatile uint16_t ) ( HAL_LL_DMA_RAM_RX_ADDRESS ));
    #elif defined dsPIC33EP_FAMILY
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].stal, ( volatile uint16_t ) ( HAL_LL_DMA_RAM_RX_ADDRESS ));
    #endif


    // Enable the channel.
    write_reg( &hal_ll_dma_hw_reg->dma_regs[0].con, HAL_LL_DMA_CON_RX_ENABLE_MASK );

    /*
     * DMA1 channel initialization for ECAN transmission (DMA RAM to ECAN).
     * Set up Channel 1 for peripheral indirect addressing mode and select TX to peripheral.
     *
     * Read from DMA RAM address, write to peripheral address.
     * Initiate block transfer complete interrupt when all data has been moved.
     * Peripheral Indirect Addressing mode.
     * Continious, Ping-Pong modes disabled.
     */
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].con, HAL_LL_DMA_CON_TX_CONFIG_MASK );

    // Set up the address of the peripheral (CxTXD).
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].pad, (volatile uint16_t) &hal_ll_buffer_hw_reg->txd );

    // Set the data block transfer size of 8.
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].cnt, HAL_LL_DMA_CNT_DATA_BLOCK_SIZE );

    // Automatic DMA TX initiation by DMA request.
    if ( HAL_LL_CAN1_BASE_ADDRESS == map->base )
        write_reg( &hal_ll_dma_hw_reg->dma_regs[1].req, HAL_LL_DMA_CNT_CAN1_TX_INTERRUPT_MASK );
    else
        write_reg( &hal_ll_dma_hw_reg->dma_regs[1].req, HAL_LL_DMA_CNT_CAN2_TX_INTERRUPT_MASK );

    // DPSRAM start address offset value (buffer 0 is used for transmitting).
    #ifdef dsPIC33FJ_FAMILY
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].sta, ( volatile uint16_t ) ( HAL_LL_DMA_RAM_TX_ADDRESS ));
    #elif defined dsPIC33EP_FAMILY
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].stal, ( volatile uint16_t ) ( HAL_LL_DMA_RAM_TX_ADDRESS ));
    #endif


    // Enable the channel.
    write_reg( &hal_ll_dma_hw_reg->dma_regs[1].con, HAL_LL_DMA_CON_TX_ENABLE_MASK );
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_can_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( ( HAL_LL_PIN_NC != map->pins.tx_pin.pin_name ) && ( HAL_LL_PIN_NC != map->pins.rx_pin.pin_name ) ) {
        hal_ll_status = hal_ll_pps_map( ( map->pins.tx_pin.pin_name & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4, map->pins.tx_pin.pin_name & HAL_LL_NIBBLE_LOW_8BIT,
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_CAN, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_CAN_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed.
        hal_ll_status = hal_ll_pps_map( ( map->pins.rx_pin.pin_name & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4, map->pins.rx_pin.pin_name & HAL_LL_NIBBLE_LOW_8BIT,
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_CAN, map->module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_CAN_SUCCESS;
    }
}

static hal_ll_err_t hal_ll_can_set_operation_mode( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct(map->base);
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;
    uint16_t mode_mask;

    hal_ll_hw_reg->ctrl1 &= ~HAL_LL_CAN_CTRL_REQOP_MASK;

    switch( config->mode ) {
        case HAL_LL_CAN_MODE_LISTENALL:
            hal_ll_hw_reg->ctrl1 |= HAL_LL_CAN_MODE_LISTENALL_MASK;
            mode_mask = HAL_LL_CAN_CTRL_OP_LISTENALL_MASK;
            break;
        case HAL_LL_CAN_MODE_LISTENONLY:
            hal_ll_hw_reg->ctrl1 |= HAL_LL_CAN_CTRL_LISTENONLY_MASK;
            mode_mask = HAL_LL_CAN_CTRL_OP_LISTENONLY_MASK;
            break;
        case HAL_LL_CAN_MODE_LOOPBACK:
            hal_ll_hw_reg->ctrl1 |= HAL_LL_CAN_CTRL_LOOPBACK_MASK;
            mode_mask = HAL_LL_CAN_CTRL_OP_LOOPBACK_MASK;
            break;
        case HAL_LL_CAN_MODE_NORMAL:
            hal_ll_hw_reg->ctrl1 |= HAL_LL_CAN_CTRL_NORMAL_MASK;
            mode_mask = HAL_LL_CAN_CTRL_OP_NORMAL_MASK;
            break;
        case HAL_LL_CAN_MODE_DISABLE:
            hal_ll_hw_reg->ctrl1 |= HAL_LL_CAN_CTRL_DISABLE_MASK;
            mode_mask = HAL_LL_CAN_CTRL_OP_DISABLE_MASK;
            break;

        default:
            // dsPIC doesn't have operation mode requested by user.
            return HAL_LL_CAN_ERROR;
    }

    while ( mode_mask != ( hal_ll_hw_reg->ctrl1 & HAL_LL_CAN_CTRL_OPMODE_MASK )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    return HAL_LL_CAN_SUCCESS;
}

static hal_ll_err_t hal_ll_can_hw_init( hal_ll_can_hw_specifics_map_t *map, hal_ll_can_config_t *config,
                                        hal_ll_can_filter_config_t *filter_config ) {
    hal_ll_can_base_handle_t *hal_ll_hw_reg = hal_ll_can_get_base_struct( map->base );
    uint16_t timeout = HAL_LL_CAN_TIMEOUT_VALUE;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_module_init( map, config ))
        return HAL_LL_CAN_ERROR;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_filter_init( map, filter_config, true ))
        return HAL_LL_CAN_ERROR;

    if ( HAL_LL_CAN_ERROR == hal_ll_can_bit_timing( map ))
        return HAL_LL_CAN_ERROR;

    hal_ll_can_dma_configure( map );

    timeout = HAL_LL_CAN_TIMEOUT_VALUE;
    // Request the leave of configuration mode.
    clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_CAN_CTRL_CONFIG_MASK );
    // Wait until HW leaves configuration mode.
    while( HAL_LL_CAN_CTRL_OP_CONFIG_MASK == ( hal_ll_hw_reg->ctrl1 & HAL_LL_CAN_CTRL_OPMODE_MASK )) {
        if( 0 == timeout-- )
            return HAL_LL_CAN_ERROR;
    }

    // Set the operation mode requested by user.
    if ( HAL_LL_CAN_ERROR == hal_ll_can_set_operation_mode( map, config ))
        return HAL_LL_CAN_ERROR;

    return HAL_LL_CAN_SUCCESS;
}
// ------------------------------------------------------------------------- END
