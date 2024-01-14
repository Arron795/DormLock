#include "sg90.h"

void TIM1_PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = SG90_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SG90_PORT,&GPIO_InitStruct);

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 驱动CNT计数器的时钟 = Fck_int/(psc+1)
    TIM_TimeBaseInitStruct.TIM_Period = (200 - 1);               // 时钟分频因子 ，用于配置死区时间，没用到，随意
    TIM_TimeBaseInitStruct.TIM_Prescaler = (7200 - 1);           // 计数器计数模式，设置为向上计数
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            // 重复计数器的值，没用到，可以随意设置
    TIM_TimeBaseInit(SG90_TIM, &TIM_TimeBaseInitStruct);         // 初始化定时器

    
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;    // 配置为PWM模式1
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;             // 输出使能
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;     // 设置占空比大小，在主函数compare中又设置一遍
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // 输出通道电平极性配置
    TIM_OCInitStruct.TIM_Pulse = 0;                            // 输出通道空闲电平极性配置
    TIM_OC1Init(SG90_TIM, &TIM_OCInitStruct);                  // 初始化通道1
    TIM_OC1PreloadConfig(SG90_TIM, TIM_OCPreload_Enable);      // 使能通道1输出

    TIM_Cmd(SG90_TIM, ENABLE);                                  // 使能计数器
    TIM_CtrlPWMOutputs(SG90_TIM, ENABLE);                       // 主输出使能，当使用的是通用定时器时，这句不需要
}

void Sg90_180_Angle(void)
{
    TIM_SetCompare1(SG90_TIM,5);    //0°
    delay_ms(1000);

    TIM_SetCompare1(SG90_TIM,15);   //90°
    delay_ms(1000);

    TIM_SetCompare1(SG90_TIM,25);   //180°
    delay_ms(1000);
}

void Sg90_Pull_Trigger(void)
{
    TIM_SetCompare1(SG90_TIM,15);   //90°
    delay_ms(2000);
    TIM_SetCompare1(SG90_TIM,5);   //0°
}

void Sg90_90_Angle(void)
{
    TIM_SetCompare1(SG90_TIM,15);   //90°
}

void Sg90_0_Angle(void)
{
    TIM_SetCompare1(SG90_TIM,5);   //0°
}
