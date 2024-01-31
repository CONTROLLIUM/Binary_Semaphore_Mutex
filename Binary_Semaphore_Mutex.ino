#include <Arduino_FreeRTOS.h>
#include <atomic.h>
#include <event_groups.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOSVariant.h>
#include <list.h>
#include <message_buffer.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <portmacro.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <stack_macros.h>
#include <stream_buffer.h>
#include <task.h>
#include <timers.h>
// se declara un menejador para el semaforo mutex que va a solicitar al puerto serie
SemaphoreHandle_t xSemaphoreSerial;
// se definen las tareas
void DigitalActions(void *pvParameters);
void AnalogActions(void *pvParaneters);

void setup()
{
    Serial.begin(115200);

    if (xSemaphoreSerial == NULL)
    {
        xSemaphoreSerial = xSemaphoreCreateMutex();
        if ((xSemaphoreSerial) != NULL)
        {
            xSemaphoreGive((xSemaphoreSerial));
        }
    }

    xTaskCreate(DigitalActions,"Digital",128,NULL,1,NULL);
    xTaskCreate(AnalogActions,"Analog",128,NULL,2,NULL);
}
void loop(){}

void DigitalActions(void *pvParameters_attribute_((unused)))
{
    /*Aqui se declaran la configuracion deigital de los pines, tanto como las entradas y las salidas y demas*/
    for(;;)
    {
        if (xSemaphoreTake(xSemaphoreSerial,(TickType_t)5)==pdTRUE)
        {
            /*aqui va el codigo a tomar*/




            xSemaphoreGive(xSemaphoreSerial);
        }
        vTaskDelay(1);
    }
}

void AnalogActions(void *pvParameters_attribute_((unused)))
{
    /*Aqui se declaran la configuracion analogic de los pines, tanto como las entradas y las salidas y demas*/
    for(;;)
    {
        if (xSemaphoreTake(xSemaphoreSerial,(TickType_t)5)==pdTRUE)
        {
            /*aqui va el codigo a tomar*/




            xSemaphoreGive(xSemaphoreSerial);
        }
        vTaskDelay(1);
    }
}