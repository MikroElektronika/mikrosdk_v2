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
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_rcc.h"

#define hal_ll_gpio_port_get_pin_index(__index) ( __index & 0xF0 )?( ( uint8_t )__index % PORT_SIZE ): \
                                                ( ( uint8_t )__index % PORT_SIZE )

#define hal_ll_gpio_port_get_port_index(__index) ( __index & 0xF0 )?( ( uint8_t )__index / PORT_SIZE ): \
                                                 ( ( uint8_t )__index / PORT_SIZE )


#define GPIO_PORT0_BASE  (0x40040000UL)
#define GPIO_PORT1_BASE  (0x40040020UL)
#define GPIO_PORT2_BASE  (0x40040040UL)
#define GPIO_PORT3_BASE  (0x40040060UL)
#define GPIO_PORT4_BASE  (0x40040080UL)
#define GPIO_PORT5_BASE  (0x400400A0UL)
#define GPIO_PORT6_BASE  (0x400400C0UL)
#define GPIO_PORT7_BASE  (0x400400E0UL)
#define GPIO_PORT8_BASE  (0x40040100UL)
#define GPIO_PORT9_BASE  (0x40040120UL)
// According to the documentation, this MCU has 10 ports,
//  but in mcu.h there are 15 port addresses
// #define GPIO_PORT10_BASE (0x40040140UL)
// #define GPIO_PORT11_BASE (0x40040160UL)
// #define GPIO_PORT12_BASE (0x40040180UL)
// #define GPIO_PORT13_BASE (0x400401A0UL)
// #define GPIO_PORT14_BASE (0x400401C0UL)

#define PWPR_REGISTER_BASE (( uint32_t * )0x40040D03UL)

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base[] =
{
    GPIO_PORT0_BASE,
    GPIO_PORT1_BASE,
    GPIO_PORT2_BASE,
    GPIO_PORT3_BASE,
    GPIO_PORT4_BASE,
    GPIO_PORT5_BASE,
    GPIO_PORT6_BASE,
    GPIO_PORT7_BASE,
    GPIO_PORT8_BASE,
    GPIO_PORT9_BASE//,
    // GPIO_PORT10_BASE,
    // GPIO_PORT11_BASE,
    // GPIO_PORT12_BASE,
    // GPIO_PORT13_BASE,
    // GPIO_PORT14_BASE
};

/**
 * @brief R_PFS_PORT_PIN [PIN] (Pin Function Selects)
 */
typedef struct
{
    union
    {
        union
        {
            volatile uint32_t PmnPFS;        /*!< (@ 0x00000000) Pin Function Control Register                              */

            struct
            {
                volatile uint32_t PODR  : 1; /*!< [0..0] Port Output Data                                                   */
                volatile uint32_t  PIDR  : 1; /*!< [1..1] Port Input Data                                                    */
                volatile uint32_t PDR   : 1; /*!< [2..2] Port Direction                                                     */
                uint32_t             : 1;
                volatile uint32_t PCR   : 1; /*!< [4..4] Pull-up Control                                                    */
                volatile uint32_t PIM   : 1; /*!< [5..5] Port Input Mode Control                                            */
                volatile uint32_t NCODR : 1; /*!< [6..6] N-Channel Open Drain Control                                       */
                uint32_t             : 3;
                volatile uint32_t DSCR  : 2; /*!< [11..10] Drive Strength Control Register                                  */
                volatile uint32_t EOFR  : 2; /*!< [13..12] Event on Falling/Rising                                          */
                volatile uint32_t ISEL  : 1; /*!< [14..14] IRQ input enable                                                 */
                volatile uint32_t ASEL  : 1; /*!< [15..15] Analog Input enable                                              */
                volatile uint32_t PMR   : 1; /*!< [16..16] Port Mode Control                                                */
                uint32_t             : 7;
                volatile uint32_t PSEL  : 5; /*!< [28..24] Port Function SelectThese bits select the peripheral
                                           *   function. For individual pin functions, see the MPC table                 */
                uint32_t : 3;
            } PmnPFS_b;
        };

        struct
        {
            union
            {
                struct
                {
                    volatile uint16_t RESERVED;

                    union
                    {
                        volatile uint16_t PmnPFS_HA;     /*!< (@ 0x00000002) Pin Function Control Register                              */

                        struct
                        {
                            volatile uint16_t PODR  : 1; /*!< [0..0] Port Output Data                                                   */
                            volatile uint16_t  PIDR  : 1; /*!< [1..1] Port Input Data                                                    */
                            volatile uint16_t PDR   : 1; /*!< [2..2] Port Direction                                                     */
                            uint16_t             : 1;
                            volatile uint16_t PCR   : 1; /*!< [4..4] Pull-up Control                                                    */
                            volatile uint16_t PIM   : 1; /*!< [5..5] Port Input Mode Control                                            */
                            volatile uint16_t NCODR : 1; /*!< [6..6] N-Channel Open Drain Control                                       */
                            uint16_t             : 3;
                            volatile uint16_t DSCR  : 2; /*!< [11..10] Drive Strength Control Register                                  */
                            volatile uint16_t EOFR  : 2; /*!< [13..12] Event on Falling/Rising                                          */
                            volatile uint16_t ISEL  : 1; /*!< [14..14] IRQ input enable                                                 */
                            volatile uint16_t ASEL  : 1; /*!< [15..15] Analog Input enable                                              */
                        } PmnPFS_HA_b;
                    };
                };

                struct
                {
                    volatile uint16_t RESERVED1;
                    volatile uint8_t  RESERVED2;

                    union
                    {
                        volatile uint8_t PmnPFS_BY;     /*!< (@ 0x00000003) Pin Function Control Register                              */

                        struct
                        {
                            volatile uint8_t PODR  : 1; /*!< [0..0] Port Output Data                                                   */
                            volatile uint8_t  PIDR  : 1; /*!< [1..1] Port Input Data                                                    */
                            volatile uint8_t PDR   : 1; /*!< [2..2] Port Direction                                                     */
                            uint8_t             : 1;
                            volatile uint8_t PCR   : 1; /*!< [4..4] Pull-up Control                                                    */
                            volatile uint8_t PIM   : 1; /*!< [5..5] Port Input Mode Control                                            */
                            volatile uint8_t NCODR : 1; /*!< [6..6] N-Channel Open Drain Control                                       */
                            uint8_t             : 1;
                        } PmnPFS_BY_b;
                    };
                };
            };
        };
    };
} R_PFS_PORT_PIN_Type;                 /*!< Size = 4 (0x4)                                                            */

/**
 * @brief R_PFS_PORT [PORT] (Port [0..14])
 */
typedef struct
{
    volatile R_PFS_PORT_PIN_Type PIN[16]; /*!< (@ 0x00000000) Pin Function Selects                                       */
} R_PFS_PORT_Type;                     /*!< Size = 64 (0x40)                                                          */


/**
 * @brief R_PFS_VLSEL [VLSEL] (VLSEL)
 */
typedef struct
{
    volatile uint8_t RESERVED[389];

    union
    {
        volatile uint8_t VL1SEL;          /*!< (@ 0x00000185) VL1 Select Control Register                                */

        struct
        {
            volatile uint8_t SELVL : 1;   /*!< [0..0] VL1 Voltage Connection Switching Control                           */
            uint8_t             : 7;
        } VL1SEL_b;
    };
} R_PFS_VLSEL_Type;                    /*!< Size = 390 (0x186)                                                        */

/**
 * @brief I/O Ports-PFS (R_PFS)
 */
typedef struct                           /*!< (@ 0x40040800) R_PFS Structure                                            */
{
    union
    {
        volatile R_PFS_PORT_Type  PORT[15]; /*!< (@ 0x00000000) Port [0..14]                                               */
        volatile R_PFS_VLSEL_Type VLSEL;    /*!< (@ 0x00000000) VLSEL                                                      */
    };
} R_PFS_Type;                            /*!< Size = 960 (0x3c0)                                                        */

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void _hal_ll_gpio_clock_enable( uint32_t *port );

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void _hal_ll_gpio_config( uint32_t *port, uint8_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state );

// TODO Esma
static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_port_index( name );
}

uint8_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    return ( 1UL << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    return _hal_ll_gpio_port_base[ name ];
}

void hal_ll_gpio_analog_input( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    int32_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        _hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static void hal_ll_gpio_clock_enable( uint32_t port ) {
    // TODO Esma - PORTs don't have clock enabling feature.
}

static void _hal_ll_gpio_config( uint32_t *port, uint8_t pin_mask, uint32_t config ) {
    R_PFS_Type port_ptr;
    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    *PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    *PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit

    // Clear the Port Mode Control bit in the PMR for the target pin to select the general I/O port.
    // TODO Esma pristup PMR registru
    port_ptr.PORT[0].PIN[0].PmnPFS_b.PMR = 0;
    // Specify the input/output function for the pin through the PSEL[4:0] bit settings in the PmnPFS register.
    // TODO Esma pristup PMR registru
    port_ptr.PORT[0].PIN[0].PmnPFS_b.PSEL = 0;
    // Set the PMR to 1 as required to switch to the selected input/output function for the pin.
    port_ptr.PORT[0].PIN[0].PmnPFS_b.PMR = 0; // ?? ovi koraci kao da je los AI ispisao

    // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
    *PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
    // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
    *PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit

}

static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {

}

// ------------------------------------------------------------------------- END
