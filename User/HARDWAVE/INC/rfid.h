#ifndef __RFID_H
#define __RFID_H

#include "stm32f10x.h"
#include <stdio.h>
//////////////////////////////////
//端口定义
/////////////////////////////////////////////////////////////////////
//MFRC500
// sbit     MF522_NSS  =P2^4 ;			//RC500片选 SDA
// sbit     MF522_SCK  = P2^5;
// sbit     MF522_SI   = P2^3;         //MOSI
// sbit     MF522_SO   = P2^2;         //MISO
// sbit     MF522_RST  = P2^1;  

//SPI方式
#define RFID_PORT   GPIOA

#define MF522_NSS    GPIO_Pin_4      //  SPI_SDA    SPI_NSS
#define MF522_SCK    GPIO_Pin_5
#define MF522_SO   GPIO_Pin_6
#define MF522_SI   GPIO_Pin_7

#define MF522_RST   GPIO_Pin_0

/////////////////////////////////////////////////////////////////////
//函数原型
/////////////////////////////////////////////////////////////////////
void InitializeSystem();                                   
                                    

#endif
