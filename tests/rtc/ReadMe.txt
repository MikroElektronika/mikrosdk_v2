Example is meant for testing RTC module using mikroSDK 2.0

## Code Structure

The code consists of several sections, including macros, variables, and application functions. Here's a brief explanation of each section:

### Macros

- `TEST_PIN_SIGNAL_SUCCESS_1` and `TEST_PIN_SIGNAL_SUCCESS_2`: These macros define signal pins for success conditions.
- `TEST_PIN_SIGNAL_SOFTWARE_RESET`, `TEST_PIN_SIGNAL_SET_TIME`, `TEST_PIN_SIGNAL_RTC_STOP`, and `TEST_PIN_SIGNAL_RTC_RESET`: These macros define test pins used for different operations.
- `TEST_PIN_1` to `TEST_PIN_5`: Additional test pins for various purposes.
- `PORT_NAME`: Defines the port used for testing.
- Several other macros define signal and timing-related functions.

### Variables

- `logger`: An instance of the logger for debugging purposes.
- `time`: An instance of the RTC data structure to hold date and time information.
- `test_pin`: An instance of the digital output for controlling test pins.
- `port`: An instance of the port for GPIO operations.
- `mask`: A mask for GPIO operations.
- `value`: A variable for managing GPIO port values.

### Application Functions

- `application_init()`: Initializes the port, logger, and RTC. It also provides an option to configure the RTC with default values.
- `application_task()`: This is the main application loop. It reads the RTC time, writes values to GPIO ports, logs the time, and optionally tests RTC operations like stopping, setting time, software reset, and RTC reset.
- `main()`: The main function that calls `application_init()` and `application_task()`.

## Usage

To use this code with your hardware, follow these steps:

1. Configure the macros in the "MACROS" section according to your hardware setup.
2. Compile and upload the code to your microcontroller.
3. Monitor the output through the UART interface (assuming it's connected to a computer).

## Functionality

- The code reads the current time from the RTC module and logs it.
- It can optionally test RTC operations such as stopping, setting time, software reset, and RTC reset.
- GPIO pins are controlled to simulate different test scenarios.

## Important Notes

- Ensure that your hardware connections match the macro definitions.
- Review the code comments for more details on how to customize and use the code for your specific application.

Feel free to modify and extend this code to suit your project's requirements.

For any questions or issues, please refer to the documentation of your microcontroller and RTC module.