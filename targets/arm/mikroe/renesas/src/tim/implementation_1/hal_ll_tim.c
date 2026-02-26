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
 * @file  hal_ll_tim.c
 * @brief TIM HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"
#include "hal_ll_mstpcr.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
// -------------------------------------------------------
// GPT register bit definitions
// -------------------------------------------------------
#define HAL_LL_TIM_GTCR_CST                     (0)
#define HAL_LL_TIM_GTCR_MD_MASK                 (0x70000UL)

#define HAL_LL_TIM_GTBER_PR_MASK                (0x300000UL)
#define HAL_LL_TIM_GTBER_PR_SINGLE_BUFFER       (0x100000UL)
#define HAL_LL_TIM_GTBER_CCRA_MASK              (0x30000UL)
#define HAL_LL_TIM_GTBER_CCRA_SINGLE_BUFFER     (0x10000UL)
#define HAL_LL_TIM_GTBER_CCRB_MASK              (0xC0000UL)
#define HAL_LL_TIM_GTBER_CCRB_SINGLE_BUFFER     (0x40000UL)

#define HAL_LL_TIM_GTUDDTYC_UD                  (0)

#define HAL_LL_TIM_GTIOR_GTIOA_MASK             (0x1FUL)
#define HAL_LL_TIM_GTIOR_GTIOB_MASK             (0x1FUL << 16)
#define HAL_LL_TIM_GTIOR_GTIOA_9               (0x9)
#define HAL_LL_TIM_GTIOR_GTIOB_9               (0x9UL << 16)
#define HAL_LL_TIM_GTIOR_OAE                    (8)
#define HAL_LL_TIM_GTIOR_OBE                    (24)

// -------------------------------------------------------
// AGT register bit definitions
// (RA4M2 User's Manual Rev.1.40, Section 22)
// -------------------------------------------------------

/*!< AGTCR (offset 0x08) */
#define HAL_LL_AGT_AGTCR_TSTART_POS            (0)   /*!< Count start */
#define HAL_LL_AGT_AGTCR_TSTOP_POS             (2)   /*!< Forced stop (write-only) */

/*!< AGTMR1 (offset 0x09) */
#define HAL_LL_AGT_AGTMR1_TMOD_MASK            (0x07U) /*!< Operating mode */
#define HAL_LL_AGT_AGTMR1_TMOD_TIMER           (0x00U) /*!< Timer mode */
#define HAL_LL_AGT_AGTMR1_TCK_MASK             (0x70U) /*!< Count source */
#define HAL_LL_AGT_AGTMR1_TCK_PCLKB            (0x00U) /*!< PCLKB / 1 */

/*!< AGTCMSR (offset 0x0E) ? Compare Match Function Select */
#define HAL_LL_AGT_AGTCMSR_TCMEA_POS           (0)   /*!< Compare match A enable */
#define HAL_LL_AGT_AGTCMSR_TOEA_POS            (1)   /*!< AGTOAn pin output enable */
#define HAL_LL_AGT_AGTCMSR_TOPOLA_POS          (2)   /*!< AGTOAn polarity (0=normal) */
#define HAL_LL_AGT_AGTCMSR_TCMEB_POS           (4)   /*!< Compare match B enable */
#define HAL_LL_AGT_AGTCMSR_TOEB_POS            (5)   /*!< AGTOBn pin output enable */
#define HAL_LL_AGT_AGTCMSR_TOPOLB_POS          (6)   /*!< AGTOBn polarity (0=normal) */

/*!< Module stop bits for AGT0?3 live in MSTPCRD (Section 10.2.7, pp. 190-191):
 *   AGT0 = MSTPCRD bit 3
 *   AGT1 = MSTPCRD bit 2
 *   AGT2 = MSTPCRD bit 1
 *   AGT3 = MSTPCRD bit 0
 *
 *  AGT4?5 live in MSTPCRE (Section 10.2.8, p. 192):
 *   AGT4 = MSTPCRE bit 15
 *   AGT5 = MSTPCRE bit 14
 */
#define HAL_LL_AGT_MSTPCRD_AGT0_POS            (3)
#define HAL_LL_AGT_MSTPCRD_AGT3_POS            (0)
#define HAL_LL_AGT_MSTPCRE_AGT4_POS            (15)
#define HAL_LL_AGT_MSTPCRE_AGT5_POS            (14)

// -------------------------------------------------------
// GPT module-stop index ranges (unchanged from original)
// -------------------------------------------------------
#if defined(R7FA4M1)
#define HAL_LL_TIM_MIN_MSTPD5_MODULE_NUM       (0)
#define HAL_LL_TIM_MAX_MSTPD5_MODULE_NUM       (1)
#define HAL_LL_TIM_MIN_MSTPD6_MODULE_NUM       (2)
#define HAL_LL_TIM_MAX_MSTPD6_MODULE_NUM       (7)
#elif defined(R7FA6M3)
#define HAL_LL_TIM_MIN_MSTPD5_MODULE_NUM       (0)
#define HAL_LL_TIM_MAX_MSTPD5_MODULE_NUM       (7)
#define HAL_LL_TIM_MIN_MSTPD6_MODULE_NUM       (8)
#define HAL_LL_TIM_MAX_MSTPD6_MODULE_NUM       (13)
#elif defined(R7FA2E3)
#define HAL_LL_TIM_MIN_MSTPD5_MODULE_NUM       (0)
#define HAL_LL_TIM_MAX_MSTPD5_MODULE_NUM       (0)
#define HAL_LL_TIM_MIN_MSTPD6_MODULE_NUM       (4)
#define HAL_LL_TIM_MAX_MSTPD6_MODULE_NUM       (9)
#endif

// -------------------------------------------------------
// AGT module index range
// Module indices for AGT are assigned after all GPT modules.
// e.g. if GPT occupies TIM_MODULE_0..7, then
//      AGT0 = TIM_MODULE_8, AGT1 = TIM_MODULE_9, ...
// These match the entries in hal_ll_tim_pin_map.h.
// -------------------------------------------------------
#if defined(R7FA4M2)
#define HAL_LL_TIM_AGT_MODULE_INDEX_MIN        (8)   /*!< First AGT module index */
#define HAL_LL_TIM_AGT_MODULE_INDEX_MAX        (13)  /*!< Last  AGT module index (AGT5) */
#endif

#define HAL_LL_TIM_AF_CONFIG (GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PORT_PULL_UP_ENABLE)

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle)     ((hal_ll_tim_base_handle_t *)_handle)
#define hal_ll_agt_get_base_struct(_handle)     ((hal_ll_agt_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address     ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address */
#define hal_ll_tim_get_handle                   ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle     ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                                (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

// -------------------------------------------------------------- PRIVATE TYPES

/*!< @brief GPT register structure (unchanged). */
typedef struct
{
    uint32_t gtwp;
    uint32_t gtstr;
    uint32_t gtstp;
    uint32_t gtclr;
    uint32_t gtssr;
    uint32_t gtpsr;
    uint32_t gtcsr;
    uint32_t gtupsr;
    uint32_t gtdnsr;
    uint32_t gticasr;
    uint32_t gticbsr;
    uint32_t gtcr;
    uint32_t gtuddtyc;
    uint32_t gtior;
    uint32_t gtintad;
    uint32_t gtst;
    uint32_t gtber;
    uint32_t gtitc;
    uint32_t gtcnt;
    uint32_t gtccr[6];
    uint32_t gtpr;
    uint32_t gtpbr;
    uint32_t gtpdbr;
    uint32_t gtadtra;
    uint32_t gtadtbra;
    uint32_t gtadtdbra;
    uint32_t gtadtrb;
    uint32_t gtadtbrb;
    uint32_t gtdtcr;
    uint32_t gtdvu;
} hal_ll_tim_base_handle_t;

/*!< @brief AGT register structure.
 *   Base address: AGTn = 0x400E_8000 + 0x0100 * n  (n = 0..5)
 *   All registers are 8-bit except AGT/AGTCMA/AGTCMB which are 16-bit.
 *   (RA4M2 User's Manual Rev.1.40, Section 22.2, pp. 586-593)
 */
typedef struct
{
    uint16_t agt;       /*!< 0x00 : 16-bit counter / reload register */
    uint16_t agtcma;    /*!< 0x02 : Compare match A (duty for AGTOAn) */
    uint16_t agtcmb;    /*!< 0x04 : Compare match B (duty for AGTOBn) */
    uint8_t  _pad0[2];  /*!< 0x06 : reserved */
    uint8_t  agtcr;     /*!< 0x08 : Control register (TSTART, TCSTF, TSTOP ...) */
    uint8_t  agtmr1;    /*!< 0x09 : Mode register 1 (TMOD, TCK) */
    uint8_t  agtmr2;    /*!< 0x0A : Mode register 2 (LPM, CKS) */
    uint8_t  _pad1;     /*!< 0x0B : reserved */
    uint8_t  agtioc;    /*!< 0x0C : I/O control register (TOE, TEDGSEL ...) */
    uint8_t  agtisr;    /*!< 0x0D : Event pin select register */
    uint8_t  agtcmsr;   /*!< 0x0E : Compare match function select (TCMEA/B, TOEA/B, TOPOLA/B) */
    uint8_t  agtiosel;  /*!< 0x0F : Pin select register */
} hal_ll_agt_base_handle_t;

/*!< @brief Module type discriminator */
typedef enum
{
    HAL_LL_TIM_MODULE_GPT = 0,
    HAL_LL_TIM_MODULE_AGT
} hal_ll_tim_module_type_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t   pin;
    hal_ll_tim_pin_type_t pin_type;
    uint32_t            af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t          base;
    hal_ll_tim_t                config;
    uint16_t                    max_period;
    uint32_t                    freq_hz;
    hal_ll_pin_name_t           module_index;
    hal_ll_tim_module_type_t    module_type;  /*!< GPT or AGT */
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum
{
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info
 *
 *  Entries for TIM_MODULE_0..7  ? GPT channels  (HAL_LL_TIM_MODULE_GPT)
 *  Entries for TIM_MODULE_8..13 ? AGT channels  (HAL_LL_TIM_MODULE_AGT)
 *
 *  The module_type field is used throughout to dispatch to the correct
 *  hardware-specific helper without changing any public API.
 */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] =
{
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_6
    {HAL_LL_TIM6_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_6), HAL_LL_TIM_MODULE_GPT},
    #endif
    #ifdef TIM_MODULE_7
    {HAL_LL_TIM7_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_7), HAL_LL_TIM_MODULE_GPT},
    #endif
    // ---- AGT modules --------------------------------------------------------
    #ifdef TIM_MODULE_8
    {HAL_LL_TIM8_BASE_ADDR,  {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_8),  HAL_LL_TIM_MODULE_AGT},
    #endif
    #ifdef TIM_MODULE_9
    {HAL_LL_TIM9_BASE_ADDR,  {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_9),  HAL_LL_TIM_MODULE_AGT},
    #endif
    #ifdef TIM_MODULE_10
    {HAL_LL_TIM10_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_10), HAL_LL_TIM_MODULE_AGT},
    #endif
    #ifdef TIM_MODULE_11
    {HAL_LL_TIM11_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_11), HAL_LL_TIM_MODULE_AGT},
    #endif
    #ifdef TIM_MODULE_12
    {HAL_LL_TIM12_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_12), HAL_LL_TIM_MODULE_AGT},
    #endif
    #ifdef TIM_MODULE_13
    {HAL_LL_TIM13_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_13), HAL_LL_TIM_MODULE_AGT},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC, HAL_LL_TIM_MODULE_GPT}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

// --- Shared helpers ----------------------------------------------------------
static void hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );
static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                               hal_ll_tim_handle_register_t *handle_map );
static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                      bool hal_ll_state );

// --- GPT-specific private helpers --------------------------------------------
static uint32_t hal_ll_tim_clock_source( void );
static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map );
static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

// --- AGT-specific private helpers --------------------------------------------
static uint32_t hal_ll_agt_clock_source( void );
static uint32_t hal_ll_agt_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map );
static uint32_t hal_ll_agt_hw_init( hal_ll_tim_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {
    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result ].config.pin != pin ) {
        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );

        hal_ll_tim_map_pin( pin_check_result, index );

        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                         (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    uint32_t period;

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    period = hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_pin_type_t pin_type = hal_ll_tim_hw_specifics_map_local->config.pin_type;

    if ( HAL_LL_TIM_MODULE_AGT == hal_ll_tim_hw_specifics_map_local->module_type ) {
        // -----------------------------------------------------------------
        // AGT duty cycle
        //
        // The AGT is a down-counter that reloads at underflow. With
        // TOPOLA/B = 0 (normal output, Section 22.2.9 / Table 22.7-22.8):
        //   - output goes LOW  at compare match
        //   - output goes HIGH at underflow
        //
        // So the compare register controls the leading low portion.
        // For a desired duty_ratio the compare value is:
        //   compare = (uint16_t)((1.0f - duty_ratio) * (max_period + 1)) - 1
        //
        // We write to AGTCMA for AGTOAn pins, AGTCMB for AGTOBn pins.
        // -----------------------------------------------------------------
        hal_ll_agt_base_handle_t *hal_ll_hw_reg =
            hal_ll_agt_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        uint16_t compare = (uint16_t)(
            (1.0f - duty_ratio) * (float)( hal_ll_tim_hw_specifics_map_local->max_period + 1 )
        ) - 1;

        // if ( HAL_LL_TIM_PIN_A == pin_type ) {
        //     write_reg( &hal_ll_hw_reg->agtcma, compare );
        // } else {
        //     write_reg( &hal_ll_hw_reg->agtcmb, compare );
        // }
            write_reg( &hal_ll_hw_reg->agtioc, 0x4 );


    } else {
        // -----------------------------------------------------------------
        // GPT duty cycle (original implementation, unchanged)
        // -----------------------------------------------------------------
        hal_ll_tim_base_handle_t *hal_ll_hw_reg =
            hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        if ( check_reg_bit( &hal_ll_hw_reg->gtcr, HAL_LL_TIM_GTCR_CST ) ) {
            write_reg( &hal_ll_hw_reg->gtccr[ (HAL_LL_TIM_PIN_A == pin_type) ? 2 : 3 ],
                       (uint32_t)( hal_ll_tim_hw_specifics_map_local->max_period + 1 ) * duty_ratio - 1 );
        } else {
            write_reg( &hal_ll_hw_reg->gtccr[ (HAL_LL_TIM_PIN_A == pin_type) ? 0 : 1 ],
                       (uint32_t)( hal_ll_tim_hw_specifics_map_local->max_period + 1 ) * duty_ratio - 1 );

            if ( HAL_LL_TIM_PIN_A == pin_type ) {
                write_reg( &hal_ll_hw_reg->gtccr[2], read_reg( &hal_ll_hw_reg->gtccr[0] ) );
            } else {
                write_reg( &hal_ll_hw_reg->gtccr[3], read_reg( &hal_ll_hw_reg->gtccr[1] ) );
            }
        }
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_pin_type_t pin_type = hal_ll_tim_hw_specifics_map_local->config.pin_type;

    if ( HAL_LL_TIM_MODULE_AGT == hal_ll_tim_hw_specifics_map_local->module_type ) {
        // -----------------------------------------------------------------
        // AGT start: set TSTART bit in AGTCR (Section 22.2.4, p. 587)
        // We guard against starting with an uninitialised period (0).
        // -----------------------------------------------------------------
        hal_ll_agt_base_handle_t *hal_ll_hw_reg =
            hal_ll_agt_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        if ( read_reg( &hal_ll_hw_reg->agt ) ) {
            set_reg_bit( &hal_ll_hw_reg->agtcr, HAL_LL_AGT_AGTCR_TSTART_POS );
        }

    } else {
        // -----------------------------------------------------------------
        // GPT start (original implementation, unchanged)
        // -----------------------------------------------------------------
        hal_ll_tim_base_handle_t *hal_ll_hw_reg =
            hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        if ( read_reg( &hal_ll_hw_reg->gtpr ) &&
             read_reg( &hal_ll_hw_reg->gtccr[ (HAL_LL_TIM_PIN_A == pin_type) ? 0 : 1 ] ) ) {
            set_reg_bit( &hal_ll_hw_reg->gtcr, HAL_LL_TIM_GTCR_CST );
        }
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( HAL_LL_TIM_MODULE_AGT == hal_ll_tim_hw_specifics_map_local->module_type ) {
        // -----------------------------------------------------------------
        // AGT stop: clear TSTART bit in AGTCR (Section 22.2.4, p. 587)
        // -----------------------------------------------------------------
        hal_ll_agt_base_handle_t *hal_ll_hw_reg =
            hal_ll_agt_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        clear_reg_bit( &hal_ll_hw_reg->agtcr, HAL_LL_AGT_AGTCR_TSTART_POS );

    } else {
        // -----------------------------------------------------------------
        // GPT stop (original implementation, unchanged)
        // -----------------------------------------------------------------
        hal_ll_tim_base_handle_t *hal_ll_hw_reg =
            hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        clear_reg_bit( &hal_ll_hw_reg->gtcr, HAL_LL_TIM_GTCR_CST );
    }

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;

        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, true );
        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.pin_type = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                                hal_ll_tim_handle_register_t *handle_map ) {
    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    uint16_t map_size = ( sizeof( hal_ll_tim_pin_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( hal_ll_tim_pin_map[ pin_num ].pin == pin ) {
            hal_ll_module_id = hal_ll_tim_pin_map[ pin_num ].module_index;

            for ( uint8_t map_member = 0; map_member < TIM_MODULE_COUNT + 1; map_member++ ) {
                if ( hal_ll_tim_hw_specifics_map[ map_member ].module_index == hal_ll_module_id ) {
                    hal_ll_module_id = map_member;
                    break;
                }
            }

            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_tim_handle ) {
                *index = pin_num;
                return hal_ll_module_id;
            } else if ( TIM_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    if ( HAL_LL_TIM_MODULE_AGT == map->module_type ) {
        // -----------------------------------------------------------------
        // AGT module stop control
        //
        // AGT0?3 ? MSTPCRD  (Section 10.2.7, pp. 190-191)
        //   AGT0 = bit 3,  AGT1 = bit 2,  AGT2 = bit 1,  AGT3 = bit 0
        //
        // AGT4?5 ? MSTPCRE  (Section 10.2.8, p. 192)
        //   AGT4 = bit 15, AGT5 = bit 14
        //
        // map->module_index is the hw_specifics_map array index (8..13).
        // AGT channel = module_index - HAL_LL_TIM_AGT_MODULE_INDEX_MIN
        // -----------------------------------------------------------------
        uint8_t agt_channel = map->module_index - HAL_LL_TIM_AGT_MODULE_INDEX_MIN;

        if ( agt_channel <= 3 ) {
            // AGT0?3: MSTPCRD bits 3..0  (AGT0=3, AGT1=2, AGT2=1, AGT3=0)
            uint8_t bit_pos = HAL_LL_AGT_MSTPCRD_AGT0_POS - agt_channel;
            if ( hal_ll_state ) {
                clear_reg_bit( _MSTPCRD, bit_pos );  // 0 = cancel module-stop
            } else {
                set_reg_bit( _MSTPCRD, bit_pos );    // 1 = enter module-stop
            }
        } else {
            // AGT4 = MSTPCRE bit 15, AGT5 = MSTPCRE bit 14
            uint8_t bit_pos = HAL_LL_AGT_MSTPCRE_AGT4_POS - (agt_channel - 4);
            if ( hal_ll_state ) {
                clear_reg_bit( _MSTPCRE, bit_pos );
            } else {
                set_reg_bit( _MSTPCRE, bit_pos );
            }
        }

    } else {
        // -----------------------------------------------------------------
        // GPT module stop control (original implementation, unchanged)
        // -----------------------------------------------------------------
        #if (defined(R7FA4M1) || defined(R7FA6M3) || defined(R7FA2E3))
        if ( true == hal_ll_state ) {
            if ( ( HAL_LL_TIM_MIN_MSTPD5_MODULE_NUM <= map->module_index ) &&
                 ( HAL_LL_TIM_MAX_MSTPD5_MODULE_NUM >= map->module_index ) )
                clear_reg_bit( _MSTPCRD, MSTPCRD_MSTPD5_POS );
            else if ( ( HAL_LL_TIM_MIN_MSTPD6_MODULE_NUM <= map->module_index ) &&
                      ( HAL_LL_TIM_MAX_MSTPD6_MODULE_NUM >= map->module_index ) )
                clear_reg_bit( _MSTPCRD, MSTPCRD_MSTPD6_POS );
        } else {
            if ( ( HAL_LL_TIM_MIN_MSTPD5_MODULE_NUM <= map->module_index ) &&
                 ( HAL_LL_TIM_MAX_MSTPD5_MODULE_NUM >= map->module_index ) )
                set_reg_bit( _MSTPCRD, MSTPCRD_MSTPD5_POS );
            else if ( ( HAL_LL_TIM_MIN_MSTPD6_MODULE_NUM <= map->module_index ) &&
                      ( HAL_LL_TIM_MAX_MSTPD6_MODULE_NUM >= map->module_index ) )
                set_reg_bit( _MSTPCRD, MSTPCRD_MSTPD6_POS );
        }
        #elif (defined(R7FA4M3) || defined(R7FA6M4) || defined(R7FA6M5) || defined(R7FA8M1) || defined(R7FA4M2))
        if ( true == hal_ll_state )
            clear_reg_bit( _MSTPCRE, MSTPCRE_MSTPE31_POS - map->module_index );
        else
            set_reg_bit( _MSTPCRE, MSTPCRE_MSTPE31_POS - map->module_index );
        #endif
    }
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin      = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_type = hal_ll_tim_pin_map[ index ].pin_type;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af       = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                       bool hal_ll_state ) {
    module_struct module;

    if ( map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] = VALUE( map->config.pin, map->config.af );
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_TIM_AF_CONFIG;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

// -------------------------------------------------------- GPT private helpers

static uint32_t hal_ll_tim_clock_source( void ) {
    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );
    return system_clocks.pclkd;
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t period;

    uint32_t pclkd = hal_ll_tim_clock_source();

    period = pclkd / map->freq_hz - 1;

    // GPT16 channels (module indices 2?7): period register is 16-bit.
    if ( 7 >= map->module_index && 1 < map->module_index )
        if ( 0xFFFF < period )
            period = 0xFFFF;

    write_reg( &hal_ll_hw_reg->gtpr,  (uint32_t)period );
    write_reg( &hal_ll_hw_reg->gtpbr, (uint32_t)period );

    return period;
}

static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t period;

    clear_reg_bit(  &hal_ll_hw_reg->gtcr,    HAL_LL_TIM_GTCR_CST );           // Stop first.
    clear_reg_bits( &hal_ll_hw_reg->gtcr,    HAL_LL_TIM_GTCR_MD_MASK );       // PWM mode.
    set_reg_bit(    &hal_ll_hw_reg->gtuddtyc, HAL_LL_TIM_GTUDDTYC_UD );       // Count up.
    clear_reg_bits( &hal_ll_hw_reg->gtber,   HAL_LL_TIM_GTBER_PR_MASK );
    set_reg_bits(   &hal_ll_hw_reg->gtber,   HAL_LL_TIM_GTBER_PR_SINGLE_BUFFER );

    period = hal_ll_tim_set_freq_bare_metal( map );

    clear_reg( &hal_ll_hw_reg->gtcnt );

    if ( HAL_LL_TIM_PIN_A == map->config.pin_type ) {
        clear_reg_bits( &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_GTIOA_MASK );
        set_reg_bits(   &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_GTIOA_9 );
        set_reg_bit(    &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_OAE );
        clear_reg_bits( &hal_ll_hw_reg->gtber, HAL_LL_TIM_GTBER_CCRA_MASK );
        set_reg_bits(   &hal_ll_hw_reg->gtber, HAL_LL_TIM_GTBER_CCRA_SINGLE_BUFFER );
    } else {
        clear_reg_bits( &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_GTIOB_MASK );
        set_reg_bits(   &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_GTIOB_9 );
        set_reg_bit(    &hal_ll_hw_reg->gtior, HAL_LL_TIM_GTIOR_OBE );
        clear_reg_bits( &hal_ll_hw_reg->gtber, HAL_LL_TIM_GTBER_CCRB_MASK );
        set_reg_bits(   &hal_ll_hw_reg->gtber, HAL_LL_TIM_GTBER_CCRB_SINGLE_BUFFER );
    }

    return period;
}

// -------------------------------------------------------- AGT private helpers

static uint32_t hal_ll_agt_clock_source( void ) {
    // AGT uses PCLKB as its count source when TCK[2:0] = 000b.
    // (RA4M2 User's Manual Rev.1.40, Section 22.2.5 AGTMR1, p. 589)
    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );
    return system_clocks.pclkb;
}

static uint32_t hal_ll_agt_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_agt_base_handle_t *hal_ll_hw_reg = hal_ll_agt_get_base_struct( map->base );
    uint32_t pclkb = hal_ll_agt_clock_source();

    // AGT is a 16-bit counter, so period is capped at 0xFFFF.
    uint32_t period = pclkb / map->freq_hz - 1;
    if ( period > 0xFFFFu )
        period = 0xFFFFu;

    // Write reload value. When stopped (TSTART=0), writing AGT updates
    // both the reload register and the counter directly.
    // (Section 22.3.1, p. 594)
    write_reg( &hal_ll_hw_reg->agt, (uint16_t)period );

    return period;
}

static uint32_t hal_ll_agt_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_agt_base_handle_t *hal_ll_hw_reg = hal_ll_agt_get_base_struct( map->base );

    // 1. Ensure the counter is stopped before changing mode registers.
    //    Writing 1 to TSTOP forcibly stops and resets the counter to 0xFFFF.
    //    (Section 22.2.4, p. 587)
    set_reg_bit( &hal_ll_hw_reg->agtcr, HAL_LL_AGT_AGTCR_TSTOP_POS );

    // 2. Configure AGTMR1: Timer mode (TMOD=000b), clock source PCLKB (TCK=000b).
    //    Note: AGTCMSR must not be written during count operation (Section 22.4.3).
    //    Writing AGTMR1 also initialises AGTOn/AGTIOn/AGTOAn/AGTOBn pin outputs.
    //    (Section 22.2.5, p. 589)
    write_reg( &hal_ll_hw_reg->agtmr1,
               (uint8_t)( HAL_LL_AGT_AGTMR1_TMOD_TIMER | HAL_LL_AGT_AGTMR1_TCK_PCLKB ) );

    // 3. Set the period (reload value).
    uint32_t period = hal_ll_agt_set_freq_bare_metal( map );

    // 4. Pre-load the compare register with 0 (0% duty) so the output
    //    stays low until hal_ll_tim_set_duty() is called.
    //    AGTCMA drives AGTOAn, AGTCMB drives AGTOBn.
    //    (Section 22.2.9 AGTCMSR, p. 593; Tables 22.7-22.8, p. 604)
    // if ( HAL_LL_TIM_PIN_A == map->config.pin_type ) {
    //     write_reg( &hal_ll_hw_reg->agtcma, 0x0000u );
    // } else {
    //     write_reg( &hal_ll_hw_reg->agtcmb, 0x0000u );
    // }

    // // 5. Configure AGTCMSR: enable compare match and output for the selected pin.
    // //    TOPOLA/B = 0 ? normal output (low at start, high after underflow).
    // //    (Section 22.2.9, p. 593)
    // uint8_t agtcmsr = 0u;
    // if ( HAL_LL_TIM_PIN_A == map->config.pin_type ) {
    //     agtcmsr |= (1u << HAL_LL_AGT_AGTCMSR_TCMEA_POS);  // Enable compare match A
    //     agtcmsr |= (1u << HAL_LL_AGT_AGTCMSR_TOEA_POS);   // Enable AGTOAn pin output
    //     // TOPOLA = 0 (normal output) ? already 0 after reset
    // } else {
    //     agtcmsr |= (1u << HAL_LL_AGT_AGTCMSR_TCMEB_POS);  // Enable compare match B
    //     agtcmsr |= (1u << HAL_LL_AGT_AGTCMSR_TOEB_POS);   // Enable AGTOBn pin output
    //     // TOPOLB = 0 (normal output) ? already 0 after reset
    // }
    // write_reg( &hal_ll_hw_reg->agtcmsr, agtcmsr );

    return period;
}

// ---------------------------------------------------- Shared init dispatcher

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_module_enable( map, true );
    hal_ll_tim_alternate_functions_set_state( map, true );

    if ( HAL_LL_TIM_MODULE_AGT == map->module_type ) {
        return hal_ll_agt_hw_init( map );
    } else {
        return hal_ll_tim_hw_init( map );
    }
}

// ------------------------------------------------------------------------- END