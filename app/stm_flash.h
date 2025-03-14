#ifndef __STM_FLASH_H
#define __STM_FLASH_H
#include "main.h"
#include "ui_home.h"


#define STM32_FLASH_SIZE 64  //FLASH��ҳ��
#define STM32_SECTOR_SIZE 1024 //һҳ�Ĵ�С
#define STM32_FLASH_BASE 0x08000000  //flash��ʼ��ַ

void flash_write(uint32_t writeaddr,uint16_t *pbuffer,uint16_t num);
void flash_read(uint32_t readaddr,uint16_t *pbuffer,uint16_t num);
uint8_t stm_flash_erase_sector(uint32_t saddr);
void copy_nfc_message(uint32_t readaddr,rfid temp[2]);
void write_nfc_message(uint32_t readaddr,rfid nfc);

#endif
