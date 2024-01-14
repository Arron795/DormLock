#include "DormLock.h"

void led_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOC,&GPIO_InitStruct);

    //GPIO_ResetBits(GPIOC,GPIO_Pin_13); //0亮
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
}


void DoorLock_Open(void)
{
    Beep_On();
    delay_ms(500);
    Beep_Off();
    Sg90_Pull_Trigger();
}

uint8_t isDormCard(uint8_t* CardID, uint32_t dormCard) {

	uint8_t CompareID[4] = {0};
	CompareID[0] = (dormCard >> 24) & 0xFF;
	CompareID[1] = (dormCard >> 16) & 0xFF;
	CompareID[2] = (dormCard >> 8) & 0xFF;
	CompareID[3] = dormCard  & 0xFF;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (CardID[i] != CompareID[i])
        {
            return MI_ERR;
        } 
    }
    return MI_OK;
}



void configureExternalInterrupt(void) {
    // 配置外部中断引脚     一个开关按键作为外部中断    PB5
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);       /* 使能复用功能时钟 */  //设置外部中断需要复用功能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
    // 配置中断触发条件
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;  // 外部中断线号
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置中断优先级
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;  // 外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void shutOthersPeripherals(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE ,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    USART_DeInit(USART2); 
    USART_DeInit(USART3); 

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2 ,DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |
                            RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | 
                            RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3 |
                            RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2 |
                            RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2 ,DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3 |
                            RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE ,DISABLE);
}


void EXTI9_5_IRQHandler(void) {

    if (EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        // 清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line5);
        //flag = 1;
        // 处理MFRC522中断  处理外部中断5的中断服务程序
        //...这里不做处理
    }

}


