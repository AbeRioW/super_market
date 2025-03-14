#ifndef __UI_HOME_H
#define __UI_HOME_H

#include "oled.h"
#include "gpio.h"
#include "ui_setting.h"


typedef struct Rfid{
	uint8_t id[4];
	uint16_t price;
}rfid;

void ui_home(void);


#endif

