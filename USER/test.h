/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/

#ifndef __TEST_H
#define __TEST_H	 

#include "stm32f4xx.h"

void time_init(void);
void time_init1(void);	
int Read_Encoder(u8 TIMX);
#endif
