// Include section.

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// BEGIN HW initialization.
#include "hw_eth.h"
// END HW initialization.
#include "mcu.h"

#include "log.h"
#include "board.h"
#ifdef SYSTICK_PRESENT
#include "systick.h"
#endif
#include "drv_digital_in.h"
#include "drv_digital_out.h"
#include "ftp/ftp_client.h"
#include "debug.h"

// Include currently active driver header.
#include "eth_driver.h"

// User defined PHY driver.
#include "drivers/phy/lan8720_driver.h"

// Defined test name.
#define TEST_NAME "MikroE FTP Client Demo"

// Current MCU passed as PLD via CMAKE.
#define MCU_NAME MCU_NAME_CMAKE

// Select button which runs the test.
#define TEST_BUTTON PB1  // TODO

// Define debug console settings.
#define LED_SYSCTICK_CHECK PE0  // TODO
#define LED_SANITY_CHECK PE1    // TODO
#define LED_DEBUG_CHECK PE2     // TODO
#define LED_SYSCTICK_CHECK_POS 0
#define LED_SANITY_POS 1
#define LED_DEBUG_POS 2
#define CONSOLE_BAUD 115200

// Timeout value in ms.
// Used to exit an infinite loop if there is any net error.
#define TIMEOUT_VALUE_MS 10000

// Ethernet interface configuration.
#define APP_IF_NAME "eth0"
#define APP_HOST_NAME "ftp-client-demo"
#define APP_MAC_ADDR "00-AB-CD-EF-55-00"

// Application configuration.
#define APP_FTP_SERVER_NAME "test.rebex.net"
#define APP_FTP_SERVER_PORT 21
#define APP_FTP_LOGIN "demo"
#define APP_FTP_PASSWORD "password"
#define APP_FTP_FILENAME "readme.txt"

// Pointer function typedef.
typedef int (*fun_ptr)(void);
fun_ptr fun_ptr_client_init;
fun_ptr fun_ptr_slac_configure;

// Global variables.
static NetInterface *interface;
static DhcpClientSettings dhcpClientSettings;
static DhcpClientContext dhcpClientContext;
static SlaacSettings slaacSettings;
static SlaacContext slaacContext;
static FtpClientContext ftpClientContext;

// ETH state signal.
static bool ethInitialized = false;
static uint32_t msCount = 0;
uint32_t timeout = 0;

// Debug array with pins.
static digital_out_t debugErrArray[3];
static pin_name_t debugPins[3] = {LED_SYSCTICK_CHECK, LED_SANITY_CHECK, LED_DEBUG_CHECK};

// Test runner button.
static digital_in_t button;

// Debug handle.
log_t console;
static log_cfg_t console_cfg;

// API prototypes.
static void testInitDebug(void);
static void testSetPointers(void);
static int testInitStack(void);
static int testRun(void);
static int testInitClientDhcp(void);
static int testIpv6SlaacEnable(void);

// Task prototypes.
static void ledTask(void);
static error_t ftpClientTest(void);
static error_t httpClientTest(void);
#ifndef SYSTICK_PRESENT
void init_1ms_timer();
#endif

int main(void) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    #ifndef SYSTICK_PRESENT
    init_1ms_timer();
    #else
    // Configure SYSTICK to 1ms interrupt.
    if (!sysTickConfig(GET_TICK_NUMBER_PER_CLOCK)) {
        sysTickInit(15); // Maximum priority - level 15.
    } else {
        while(1);
    }
    #endif

    // Initialize debug console.
    testInitDebug();

    // Set appropriate function pointers.
    // TODO - Map different APIs if needed.
    testSetPointers();

    // Initialize net stack.
    if (testInitStack()) {
        while(1);
    }

    // Initialize DHCP client.
    if ((*fun_ptr_client_init)()) {
        while(1);
    }

    // Initialize SLAAC.
    if ((*fun_ptr_slac_configure)()) {
        while(1);
    }

    // If we get here, ETH module is considered initialized.
    ethInitialized = true;
    while(1) {
        // Run the test once user clicks defined TEST_BUTTON.
        if (testRun()) {
            TRACE_INFO("Test failed.\r\n" );
        } else {
            TRACE_INFO("Test successful.\r\n" );
        }
    }

    return 0;
}

static void testInitDebug(void) {
    for (int i = 0; i < (sizeof(debugErrArray) / sizeof(digital_out_t)); i++) {
        digital_out_init(&debugErrArray[i], debugPins[i]);
        digital_out_low(&debugErrArray[i]);
    }

    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );

    digital_in_init(&button, TEST_BUTTON);

    // Start-up message
    TRACE_INFO("\r\n***************************************\r\n");
    TRACE_INFO("******* %s *******\r\n", TEST_NAME);
    TRACE_INFO("***************************************\r\n");
    TRACE_INFO("Copyright: ${COPYRIGHT_YEAR} MikroElektronika d.o.o.\r\n");
    TRACE_INFO("https://github.com/MikroElektronika/mikrosdk_v2\r\n");
    TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
    TRACE_INFO("Target: %s\r\n", MCU_NAME);
}

static void testSetPointers(void) {
    fun_ptr_client_init = testInitClientDhcp;
    fun_ptr_slac_configure = testIpv6SlaacEnable;
}

static int testInitStack(void) {
    error_t error;
    MacAddr macAddr;

    // TCP/IP stack initialization.
    error = netInit();
    // Any error to report?
    if(error) {
        TRACE_INFO("Failed to initialize TCP/IP stack!\r\n");
        return error;
    }

    // Configure the first Ethernet interface.
    interface = &netInterface[0];

    // Set interface name.
    netSetInterfaceName(interface, APP_IF_NAME);
    // Set host name.
    netSetHostname(interface, APP_HOST_NAME);
    // Set host MAC address.
    macStringToAddr(APP_MAC_ADDR, &macAddr);
    netSetMacAddr(interface, &macAddr);

    /**
     * @brief Select the relevant network adapter.
     * @note Set automatically by mikroSDK based on
     * active setup.
     * @warning Selected setup MUST have ETHERNET module.
     */
    netSetDriver(interface, &ETHERNET_DRIVER_HANDLER);

    /**
     * @brief Map PHY chip.
     * @note Set automatically by mikroSDK based on
     * active setup.
     * @note Set to NULL if you wish to use
     * internal PHY.
     * @warning Selected setup MUST have ETHERNET module.
     */
    netSetPhyDriver(interface, ETHERNET_PHY_CHIP);

    // Initialize network interface.
    error = netConfigInterface(interface);
    // Any error to report?
    if(error) {
        TRACE_INFO("Failed to configure interface %s!\r\n", interface->name);
        return error;
    }

    error = netStartInterface(interface);
    // Any error to report?
    if(error) {
        TRACE_INFO("Failed to start interface %s!\r\n", interface->name);
        return error;
    }

    return NO_ERROR;
}

static int testInitClientDhcp(void) {
    // Error code.
    error_t error;

    // Get default settings.
    dhcpClientGetDefaultSettings(&dhcpClientSettings);
    // Set the network interface to be configured by DHCP.
    dhcpClientSettings.interface = interface;
    // Disable rapid commit option.
    dhcpClientSettings.rapidCommit = FALSE;

    // DHCP client initialization.
    error = dhcpClientInit(&dhcpClientContext, &dhcpClientSettings);
    // Failed to initialize DHCP client?
    if(error) {
        TRACE_INFO("Failed to initialize DHCP client!\r\n");
        return error;
    }

    // Start DHCP client.
    error = dhcpClientStart(&dhcpClientContext);
    // Failed to start DHCP client?
    if(error) {
        TRACE_INFO("Failed to start DHCP client!\r\n");
        return error;
    }

    return NO_ERROR;
}

static int testIpv6SlaacEnable(void) {
    // Error code.
    error_t error;

    // Get default settings.
    slaacGetDefaultSettings(&slaacSettings);
    // Set the network interface to be configured.
    slaacSettings.interface = interface;

    // SLAAC initialization.
    error = slaacInit(&slaacContext, &slaacSettings);
    // Failed to initialize SLAAC?
    if(error) {
        TRACE_INFO("Failed to initialize SLAAC!\r\n");
        return error;
    }

    // Start IPv6 address autoconfiguration process.
    error = slaacStart(&slaacContext);
    // Failed to start SLAAC process?
    if(error) {
        TRACE_INFO("Failed to start SLAAC!\r\n");
        return error;
    }

    return NO_ERROR;
}

static int testRun(void) {
    // Error code.
    error_t error;

    // Run FTP Client test.
    while (!digital_in_read(&button));
    error = ftpClientTest();
    while (digital_in_read(&button));

    return (int)error;
}

static error_t ftpClientTest(void) {
    error_t error;
    size_t n;
    IpAddr ipAddr;
    char_t buffer[128];

    // Initialize FTP client context.
    ftpClientInit(&ftpClientContext);

    // Start of exception handling block.
    do {
        // Debug message
        TRACE_INFO("\r\n\r\nResolving server name...\r\n");

        // Resolve FTP server name.
        timeout = 0;
        do {
            if (TIMEOUT_VALUE_MS <= timeout) {
                timeout = 0;
                break;
            }
            error = getHostByName(NULL, APP_FTP_SERVER_NAME, &ipAddr, 0);
        } while (error);

        // Set timeout value for blocking operations.
        error = ftpClientSetTimeout(&ftpClientContext, 20000);
        // Any error to report?
        if (error)
            break;

        // Debug message.
        TRACE_INFO("Connecting to FTP server %s...\r\n",
                   ipAddrToString(&ipAddr, NULL));

        // Connect to the FTP server.
        timeout = 0;
        do {
            if (TIMEOUT_VALUE_MS <= timeout) {
                timeout = 0;
                break;
            }
            error = ftpClientConnect(&ftpClientContext, &ipAddr,
                                     APP_FTP_SERVER_PORT,
                                     FTP_MODE_PLAINTEXT | FTP_MODE_PASSIVE);
        } while (error);

        // Any error to report?
        if (error) {
            // Debug message.
            TRACE_INFO("Failed to connect to FTP server!\r\n");
            break;
        }

        // Login to the FTP server using the provided username and password.
        timeout = 0;
        do {
            if (TIMEOUT_VALUE_MS <= timeout) {
                timeout = 0;
                break;
            }
            error = ftpClientLogin(&ftpClientContext, APP_FTP_LOGIN, APP_FTP_PASSWORD);
        } while (error);

        // Any error to report?
        if(error)
            break;

        // Open the specified file for reading.
        timeout = 0;
        do {
            if (TIMEOUT_VALUE_MS <= timeout) {
                timeout = 0;
                break;
            }
            error = ftpClientOpenFile(&ftpClientContext,
                                    APP_FTP_FILENAME,
                                    FTP_FILE_MODE_READ | FTP_FILE_MODE_BINARY);
        } while (error);

        // Any error to report?
        if(error)
            break;

        // Read the contents of the file.
        while(!error)
        {
            // Read data.
            timeout = 0;
            do {
                if (TIMEOUT_VALUE_MS <= timeout) {
                    timeout = 0;
                    break;
                }
                error = ftpClientReadFile(&ftpClientContext, buffer, sizeof(buffer) - 1, &n, 0);
            } while ((error != NO_ERROR) && (error != ERROR_END_OF_STREAM));

            // Check status code.
            if(NO_ERROR == error)
            {
                // Properly terminate the string with a NULL character.
                buffer[n] = '\0';
                // Dump the contents of the file.
                TRACE_INFO("%s", buffer);
            }
        }

        // Terminate the string with a line feed.
        TRACE_INFO("\r\n");

        // Any error to report?
        if(error != ERROR_END_OF_STREAM)
            break;

        // Close file.
        timeout = 0;
        do {
            if (TIMEOUT_VALUE_MS <= timeout) {
                timeout = 0;
                break;
            }
            error = ftpClientCloseFile(&ftpClientContext);
        } while (error);

        // Any error to report?
        if(error)
            break;

        // Gracefully disconnect from the FTP server.
        ftpClientDisconnect(&ftpClientContext);

        // Debug message.
        TRACE_INFO("Connection closed\r\n");

        // End of exception handling block.
    } while (0);

    // Release FTP client context.
    ftpClientDeinit(&ftpClientContext);

    // Return status code.
    return error;
}

/**
 * @note Using the stack without an OS requires @ref systemTicks
 * to be incremented every 1ms.
 */
extern volatile systime_t systemTicks;
#ifndef SYSTICK_PRESENT
void __attribute__((interrupt(IPL1AUTO), vector(_TIMER_1_VECTOR))) _TIMER_1_HANDLER(void) {
    IFS0bits.T1IF = 0;
#else
__attribute__ ((interrupt("IRQ"))) void SysTick_Handler(void) {
#endif
    msCount++;
    timeout++;
    systemTicks++;

    ledTask();

    if (ethInitialized) {
        netTask();
    }
}

// Sanity check - is the MCU still running? - Called from ISR.
static void ledTask(void) {
    // Check if interrupt is 1ms.
    digital_out_toggle(&debugErrArray[LED_SYSCTICK_CHECK_POS]);
    // 1000ms counted.
    if (msCount == 1000) {
        msCount = 0;
        digital_out_toggle(&debugErrArray[LED_SANITY_POS]);
    }
}

#ifndef SYSTICK_PRESENT
void init_1ms_timer() {
    uint16_t prescaler_list[4] = { 256, 64, 8, 1 };
    uint16_t prescaler;
    int8_t index = -1;
    uint16_t remnant;
    uint32_t count = 0;
#if defined(PIC32MZ)
    uint8_t pbclk_div = PB3DIVbits.PBDIV + 1;
#elif defined(PIC32MX)
    uint8_t pbclk_div = (uint8_t)1 << OSCCONbits.PBDIV;
#endif
    uint32_t timer_clock = OSC_KHZ / pbclk_div;
    uint8_t prescaler_index;
    uint32_t period;

    // Configure Timer1 for periodic 1ms interrupts.
    do {
        ++index;
        prescaler = prescaler_list[index];
        remnant = timer_clock % prescaler;
        count = timer_clock / prescaler;
    }
    while ( ( 0 != remnant ) && ( count <= 65535 ) );

    if ( count > 65535 ) {
        if ( 0 < index ) {
            --index;
            prescaler = prescaler_list[index];
            count = timer_clock / prescaler;

        } else {
            TRACE_INFO("No valid Timer1 configuration possible!\r\n");
            while (1);
        }
    } else {
        prescaler_index = (uint8_t)(3 - index);     // Set prescaler to 1:64.
        period = count - 1;
    }

    T1CONbits.TON = 0;          // Disable Timer1 during configuration.
    T1CONbits.TCS = 0;          // Select internal peripheral clock.
    T1CONbits.TCKPS = prescaler_index; // Set the prescaler for 1ms interrupt.
    T1CONbits.TGATE = 0;        // Disable gated time accumulation.

    TMR1 = 0;                   // Clear Timer value.
    PR1 = period;               // Set Period value for 1ms interrupt.

    // Clear Timer1 interrupt flag.
    IFS0bits.T1IF = 0;
    // Set Timer1 interrupt priority to 1.
    IPC1bits.T1IP = 1;
    // Enable Multi-Vector interrupts.
    INTCONbits.MVEC = 1;
    // Enable global interrupts.
    __builtin_enable_interrupts();

    // Enable Timer1 interrupt.
    IEC0bits.T1IE = 1;
    // Start the Timer1.
    T1CONbits.TON = 1;
}
#endif

#ifdef PIC32MZ
void __attribute__((interrupt(IPL2AUTO), vector(_ETHERNET_VECTOR))) _ETHERNET_HANDLER(void) {
    digital_out_toggle(&debugErrArray[LED_DEBUG_POS]);
    pic32mzEthIrqHandler();
}
#endif

#ifdef PIC32MX
void __attribute__((interrupt(IPL2AUTO), vector(_ETH_VECTOR))) _ETH_HANDLER(void) {
    digital_out_toggle(&debugErrArray[LED_DEBUG_POS]);
    pic32mxEthIrqHandler();
}
#endif
