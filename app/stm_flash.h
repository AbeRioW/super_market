#ifndef __STM_FLASH_H
#define __STM_FLASH_H
#include "main.h"
#include "ui_home.h"


#define STM32_FLASH_SIZE 				64  				//FLASH的页数
#define STM32_SECTOR_SIZE 		1024 					//一页的大小
#define STM32_FLASH_BASE 0x08000000  				//flash起始地址
#define USER_FLASH_SIZE 				63  				//FLASH的页数

uint16_t FLASH_ReadHalfWord(uint32_t addr);
uint32_t FLASH_ReadWord(uint32_t address);
uint64_t FLASH_ReadDoubleWord(uint32_t address);



void FLASH_ReadHalfWordData(uint32_t startAddress, uint16_t *readData, uint16_t countToRead);
void FLASH_ReadWordData(uint32_t startAddress, uint32_t *readData, uint16_t countToRead);
void FLASH_ReadDoubleWordData(uint32_t startAddress, uint64_t *readData, uint16_t countToRead);

void Flash_Write(uint32_t address, uint16_t *data, uint16_t length);

#endif
