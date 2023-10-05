// Include section.

// BEGIN HW initialization.
#include "hw_eth.h"
// END HW initialization.

#include "log.h"
#include "board.h"
#include "delays.h"
#include "systick.h"
#include "core_header.h"
#include "drv_digital_in.h"
#include "drv_digital_out.h"
#include "ftp/ftp_client.h"

// Include currently active driver header.
#include "eth_driver.h"

// User defined PHY driver.
#include "drivers/phy/lan8720_driver.h"

// Defined test name.
#define TEST_NAME "MikroE FTP Client Demo"

// Current MCU passed as PLD via CMAKE.
#define MCU_NAME MCU_NAME_CMAKE

// Select button which runs the test.
#define TEST_BUTTON PB1

// Define debug console settings.
#define LED_SYSCTICK_CHECK PD2
#define LED_SANITY_CHECK PD3
#define LED_DEBUG_CHECK PD4
#define LED_SYSCTICK_CHECK_POS 0
#define LED_SANITY_POS 1
#define LED_DEBUG_POS 2
#define CONSOLE_BAUD 115200

// Timeout value in ms.
// Used to exit an infinite loop if there is any net error.
#define TIMEOUT_VALUE_MS 5000

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
static uint32_t timeout = 0;

// Debug array with pins.
static digital_out_t debugErrArray[3];
static pin_name_t debugPins[3] = {LED_SYSCTICK_CHECK, LED_SANITY_CHECK, LED_DEBUG_CHECK};

// Test runner button.
static digital_in_t button;

// Debug handle.
static log_t console;
static log_cfg_t console_cfg;

// API prototypes.
static void testInitDebug(void);
static void testSetPointers(void);
static int testInitStack(void);
static int testRun(void);
static int testInitClientDhcp(void);
static int testIpv6SlaacEnable(void);

// Task prototypes.
static void ledTask(void) __attribute__ ((interrupt));
static error_t ftpClientTest(void);

int main(void) {
    // Configure SYSTICK to 1ms interrupt.
    if (!sysTickConfig(GET_TICK_NUMBER_PER_CLOCK)) {
        sysTickInit(15); // Maximum priority - level 15.
    } else {
        while(1);
    }

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
            log_printf(&console, "Test failed.\r\n" );
        } else {
            log_printf(&console, "Test successful.\r\n" );
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
    log_printf(&console, "\r\n***************************************\r\n");
    log_printf(&console, "******* %s *******\r\n", TEST_NAME);
    log_printf(&console, "***************************************\r\n");
    log_printf(&console, "Copyright: 2023 MikroElektronika d.o.o.\r\n");
    log_printf(&console, "https://github.com/MikroElektronika/mikrosdk_v2\r\n");
    log_printf(&console, "Compiled: %s %s\r\n", __DATE__, __TIME__);
    log_printf(&console, "Target: %s\r\n", MCU_NAME);
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
        log_printf(&console, "Failed to initialize TCP/IP stack!\r\n");
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
        log_printf(&console, "Failed to configure interface %s!\r\n", interface->name);
        return error;
    }

    error = netStartInterface(interface);
    // Any error to report?
    if(error) {
        log_printf(&console, "Failed to start interface %s!\r\n", interface->name);
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
        log_printf(&console, "Failed to initialize DHCP client!\r\n");
        return error;
    }

    // Start DHCP client.
    error = dhcpClientStart(&dhcpClientContext);
    // Failed to start DHCP client?
    if(error) {
        log_printf(&console, "Failed to start DHCP client!\r\n");
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
        log_printf(&console, "Failed to initialize SLAAC!\r\n");
        return error;
    }

    // Start IPv6 address autoconfiguration process.
    error = slaacStart(&slaacContext);
    // Failed to start SLAAC process?
    if(error) {
        log_printf(&console, "Failed to start SLAAC!\r\n");
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

    // Set initial time counter to 0.
    timeout = 0;

    // Initialize FTP client context.
    ftpClientInit(&ftpClientContext);

    // Start of exception handling block.
    do {
        // Debug message
        log_printf(&console, "\r\n\r\nResolving server name...\r\n");

        // Resolve FTP server name.
        do {
            if (TIMEOUT_VALUE_MS == timeout) {
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
        log_printf(&console, "Connecting to FTP server %s...\r\n",
                   ipAddrToString(&ipAddr, NULL));

        timeout = 0;
        // Connect to the FTP server.
        do {
            if (TIMEOUT_VALUE_MS == timeout) {
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
            log_printf(&console, "Failed to connect to FTP server!\r\n");
            break;
        }

        timeout = 0;
        // Login to the FTP server using the provided username and password.
        do {
            if (TIMEOUT_VALUE_MS == timeout) {
                timeout = 0;
                break;
            }
            error = ftpClientLogin(&ftpClientContext, APP_FTP_LOGIN, APP_FTP_PASSWORD);
        } while (error);

        // Any error to report?
        if(error)
            break;

        timeout = 0;
        // Open the specified file for reading.
        do {
            if (TIMEOUT_VALUE_MS == timeout) {
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
            timeout = 0;
            // Read data.
            do {
                if (TIMEOUT_VALUE_MS == timeout) {
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
                log_printf(&console, "%s", buffer);
            }
        }

        // Terminate the string with a line feed.
        log_printf(&console, "\r\n");

        // Any error to report?
        if(error != ERROR_END_OF_STREAM)
            break;

        timeout = 0;
        // Close file.
        do {
            if (TIMEOUT_VALUE_MS == timeout) {
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
        log_printf(&console, "Connection closed\r\n");

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
__attribute__ ((interrupt("IRQ"))) void SysTick_Handler(void) {
    msCount++;
    timeout++;
    systemTicks++;

    ledTask();

    if (ethInitialized)
        netTask();
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
