以STM32F103C8T6为主控，用SPI通信驱动RFID-RC522模块，PWM驱动SG90舵机，实现宿舍刷IC卡开门，当手机NFC复制IC卡后，拥有手机即可开门，解决忘带钥匙的尴尬情况。

2023/12/22 16:25
解决了编译时，SPIClassStruct类编译报错的问题。
解决方法是，在Keil 5 上设置C/C++编译器为C99 mode模式。

2023/12/29 20:50
解决了C8T6进入__WFI()函数【睡眠模式】后，无法用外部中断唤醒C8T6的问题。
解决方法是，在设置外部中断引脚时，需要复用该引脚的功能。

2023/12/31 18:17
修复了在实体卡快速入场快速出场时，SG90舵机只会旋转第一次，不会旋转第二次，需第二次检测到卡片进场才会旋转第二次的bug。
修复方案是，在每次进入睡眠模式前，进行舵机0°的旋转，让门锁把手归位。

2024/1/9 1:11
修复了在按按钮前将实体卡提前放置在验卡区，再按下按钮，会导致后续再次按按钮放卡开门失效的问题。
修复方案是，在开门前添加了标志位判断，验卡的同时判断标志位，开门后将标志位清零。
这样当开门动作结束且标志位清零后，本次中断唤醒不会再进入执行开门动作的判断内。
这将只能一次按钮只开一次门，避免一次按钮后，长时间将卡放置在读卡区会多次开门的情况。