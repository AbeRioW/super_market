#include "ui_setting.h"
#include "stdio.h"
#include "RC522.h"
#include "ui_welcome.h"
#include "ui_home.h"
#include "string.h"
#include "main.h"
#include "stm_flash.h"
#include "ui_welcome.h"
static void handle_product_price(void);

void ui_setting(void)
{
	  int position=0;
	
	  while(1)
		{
				OLED_ShowString(15,10,(uint8_t*)"set product price",8,position==0?0:1);
				OLED_ShowString(15,30,(uint8_t*)"back to home",8,position==1?0:1);
				OLED_Refresh();
				 if(button==DOWN_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						position++;
					  if(position >1)
						{
								position=0;
						}
				 }
				 
				 if(button==UP_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						position--;
					  if(position <0)
						{
								position=1;
						}
				 }
				 
				 if(button==ENSURE_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(300);
						switch(position)
						{
							case 0:
								 OLED_Clear();
								 handle_product_price();
								break;
							case 1:
									OLED_Clear();
								 return ;
								break;
						}
						break;
				 }
		}
		OLED_Clear();
		ui_home();
}

static void handle_product_price(void)
{
	   uint16_t price_save[4]={0,0,0,0};
	   rfid mfc_id;
	   uint8_t status;
	   uint8_t g_ucTempbuf[20]; 
	   uint8_t cardid[4]={0x00};
		int position=0;
	  int price = 3;
	  char price_show[10]={0x00};
		
							  button = UNPRESSED;
		HAL_Delay(300);
	  while(1)
		{
				OLED_ShowString(15,10,(uint8_t*)"please input price",8,1);
			  sprintf(price_show,"%02d",price);
			  OLED_ShowString(60,30,(uint8_t*)price_show,16,1);
				OLED_Refresh();
				
				if(button==DOWN_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						price--;
					  if(position <0)
						{
								position=0;
						}
				 }
				 
				 if(button==UP_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						price++;

				 }
				 
				 if(button==ENSURE_BUTTON)
				 {

							button = UNPRESSED;
					    OLED_Clear();
							break;
						}
				 				 
		}
		

				OLED_ShowString(10,10,(uint8_t*)"approach NFC card",8,1);
			  OLED_Refresh();
		
		    OLED_ShowString(10,50,(uint8_t*)"Ensure button cancel",8,1);
			  OLED_Refresh();
		while(1)
		{
			  OLED_ShowString(30,30,(uint8_t*)" <<>> ",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
			  OLED_ShowString(30,30,(uint8_t*)"<<  >>",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
			
			  status = PCD_Request(PICC_REQALL, g_ucTempbuf);//Ñ°¿¨£¬·À³å×²
				if(status)
				{
					PCD_Reset();
					PCD_AntennaOff(); 
					PCD_AntennaOn(); 
			    continue;
				}
				
				status = PCD_Anticoll(cardid);
				printf("%02x %02x %02x %02x \r\n",cardid[0],cardid[1],cardid[2],cardid[3]);
				//½øÐÐ¸³Öµ²Ù×÷
				for(int i=0;i<4;i++)
				{
						if(memcmp(nfc_card[i].id,cardid,4)==0)
						{
								printf("yes\r\n");
							  nfc_card[i].price = price;
							  price_save[0]=nfc_card[0].price;
								price_save[1]=nfc_card[1].price;
							  price_save[2]=nfc_card[2].price;
								price_save[3]=nfc_card[3].price;
							  Flash_Write(STM32_FLASH_BASE+STM32_SECTOR_SIZE*USER_FLASH_PAGE,price_save,4);
								printf("%02x %02x %02x %02x \r\n",cardid[0],cardid[1],cardid[2],cardid[3]);
							  break;
						}
				}

				break;
				
		}
		

}
