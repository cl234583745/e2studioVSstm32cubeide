#include "new_thread0.h"



#include <stdio.h>

static void USR_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
static void USR_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
    uint32_t i;
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

    uint8_t *data  = (uint8_t *)p_src;
    for(i = 0; i < bytes; i++)
    {
        p_ctrl->p_reg->TDR_b.TDR = *data;
        while(p_ctrl->p_reg->SSR_b.TDRE == 0){
        }
        data++;
    }

}
int _write(int fd, char *pBuffer, int size);
int _write(int fd, char *pBuffer, int size)
{
   (void)fd;
   USR_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)pBuffer, (uint32_t)size);


   return size;
}

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void new_thread0_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    R_SCI_UART_Open(&g_uart9_ctrl, &g_uart9_cfg);
    printf("date:%s\ntime:%s\nfile:%s\nfunc:%s,line:%d\nhello world!\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
    /* TODO: add your own code here */
    while (1)
    {
        printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\r\n");
        vTaskDelay (1);
    }
}
