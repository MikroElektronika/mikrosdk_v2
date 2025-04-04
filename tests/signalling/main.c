#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "semphr.h"
#include "systick.h"
#include <sys/time.h>
#include "drv_port.h"

static SemaphoreHandle_t  sema; 
static SemaphoreHandle_t  sema2; 
static port_t portD;

static void f(void* param)
{
    while(1){
        xSemaphoreTake(sema, portMAX_DELAY);
        port_write(&portD, 0xff);
        vTaskDelay(100);
        xSemaphoreGive(sema2);
    }
}
static void f2(void* param)
{
    uint8_t elem;
    while(1){
        xSemaphoreTake(sema2, portMAX_DELAY);
        port_write(&portD, 0);
        vTaskDelay(50);
        xSemaphoreGive(sema);
    }
}

int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    __asm volatile ("cpsie i");
    port_init(&portD,PORT_D,0xff, PIN_DIRECTION_DIGITAL_OUTPUT);
    sema=xSemaphoreCreateBinary();
    sema2=xSemaphoreCreateBinary();
    xSemaphoreGive(sema);
    if(xTaskCreate(f, "task1", 128, NULL, 4, NULL)==pdPASS){
            if(xTaskCreate(f2, "task2", 128, NULL, 4, NULL)==pdFALSE){
                // Enter an infinite loop to halt the system
                while(1);
            } 
        vTaskStartScheduler();
    }
    while(1);
}
