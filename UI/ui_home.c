#include "ui_home.h"
#include "RC522.h"
#include "stdio.h"
#include "string.h"

extern rfid nfc_card[2];

void ui_home(void)
{
	
	  uint8_t status,i;
		uint8_t g_ucTempbuf[20]; 
	  uint8_t cardid[4]={0x00,0x00,0x00,0x00};
	  uint8_t comp_data[4]={0xff,0xff,0xff,0xff};
		char show_price[10]={0x00};
		OLED_ShowString(15,10,(uint8_t*)"Wait For Near",16,1);
		OLED_ShowString(80,50,(uint8_t*)"Setting",8,1);
		while(1)
		{
			  
				OLED_ShowString(30,30,(uint8_t*)" <<>> ",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
			  OLED_ShowString(30,30,(uint8_t*)"<<  >>",16,1);
			  OLED_Refresh();
				HAL_Delay(200);
			
				if(button==ENSURE_BUTTON)
				{
						button = UNPRESSED;
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
		 
		 									OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)"hellos",16,1);
									OLED_Refresh();
									HAL_Delay(300);
		 
		 for(int i=0;i<2;i++)
		 {
				if(memcmp(cardid,nfc_card[i].id,4)==0)
				{
						if(nfc_card[i].price!=0xffff)
						{
							    OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)"hello",16,1);
									OLED_Refresh();
									HAL_Delay(300);
							     OLED_Clear();
						}
						else
						{
									OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)"hellos",16,1);
									OLED_Refresh();
									HAL_Delay(300);
							     OLED_Clear();
						}
				}
				
				if(memcmp(nfc_card[i].id,comp_data,4)==0)
				{
									OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)"hellot",16,1);
									OLED_Refresh();
									HAL_Delay(300);
				}
		 }
		 
		}
		
		//进入设置页面
		ui_setting();

}