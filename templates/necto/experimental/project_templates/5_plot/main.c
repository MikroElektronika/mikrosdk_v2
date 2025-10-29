/**
 * @file main.c
 * @brief Main source file for the ${PROJECT_NAME} application.
 *
 * This example demonstrates basic usage of the `plot()` function
 * for visualizing random data in NECTO Studio.
 */

#include "MikroSDK.Plot"
#include "stdlib.h"

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#define MAX_POINTS 30

unsigned int data_x[MAX_POINTS];
unsigned int data_y[MAX_POINTS];
unsigned int data_z[MAX_POINTS];

/**
 * @brief Generates random data for plotting.
 *
 * This function fills the data_x and data_y arrays with random
 * values that can later be visualized using the `plot()` function.
 */
void generate_random_data() {
    unsigned int i;

    // Initialize the random number generator with a fixed seed
    srand(12345);

    for (i = 0; i < MAX_POINTS; i++) {
        data_x[i] = rand() % 128;        // random X value
        data_y[i] = rand() % 256;        // random Y value
        data_z[i] = rand() % 512;        // random Z value
    }
}

/**
 * @brief Application entry point.
 *
 * Initializes MCU peripherals (if required) and continuously
 * plots generated random data points.
 */
int main(void)
{
    /* Do not remove this line — it ensures that the MCU clock
     * and other system peripherals are properly initialized. */
#ifdef PREINIT_SUPPORTED
    preinit();
#endif

    // Generate data to be displayed on the Plot tab
    generate_random_data();

    while (1)
    {
        // Example loop for plotting generated data.
        // You can modify this section to plot sensor readings
        // or other dynamic data from your project.
        //
        // NOTE:
        // 1. Build and program your MCU as usual.
        // 2. Run the project in Debug mode (F9).
        // 3. Open the "Plot" tab in NECTO Studio to visualize data.

        for (int i = 0; i < MAX_POINTS; ++i)
        {
            plot("Point X:", data_x[i]);
            plot("Point Y:", data_y[i]);
            plot("Point Z:", data_z[i]);
            Delay_ms(500);  // Slow down plotting for better visibility
        }
    }

    return 0;
}
