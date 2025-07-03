#if 0
// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_digital_in.h"
#include "board.h"
#include "delays.h"
#ifdef __XC8__
#include "string.h"
#endif
// -------------------------------------------------------------------- MACROS

#define TEST_PIN_I2C_SCL HAL_PIN_NC // TODO define I2C SCL pin
#define TEST_PIN_I2C_SDA HAL_PIN_NC // TODO define I2C SDA pin

// TODO
// Define an existing pin to check the accuracy of write and read functions
#define TEST_PIN_FIRST_PASS HAL_PIN_NC
// TODO
// Define an existing pin to check the accuracy of write and read functions
#define TEST_PIN_SECOND_PASS HAL_PIN_NC

// TODO
// Set array size.
// This is the number of bytes which shall be sent/read.
// Tako into consideration that the max size is 1 byte( 255 )
#define ARRAY_LENGTH 150

// TODO
// Used for single read check
#define TEST_READ 71

// TODO Set correct slave addres for eeprom click.
#define I2C_MASTER_SLAVE_ADDRESS 0x50

// TODO Define test pins according to hardware
// Feel free to add additional pins if needed
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin)        digital_out_init( &test_pin, pin ); \
                                 digital_out_high( &test_pin ); \
                                 while(1)

#define signal_success(port,pin) digital_out_init( &port, pin ); \
                                 digital_out_write( &port, 1 )

#define signal_end(pin)          signal_error(pin)
// ----------------------------------------------------------------- VARIABLES

static digital_out_t test_pin, scl_pin;
static digital_in_t sda_pin;

static i2c_master_t i2c_master;
static i2c_master_config_t i2c_master_cfg;

static digital_out_t output_pin_first_pass;
static digital_out_t output_pin_second_pass;

static uint8_t write_buffer[ARRAY_LENGTH];
static uint8_t read_buffer[ARRAY_LENGTH];

static volatile uint8_t check_value = 0;
static uint8_t i;
// ----------------------------------------------------------------- USER CODE
void EEPROM_24C02_WrSingle(uint8_t wAddr, uint8_t wData) {
    uint8_t wr_dat[2];

    wr_dat[0] = wAddr;
    wr_dat[1] = wData;

    if ( I2C_MASTER_ERROR == i2c_master_write(&i2c_master, &wr_dat, 2) ) {
        signal_error( TEST_PIN_5 );
    }
}

uint8_t EEPROM_24C02_RdSingle(uint8_t rAddr) {
    uint8_t rd_dat[1];
    uint8_t wr_dat[1];

    wr_dat[0] = rAddr;

    if ( I2C_MASTER_ERROR == i2c_master_write(&i2c_master, &wr_dat, 1) ) {
        signal_error( TEST_PIN_7 );
    }

    if ( I2C_MASTER_ERROR == i2c_master_read(&i2c_master, &rd_dat, 1) ) {
        signal_error( TEST_PIN_8 );
    }

    return rd_dat[0];
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initializes i2c master configuration structure to default values.
    i2c_master_configure_default( &i2c_master_cfg );
    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher then 7. For example, for porta, pins
    // GPIO_PA8, GPIO_PA9, GPIO_PA10 etc.

    i2c_master_cfg.scl = TEST_PIN_I2C_SCL;
    i2c_master_cfg.sda = TEST_PIN_I2C_SDA;

    digital_out_init( &scl_pin, TEST_PIN_I2C_SCL );
    digital_in_init( &sda_pin, TEST_PIN_I2C_SDA);
    digital_out_high( &scl_pin );
    while ( digital_in_read( &sda_pin ) == 0)
    {
        digital_out_low(&scl_pin);
        Delay_ms(1);
        digital_out_high(&scl_pin);
        Delay_ms(1);
    }

    if( ACQUIRE_FAIL == i2c_master_open( &i2c_master, &i2c_master_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    //------------------------------------------------------------------------
    // I2C settings
    //------------------------------------------------------------------------

    // Set i2c timeout.
    // TODO Test different timeout values.
    // Test by debugging and stepping into hal_ll_i2c_master.c.
    // Make sure to confirm that correct value is set to a hw
    // specifc map in hal_ll_i2c_master.c.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_timeout( &i2c_master, 0 ) ) {
        signal_error( TEST_PIN_2 );
    }

    // I2C master set speed.
    // TODO Test different speed values.
    // Make sure to test 100K,400K and if possible 1M.
    // (Test using i2c_master_speed_t enum for different speed).
    // Also Test with different uint32_t values if possible.
    // Using logic analyzer test if set speed is correct.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_speed(&i2c_master,
                                                    I2C_MASTER_SPEED_FULL) ) {
        signal_error( TEST_PIN_3 );
    }

    // I2C master set slave address.
    // TODO It is necessary to set the correct slave address for eeprom click.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_slave_address(&i2c_master,
                                                            I2C_MASTER_SLAVE_ADDRESS) ) {
        signal_error( TEST_PIN_4 );
    }

    for(i = 0; i < ARRAY_LENGTH; i++) {
        EEPROM_24C02_WrSingle(i,0);
        write_buffer[i] = 0;
        Delay_ms(10);
    }

    if ( I2C_MASTER_ERROR == i2c_master_write_then_read(&i2c_master,
                                                        &write_buffer,
                                                        1,
                                                        &read_buffer,
                                                        ARRAY_LENGTH) ) {
        signal_error( TEST_PIN_5 );
    }

    if (!memcmp(write_buffer , read_buffer, sizeof(write_buffer))){
        signal_success(output_pin_first_pass,TEST_PIN_FIRST_PASS);
    }

    for(i = 0; i < ARRAY_LENGTH; i++) {
        EEPROM_24C02_WrSingle(i,i);
        write_buffer[i] = i;
        Delay_ms(10);
    }

    if ( I2C_MASTER_ERROR == i2c_master_write_then_read(&i2c_master,
                                                        &write_buffer,
                                                        1,
                                                        &read_buffer,
                                                        ARRAY_LENGTH) ) {
        signal_error( TEST_PIN_6 );
    }

    if (!memcmp(write_buffer , read_buffer, sizeof(write_buffer))){
        signal_success(output_pin_second_pass,TEST_PIN_SECOND_PASS);
    }

    // TODO Test a couple of different addresses
    // Expected data should be as written earlier.
    if ( TEST_READ != EEPROM_24C02_RdSingle(TEST_READ) ) {
        signal_error( TEST_PIN_7 );
    }

    // Close I2C module.
    // TODO Test by debugging and stepping into.
    // Make sure to confirm that everything is
    // disabled/dealocated etc.
    i2c_master_close(&i2c_master);
    signal_end( TEST_PIN_8 );

    return 0;
}

// ----------------------------------------------------------------------- END

#else
/*
 * Simplified I2C Master Library (Polling, Repeated Start, 7/10-bit Addressing)
 * For RA4M1 or compatible Renesas MCU
 */

#include <stdint.h>
#include <stdbool.h>
#include "mcu.h"  // Replace with correct MCU register definitions

#define I2C_MASTER_OK        (0)
#define I2C_MASTER_ERR       (-1)

// User must define these macros appropriately
// #define IIC1_BASE           (R_IIC1)
// #define IIC_ICCR1           (IIC1_BASE->ICCR1)
// #define IIC_ICCR2           (IIC1_BASE->ICCR2)
// #define IIC_ICMR3           (IIC1_BASE->ICMR3)
// #define IIC_ICDRT           (IIC1_BASE->ICDRT)
// #define IIC_ICDRR           (IIC1_BASE->ICDRR)
// #define IIC_ICSR2           (IIC1_BASE->ICSR2)
// #define IIC_ICSR1           (IIC1_BASE->ICSR1)
// #define IIC_ICFER           (IIC1_BASE->ICFER)
// #define IIC_ICIER           (IIC1_BASE->ICIER)
// #define IIC_ICSER           (IIC1_BASE->ICSER)
// #define IIC_ICMR1           (IIC1_BASE->ICMR1)
// #define IIC_ICMR2           (IIC1_BASE->ICMR2)
// #define IIC_ICBRL           (IIC1_BASE->ICBRL)
// #define IIC_ICBRH           (IIC1_BASE->ICBRH)

static void i2c_master_wait_for_tend(void)
{
    while (!(R_IIC1->ICSR2_b.TEND)) {} // TEND bit
    R_IIC1->ICSR2 &= ~(1 << 6); // Clear TEND
}

static void i2c_master_wait_for_txi(void)
{
    while (R_IIC1->ICSR2 & (1 << 7)) {} // Wait while no transmit data
    R_IIC1->ICSR2 &= ~(1 << 7);
}

static void i2c_master_wait_for_rxi(void)
{
    while (!(R_IIC1->ICSR2 & (1 << 5))) {} // RXI
    R_IIC1->ICSR2 &= ~(1 << 5);
}

static void i2c_master_send_start(void)
{
    R_IIC1->ICCR2 |= (1 << 1); // Set ST bit
    while (!(R_IIC1->ICCR2 & (1 << 1))) {} // Wait for ST cleared
}

static void i2c_master_send_stop(void)
{
    R_IIC1->ICCR2 |= (1 << 3); // Set SP bit
    while (R_IIC1->ICCR2 & (1 << 3)) {} // Wait for SP cleared
}

static void i2c_master_send_address(uint16_t address, bool read)
{
    if (address > 0x7F) {
        // 10-bit address mode
        uint8_t high = 0xF0 | ((address >> 7) & 0x06) | (read ? 1 : 0);
        uint8_t low = address & 0xFF;
        R_IIC1->ICDRT = high;
        i2c_master_wait_for_tend();
        R_IIC1->ICDRT = low;
    } else {
        // 7-bit address mode
        R_IIC1->ICDRT = (address << 1) | (read ? 1 : 0);
    }
    // i2c_master_wait_for_tend();
}

int i2c_master_init(uint32_t bitrate_hz)
{
    // Simplified fixed init
    R_IIC1->ICCR1 = 0; // Stop I2C

    R_IIC1->ICMR1 = 0x00;
    R_IIC1->ICMR2 = 0x00;
    R_IIC1->ICMR3 = 0x00;

    R_IIC1->ICBRL = 20; // Tune these for bitrate
    R_IIC1->ICBRH = 20;

    R_IIC1->ICFER = 0x77;
    R_IIC1->ICIER = 0x00;
    R_IIC1->ICCR1 = 0x80; // Enable I2C

    return I2C_MASTER_OK;
}

int i2c_master_write(uint16_t address, const uint8_t *data, uint32_t length, bool send_stop)
{
    i2c_master_send_start();
    i2c_master_send_address(address, false);

    for (uint32_t i = 0; i < length; i++) {
        R_IIC1->ICDRT = data[i];
        // i2c_master_wait_for_tend();
    }

    i2c_master_wait_for_tend();
    if (send_stop) {
        i2c_master_send_stop();
    }
    return I2C_MASTER_OK;
}

int i2c_master_read(uint16_t address, uint8_t *data, uint32_t length, bool send_stop)
{
    i2c_master_send_start();
    i2c_master_send_address(address, true);

    for (uint32_t i = 0; i < length; i++) {
        if (i == (length - 1)) {
            R_IIC1->ICMR3 |= (1 << 2); // NACK
        }
        i2c_master_wait_for_rxi();
        data[i] = R_IIC1->ICDRR;
    }

    i2c_master_wait_for_tend();
    if (send_stop) {
        i2c_master_send_stop();
    }
    return I2C_MASTER_OK;
}

int main() {
    #if 0
    // Enable IIC1 peripheral
    R_MSTP->MSTPCRB &= ~(1U << 8);
    __asm volatile("dsb");

    // Configure IIC0 pins (SCL = P205, SDA = P206)
    // === 1. Enable write to PFS registers ===
    R_PMISC->PWPR = 0x00;  // Clear B0WI and PFSWE
    R_PMISC->PWPR = 0x40;  // Set PFSWE = 1, B0WI = 0

    // === 2. Set pin functions ===
    // P205 ? IIC0_SCL (PSEL = 0x0F), PMR = 1 (peripheral)
    // R_PFS->P205PFS = (0x0F << 24) | (1 << 16);  // PSEL[4:0] = 0x0F, PMR = 1
    R_PFS->PORT[2].PIN[5].PmnPFS = (0x7 << 24) | (1 << 16);  // PSEL[4:0] = 0x7, PMR = 1

    // P206 ? IIC0_SDA (PSEL = 0x7), PMR = 1 (peripheral)
    // R_PFS->P206PFS = (0x7 << 24) | (1 << 16);  // PSEL[4:0] = 0x7, PMR = 1
    R_PFS->PORT[2].PIN[6].PmnPFS = (0x7 << 24) | (1 << 16);  // PSEL[4:0] = 0x7, PMR = 1

    // === 3. Disable write ===
    R_PMISC->PWPR = 0x80;  // Lock with B0WI = 1

    // Example data to write
    uint8_t write_data[] = { 0x00, 0x10, 0xA5 }; // Example: register 0x10 = 0xA5
    uint8_t read_data[2] = {0};

    // Initialize I2C with desired bitrate (100kHz for example)
    i2c_master_init(100000);

    // Write data to device 0x50 (register + value)
    i2c_master_write(0x50, write_data, sizeof(write_data), false); // No STOP ? repeated start

    // Read back 2 bytes starting from register 0x10
    i2c_master_read(0x50, read_data, 2, true); // STOP after read

    // You can now inspect read_data[0] and read_data[1]
    while (1)
    {
        // Do nothing ? loop forever
    }

    return 0;
    #else

    // Enable IIC1 peripheral
    R_MSTP->MSTPCRB &= ~(1U << 8);
    __asm volatile("dsb");

    // Pin initialization
    R_PMISC->PWPR = 0x00;  // Clear B0WI and PFSWE
    R_PMISC->PWPR = 0x40;  // Set PFSWE = 1, B0WI = 0

    R_PFS->PORT[2].PIN[5].PmnPFS = (0x7 << 24) | (1 << 16);  // PSEL[4:0] = 0x7, PMR = 1
    R_PFS->PORT[2].PIN[6].PmnPFS = (0x7 << 24) | (1 << 16);  // PSEL[4:0] = 0x7, PMR = 1

    R_PMISC->PWPR = 0x80;  // Lock with B0WI = 1

    // I2C initialization
    R_IIC1->ICCR1_b.ICE = 0; // 1. Set the ICCR1.ICE bit set to 0 to set the SCLn and SDAn pins to the inactive state.
    R_IIC1->ICCR1_b.IICRST = 1; // 2. Set the ICCR1.IICRST bit to 1 to initiate IIC reset
    R_IIC1->ICCR1_b.ICE = 1; // 3. Set the ICCR1.ICE bit to 1 to initiate internal reset.

    // 4. Set the SARLy, SARUy, ICSER, ICMR1, ICBRH, and ICBRL registers
    // (y = 0 to 2), and set the other registers as required.
    R_IIC1->SAR[1].U_b.FS = 0;
    R_IIC1->SAR[1].L_b.SVA = 0x50 << 1;
    R_IIC1->ICSER = 0;
    // Bit rate?
    R_IIC1->ICBRL = 20; // Tune these for bitrate
    R_IIC1->ICBRH = 20;
    // Bit rate?

    // Set ICIER // HOW?

    // 5. When the required register settings are complete, set the ICCR1.IICRST bit to 0 to release the IIC reset.
    R_IIC1->ICCR1_b.IICRST = 0;

    while(R_IIC1->ICCR2_b.BBSY); // Wait while the bus is busy

    R_IIC1->ICCR2_b.ST = 1; // Start condition

    // while(!(R_IIC1->ICSR2_b.NACKF)) {
        if(R_IIC1->ICSR2_b.TDRE) {
            R_IIC1->ICDRT = 0x50 << 1;
        }
        if(R_IIC1->ICSR2_b.NACKF) // No slave device recognized
            R_IIC1->ICCR2_b.SP = 1; // Stop condition

        uint8_t dat = 50;
        while(dat)
            while(R_IIC1->ICSR2_b.TDRE)
                R_IIC1->ICDRT = dat--;
        
        while(!(R_IIC1->ICSR2_b.TEND));

    // }

    R_IIC1->ICSR2_b.STOP = 0;
    R_IIC1->ICCR2_b.SP = 1;

    while(!(R_IIC1->ICSR2_b.STOP));

    R_IIC1->ICSR2_b.NACKF = 1;
    R_IIC1->ICSR2_b.STOP = 0;

    return 0;
    #endif
}

#endif