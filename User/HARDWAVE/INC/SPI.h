#ifndef __SPI_AS_H
#define __SPI_AS_H
 
#include "main.h"
 
typedef struct {
	void (* SPI1_Init)(void);
	void (* SPI2_Init)(void);
	uint8_t (* WriteRead)(SPI_TypeDef *, uint8_t, uint32_t);
	void (* WriteCSPin)(SPI_TypeDef *, BitAction);
} SPIClassStruct;
 
extern SPIClassStruct SPIClass;
 
#endif
