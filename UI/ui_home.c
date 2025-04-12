#include "ui_home.h"
#include "RC522.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "stdbool.h"

uint8_t card_test[100]={0};

//两站卡的ID:D2C7B205  13D08608
rfid nfc_card[4]={{{0x54,0x2b,0x1d,0x05},0},{{0x03,0x1c,0x1a,0x05},0},{{0xae,0x41,0x1d,0x05},0},{{0x51,0xb3,0x19,0x05},0}};
uint8_t youhui_card[4]={0xd2,0xc7,0xb2,0x05};
uint8_t jiesuan_card[4]={0x13,0xD0,0x86,0x08};

void ui_home(void)
{
	  int card_test_position=0;
	  bool  discount = false;
	  float money=0;;
	  uint16_t card_price=0;
	  char show_id[20];
	  uint8_t status,i;
		uint8_t g_ucTempbuf[20]; 
	  uint8_t cardid[4]={0x00,0x00,0x00,0x00};
	  uint8_t comp_data[4]={0xff,0xff,0xff,0xff};
		char show_price[10]={0x00},show_all[20]={0};
		
		char show_id_f[10];
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
//		 sprintf(show_id,"%02x%02x%02x%02x",cardid[0],cardid[1],cardid[2],cardid[3]);
//		 
//		 OLED_Clear();
//		 OLED_ShowString(30,30,(uint8_t*)show_id,16,1);
//		 OLED_Refresh();
//		 HAL_Delay(300);
		 
		 for(int i=0;i<4;i++)
		 {
				if(memcmp(cardid,nfc_card[i].id,4)==0)
				{
					        uint8_t price_send[2]={0,0};
									sprintf(show_price,"price:%04x",nfc_card[i].price);
									OLED_Clear();
									OLED_ShowString(30,30,(uint8_t*)show_price,16,1);
									OLED_Refresh();                 
									card_price+=nfc_card[i].price;      //价格进行累加
									memcpy(card_test+card_test_position*4,cardid,4);  //对商品进行累加
									card_test_position++;
									HAL_Delay(1000);
									OLED_Clear();
									
									
//									price_send[0]=(nfc_card[i].price>>8)&0xff;
//									price_send[1]=nfc_card[i].price&0xff;
//					        HAL_UART_Transmit(&huart3,price_send,2,0xffff);
//									printf("hello\r\n");
//																		HAL_Delay(3000);
//					        OLED_Clear();
				}
				
		 }
		 
		 if(memcmp(cardid,youhui_card,4)==0)  //刷了优惠卡
		 {
			  discount = true;
				OLED_Clear();
				OLED_ShowString(30,30,(uint8_t*)"discount card",8,1);
				OLED_Refresh(); 
        HAL_Delay(1000);
				OLED_Clear();			 
		 }
		 
		 if(memcmp(cardid,jiesuan_card,4)==0)  //刷了优惠卡
		 {		 
			   if(discount)
				 {
						money = (float)card_price*0.8;
				 }
				 else
				 {
						money = (float)card_price;
				 }
				 
				 	for(int i_card=0;i_card<card_test_position;i_card++)
				 {
					    sprintf(show_id_f,"%02x%02x%02x%02x",card_test[0+i*4],card_test[1+i*4],card_test[2+i*4],card_test[3+i*4]);
							OLED_ShowString(0,i_card*8,(uint8_t*)show_id_f,8,1);
					 				 OLED_Refresh(); 
				 }

         HAL_Delay(2000);
				 OLED_Clear();	
				 
				 
				 sprintf(show_all,"settlement:%.2f",money);
				 
				 OLED_Clear();
				 				 OLED_ShowString(30,30,(uint8_t*)show_all,8,1);
				 HAL_UART_Transmit(&huart3,(uint8_t*)show_all,sizeof(show_all),0xffff);
				 OLED_Refresh(); 
				 				          HAL_Delay(2000);
				 

		 }
		 
		}
		
		//进入设置页面
		button = UNPRESSED;
		ui_setting();

}