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

    /* ������Ƴ�ʼ�� */
    TIM2_Init( 1000, 84 );
	/*TIM3_PWM��ʼ��*/
    TIM5_Init( 10000, 84 );
    TIM10_Init( 40000, 84 );

    USART1_Config( 115200 );

	/*loop-------------------------------------*/
    TIM_SetCompare1( TIM5, 1000);
    TIM_SetCompare2( TIM5, 2000);
    TIM_SetCompare3( TIM5, 3000);
    TIM_SetCompare4( TIM5, 4000);

    TIM_SetCompare1( TIM10, 3000 );
//    TIM_SetCompare1( TIM10, 5000 );
//    TIM_SetCompare1( TIM10, 775 );
//    TIM_SetCompare1( TIM10, 1025 );

    USART1_Write_String( "hello world!\r\n", sizeof("hello world!\r\n") );
    //actuator_control( LEFT, 125 );
    //actuator_control( RIGHT, 125 );
    //Motor_Control( BACK, 8000 );
	Motor_Control( FORWARD, 2000 );


    while (1)
    {
        USART1_Driver();
    }
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
