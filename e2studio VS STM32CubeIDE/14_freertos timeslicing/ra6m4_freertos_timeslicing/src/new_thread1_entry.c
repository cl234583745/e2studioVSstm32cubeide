#include "new_thread1.h"
/* New Thread1 entry function */
/* pvParameters contains TaskHandle_t */
void new_thread1_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    vTaskDelay (1000);
    /* TODO: add your own code here */
    while (1)
    {
        printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\r\n");
        vTaskDelay (1);
    }
}
