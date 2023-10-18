/**
 * @brief: Test procedure for SPI Master implementation in mikroSDK.
 *
 * @note:
 *      Choose between two types of testing:
 *      - SINGLE_SRAM_CLICK_TEST:
 *          - mikroBUS1
 *      - DUAL_SRAM_CLICK_TEST:
 *          - mikroBUS1 and mikroBUS4
 *
 * @note:
 *      Insert one TESTER Click into mikroBUS5.
 *
 * @note:
 *      If result is a success:
 *      - mikroBUS_5_AN LED will turn ON    (SRAM Click 1 @mikroBUS1)
 *      - mikroBUS_5_PWM LED will turn ON   (SRAM Click 2 @mikroBUS4)
 */

/// @note: Uncomment/comment out, to run desired test.
#define SINGLE_SRAM_CLICK_TEST
// #define DUAL_SRAM_CLICK_TEST

// ------------------------------------------------------------------ INCLUDES

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "board.h"

// -------------------------------------------------------------------- MACROS

// -------------------------------
// Pin definitions - SRAM Click 1.
// -------------------------------

#define TEST_PIN_SPI_CS1   HAL_PIN_NC // TODO Define Chip Select pin.
#define TEST_PIN_SPI_SCK1  HAL_PIN_NC // TODO Define SCK pin.
#define TEST_PIN_SPI_MISO1 HAL_PIN_NC // TODO Define MISO pin.
#define TEST_PIN_SPI_MOSI1 HAL_PIN_NC // TODO Define MOSI pin.

// -------------------------------
// Pin definitions - SRAM Click 2.
// -------------------------------

#define TEST_PIN_SPI_CS2   HAL_PIN_NC // TODO Define Chip Select pin.
#define TEST_PIN_SPI_SCK2  HAL_PIN_NC // TODO Define SCK pin.
#define TEST_PIN_SPI_MISO2 HAL_PIN_NC // TODO Define MISO pin.
#define TEST_PIN_SPI_MOSI2 HAL_PIN_NC // TODO Define MOSI pin.

// -------------------------------
// Pin definitions - TESTER Click.
// -------------------------------

#define TEST_PIN_SIGNAL_SUCCESS1 HAL_PIN_NC // TODO Define signal pin.
#define TEST_PIN_SIGNAL_SUCCESS2 HAL_PIN_NC // TODO Define signal pin.

// TODO Define test pins according to hardware.
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_PIN_9  HAL_PIN_NC
#define TEST_PIN_10 HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin)   digital_out_init( &test_pin, pin ); \
                            digital_out_high( &test_pin ); \
                            while(1)

#define signal_success(port,pin)    digital_out_init( &port, pin ); \
                                    digital_out_write( &port, 1 )

// SRAM Click specific macros.
#define DATA_LENGTH                         150
#define SRAM_CLICK_WRITE_CMD                2
#define SRAM_CLICK_READ_CMD                 3
#define SRAM_CLICK_WRITE_DATA_LENGTH        5
#define SRAM_CLICK_WRITE_READ_DATA_LENGTH   4
#define SRAM_CLICK_DEFAULT_WRITE_DATA       0

#define SRAM_CLICK_1_SPEED                  100000
#define SRAM_CLICK_2_SPEED                  100000

// ----------------------------------------------------------------- VARIABLES
// Instances of structs necessary for SPI Master testing.
static digital_out_t test_pin;

static digital_out_t result_pin_sram_click_1;

static spi_master_t sram_click_1;
static spi_master_config_t sram_click_1_config;

#if defined (DUAL_SRAM_CLICK_TEST)
static digital_out_t result_pin_sram_click_2;

static spi_master_t sram_click_2;
static spi_master_config_t sram_click_2_config;
#endif

// SRAM Click specific variables.
// Array for data to be written - SRAM Click 1.
static uint8_t write_data_buffer_sram_click_1[DATA_LENGTH];

// Array for data to be read - SRAM Click 1.
static uint8_t read_data_buffer_sram_click_1[DATA_LENGTH];

#if defined (DUAL_SRAM_CLICK_TEST)
// Array for data to be written - SRAM Click 2.
static uint8_t write_data_buffer_sram_click_2[DATA_LENGTH];

// Array for data to be read - SRAM Click 2.
static uint8_t read_data_buffer_sram_click_2[DATA_LENGTH];
#endif
// ----------------------------------------------------------------- USER CODE

// SRAM Click 1 Write procedure.
void sram_click_1_write(uint32_t address, uint8_t data_to_be_written) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[SRAM_CLICK_WRITE_DATA_LENGTH] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_WRITE_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;
    local_array[4] = data_to_be_written;

    #ifdef DUAL_SRAM_CLICK_TEST
    // Make sure SRAM Click 2 is deselected.
    spi_master_deselect_device(TEST_PIN_SPI_CS2);
    #endif

    // Select SRAM Click 1.
    spi_master_select_device(TEST_PIN_SPI_CS1);

    // Write data to SRAM Click 1.
    spi_master_write(&sram_click_1, &local_array, SRAM_CLICK_WRITE_DATA_LENGTH);

    // Deselect SRAM Click 1.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);
}

// SRAM Click 1 Read procedure.
void sram_click_1_read(uint32_t address) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[4] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_READ_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;

    #ifdef DUAL_SRAM_CLICK_TEST
    // Make sure SRAM Click 2 is deselected.
    spi_master_deselect_device(TEST_PIN_SPI_CS2);
    #endif

    // Select SRAM Click 1.
    spi_master_select_device(TEST_PIN_SPI_CS1);

    // Write data to SRAM Click 1.
    spi_master_write_then_read(&sram_click_1, &local_array, SRAM_CLICK_WRITE_READ_DATA_LENGTH, &read_data_buffer_sram_click_1, DATA_LENGTH);

    // Deselect SRAM Click 1.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);
}

// SRAM Click 2 Write procedure.
#if defined (DUAL_SRAM_CLICK_TEST)
void sram_click_2_write(uint32_t address, uint8_t data_to_be_written) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[SRAM_CLICK_WRITE_DATA_LENGTH] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_WRITE_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;
    local_array[4] = data_to_be_written;

    // Make sure SRAM Click 1 is deselected.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);

    // Select SRAM Click 2.
    spi_master_select_device(TEST_PIN_SPI_CS2);

    // Write data to SRAM Click 2.
    spi_master_write(&sram_click_2, &local_array, SRAM_CLICK_WRITE_DATA_LENGTH);

    // Deselect SRAM Click 2.
    spi_master_deselect_device(TEST_PIN_SPI_CS2);
}

// SRAM Click 2 Read procedure.
void sram_click_2_read(uint32_t address) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[4] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_READ_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;

    // Make sure SRAM Click 1 is deselected.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);

    // Select SRAM Click 2.
    spi_master_select_device(TEST_PIN_SPI_CS2);

    // Write data to SRAM Click 2.
    spi_master_write_then_read(&sram_click_2, &local_array, SRAM_CLICK_WRITE_READ_DATA_LENGTH, &read_data_buffer_sram_click_2, DATA_LENGTH);

    // Deselect SRAM Click 2.
    spi_master_deselect_device(TEST_PIN_SPI_CS2);
}
#endif

// Application initialization procedure.
void application_init() {
    // Set default properties for SRAM Click 1.
    spi_master_configure_default(&sram_click_1_config);

    // Set desired basic properties for SRAM Click 1 which is on mikroBUS1.
    sram_click_1_config.sck = TEST_PIN_SPI_SCK1;
    sram_click_1_config.miso = TEST_PIN_SPI_MISO1;
    sram_click_1_config.mosi = TEST_PIN_SPI_MOSI1;
    sram_click_1_config.speed = SRAM_CLICK_1_SPEED;
    sram_click_1_config.mode = SPI_MASTER_MODE_DEFAULT;
    sram_click_1_config.default_write_data = SRAM_CLICK_DEFAULT_WRITE_DATA;

    // Try to reserve memory for the SRAM Click 1.
    if (ACQUIRE_FAIL == spi_master_open(&sram_click_1, &sram_click_1_config)) {
        signal_error( TEST_PIN_1 );
    }

    // spi_master_close(&sram_click_1);  //TODO This is the perfect place in code to test spi_master_close via debug!!!

    // Set Chip Select polarity (SRAM Click requires active low).
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    // Set desired default write (dummy) data.
    spi_master_set_default_write_data(&sram_click_1, SRAM_CLICK_DEFAULT_WRITE_DATA);

    // Set desired baud rate (speed).
    spi_master_set_speed(&sram_click_1, SRAM_CLICK_1_SPEED);

    // Set desired mode (SRAM Click requires mode 0).
    spi_master_set_mode(&sram_click_1, SPI_MASTER_MODE_DEFAULT);

    #if defined (DUAL_SRAM_CLICK_TEST)

    // Set default properties for SRAM Click 2.
    spi_master_configure_default(&sram_click_2_config);

    // Set desired basic properties for SRAM Click 2 which is on mikroBUS4.
    sram_click_2_config.sck = TEST_PIN_SPI_SCK2;
    sram_click_2_config.miso = TEST_PIN_SPI_MISO2;
    sram_click_2_config.mosi = TEST_PIN_SPI_MOSI2;
    sram_click_2_config.speed = SRAM_CLICK_2_SPEED;
    sram_click_2_config.mode = SPI_MASTER_MODE_DEFAULT;
    sram_click_2_config.default_write_data = SRAM_CLICK_DEFAULT_WRITE_DATA;

    // Try to reserve memory for the SRAM Click 2.
    if (ACQUIRE_FAIL == spi_master_open(&sram_click_2, &sram_click_2_config)) {
        signal_error(TEST_PIN_2);
    }

    // spi_master_close(&sram_click_2);  // TODO This is the perfect place in code to test spi_master_close via debug!!!

    // Set Chip Select polarity (SRAM Click requires active low).
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    // Set desired default write (dummy) data.
    spi_master_set_default_write_data(&sram_click_2, SRAM_CLICK_DEFAULT_WRITE_DATA);

    // Set desired baud rate (speed).
    spi_master_set_speed(&sram_click_2, SRAM_CLICK_2_SPEED);

    // Set desired mode (SRAM Click requires mode 0).
    spi_master_set_mode(&sram_click_2, SPI_MASTER_MODE_DEFAULT);
    #endif
}

// Application task procedure.
void application_task() {
    uint8_t address_and_data = 0;

    // Write sequence - SRAM Click 1.
    for (address_and_data = 0; address_and_data < DATA_LENGTH; address_and_data++) {

        // Write data via SPI protocol.
        sram_click_1_write(address_and_data, address_and_data);

        // Insert data to be written into new array, just to be able to compare it afterwards.
        write_data_buffer_sram_click_1[address_and_data] = address_and_data;

        Delay_ms(1);
    }

    #if defined (DUAL_SRAM_CLICK_TEST)
    uint8_t local_counter = 0;

    // Write sequence - SRAM Click 2.
    for (address_and_data = 100; address_and_data < 250; address_and_data++) {

        // Write data via SPI protocol.
        sram_click_2_write(address_and_data, address_and_data);

        // Insert data to be written into new array, just to be able to compare it afterwards.
        write_data_buffer_sram_click_2[local_counter++] = address_and_data;

        Delay_ms(1);
    }
    #endif

    Delay_ms(1);

    // Read data from SRAM Click 1.
    sram_click_1_read(0);

    #if defined (DUAL_SRAM_CLICK_TEST)
    // Read data from SRAM Click 2.
    sram_click_2_read(100);
    #endif

    // Check if data is valid.
    if (!memcmp(write_data_buffer_sram_click_1, read_data_buffer_sram_click_1, sizeof(read_data_buffer_sram_click_1))) {
        signal_success(result_pin_sram_click_1, TEST_PIN_SIGNAL_SUCCESS1);
    }

    #if defined (DUAL_SRAM_CLICK_TEST)
    // Check if data is valid.
    if (!memcmp(write_data_buffer_sram_click_2, read_data_buffer_sram_click_2, sizeof(read_data_buffer_sram_click_2))) {
        signal_success(result_pin_sram_click_2, TEST_PIN_SIGNAL_SUCCESS2);
    }
    #endif

    // Erase object instance configuration for SRAM Click 1.
    spi_master_close(&sram_click_1);

    #if defined (DUAL_SRAM_CLICK_TEST)
    // Erase object instance configuration for SRAM Click 2.
    spi_master_close(&sram_click_2);
    #endif
}

// ------------------------------------------------------------
// Main function.
// ------------------------------------------------------------

int main(void) {
    // Initialize necessary SPI protocol properties.
    application_init();

    // Write, read, then subsequently display results at mikroBUS5 Tester Click.
    application_task();

    return 0;
}

// ----------------------------------------------------------------------- END
