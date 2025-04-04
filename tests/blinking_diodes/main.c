#include "board.h"
#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "semphr.h"
#include "systick.h"
#include <sys/time.h>
#include "drv_port.h"

#define NUMBER_OF_PINS 4

static digital_out_t pinA;
static digital_out_t pinB;
static digital_out_t pinC;
static digital_out_t pinD;
static digital_out_t pins[NUMBER_OF_PINS];
static SemaphoreHandle_t semaphores[NUMBER_OF_PINS];

static void foo(void* param)
{
    while(1){
        xSemaphoreTake(semaphores[((int)param)], portMAX_DELAY);
        digital_out_toggle(&pins[((int)param)]);
        vTaskDelay(100);
        xSemaphoreGive(semaphores[(((int)param)+1)%NUMBER_OF_PINS]);
    }
}

int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    __asm volatile ("cpsie i");
    digital_out_init(&pinA, PD0);
    digital_out_init(&pinB, PD1);
    digital_out_init(&pinC, PD2);
    digital_out_init(&pinD, PD3);
    pins[0]=pinA;
    pins[1]=pinB;
    pins[2]=pinC;
    pins[3]=pinD;
    for(int i=0; i<NUMBER_OF_PINS; i++){
        semaphores[i]=xSemaphoreCreateBinary();
    }
    xSemaphoreGive(semaphores[0]);
    
    for(int i=0; i<NUMBER_OF_PINS; i++){
        if(xTaskCreate(foo, '0'+i, 128, i, 4, NULL)==pdPASS){
           
        }else {
            while(1);
        }
    }
    vTaskStartScheduler();
    while(1);
}
