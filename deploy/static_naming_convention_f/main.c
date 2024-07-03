// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroSDKDriverADC
#include "drv_analog_in.h"
#endif
#ifdef MikroSDKDriverI2CMaster
#include "drv_i2c_master.h"
#endif
#ifdef MikroSDKDriverDMA
#include "drv_dma.h"
#endif
#ifdef MikroSDKDriverOneWire
#include "drv_one_wire.h"
#endif
#ifdef MikroSDKDriverUART
#include "drv_uart.h"
#endif
#ifdef MikroSDKDriverSPIMaster
#include "drv_spi_master.h"
#endif
#ifdef MikroSDKDriverPWM
#include "drv_pwm.h"
#endif
#ifdef MikroSDKDriverGPIOPort
#include "drv_port.h"
#endif
#ifdef MikroSDKDriverGPIOOut
#include "drv_digital_out.h"
#endif
#ifdef MikroSDKDriverGPIOIn
#include "drv_digital_in.h"
#endif
#ifdef MikroSDKDriverCAN
#include "drv_can.h"
#endif
#ifdef MikroSDKDriverRTC
#include "drv_rtc.h"
#endif

// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    #ifdef MikroSDKDriverADC
    analog_in_set_resolution((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverI2CMaster
    i2c_master_set_speed((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverDMA
    dma_transfer_start((void *)0);
    #endif
    #ifdef MikroSDKDriverOneWire
    one_wire_search_first_device((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverUART
    uart_set_baud((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverSPIMaster
    spi_master_set_speed((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverPWM
    pwm_set_freq((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverGPIOPort
    port_write((void *)0, 0);
    #endif
    #ifdef MikroSDKDriverGPIOOut
    digital_out_toggle((void *)0);
    #endif
    #ifdef MikroSDKDriverGPIOIn
    digital_in_read((void *)0);
    #endif
    #ifdef MikroSDKDriverCAN
    can_transmit((void *)0, (void *)0);
    #endif
    #ifdef MikroSDKDriverRTC
    rtc_set_time((void *)0);
    #endif

    while(1);

    return 0;
}

// ----------------------------------------------------------------------- END
