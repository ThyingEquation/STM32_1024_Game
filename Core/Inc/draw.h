#ifndef INC_DRAW_H_
#define INC_DRAW_H_

#include "main.h"
#include "usbd_cdc_if.h"

// Заменить нижний #define PRINT_DATA(value) этим и можно играть в VS Code в консоли
//#define PRINT_DATA(value) printf(value); // Заменить этим и можно играть в VS Code в консоли

#define PRINT_DATA(value) CDC_Transmit_FS((uint8_t*)value, strlen((const char*)value)); HAL_Delay(1);

void drawGame(int arr[], int gameScore);

#endif /* INC_DRAW_H_ */
