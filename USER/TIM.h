/************************************************
	 ��    �ƣ���ʱ������ 
	 
	 �޸����ڣ�2018/6/1
************************************************/

#ifndef __TIM_H
#define __TIM_H	 

#include "stm32f4xx.h"

#define LEFT    0       // ����
#define RIGHT   1       // ����

#define FORWARD 1       // ǰ��
#define BACK    0       // ����

//void TIM3_Init(u16 arr, u16 psc, u16 CCR1_Val, u16 CCR2_Val);
void TIM3_Init(u16 arr, u16 psc);
void TIM4_Init(u16 arr, u16 psc);
void TIM2_Init(u16 arr, u16 psc);
u8 actuator_control( u8 direction, u32 number );
u8 Motor_Left_Control( u8 direction, u32 speed );
u8 Motor_Right_Control( u8 direction, u32 speed );
u8 Motor_Control( u8 direction, u32 speed );

		 				    
#endif
