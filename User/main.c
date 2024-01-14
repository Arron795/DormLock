//=============================================================================
//�ļ����ƣ�main.c
//���ܸ�Ҫ��STM32F103C8���ļ��
//��Ȩ���У�Դ�ع�����www.vcc-gnd.com
//��Ȩ���£�2013-02-20
//���Է�ʽ��J-Link OB ARM SW��ʽ 5MHz
//=============================================================================

//ͷ�ļ�
#include "stm32f10x.h"
#include "GPIOLIKE51.h"


//��������
//void GPIO_Configuration(void);
void LED_Init(void);
void RCC_Configuration(void);

//=============================================================================
//�ļ����ƣ�Delay
//���ܸ�Ҫ����ʱ
//����˵����nCount����ʱ����
//�������أ���
//=============================================================================

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


//=============================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��������
//����˵������
//�������أ�int
//=============================================================================
int main(void)
{
		//GPIO_Configuration();

		RCC_Configuration();							//
		
	  LED_Init();
    while (1)
		{
			PAout(1)=0;					//1Ϊ��
			Delay(0xfffff);
			Delay(0xfffff);	
			Delay(0xfffff);
			Delay(0xfffff);
			Delay(0xfffff);
			PAout(1)=1;

			PBout(12)=0;					//0Ϊ��
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


//				GPIO_SetBits(GPIOA,GPIO_Pin_1);	//������ǽ�IO������Ϊ�ߵ�ƽ����3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				GPIO_ResetBits(GPIOA,GPIO_Pin_1);//������ǽ�IO������Ϊ�͵�ƽ����0V
//				Delay(0xfffff);   						
//				Delay(0xfffff);
//				GPIO_SetBits(GPIOB,GPIO_Pin_12);	//������ǽ�IO������Ϊ�ߵ�ƽ����3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff); 
//				GPIO_ResetBits(GPIOB,GPIO_Pin_12);//������ǽ�IO������Ϊ�͵�ƽ����0V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff);  
//				GPIO_SetBits(GPIOC,GPIO_Pin_15);	//������ǽ�IO������Ϊ�ߵ�ƽ����3.3V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff); 
//				GPIO_ResetBits(GPIOC,GPIO_Pin_15);//������ǽ�IO������Ϊ�͵�ƽ����0V
//				Delay(0xfffff);
//				Delay(0xfffff);
//				Delay(0xfffff);
    }
}

//=============================================================================
//�ļ����ƣ�GPIO_Configuration
//���ܸ�Ҫ��GPIO��ʼ��
//����˵������
//�������أ���
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//����GPIOAʱ�Ӳ�ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOBʱ�Ӳ�ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//����GPIOCʱ�Ӳ�ʹ��
}

void LED_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;												//����GPIO��ʼ���ṹ��,����Ҫ����ǰ��

		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//����GPIOAʱ�Ӳ�ʹ��

		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;									//����GPIO��ʼ���ṹ���GPIO����
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//����GPIO��ʼ���ṹ���GPIO���ģʽ
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//����GPIO��ʼ���ṹ���GPIO����

		GPIO_Init(GPIOA,  &GPIO_InitStruct);										//��ʼ��GPIO

		//GPIO_ResetBits(GPIOA,GPIO_Pin_1);					//���ùܽų�ʼֵ����Ϊ�͵�ƽ


		//GPIO_InitTypeDef GPIO_InitStruct;											//��Ϊ�������Ѿ�������һ�Σ�����ֱ�Ӹ��ü��ɣ�����Ҫ�ٴ�����


		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;									//����GPIO��ʼ���ṹ���GPIO����
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//����GPIO��ʼ���ṹ���GPIO���ģʽ���������ģʽ
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//����GPIO��ʼ���ṹ���GPIO����

		GPIO_Init(GPIOB,  &GPIO_InitStruct);										//��ʼ��GPIO

		//GPIO_ResetBits(GPIOB,GPIO_Pin_12);



		//GPIO_InitTypeDef GPIO_InitStruct;											//��Ϊ�������Ѿ�������һ�Σ�����ֱ�Ӹ��ü��ɣ�����Ҫ�ٴ�����



		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;									//����GPIO��ʼ���ṹ���GPIO����
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						//����GPIO��ʼ���ṹ���GPIO���ģʽ���������ģʽ
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//����GPIO��ʼ���ṹ���GPIO����

		GPIO_Init(GPIOC,  &GPIO_InitStruct);										//��ʼ��GPIO

		//GPIO_ResetBits(GPIOC,GPIO_Pin_15);


// GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //����ʱ��
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //��ʼ���ܽ�
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������ģʽ���������ģʽ
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�����������
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 
// GPIO_ResetBits(GPIOA,GPIO_Pin_0);					//���ùܽų�ʼֵ����Ϊ�͵�ƽ
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


