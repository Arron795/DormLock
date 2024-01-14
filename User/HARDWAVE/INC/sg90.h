#ifndef __SG90_H
#define __SG90_H

#define SG90_PORT   GPIOA
#define SG90_PIN    GPIO_Pin_8      
#define SG90_TIM    TIM1    
//电源接5V
#include "main.h"
void TIM1_PWM_Init(void);
void Sg90_180_Angle(void);
void Sg90_Pull_Trigger(void);
void Sg90_90_Angle(void);
void Sg90_0_Angle(void);                                                                 

#endif
