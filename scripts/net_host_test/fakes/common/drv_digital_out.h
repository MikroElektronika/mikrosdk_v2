/* Host test only: the parts of mikroSDK's drv_digital_out.h the on-chip MAC drivers use. */
#ifndef FAKE_DRV_DIGITAL_OUT_H
#define FAKE_DRV_DIGITAL_OUT_H

#include <stdint.h>

typedef int32_t err_t;
typedef uint32_t pin_name_t;
typedef struct { pin_name_t pin; } digital_out_t;
#define HAL_PIN_NC ( ( pin_name_t )0xFFFFFFFF )
#define DIGITAL_OUT_SUCCESS 0

err_t digital_out_init( digital_out_t *out, pin_name_t name );
err_t digital_out_high( digital_out_t *out );
err_t digital_out_low( digital_out_t *out );

#endif
