// ------------------------------------------------------------------ INCLUDES

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_digital_in.h"
#include "board.h"

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

void main() {
    // Initializes i2c master configuration structure to default values.
    i2c_master_configure_default( &i2c_master_cfg );
    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher then 7. For example, for porta, pins
    // PA8, PA9, PA10 etc.

    i2c_master_cfg.scl = TEST_PIN_I2C_SCL;
    i2c_master_cfg.sda = TEST_PIN_I2C_SDA;
    
    digital_out_init( &scl_pin, TEST_PIN_I2C_SCL );
    digital_in_init( &sda_pin, TEST_PIN_I2C_SDA);
    digital_out_high( &scl_pin );
    while ( digital_in_read( &sda_pin ) == 0)
    {
        digital_out_low(&scl_pin);
        Delay_us(10);
        digital_out_high(&scl_pin);
        Delay_us(10);
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
        Delay_ms(1);
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
        Delay_ms(1);
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
}

// ----------------------------------------------------------------------- END
