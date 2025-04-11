#include "board.h"
#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "systick.h"
#include <sys/time.h>

static digital_out_t pinC;
static digital_out_t pinD;

static void foo(void* param);
static void foo2(void* param);
static void foo(void* param)
{
    while(1){
        digital_out_toggle(&pinC);
        vTaskDelay(100);
    }
}
static void foo2(void* param)
{
    while(1){
        digital_out_toggle(&pinD);
        vTaskDelay(200);
    }
}


int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    __asm volatile ("cpsie i");
    digital_out_init(&pinC, PC8);
    digital_out_init(&pinD, PC9);
    TaskHandle_t ledBlinking;
    if(xTaskCreate(foo, "task", 128, NULL, 4, NULL)==pdPASS){
        if(xTaskCreate(foo2, "task", 128, NULL, 4, NULL)==pdPASS){ 

            vTaskStartScheduler();
        }
    }
    while(1);
}
