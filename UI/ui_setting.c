#include "ui_setting.h"
#include "stdio.h"
#include "RC522.h"
#include "ui_welcome.h"
#include "ui_home.h"
#include "string.h"

static void handle_product_price(void);

void ui_setting(void)
{
	  int position=0;
	
	  while(1)
		{
				OLED_ShowString(15,10,(uint8_t*)"set product price",8,position==0?0:1);
				OLED_ShowString(15,20,(uint8_t*)"set admin pin",8,position==1?0:1);
				OLED_ShowString(15,30,(uint8_t*)"back to home",8,position==2?0:1);
				OLED_Refresh();
				 if(button==DOWN_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						position++;
					  if(position >2)
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
								position=2;
						}
				 }
				 
				 if(button==ENSURE_BUTTON)
				 {

					  button = UNPRESSED;
					  HAL_Delay(100);
						switch(position)
						{
							case 0:
								 OLED_Clear();
								 handle_product_price();
								break;
							case 1:
								break;
							case 2:
								 OLED_Clear();
								 return ;
								break;
						}
				 }
		}
}

static void handle_product_price(void)
{
	   rfid mfc_id;
	   uint8_t status;
	   uint8_t g_ucTempbuf[20]; 
	   uint8_t cardid[4]={0x00};
		int position=0;
	  int price = 3;
	  char price_show[10]={0x00};
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
				
				//½øÐÐ¸³Öµ²Ù×÷
				memcpy(mfc_id.id,cardid,4);
				mfc_id.price = price;
				
				printf("%02x %02x %02x %02x \r\n",cardid[0],cardid[1],cardid[2],cardid[3]);
				
		}
}