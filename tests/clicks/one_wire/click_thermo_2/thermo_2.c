#include "thermo_2.h"

// Lookup table.
static const float lookup_table[ THERMO_2_LOOKUP_TABLE_ELEMENTS ] = {
    0.0625, 0.125, 0.25, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0
};

// Function definition for temperature conversion.
float thermo_2_convert_temperature( uint16_t raw_temperature_value, thermo_2_resolution_t resolution_value ) {
    bool is_temperature_negative = false;
    uint8_t local_loop_counter = 0;
    uint16_t local_raw_value = 0;
    uint16_t temp_storage = 0;
    float final_value = 0;

    // Check if user selected temperature conversion resolution which is in range.
    if ( ( resolution_value < THERMO_2_DEFAULT_RESOLUTION ) || ( resolution_value > THERMO_2_RESOLUTION_9_BIT ) ) {
        return THERMO_2_RESOLUTION_ERROR;
    }

    // Checking whether temperature is negative.
    if ( raw_temperature_value & ( 0x1F << 11 ) ) {
        // Convert from negative into positive representation.
        raw_temperature_value = ( ~raw_temperature_value ) + 1;

        // Set boolean.
        is_temperature_negative = true;
    }

    // Checking lookup table to calculate final temperature.
    for ( local_loop_counter = resolution_value; local_loop_counter < 11; local_loop_counter++ ) {
        if ( raw_temperature_value & ( 1 << local_loop_counter ) ) {
            final_value += lookup_table[ local_loop_counter ];
        }
    }

    // Returning temperature value.
    if ( is_temperature_negative ) {
        return -final_value;
    } else {
        return final_value;
    }
}
