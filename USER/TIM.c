/************************************************
	 ��    �ƣ���ʱ������ 
	 
	 �޸����ڣ�2018/6/1
************************************************/


/*Include--------------------------------------*/
#include "TIM.h"
#include "usart.h"


/************************************************/
/*	��������TIM3_Init														*/
/*	��  ������ʱ��3��ʼ������ 									*/
/*	��  �룺arr-----����ֵ											*/
/*					psc-----��Ƶϵ��										*/
/*					CCR2_Val--����ռ�ձ�								*/
/*	��  ������																	*/
/************************************************/

u16 cnt = 0;

//void TIM3_Init(u16 arr, u16 psc, u16 CCR1_Val, u16 CCR2_Val)
void TIM3_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //TIM3
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB?
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB?
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3); //GPIOB?��
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3); //GPIOB?

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;  //GPIOB
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //
    GPIO_Init(GPIOB,&GPIO_InitStructure);               //
     
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_Period=arr;                       
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);                  


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = 6000;//����ռ�ձ�

    TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 


    TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  


    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
       
    TIM_ARRPreloadConfig(TIM3,ENABLE);

    TIM_Cmd(TIM3, ENABLE);
    /*
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIOʱ��
	 
 
    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.7
    //�������ÿ��ֻ�ܶ�Ӧ��ʼ��һ��IO��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;           //GPIOA7
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

	//��ʼ��TIM3 Channel3 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM3; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ3
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;//����ռ�ձ�
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC3

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel4 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM4; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ4
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;//����ռ�ձ�
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
    */
}

void TIM4_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);   //TIM3
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); //GPIOB?

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;  //GPIOB
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //
    GPIO_Init(GPIOB,&GPIO_InitStructure);               //
     
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_Period=arr;                       
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);                  


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = 6000;//����ռ�ձ�

    TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM4,ENABLE);

    TIM_Cmd(TIM4, ENABLE);
}

void TIM2_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //TIM3

    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
    TIM_TimeBaseStructure.TIM_Period=arr;                       
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);                  

    TIM_ITConfig( TIM2 ,TIM_IT_Update, ENABLE );

    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

void TIM2_IRQHandler()
{

    if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET )
    {
        USART1_Rx_Monitor( 1 );
        if ( ++cnt > 1000 )
        {
            cnt = 0;
            USART1_Write_String( "in interrupt!\r\n" , sizeof( "in interrupt!\r\n" ) );
        }
    }
    TIM_ClearITPendingBit( TIM2, TIM_IT_Update );
}

//  0 < number < 125
u8 actuator_control( u8 direction, u32 number )
{
    u8 number_flag = 0;
    u8 buf[4];

    if ( number > 125 )
    {
        USART1_Write_String( "bad number1\r\n", sizeof("bad number1\r\n") );
        return -1;
    }

    if ( direction == LEFT )
    {
        number_flag = 1;
        number = 900 + number;
    }
    else if (direction == RIGHT)
    {
        number_flag = 1;
        number = 900 - number;
    }
    else
    {
        USART1_Write_String( "bad number2\r\n", sizeof("bad number2\r\n") );
        return -1;
    }

    buf[0] = number / 1000 + '0';
    buf[1] = number / 100 % 10 + '0';
    buf[2] = number / 10 % 10 + '0';
    buf[3] = number % 10 + '0';
    buf[4] = '\0';

    USART1_Write_String( buf, 4 );
    USART1_Write_String( "\r\n", sizeof("\r\n") );
    
    // ����������ֵ 900 ��ǰ�� 1025��ת�� 775 ��ת
    if ( number_flag == 1 )
    {
        TIM_SetCompare3( TIM4, number );
    }
    else
    {
        USART1_Write_String( "unsafe data!/r/n", sizeof("unsafe data!/r/n") );
    }

    return 1;
}
