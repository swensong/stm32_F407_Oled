/************************************************
	 名称：PWM输出实验

	 作者：BW
	 
	 注意：定时器PWM固定通道输出IO口在一般情况下
				 固定,本实验使用TIM3的通道2，IO口为PA7，
				 其他定时器和通道可查找官方手册或百度
				 
	 现象：连接示波器可看到一个频率为10KHz占空比为
				  40%的矩形波
	 
	 日期：2018/6/1
	 
	 目标：熟悉定时器和PWM输出模式的使用
************************************************/


/*Include-----------------------------------*/
#include "stm32f4xx.h"
#include "TIM.h"
#include "usart.h"
#include "oled.h"
#include "led.h"
#include "test.h"

/*Main---------------------------------------*/
int main(void)
{
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );

    LED_Init();
    /* 舵机控制初始化 */
    /*TIM3_PWM初始化*/
    TIM5_Init( 100, 84 );

    tim_init1();	


    USART1_Config( 115200 );

    OLED_Init();
    TIM2_Init( 1000, 84 );

    OLED_ShowString(0,0,"hello world!",12);

    USART1_Write_String("hello world!\r\n", sizeof("hello world!\r\n"));

	// 12的参数不能相等否则无法转动
    BIN2 = 1;
    BIN1 = 0;
    STBY = 1;
    AIN1 = 0;
    AIN2 = 1;
    TIM_SetCompare1( TIM5, 50);
    TIM_SetCompare2( TIM5, 50);

    while (1)
    {
        USART1_Driver();
    }
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
