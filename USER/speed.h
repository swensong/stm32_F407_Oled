/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/

#ifndef __SPEED_H
#define __SPEED_H	 

#include "stm32f4xx.h"

#define RIGHT 1
#define LEFT  0

void speed_init(void);
int read_speed(u8 direction);
#endif