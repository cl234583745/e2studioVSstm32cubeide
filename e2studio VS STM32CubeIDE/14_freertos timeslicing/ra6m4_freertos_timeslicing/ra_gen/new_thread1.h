/* generated thread header file - do not edit */
#ifndef NEW_THREAD1_H_
#define NEW_THREAD1_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void new_thread1_entry(void * pvParameters);
                #else
extern void new_thread1_entry(void *pvParameters);
#endif
FSP_HEADER
FSP_FOOTER
#endif /* NEW_THREAD1_H_ */
