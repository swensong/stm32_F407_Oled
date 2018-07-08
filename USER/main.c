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

/*Main---------------------------------------*/
int main(void)
{
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );

    TIM2_Init( 1000, 84 );
	/*TIM3_PWM初始化*/
    TIM3_Init( 10000, 84 );
    TIM4_Init( 20000, 84 );

    USART1_Config( 115200 );

	/*loop-------------------------------------*/
    TIM_SetCompare1( TIM3, 1000);
    TIM_SetCompare2( TIM3, 2000);
    TIM_SetCompare3( TIM3, 3000);
    TIM_SetCompare4( TIM3, 4000);

    USART1_Write_String( "hello world!\r\n", sizeof("hello world!\r\n") );
    actuator_control( LEFT, 123);

    while (1)
    {
        USART1_Driver();
    }
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
