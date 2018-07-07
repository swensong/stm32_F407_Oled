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

/*Main---------------------------------------*/
int main(void)
{
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );

    TIM2_Init( 10000, 84 );
	/*TIM3_PWM��ʼ��*/
    TIM3_Init( 10000, 84 );
    TIM4_Init( 20000, 84 );

    USART1_Config( 115200 );

	/*loop-------------------------------------*/
    TIM_SetCompare1( TIM3, 1000);
    TIM_SetCompare2( TIM3, 2000);
    TIM_SetCompare3( TIM3, 3000);
    TIM_SetCompare4( TIM3, 4000);

    // ����������ֵ 900 ��ǰ�� 1025��ת�� 775 ��ת
    TIM_SetCompare3( TIM4, 900 );

    USART1_Write_String( "hello world!\r\n", sizeof("hello world!\r\n") );

    while (1)
    {
        USART1_Driver();
    }
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
