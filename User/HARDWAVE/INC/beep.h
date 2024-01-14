#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

#define BEEP_PIN    GPIO_Pin_1              //PA1

void Beep_Init(void);
void Beep_On(void);
void Beep_Off(void);
void Beep_Warning(void);

#endif
