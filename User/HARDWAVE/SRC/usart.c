#include "usart.h"
#include "stdio.h"

#if 1
	#pragma import(__use_no_semihosting)             
	//??????????                 
	struct __FILE 
	{ 
		int handle; 
		/* Whatever you require here. If the only file you are using is */ 
		/* standard output using printf() for debugging, no file handling */ 
		/* is required. */ 
	}; 
	/* FILE is typedef?d in stdio.h. */ 
	FILE __stdout;       
	//??_sys_exit()??????????    
	int _sys_exit(int x) 
	{ 
		x = x; 
	
		return 0;
	} 
	//???fputc?? 
	int fputc(int ch, FILE *f)
	{      
		while((USART1->SR&0X40)==0);//????,??????   
		USART1->DR = (u8) ch;      
		return ch;
	}
#endif


//void Usart1_Init(uint32_t baudrate)
//{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
//	USART_InitTypeDef USART_InitStruct = {0};
//	NVIC_InitTypeDef NVIC_InitStruct = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	//记得加上这两句引脚复用映射 
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);	
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);
//	
//	USART_InitStruct.USART_BaudRate = baudrate;
//	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_InitStruct.USART_Parity = USART_Parity_No;
//	USART_InitStruct.USART_StopBits = USART_StopBits_1;
//	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_Init(USART1,&USART_InitStruct);
//	
//	//串口使能
//	USART_Cmd(USART1,ENABLE);							//使能指定串口外围设备
//	
//	USART_ClearFlag(USART1,USART_FLAG_TC);				//清除标志位
//	
//	//串口中断使能
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//接收中断，使能指定串口中断
//	//USART_ITConfig(USART1,USART_IT_TC,ENABLE);			//空闲中断
//	
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);		//空闲中断 这句很重要
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);
//	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;		//抢占
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;				//响应
//	
//	NVIC_Init(&NVIC_InitStruct);
//}

void Usart1_Init(uint32_t baudrate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//GPIO口时钟
	
	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //复用usart模块
	
	//GPIO口初始化
	GPIO_InitTypeDef  GPIO_InitStructure = {0};
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//串口初始化
	
	USART_InitTypeDef  USART_InitStructure = {0};
	USART_InitStructure.USART_BaudRate = baudrate;       	//波特率  
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //收发模式控制
	USART_InitStructure.USART_Parity = USART_Parity_No;   //校验位控制 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //停止位控制 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位控制 
	USART_Init(USART1, &USART_InitStructure);

	//清除串口发送标志位
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	//中断
	NVIC_InitTypeDef NVIC_InitStructure = {0};
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 			//中断向量
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;     //响应优先级
	NVIC_Init(&NVIC_InitStructure);
	

	//串口中断使能
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);  //空闲中断
	
	
	//串口使能
	USART_Cmd(USART1, ENABLE);


}


/*
中断服务函数：USART1_IRQHandler
参数：无
返回值：void
描述：cccc
*/
uint8_t recbuff[SIZE] = {0};
uint8_t rec_buff_i = 0;

void USART1_IRQHandler(void)
{
//	uint16_t rece;
	//判断发生什么样的中断		接收中断
	if(USART_GetITStatus(USART1,  USART_IT_RXNE) == SET)	//IT代表中断
	{
		//printf("到此");
		//清除对应的中断标志位
		USART_ClearITPendingBit(USART1,  USART_IT_RXNE);

		//处理紧急事件
		recbuff[rec_buff_i] = USART_ReceiveData(USART1);
		rec_buff_i++;
		
		//输出发送的数据
//		if(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == SET)
//		{
//			rece = USART_ReceiveData(USART1);
//			USART_SendData(USART1,rece);
//		}
	}

	//判断发生什么样的中断		空闲中断
	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
	{
		//清除对应的中断标志位
		USART1 -> SR;
		USART1 -> DR;
		//处理紧急事件
		recbuff[rec_buff_i] = '\0';
		rec_buff_i = 0;
	}
	
	//
//	uint16_t rece;
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == SET)
//	{
//		rece = USART_ReceiveData(USART1);
//		USART_SendData(USART1,rece);
//	}
}

void Usart_SendData(const uint8_t *data)
{
	while(*data && USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET)
	{
		USART_SendData(USART1,*data);
	}
}

void usart1_SendByte(uint8_t data)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	USART_SendData(USART1,data);
}

//发送数组
//uint8_t ch[10] = {0};
//void usart1_SendString(uint8_t *string)
//{
//	for(uint8_t i = 0;i<sizeof(ch);i++)
//	{
//		usart1_SendByte(ch[i]);
//	}
//}

const char *ch;

//发送字符串
void usart1_SendStr(char *str)
{
	while(*str != '\0')
	{
		usart1_SendByte(*str);
		str++;
	}
}


