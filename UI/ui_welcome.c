#include "ui_welcome.h"
#include "stdio.h"
#include "string.h"
#include "ui_home.h"

uint8_t pin_code[4]={0x00,0x00,0x00,0x00};
uint8_t pin_contrast[4]= {0x00,0x00,0x00,0x00}; //这里是取出来对比的PIN码

char* pin_show[12]={"0","1","2","3","4","5","6","7","8","9","<","_"};
void ui_welcome(void)
{
	  int break_s = 0;
	  int pin_pos=11,i;
	  int position=0;
	  char* pin1_show[4]= {pin_show[11],pin_show[11],pin_show[11],pin_show[11]};
	  
	  while(1)
		{

			  OLED_ShowString(10,10,(uint8_t*)"Admin Password ",16,1);
				if(button==DOWN_BUTTON)
				 {
					  HAL_Delay(300);
					  button = UNPRESSED;
					 
					  if(pin_pos==11)
						{
								pin_pos-=2;
						}
						else
						{
								pin_pos--;
							  if(pin_pos<0)
								{
									position==0?(pin_pos=9):(pin_pos=10);
								}
						}
						pin1_show[position]=pin_show[pin_pos];
				 }
				 
				 if(button==UP_BUTTON)
				 {
            HAL_Delay(300);
					  button = UNPRESSED;
					 
					  if(pin_pos==11)
						{
								pin_pos=0;;
						}
						else
						{
							  pin_pos++;
									if(position==0)
									{
										  if(pin_pos>9)
											{
													pin_pos=0;
											}
									}
									else
									{

										  if(pin_pos>10)
											{
													pin_pos=0;
											}
									}
						}
						
						pin1_show[position]=pin_show[pin_pos];

				 }
				 
				 if(button==ENSURE_BUTTON)
				 {
					  HAL_Delay(300);
					  button = UNPRESSED;
					 
					  if(pin_pos==10)
						{
							  pin_pos=11;
							  pin1_show[position]=pin_show[pin_pos];
							  position--;
							  pin1_show[position]=pin_show[pin_pos];
						}
						else
						{
							  pin_code[position] = pin_pos; //进行赋值
							
								position++;
							  if(position>3)
								{
										for(i=0;i<4;i++)
									  {
												if(pin_code[i]==0x0b)
												{
															OLED_Clear();
													    OLED_ShowString(30,40,(uint8_t*)"pin errors",16,1);
													  OLED_Refresh();
													    HAL_Delay(1000);
														  OLED_Clear();
													
													   //数据归位
															pin_pos=11;
															position=0;
															pin1_show[0]= pin_show[11];
															pin1_show[1]= pin_show[11];
															pin1_show[2]= pin_show[11];
															pin1_show[3]= pin_show[11];
													    break_s = 1;
													    break;   //这里是退出for循环
												}			
										}
										
										if(break_s)
										{
												break_s=0;
											  continue;
										}

										if(memcmp(pin_code,pin_contrast,4)==0)
										{
											  OLED_Clear();
												break;
										}
										else
										{			
												OLED_Clear();
												OLED_ShowString(30,40,(uint8_t*)"pin error",16,1);
											  OLED_Refresh();
												HAL_Delay(1000);
											  OLED_Clear();
													
												//数据归位
												pin_pos=11;
												position=0;
												pin1_show[0]= pin_show[11];
												pin1_show[1]= pin_show[11];
												pin1_show[2]= pin_show[11];
												pin1_show[3]= pin_show[11];
												continue;
												
										}


								}
								pin_pos=11;
								pin1_show[position]=pin_show[pin_pos];
							  
							  
						}

								
				 }
				 
				OLED_ShowString(30,40,(uint8_t*)pin1_show[0],16,position==0?0:1);
				OLED_ShowString(50,40,(uint8_t*)pin1_show[1],16,position==1?0:1);
				OLED_ShowString(70,40,(uint8_t*)pin1_show[2],16,position==2?0:1);
				OLED_ShowString(90,40,(uint8_t*)pin1_show[3],16,position==3?0:1);
				OLED_Refresh();
				 				 
		}
		
		//判断正确了
		ui_home();
	  
		//printf("%02x %02x %02x %02x",pin_code[0],pin_code[1],pin_code[2],pin_code[3]);
		
		
}

