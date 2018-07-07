#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"


void USART1_Config(u32 bound);
void USART1_Driver(void);
void USART1_Write_String( u8 *buf, u8 len );
u8 USART1_Read_String( u8 *buf, u8 len );
void USART1_Rx_Monitor(u16 ms);
u8 Cmp_Memory( u8 *ptr1, u8 *ptr2, u8 len );
void USART1_Action( u8 *buf, u8 len );

#endif
