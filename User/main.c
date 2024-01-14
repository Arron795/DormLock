//=============================================================================
//文件名称：main.c
//功能概要：STM32F103C8核心检测
//版权所有：源地工作室www.vcc-gnd.com
//版权更新：2013-02-20
//调试方式：J-Link OB ARM SW方式 5MHz
//=============================================================================

//头文件
#include "stm32f10x.h"
#include "GPIOLIKE51.h"


//函数声明
//void GPIO_Configuration(void);
void LED_Init(void);
void RCC_Configuration(void);

//=============================================================================
//文件名称：Delay
//功能概要：延时
//参数说明：nCount：延时长短
//函数返回：无
//=============================================================================

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


//=============================================================================
//文件名称：main
//功能概要：主函数
//参数说明：无
//函数返回：int
//=============================================================================
int main(void)
{
		//GPIO_Configuration();

		RCC_Configuration();							//
		
	  LED_Init();
    while (1)
		{
			PAout(1)=0;					//1为灭
			Delay(0xfffff);
			Delay(0xfffff);	
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			PAout(1)=1;

			PBout(12)=0;					//0为亮
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			PBout(12)=1;

			PCout(15)=0;					
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			PCout(15)=1;


//				GPIO_SetBits(GPIOA,GPIO_Pin_1);	//这个就是将IO口设置为高电平就是3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				GPIO_ResetBits(GPIOA,GPIO_Pin_1);//这个就是将IO口设置为低电平就是0V
//				Delay(0xfffff);   						
//				Delay(0xfffff);
//				GPIO_SetBits(GPIOB,GPIO_Pin_12);	//这个就是将IO口设置为高电平就是3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff); 
//				GPIO_ResetBits(GPIOB,GPIO_Pin_12);//这个就是将IO口设置为低电平就是0V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff);  
//				GPIO_SetBits(GPIOC,GPIO_Pin_15);	//这个就是将IO口设置为高电平就是3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff); 
//				GPIO_ResetBits(GPIOC,GPIO_Pin_15);//这个就是将IO口设置为低电平就是0V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff);
    }
}

//=============================================================================
//文件名称：GPIO_Configuration
//功能概要：GPIO初始化
//参数说明：无
//函数返回：无
//=============================================================================
//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
////=============================================================================
////LED -> PC13
////=============================================================================			 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);

//}

void RCC_Configuration(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA时钟并使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB时钟并使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//开启GPIOC时钟并使能
}

void LED_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;												//声明GPIO初始化结构体,声明要在最前面

		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA时钟并使能

		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;									//定义GPIO初始化结构体的GPIO引脚
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//定义GPIO初始化结构体的GPIO输出模式
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//定义GPIO初始化结构体的GPIO速率

		GPIO_Init(GPIOA,  &GPIO_InitStruct);										//初始化GPIO

		//GPIO_ResetBits(GPIOA,GPIO_Pin_1);					//将该管脚初始值定义为低电平


		//GPIO_InitTypeDef GPIO_InitStruct;											//因为最上面已经声明了一次，这里直接复用即可，不需要再次声明


		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;									//定义GPIO初始化结构体的GPIO引脚
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//定义GPIO初始化结构体的GPIO输出模式，推挽输出模式
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//定义GPIO初始化结构体的GPIO速率

		GPIO_Init(GPIOB,  &GPIO_InitStruct);										//初始化GPIO

		//GPIO_ResetBits(GPIOB,GPIO_Pin_12);



		//GPIO_InitTypeDef GPIO_InitStruct;											//因为最上面已经声明了一次，这里直接复用即可，不需要再次声明



		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;									//定义GPIO初始化结构体的GPIO引脚
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//定义GPIO初始化结构体的GPIO输出模式，推挽输出模式
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//定义GPIO初始化结构体的GPIO速率

		GPIO_Init(GPIOC,  &GPIO_InitStruct);										//初始化GPIO

		//GPIO_ResetBits(GPIOC,GPIO_Pin_15);


// GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //开启时钟
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //初始化管脚
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //设置输出模式，推挽输出模式
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置输出速率
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 
// GPIO_ResetBits(GPIOA,GPIO_Pin_0);					//将该管脚初始值定义为低电平
//	
//// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
// GPIO_Init(GPIOB, &GPIO_InitStructure);					 
// GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//	
//// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
// GPIO_Init(GPIOC, &GPIO_InitStructure);					 
// GPIO_ResetBits(GPIOC,GPIO_Pin_15);

}


