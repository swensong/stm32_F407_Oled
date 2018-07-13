#ifndef _OLED_H_
#define _OLED_H_


#include "stm32f4xx.h" 
#include "time.h"

void Delay_Ms(u32 ms);

void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);
void OLED_ShowFloat(u8 x,u8 y,const float p,u8 size,u8 pos);
u32 mypow(u8 m,u8 n);
#define LCD_SCL(x)  x?GPIO_WriteBit(GPIOD,GPIO_Pin_0,Bit_SET):GPIO_WriteBit(GPIOD,GPIO_Pin_0,Bit_RESET)      //SCLK  时钟 D0（SCLK）
#define LCD_SDA(x)  x?GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_SET):GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_RESET)      //SDA   D1（MOSI） 数据
#define LCD_RST(x)  x?GPIO_WriteBit(GPIOD,GPIO_Pin_4,Bit_SET):GPIO_WriteBit(GPIOD,GPIO_Pin_4,Bit_RESET)  //_RES  hardware reset   复位 
#define LCD_DC(x)   x?GPIO_WriteBit(GPIOD,GPIO_Pin_6,Bit_SET):GPIO_WriteBit(GPIOD,GPIO_Pin_6,Bit_RESET)   //DC  H/L 命令数据选通端，H：数据，L:命令
#define LCD_CS(x)   x?GPIO_WriteBit(GPIOG,GPIO_Pin_9,Bit_SET):GPIO_WriteBit(GPIOG,GPIO_Pin_9,Bit_RESET)   //CS  H/L 命令数据选通端，H：数据，L:命令




#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据 

#endif
