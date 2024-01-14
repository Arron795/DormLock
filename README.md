# DormLock
A  DormLock based on STM32 and RFID-RC522.

Using STM32F103C8T6 as the main control, SPI communication is used to drive the RFID-RC522 module, PWM is used to drive the SG90 servo, achieving dormitory IC card swiping to open the door. When the NFC of the mobile phone copies the IC card, owning the phone can open the door, solving the embarrassing situation of forgetting the key.





一个基于 STM32 和 RFID-RC522 的宿舍门锁。

以STM32F103C8T6为主控，用SPI通信驱动RFID-RC522模块，PWM驱动SG90舵机，实现宿舍刷IC卡开门，当手机NFC复制IC卡后，拥有手机即可开门，解决忘带钥匙的尴尬情况。
