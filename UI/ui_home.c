#include "ui_home.h"
#include "RC522.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"



//两站卡的ID:D2C7B205  13D08608
rfid nfc_card[2]={{{0xd2,0xc7,0xb2,0x05},0},{{0x13,0xd0,0x86,0x08},0}};

void ui_home(void)
{
	  char show_id[20];
	  uint8_t status,i;
		uint8_t g_ucTempbuf[20]; 
	  uint8_t cardid[4]={0x00,0x00,0x00,0x00};
	  uint8_t comp_data[4]={0xff,0xff,0xff,0xff};
		char show_price[10]={0x00};
		while(1)
		{
			  
					OLED_ShowString(15,10,(uint8_t*)"Wait For Near",16,1);
				OLED_ShowString(80,50,(uint8_t*)"Setting",8,1);
				OLED_ShowString(30,30,(uint8_t*)" <<>> ",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
			  OLED_ShowString(30,30,(uint8_t*)"<<  >>",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
				if(button==ENSURE_BUTTON)
				{
						button = UNPRESSED;
					  				HAL_Delay(400);
					  OLED_Clear();
						break;
				}
				
		 status = PCD_Request(PICC_REQALL, g_ucTempbuf);//???
		 if(status)
		 {
				PCD_Reset();
				PCD_AntennaOff(); 
				PCD_AntennaOn(); 
			  continue;
		 }
		 status = PCD_Anticoll(cardid);
		 sprintf(show_id,"%02x%02x%02x%02x",cardid[0],cardid[1],cardid[2],cardid[3]);
		 
//		 OLED_Clear();
//		 OLED_ShowString(30,30,(uint8_t*)show_id,16,1);
//		 OLED_Refresh();
//		 HAL_Delay(300);
		 
		 for(int i=0;i<2;i++)
		 {
				if(memcmp(cardid,nfc_card[i].id,4)==0)
				{
					        uint8_t price_send[2]={0,0};
									sprintf(show_price,"price:%04x",nfc_card[i].price);
									OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)show_price,16,1);
									OLED_Refresh();

									
									price_send[0]=(nfc_card[i].price>>8)&0xff;
									price_send[1]=nfc_card[i].price&0xff;
					        HAL_UART_Transmit(&huart3,price_send,2,0xffff);
									printf("hello\r\n");
																		HAL_Delay(3000);
					        OLED_Clear();
				}
				
		 }
		 
		}
		
		//进入设置页面
								button = UNPRESSED;
		ui_setting();

}