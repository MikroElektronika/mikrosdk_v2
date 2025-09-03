// TODO
// Test is done by checking board hardware status / LED's.
// TODO
// Make sure to test different pins.
// Also, make sure to use higher nibble pins.
// For example, if port is 16-bit, make sure
// to use GPIO_PB8-GPIO_PB15.
// If port is 32-bit, make sure to use pins from
// GPIO_PB16-GPIO_PB31. -- NXP specific( 32-bit ports )
// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_port.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS
// TODO
#define TEST_CLOCK        false
#define CLOCK_TEST_PORT   HAL_PORT_NC

#define TEST_FLATTENER    false

#define FULL_TEST         false

#if FULL_TEST
#define PIN_TEST          true
#define PORT_TEST         true
#define BUTTON_TEST       true
#else
#define PIN_TEST          true
#define PORT_TEST         true
#define BUTTON_TEST       true
#endif
// TODO
// Define port used for signaling errors.
#define PORT_SIGNAL_ERROR GPIO_PORT_A // HAL_PORT_NC // Example: GPIO_PORT_C
#define signal_error port_init( &test_port, PORT_SIGNAL_ERROR, \
                                PORT_MASK, PIN_DIRECTION_DIGITAL_OUTPUT ); \
                     while(1) { \
                     port_write( &test_port, PORT_MASK ); \
                     Delay_100ms(); \
                     port_write( &test_port, ~PORT_MASK ); \
                     }

#define CLOCK_TEST(x) port_init( &test_port, x, 0xFF, PIN_DIRECTION_DIGITAL_OUTPUT ); \
                      while(1) { \
                          port_write( &test_port, 0xFF ); \
                          Delay_1sec(); \
                          port_write( &test_port, 0x00 ); \
                          Delay_1sec(); \
                      }

// TODO
// Define port used for testing.
#define PORT_NAME GPIO_PORT_B  //HAL_PORT_NC // Example: GPIO_PORT_B
#define PORT_MASK (port_size_t)0x0000FFFF
#define PORT_READ_VALUE 0xAA
#define SINGLE_LED_DELAY 300  // Delay LED single shift test.
// TODO
// Define pins used for testing digital in/out.
#define LED GPIO_PE0        // Example: GPIO_PA0
#define BUTTON GPIO_PE1     // Example: GPIO_PB0
// ----------------------------------------------------------------- VARIABLES
static port_t test_port;          // PORT driver context structure.
static digital_in_t input_pin;    // Digital input driver context structure.
static digital_out_t output_pin;  // Digital output driver context structure.

static uint8_t port_counter = port_count_size;  // Defined in memake file.
// ----------------------------------------------------------------- USER CODE

typedef struct
{
    uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    uint32_t AHBCLK;                /*!< [0x0004] AHB Devices Clock Enable Control Register                        */
    uint32_t APBCLK0;               /*!< [0x0008] APB Devices Clock Enable Control Register 0                      */
    uint32_t APBCLK1;               /*!< [0x000C] APB Devices Clock Enable Control Register 1                      */
    uint32_t CLKSEL0;               /*!< [0x0010] Clock Source Select Control Register 0                           */
    uint32_t CLKSEL1;               /*!< [0x0014] Clock Source Select Control Register 1                           */
    uint32_t CLKSEL2;               /*!< [0x0018] Clock Source Select Control Register 2                           */
    uint32_t CLKSEL3;               /*!< [0x001C] Clock Source Select Control Register 3                           */
    uint32_t CLKDIV0;               /*!< [0x0020] Clock Divider Number Register 0                                  */
    uint32_t CLKDIV1;               /*!< [0x0024] Clock Divider Number Register 1                                  */
    uint32_t RESERVE0[2];
    uint32_t CLKDIV4;               /*!< [0x0030] Clock Divider Number Register 4                                  */
    uint32_t RESERVE7[1];
    uint32_t RESERVE1[2];
    uint32_t PLLCTL;                /*!< [0x0040] PLL Control Register                                             */
    uint32_t RESERVE2[3];
    uint32_t STATUS;                /*!< [0x0050] Clock Status Monitor Register                                    */
    uint32_t RESERVE3[3];
    uint32_t CLKOCTL;               /*!< [0x0060] Clock Output Control Register                                    */
    uint32_t RESERVE4[3];
    uint32_t CLKDCTL;               /*!< [0x0070] Clock Fail Detector Control Register                             */
    uint32_t CLKDSTS;               /*!< [0x0074] Clock Fail Detector Status Register                              */
    uint32_t CDUPB;                 /*!< [0x0078] Clock Frequency Detector Upper Boundary Register                 */
    uint32_t CDLOWB;                /*!< [0x007C] Clock Frequency Detector Low Boundary Register                   */
    uint32_t RESERVE5[4];
    uint32_t PMUCTL;                /*!< [0x0090] Power Manager Control Register                                   */
    uint32_t PMUSTS;                /*!< [0x0094] Power Manager Status Register                                    */
    uint32_t RESERVE6[1];
    uint32_t SWKDBCTL;              /*!< [0x009C] Standby Power-down Wake-up De-bounce Control Register            */
    uint32_t PASWKCTL;              /*!< [0x00A0] GPA Standby Power-down Wake-up Control Register                  */
    uint32_t PBSWKCTL;              /*!< [0x00A4] GPB Standby Power-down Wake-up Control Register                  */
    uint32_t PCSWKCTL;              /*!< [0x00A8] GPC Standby Power-down Wake-up Control Register                  */
    uint32_t PDSWKCTL;              /*!< [0x00AC] GPD Standby Power-down Wake-up Control Register                  */
    uint32_t IOPDCTL;               /*!< [0x00B0] GPIO Standby Power-down Control Register                         */
    uint32_t HXTFSEL;               /*!< [0x00B4] HXT Filter Select Control Register                               */
}clk_t;

#define CLK_BASE 0x40000200;
static clk_t* clk = CLK_BASE;

#define CLK_PWRCTL_HIRCEN_Pos            (2)

#define CLK_STATUS_MIRCSTB_Pos           (5)
#define CLK_STATUS_MIRCSTB_Msk           (0x1ul << CLK_STATUS_MIRCSTB_Pos)

#define CLK_CLKSEL0_HCLKSEL_Pos          (0)                                              
#define CLK_CLKSEL0_HCLKSEL_Msk          (0x7ul << CLK_CLKSEL0_HCLKSEL_Pos)

#define CLK_CLKDIV0_HCLKDIV_Pos          (0)
#define CLK_CLKDIV0_HCLKDIV_Msk          (0xful << CLK_CLKDIV0_HCLKDIV_Pos)

#define CLK_CLKSEL1_CLKOSEL_Pos          (28) 

#define SYS_GPC_MFPH_PC13MFP_Pos         (20)

#define SYS_GPC_MFPH 0x40000044

static uint32_t* gpc_mfph = SYS_GPC_MFPH;

void clock_init()
{
    /* Enable internal HIRC (12 MHz) */
    //CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Enable internal HIRC (48 MHz) */
    // CLK_EnableXtalRC(CLK_PWRCTL_HIRC48EN_Msk);

    clk->PWRCTL |= ( 0x1 << CLK_PWRCTL_HIRCEN_Pos );

    /* Wait for HIRC clock ready */
    // CLK_WaitClockReady(CLK_STATUS_HIRC48STB_Msk);
    while ( !( clk->STATUS & CLK_STATUS_MIRCSTB_Msk ) );

    /* Set HCLK source to HIRC and divider to 1 */
    // CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC48, CLK_CLKDIV0_HCLK(1));
    clk->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    clk->CLKDIV0 &= ~CLK_CLKDIV0_HCLKDIV_Msk;

    /* Update System Core Clock variables */
    //SystemCoreClockUpdate();

    /* Set PC13 to CLKO function (for clock frequency verification) */
    //SYS->GPC_MFPH = (SYS->GPC_MFPL & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;
    *gpc_mfph &= ~( 0xFUL << SYS_GPC_MFPH_PC13MFP_Pos );
    *gpc_mfph |= ( 0xDUL << SYS_GPC_MFPH_PC13MFP_Pos );

    /* Select CLKO clock source as HCLK (should be 12 MHz) */
    //CLK_EnableCKO(0x3 << CLK_CLKSEL1_CLKOSEL_Pos, 0, 1); // 0 = divide by 1
    clk->CLKSEL1 |= ( 0x3 <<  CLK_CLKSEL1_CLKOSEL_Pos );

   // CLK_EnableModuleClock(GPA_MODULE);
}


int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    clock_init();

    volatile pin_name_t fetch_pin = hal_gpio_fetch_pin(LED);
    volatile port_name_t fetch_port = hal_gpio_fetch_port(LED);

    #if TEST_CLOCK
    CLOCK_TEST( CLOCK_TEST_PORT );
    #endif

    #if TEST_FLATTENER
    digital_out_init( &output_pin, LED );
    while(1) {
        digital_out_toggle( &output_pin );
    }
    #endif

    #if PORT_TEST
    // ------------------------------------------------------------------ PORT
    // TODO
    // Test out different ports using different masks.
    // Output on LED's should be as expected based on defined port/mask.
    port_init( &test_port, PORT_NAME, PORT_MASK, PIN_DIRECTION_DIGITAL_OUTPUT );

    // TODO
    // Make sure to use a full port ( all LED's connected )
    // All LED's should turn on.
    port_write( &test_port, PORT_MASK );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, ~PORT_MASK );
    Delay_1sec();
    // All LED's should turn on.
    port_write( &test_port, PORT_MASK );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, ~PORT_MASK );
    Delay_1sec();

    // TODO
    // This is a sanity check using pin shifting
    // Make sure to define the delay value in order
    // to see all LED's change.
    while ( --port_counter ) {
        port_write( &test_port, 1ul << port_counter );
        Delay_ms(SINGLE_LED_DELAY);
    }
    for ( uint8_t i = 0; i < port_count_size; i++ ) {
        port_write( &test_port, 1ul << i );
        Delay_ms(SINGLE_LED_DELAY);
    }

    // TODO
    // Test read on different ports.
    port_write( &test_port, PORT_READ_VALUE );
    if ( PORT_READ_VALUE != port_read( &test_port ) ) {
        signal_error
    }
    Delay_1sec();
    #endif
    // -------------------------------------------------------------- EOF PORT
    // -------------------------------------------------------- DIGITAL_IN_OUT
    volatile uint8_t value = 0;
    #if PIN_TEST
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, LED );

    // TODO
    // Check if defined pin is being toggled.
    uint8_t i = 60;
    while ( i-- > 40 ) {
        digital_out_high( &output_pin );
        Delay_100ms();
        digital_out_low ( &output_pin );
        Delay_100ms();
    }

    while ( i-- > 20 ) {
        digital_out_toggle( &output_pin );
        Delay_100ms();
    }

    while ( i-- ) {
        digital_out_write( &output_pin, true );
        Delay_100ms();
        digital_out_write( &output_pin, false );
        Delay_100ms();
    }
    #endif
    #if BUTTON_TEST
    // Initializes digital input driver context structure and individual GPIO
    // pin as digital input.
    digital_in_init( &input_pin, BUTTON );
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, LED );
    digital_out_write( &output_pin, value );  // Write read value.
    digital_out_write( &output_pin, value );  // Write read value.

    while(1) {
        // TODO
        // Set button press level for PORT high.
        // Pull down pin.
        // By pressing adequate pin button, same
        // value should be set to defined LED pin.
        value = digital_in_read( &input_pin );    // Read digital input value.
        digital_out_write( &output_pin, value );  // Write read value.
    }
    #endif
    // -----------------------------------------------------EOF DIGITAL_IN_OUT
    while(1);

    return 0;
}

// ----------------------------------------------------------------------- END
