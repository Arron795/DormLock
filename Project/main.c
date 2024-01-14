#include "main.h"

int main()
{
	uint32_t dormCard = 0xF38D2A10;
	uint8_t cardID[5] = {0};
	shutOthersPeripherals();			//关掉不用的外设
	Usart1_Init(115200);
	led_Init();
	configureExternalInterrupt();		//配置外部中断引脚PB5
	SPIClass.SPI1_Init(); 				// SPI初始化
	MFRC522_Init();						// RC522初始化
	Beep_Init();
	TIM1_PWM_Init();					//定时器 舵机SG90初始化

	static uint8_t flag = 1;			//标志位判断是否进入验卡开门环节 防止按按钮中断前提前放卡导致的验卡失败
	while (1)
	{
		flag = 1;
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		for (int i = 0; i < 150; i++)
		{
			if(!RC522_cardScan(cardID) ) 
			{
				if(!isDormCard(cardID,dormCard)&& flag)
				{
					flag = 0;			//标志位清零 本次循环不会再进入此处 按一次按钮刷一次卡开一次门 
					//printf("open the door!\r\n");		避免一次按钮后 长时间将卡放置在读卡区 会多次开门
					DoorLock_Open();
				}
				else
				{
					Beep_Warning();
					//printf("open failed...\r\n");
				}
			} 
			else 
			{
				//printf("card scanned failure. \r\n");
				
			}
		}
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		TIM_SetCompare1(SG90_TIM,5);
		__WFI();				//进入睡眠模式		有外部中断时唤醒
    }
}
