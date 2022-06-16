// ------------------------------------------------------------------ INCLUDES

#include "mikrobus_i2c.h"

// -------------------------------------------------------------------- MACROS

// NOTE If set to true, test is done on a single module.
//      If set to false, test is done on all mikroBUS pins
//      defined in 'board.h'.
#define SINGLE_MIKROBUS true

// TODO Define timeout if using multiple mikroBUSes.
// NOTE Use this time to place EEPROM click on another mikroBUS.
#define change_bus_wait_time_seconds 10

#if SINGLE_MIKROBUS
    // TODO Define I2C test pins if 'SINGLE_MIKROBUS' set to 'true'.
    // NOTE MIKROBUS_x_SCL where 'x' is mikroBUS number.
    // NOTE MIKROBUS_x_SDA where 'x' is mikroBUS number.
    #define TEST_PIN_SCL HAL_PIN_NC
    #define TEST_PIN_SDA HAL_PIN_NC
    #define TEST_MODULE_COUNT 1
    pin_name_t test_pins[1][2] = {TEST_PIN_SCL,TEST_PIN_SDA};
#else
    #define TEST_MODULE_COUNT MIKROBUS_COUNT
    pin_name_t (*test_pins)[2] = test_pins_mikrobus;
#endif

// TODO Declare device slave address
// NOTE 0x50 is by default.
#define I2C_MASTER_SLAVE_ADDRESS 0x50

// TODO Declare data check pin.
// NOTE These pins are turned ON if
// data comparison was successful.
#define TEST_PIN_FIRST_PASS HAL_PIN_NC
#define TEST_PIN_SECOND_PASS HAL_PIN_NC

// TODO Declare number of data to be written/read.
#define ARRAY_LENGTH 150

// TODO Declare single write/read data.
#define TEST_READ 71

// Declare error signal pins.
// NOTE Optional
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC

// NOTE Do not edit these.
#define MIKROBUS_SCL_PIN 0
#define MIKROBUS_SDA_PIN 1

// ----------------------------------------------------------------- VARIABLES

static digital_out_t test_pin, scl_pin;
static digital_in_t sda_pin;

static i2c_master_t i2c_master;
static i2c_master_config_t i2c_master_cfg;

static digital_out_t output_pin_first_pass;
static digital_out_t output_pin_second_pass;

static uint8_t write_buffer[ARRAY_LENGTH];
static uint8_t read_buffer[ARRAY_LENGTH];

static uint8_t i;

// ------------------------------------------------------ SUPPORTING FUNCTIONS

/*< @brief Single data write function. */
void eeprom_write_single(uint8_t wAddr, uint8_t wData) {
    uint8_t wr_dat[2];

    wr_dat[0] = wAddr;
    wr_dat[1] = wData;

    if ( I2C_MASTER_ERROR == i2c_master_write(&i2c_master, &wr_dat, 2) ) {
        signal_error( TEST_PIN_5 );
    }
}

/*< @brief Single data read function. */
uint8_t eeprom_read_single(uint8_t rAddr) {
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

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    uint8_t cnt = 0;

    while(1) {
        for ( cnt = 0; cnt < TEST_MODULE_COUNT; cnt++ ) {
            // STEP 1: If I2C pins are stuck from previous data exchange,
            //         make sure to reset them first.
            // ---------------------------------------------------------------
            i2c_master_configure_default( &i2c_master_cfg );

            // NOTE 'cnt' represents mikroBUS number
            //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
            i2c_master_cfg.scl = test_pins[cnt][MIKROBUS_SCL_PIN];
            i2c_master_cfg.sda = test_pins[cnt][MIKROBUS_SDA_PIN];

            digital_out_init( &scl_pin, i2c_master_cfg.scl );
            digital_in_init( &sda_pin, i2c_master_cfg.sda);
            digital_out_high( &scl_pin );
            while ( digital_in_read( &sda_pin ) == 0)
            {
                digital_out_low(&scl_pin);
                Delay_ms(1);
                digital_out_high(&scl_pin);
                Delay_ms(1);
            }
            // ---------------------------------------------------------------
            
            // STEP 2: Initialize I2C module and configure it.
            // ---------------------------------------------------------------
            if( ACQUIRE_FAIL == i2c_master_open( &i2c_master, &i2c_master_cfg ) ) {
                signal_error( TEST_PIN_1 );
            }

            if ( I2C_MASTER_SUCCESS != i2c_master_set_timeout( &i2c_master, 0 ) ) {
                signal_error( TEST_PIN_2 );
            }

            if ( I2C_MASTER_SUCCESS != i2c_master_set_speed(&i2c_master,
                                                            I2C_MASTER_SPEED_FULL) ) {
                signal_error( TEST_PIN_3 );
            }

            if ( I2C_MASTER_SUCCESS != i2c_master_set_slave_address(&i2c_master,
                                                                    I2C_MASTER_SLAVE_ADDRESS) ) {
                signal_error( TEST_PIN_4 );
            }
            // ---------------------------------------------------------------
            
            // STEP 3: EEPROM click has retensive memory, so we first have 
            //         to make sure the data is cleared. (write all zeros)
            // ---------------------------------------------------------------
            for(i = 0; i < ARRAY_LENGTH; i++) {
                eeprom_write_single(i,0);
                write_buffer[i] = 0;
                Delay_ms(1);
            }
            // ---------------------------------------------------------------

            // STEP 4: Read all data from previously cleared addresses.
            // ---------------------------------------------------------------
            if ( I2C_MASTER_ERROR == i2c_master_write_then_read(&i2c_master,
                                                                &write_buffer,
                                                                1,
                                                                &read_buffer,
                                                                ARRAY_LENGTH) ) {
                signal_error( TEST_PIN_5 );
            }
            // ---------------------------------------------------------------

            // STEP 5: Compare the data. Both arrays should be zero filled.
            // ---------------------------------------------------------------
            if (!memcmp(write_buffer , read_buffer, sizeof(write_buffer))){
                signal_success(output_pin_first_pass,TEST_PIN_FIRST_PASS);
            }
            // ---------------------------------------------------------------

            // STEP 6: Now write actual data to addresses.
            // ---------------------------------------------------------------
            for(i = 0; i < ARRAY_LENGTH; i++) {
                eeprom_write_single(i,i);
                write_buffer[i] = i;
                Delay_ms(1);
            }
            // ---------------------------------------------------------------

            // STEP 7: Read all data from previously written addresses.
            // ---------------------------------------------------------------
            if ( I2C_MASTER_ERROR == i2c_master_write_then_read(&i2c_master,
                                                                &write_buffer,
                                                                1,
                                                                &read_buffer,
                                                                ARRAY_LENGTH) ) {
                signal_error( TEST_PIN_6 );
            }
            // ---------------------------------------------------------------

            // STEP 8: Compare the data. Both arrays should have data from
            //         0 to 'ARRAY_LENGTH'.
            // ---------------------------------------------------------------
            if (!memcmp(write_buffer , read_buffer, sizeof(write_buffer))){
                signal_success(output_pin_second_pass,TEST_PIN_SECOND_PASS);
            }
            // ---------------------------------------------------------------

            // STEP 9: Do a single read from 'TEST_READ' address.
            // NOTE Make sure that 'TEST_READ' is an address between
            //      0 and 'ARRAY_LENGTH'.
            // ---------------------------------------------------------------
            if ( TEST_READ != eeprom_read_single(TEST_READ) ) {
                signal_error( TEST_PIN_7 );
            }
            // ---------------------------------------------------------------

            // STEP 10: Close the module and prepare for next mikroBUS.
            // ---------------------------------------------------------------
            i2c_master_close(&i2c_master);

            Delay_1sec();
            digital_out_low(&output_pin_first_pass);
            digital_out_low(&output_pin_second_pass);

            Delay_ms(change_bus_wait_time_seconds*1000);
            // ---------------------------------------------------------------
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
