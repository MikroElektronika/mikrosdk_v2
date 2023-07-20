#include "tft_defines.h"

#ifdef __SSD1963__

pin_name_t pins[TFT_PIN_COUNT] = {
    CTP_SDA, CTP_SCL, // I2C touch panel pins
    TFT_GPIO, CTP_INT, TFT_D_C, TFT_RST, // Control pins + Touch INT
    TFT_WR, TFT_CS, TFT_TE , TFT_RD // Control pins
    // BEGIN OF DATA PINS
    #ifdef __8_bit_data_port__
    , TFT_D0, TFT_D1, TFT_D2, TFT_D3,
    TFT_D4, TFT_D5, TFT_D6, TFT_D7
    #endif
    #ifdef __16_bit_data_port__
    , TFT_D8, TFT_D9, TFT_D10, TFT_D11,
    TFT_D12, TFT_D13, TFT_D14, TFT_D15
    #endif
    #ifdef __24_bit_data_port__
    , TFT_D16, TFT_D17, TFT_D18, TFT_D19,
    TFT_D20, TFT_D21, TFT_D22, TFT_D23
    #endif
    // END OF DATA PINS
    , CTP_RST, TFT_BPWM, CTP_WAKE // I2C touch panel pins + PWM
};

#elif defined(__ILI9341__)
// TODO Add ILI9341 test once it's added to SDK.'
#else
    #    error: "TFT NOT IMPLEMENTED!!!"
#endif
