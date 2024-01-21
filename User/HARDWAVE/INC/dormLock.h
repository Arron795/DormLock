#ifndef __DORMLOCK_H
#define __DORMLOCK_H

#include "main.h"

uint8_t isDormCard(uint8_t* CardID, uint32_t dormCard);
void led_Init(void);
void DoorLock_Open(void);
void configureExternalInterrupt(void);
void shutOthersPeripherals(void);
void EXTI9_5_IRQHandler(void);

extern volatile uint8_t flag;
#endif
