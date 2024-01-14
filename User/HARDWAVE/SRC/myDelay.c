#include "myDelay.h"

void delay_s(uint32_t s)
{
    SysTick->CTRL = 0;              //关闭定时器
    SysTick->CTRL = 0x00000004;     //选择处理器时钟 (时钟源HCLK 并打开定时器)
    SysTick->CTRL = 0x00000001;     //开启定时器 (使能)

    
    //SystemCoreClock = 72兆赫兹 = 72Mhz = 72000000 （6个0）                                
    SysTick->LOAD = (SystemCoreClock ) * s - 1;       //设置计数器                                                        
    SysTick->VAL = 0;               //清空定时器

    while (!(SysTick ->CTRL & 0x00010000)); //等待标志位出现（计数完成/计数到0）
    
}

void delay_ms(uint32_t ms)
{
    SysTick->CTRL = 0;              //关闭定时器
    SysTick->CTRL = 0x00000004;     //选择处理器时钟 (时钟源HCLK 并打开定时器)
    SysTick->CTRL = 0x00000001;     //开启定时器 (使能)

    
    //SystemCoreClock = 72兆赫兹 = 72Mhz = 72000000 （6个0）                                
    SysTick->LOAD = (SystemCoreClock / 1000) * ms - 1;       //设置计数器                                                        
    SysTick->VAL = 0;               //清空定时器

    while (!(SysTick ->CTRL & 0x00010000)); //等待标志位出现（计数完成/计数到0）
    
}

void delay_us(uint32_t us)
{
    SysTick ->CTRL = 0;     //关闭定时器
    SysTick->CTRL = 0x00000004;     //选择处理器时钟 (时钟源HCLK 并打开定时器)
    SysTick->CTRL = 0x00000001;     //开启定时器 (使能)   
    

    SysTick ->LOAD = (SystemCoreClock / 1000 / 1000) *us - 1;   //写入装载值
    SysTick ->VAL = 0 ;      //清零定时器

    while(!(SysTick ->CTRL & 0x00010000));
}


void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


