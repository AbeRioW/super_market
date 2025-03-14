#include "stm_flash.h"
#include "stm32f1xx_hal_flash_ex.h"


typedef __IO uint16_t vu16;
static uint16_t stmflash_readHalfWord(uint32_t addr)
{
		return *(vu16*)addr;
}

static uint8_t stmflash_get_error_status(void)
{
		uint32_t res;
	  
		res = FLASH->SR;
	  
	  if(res&(1<<0)) return 1;   //bus=1,æ
		if(res&(1<<2)) return 2;   //PGEER=1,��̴���
	  if(res&(1<<4)) return 3;   //WRPRTERR = 1,д�������� 
}

static uint8_t stmflash_wait_done(uint32_t time)
{
		uint8_t res;
	  
	   do{
				res = stmflash_get_error_status();
			  if(res!=1)
				{
					break;   //��æ����ȴ�ֱ���˳�
				}
				
				time--;
		 }while(time);
		 
		 if(time ==0)
			 res= 0xff;
		 
		 return res;
}

uint8_t stm_flash_erase_sector(uint32_t saddr){
	uint8_t res = 0;
	res = stmflash_wait_done(0x5fffffff);   //�ȴ��ϴβ������,>20ms
	if(res==0)
	{
			FLASH->CR |= 1<<1; //ҳ����
			FLASH->AR = saddr;     //����ҳ��ַ(ʵ���ǰ��ֵ�ַ)
		  FLASH->CR |= 1<<6;   //��ʼ����
		  res = stmflash_wait_done(0x5fffffff);
		   
		  if(res!=1)
			{
					FLASH->CR &= ~(1<<1);   //���ҳ������־
			}
	}
	
	return res;
}

void flash_write(uint32_t writeaddr,uint16_t *pbuffer,uint16_t num)
{
		uint16_t i;
	  HAL_FLASH_Unlock();
	  for(i=0;i<num;i++)
		{
			  
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,writeaddr,pbuffer[i]);
			  writeaddr+=2; //��ַ��2
		}
		HAL_FLASH_Lock();
}

void flash_read(uint32_t readaddr,uint16_t *pbuffer,uint16_t num)
{
		uint16_t i;
	  for(i=0;i<num;i++)
		{
			  pbuffer[i]=stmflash_readHalfWord(readaddr);
			  readaddr+=2; //��ַ��2
		}
}

///////////////////////////////////////////////////////////
//flash��������,����и�ֵ
//STM32_FLASH_BASE+STM32_SECTOR_SIZE*60
void copy_nfc_message(uint32_t readaddr,rfid temp[2])
{

	  uint16_t * buffer;
	  int num;
	  flash_read(readaddr,buffer,num);
	
	  temp[0].id[0] = (uint8_t)(buffer[0]>>8);
		temp[0].id[1] = (uint8_t)(buffer[0]);

	  temp[0].id[2] = (uint8_t)(buffer[1]>>8);
		temp[0].id[3] = (uint8_t)(buffer[1]);
	
		temp[0].price = buffer[2];
	
		temp[1].id[0] = (uint8_t)(buffer[3]>>8);
		temp[1].id[1] = (uint8_t)(buffer[3]);

	  temp[1].id[2] = (uint8_t)(buffer[4]>>8);
		temp[1].id[3] = (uint8_t)(buffer[4]);
	
		temp[1].price = buffer[5];
		
}


void write_nfc_message(uint32_t readaddr,rfid nfc)
{
	   uint16_t flash_buf[3]= {0xffff,0xffff,0xffff};
	   flash_buf[0]=(nfc.id[0]<<8)+(nfc.id[1]);
		 flash_buf[1]=(nfc.id[2]<<8)+(nfc.id[3]);
		 flash_buf[2]=nfc.price;
		 stm_flash_erase_sector(readaddr);
	   flash_write(STM32_FLASH_BASE+STM32_SECTOR_SIZE*60,flash_buf,3);
}


