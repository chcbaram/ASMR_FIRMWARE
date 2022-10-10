#ifndef BSP_H_
#define BSP_H_


#include "def.h"


#include "stm32h7xx_hal.h"


bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t millis(void);


#endif