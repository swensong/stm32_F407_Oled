/************************************************
	 ���ƣ�PWM���ʵ��

	 ���ߣ�BW
	 
	 ע�⣺��ʱ��PWM�̶�ͨ�����IO����һ�������
				 �̶�,��ʵ��ʹ��TIM3��ͨ��2��IO��ΪPA7��
				 ������ʱ����ͨ���ɲ��ҹٷ��ֲ��ٶ�
				 
	 ��������ʾ�����ɿ���һ��Ƶ��Ϊ10KHzռ�ձ�Ϊ
				  40%�ľ��β�
	 
	 ���ڣ�2018/6/1
	 
	 Ŀ�꣺��Ϥ��ʱ����PWM���ģʽ��ʹ��
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
    /* ������Ƴ�ʼ�� */
    /*TIM3_PWM��ʼ��*/
    TIM5_Init( 100, 84 );

    tim_init1();	


    USART1_Config( 115200 );

    OLED_Init();
    TIM2_Init( 1000, 84 );

    OLED_ShowString(0,0,"hello world!",12);

    USART1_Write_String("hello world!\r\n", sizeof("hello world!\r\n"));

	// 12�Ĳ���������ȷ����޷�ת��
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
