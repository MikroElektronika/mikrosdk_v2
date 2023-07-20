#include "drv_digital_out.h"
#include "board.h"

#ifdef __SSD1963__
#if defined(__8_bit_interface__) || defined(__16_bit_interface__) || defined(__24_bit_interface__)
#define __8_bit_data_port__
#endif
#if defined(__16_bit_interface__) || defined(__24_bit_interface__)
#define __16_bit_data_port__
#endif
#ifdef __24_bit_interface__
#define __24_bit_data_port__
#endif

#ifdef __24_bit_interface__
    #define TFT_DATA_PIN_COUNT 24
#elif defined(__16_bit_interface__)
    #define TFT_DATA_PIN_COUNT 16
#else
    #define TFT_DATA_PIN_COUNT 8
#endif

#define TFT_I2C_PIN_COUNT 5
#define TFT_CONTROL_PIN_COUNT 8
#define TFT_PIN_COUNT (TFT_I2C_PIN_COUNT+TFT_CONTROL_PIN_COUNT+TFT_DATA_PIN_COUNT)
#endif
