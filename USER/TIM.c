/************************************************
	 ��    �ƣ���ʱ������ 
	 
	 �޸����ڣ�2018/6/1
************************************************/


/*Include--------------------------------------*/
#include "TIM.h"


/************************************************/
/*	��������TIM3_Init														*/
/*	��  ������ʱ��3��ʼ������ 									*/
/*	��  �룺arr-----����ֵ											*/
/*					psc-----��Ƶϵ��										*/
/*					CCR2_Val--����ռ�ձ�								*/
/*	��  ������																	*/
/************************************************/

void TIM3_Init(u16 arr, u16 psc, u16 CCR1_Val, u16 CCR2_Val)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIOʱ��
	 
 
    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.7
    //�������ÿ��ֻ�ܶ�Ӧ��ʼ��һ��IO��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;           //GPIOA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA7
 
    
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM3 Channel1 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//����ռ�ձ�
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1

    TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;//����ռ�ձ�
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}
