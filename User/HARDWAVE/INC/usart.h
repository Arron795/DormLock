#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define SIZE			10

extern uint8_t recbuff[SIZE];	//声明外部变量
extern uint8_t rec_buff_i ;

void Usart1_Init(uint32_t baudrate);
void USART1_IRQHandler(void);
void Usart_SendData(const uint8_t *data);
void Usart_SendIntData( int data);
void usart1_SendByte(uint8_t data);
void usart1_SendString(uint8_t *string);
void usart1_SendStr(char *str);


#endif

