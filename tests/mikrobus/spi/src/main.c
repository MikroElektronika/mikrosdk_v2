// ------------------------------------------------------------------ INCLUDES

#include "mikrobus_spi.h"

// -------------------------------------------------------------------- MACROS

// NOTE If set to true, test is done on a single module.
//      If set to false, test is done on all mikroBUS pins
//      defined in 'board.h'.
#define SINGLE_MIKROBUS true

// TODO Define timeout if using multiple mikroBUSes.
// NOTE Use this time to place SRAM click on another mikroBUS.
// NOTE Spi communictaion isn't blocking, so theoretically
//      this isn't necessary.
#define change_bus_wait_time_seconds 10

#if SINGLE_MIKROBUS
    // TODO Define SPI test pins.
    // NOTE MIKROBUS_x_SCK  where 'x' is mikroBUS number.
    // NOTE MIKROBUS_x_MISO where 'x' is mikroBUS number.
    // NOTE MIKROBUS_x_MOSI where 'x' is mikroBUS number.
    // NOTE MIKROBUS_x_CS   where 'x' is mikroBUS number.
    #define TEST_PIN_SCK  HAL_PIN_NC
    #define TEST_PIN_MISO HAL_PIN_NC
    #define TEST_PIN_MOSI HAL_PIN_NC
    #define TEST_PIN_CS   HAL_PIN_NC
    #define TEST_MODULE_COUNT 1
    pin_name_t test_pins[1][4] = {TEST_PIN_SCK,TEST_PIN_MISO,TEST_PIN_MOSI,TEST_PIN_CS};
#else
    #define TEST_MODULE_COUNT MIKROBUS_COUNT
    pin_name_t (*test_pins)[4] = test_pins_mikrobus;
#endif

// TODO Declare desired speed value.
// NOTE 100K by default.
#define SPI_SPEED 100000

// TODO Declare data check pin.
// NOTE This pin(LED) is turned ON if
//      data comparison was successful.
#define TEST_PIN_SUCCESS HAL_PIN_NC

// TODO Declare number of data to be written/read.
// NOTE 150 by default.
#define ARRAY_LENGTH 150

// Dummy read data.
#define SPI_DUMMY_DATA 0

// Declare error signal pins.
// NOTE Optional.
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC

// NOTE Do not edit these.
#define SRAM_CLICK_WRITE_CMD 2
#define SRAM_CLICK_READ_CMD  3
#define MIKROBUS_SCK_PIN     0
#define MIKROBUS_MISO_PIN    1
#define MIKROBUS_MOSI_PIN    2
#define MIKROBUS_CS_PIN      3

// ----------------------------------------------------------------- VARIABLES

static digital_out_t test_pin;

static spi_master_t spi_master;
static spi_master_config_t spi_master_cfg;

static digital_out_t output_signal_pass;

static uint8_t write_buffer[ARRAY_LENGTH];
static uint8_t read_buffer[ARRAY_LENGTH];

static uint8_t i;

// ------------------------------------------------------ SUPPORTING FUNCTIONS

/*< @brief Initializes CS(SS) pins and deselects them. */
void initialize_cs_pins(void) {
    uint8_t pin_count = TEST_MODULE_COUNT;

    // Set Chip Select polarity (SRAM Click requires active low).
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    while ( pin_count-- ) {
        // NOTE 'pin_count' represents mikroBUS number
        //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
        spi_master_deselect_device(test_pins[pin_count][MIKROBUS_CS_PIN]);
    }

}

/*< @brief SRAM Click Write procedure. */
void sram_click_write(uint32_t address, uint8_t data_to_be_written, uint8_t pin_id) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[ARRAY_LENGTH] = {0};

    // Default SRAM click procedure.
    local_array[0] = SRAM_CLICK_WRITE_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;
    local_array[4] = data_to_be_written;

    // Select SRAM Click.
    spi_master_select_device(test_pins[pin_id][MIKROBUS_CS_PIN]);

    // Write data to SRAM Click.
    spi_master_write(&spi_master, &local_array, 5);

    // Deselect SRAM Click.
    spi_master_deselect_device(test_pins[pin_id][MIKROBUS_CS_PIN]);
}

/*< @brief SRAM Click Read procedure. */
void sram_click_read(uint32_t address, uint8_t pin_id) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[4] = {0};

    // Default SRAM click procedure.
    local_array[0] = SRAM_CLICK_READ_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;

    // Select SRAM Click.
    spi_master_select_device(test_pins[pin_id][MIKROBUS_CS_PIN]);

    // Write data to SRAM Click.
    spi_master_write_then_read(&spi_master, &local_array,
                               4, &read_buffer,
                               ARRAY_LENGTH);

    // Deselect SRAM Click.
    spi_master_deselect_device(test_pins[pin_id][MIKROBUS_CS_PIN]);
}

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    uint8_t cnt = 0;
    uint8_t address_and_data = 0;

    initialize_cs_pins();

    while(1) {
        for ( cnt = 0; cnt < TEST_MODULE_COUNT; cnt++ ) {
            // STEP 1: Initialize and configure SPI module.
            // ---------------------------------------------------------------
            // Set default properties for SRAM Click 1.
            spi_master_configure_default(&spi_master_cfg);

            // Set desired basic properties for SRAM Click 1 which is on mikroBUS1.
            // NOTE 'cnt' represents mikroBUS number
            //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
            spi_master_cfg.sck = test_pins[cnt][MIKROBUS_SCK_PIN];
            spi_master_cfg.miso = test_pins[cnt][MIKROBUS_MISO_PIN];
            spi_master_cfg.mosi = test_pins[cnt][MIKROBUS_MOSI_PIN];
            spi_master_cfg.speed = SPI_SPEED;
            spi_master_cfg.mode = SPI_MASTER_MODE_DEFAULT;
            spi_master_cfg.default_write_data = SPI_DUMMY_DATA;

            // Try to reserve memory for the SRAM Click 1.
            if (ACQUIRE_FAIL == spi_master_open(&spi_master, &spi_master_cfg)) {
                signal_error( TEST_PIN_1 );
            }

            // Set desired default write (dummy) data.
            spi_master_set_default_write_data(&spi_master, SPI_DUMMY_DATA);

            // Set desired baud rate (speed).
            spi_master_set_speed(&spi_master, SPI_SPEED);

            // Set desired mode (SRAM Click requires mode 0).
            spi_master_set_mode(&spi_master, SPI_MASTER_MODE_DEFAULT);
            // ---------------------------------------------------------------

            // STEP 2: Write data from address 0 to 'ARRAY_LENGTH'.
            // ---------------------------------------------------------------
            // Write sequence - SRAM Click.
            for ( address_and_data = 0; address_and_data < ARRAY_LENGTH; address_and_data++) {
                // Write data via SPI protocol.
                sram_click_write(address_and_data, address_and_data, cnt);
                write_buffer[address_and_data] = address_and_data;
                Delay_1ms();
            }
            // ---------------------------------------------------------------

            // STEP 3: Read data from address 0 to 'ARRAY_LENGTH'.
            // ---------------------------------------------------------------
            // Read data from SRAM Click 1.
            sram_click_read(0, cnt);
            // ---------------------------------------------------------------

            // STEP 4: Compare written and read data.
            // ---------------------------------------------------------------
            // Check if data is valid.
            if (!memcmp(write_buffer, read_buffer, sizeof(read_buffer))) {
                signal_success(output_signal_pass, TEST_PIN_SUCCESS);
            }
            // ---------------------------------------------------------------

            // STEP 5: Close the module and prepare for next mikroBUS.
            // ---------------------------------------------------------------
            memset(read_buffer,0,sizeof(read_buffer));
            Delay_1sec();
            digital_out_low(&output_signal_pass);

            spi_master_close(&spi_master);
            Delay_ms(change_bus_wait_time_seconds*1000);
            // ---------------------------------------------------------------
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
