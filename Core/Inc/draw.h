#ifndef INC_DRAW_H_
#define INC_DRAW_H_

#include "main.h"

#include "usbd_cdc_if.h"

//#define PRINT_DATA(value) printf(value);
#define PRINT_DATA(value) CDC_Transmit_FS((uint8_t*)value, strlen((const char*)value)); HAL_Delay(1);

void drawGame(int arr[]);

#endif /* INC_DRAW_H_ */
