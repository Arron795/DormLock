#include "beep.h"

void Beep_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = BEEP_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //GPIO_ResetBits(GPIOA,BEEP_PIN);
}

void Beep_On(void)
{
    GPIO_SetBits(GPIOA,BEEP_PIN);
}

void Beep_Off(void)
{
    GPIO_ResetBits(GPIOA,BEEP_PIN);
}

void Beep_Warning(void)
{
    for (int i = 0; i < 3; i++)
    {
        GPIO_SetBits(GPIOA,BEEP_PIN);
        delay_ms(10);
        GPIO_ResetBits(GPIOA,BEEP_PIN);
        delay_ms(10);
    }
}
