/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/

#ifndef __TIM_H
#define __TIM_H	 

#include "stm32f4xx.h"

#define LEFT    0       // 向左
#define RIGHT   1       // 向右
#define UP      0       // 向前
#define DOWN    1       // 向后

//void TIM3_Init(u16 arr, u16 psc, u16 CCR1_Val, u16 CCR2_Val);
void TIM3_Init(u16 arr, u16 psc);
void TIM4_Init(u16 arr, u16 psc);
void TIM2_Init(u16 arr, u16 psc);
u8 actuator_control( u8 direction, u32 number );

		 				    
#endif
