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
void TIM5_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);   //TIM3
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOB?
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //GPIOB?
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); //GPIOB?��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); //GPIOB?

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  //GPIOB
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //
    GPIO_Init(GPIOA,&GPIO_InitStructure);               //
     
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_Period=arr;                       
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);                  


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_Pulse = 6000;//����ռ�ձ�

    TIM_OC1Init(TIM5, &TIM_OCInitStructure); 
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM5, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); 

    TIM_OC3Init(TIM5, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  

    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  
       
    TIM_ARRPreloadConfig(TIM5,ENABLE);

    TIM_Cmd(TIM5, ENABLE);
}

void TIM10_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10); //GPIOB?

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

    TIM_TimeBaseInit(TIM10,&TIM_TimeBaseStructure);                  


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_Pulse = 6000;//����ռ�ձ�

    TIM_OC1Init(TIM10, &TIM_OCInitStructure); 
    TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM10,ENABLE);

    TIM_Cmd(TIM10, ENABLE);
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

//  0 < number < 125
u8 actuator_control( u8 direction, u32 number )
{
    u8 number_flag = 0;
    u8 buf[4];

    if ( number > 125 )
    {
        USART1_Write_String( "bad number1\r\n", sizeof("bad number1\r\n") );
        return 0;
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
        return 0;
    }

    buf[0] = number / 1000 + '0';
    buf[1] = number / 100 % 10 + '0';
    buf[2] = number / 10 % 10 + '0';
    buf[3] = number % 10 + '0';

    USART1_Write_String( buf, 4 );
    USART1_Write_String( "\r\n", sizeof("\r\n") );
    
    // ����������ֵ 900 ��ǰ�� 1025��ת�� 775 ��ת
    if ( number_flag == 1 )
    {
        TIM_SetCompare1( TIM10, number );
    }
    else
    {
        USART1_Write_String( "unsafe data!/r/n", sizeof("unsafe data!/r/n") );
    }

    return 1;
}

/* 0 =< speed =< 9999 */
// ���������
u8 Motor_Left_Control( u8 direction, u32 speed )
{


    if ( speed > 9999 )
    {
        USART1_Write_String( "number1 error\r\n", sizeof("number1 error\r\n") );
        return 0;
    }

    if ( direction == FORWARD )
    {
        TIM_SetCompare1( TIM5, speed);
        TIM_SetCompare2( TIM5, 0);
    }
    else if ( direction == BACK )
    {
        TIM_SetCompare1( TIM5, 0);
        TIM_SetCompare2( TIM5, speed);
    }
    else
    {
        USART1_Write_String( "direction error\r\n", sizeof("direction error\r\n") );
    }
	
	return 1;
}

/* 0 =< speed =< 9999 */
// �����Ҳ���
u8 Motor_Right_Control( u8 direction, u32 speed )
{


    if ( speed > 9999 )
    {
        USART1_Write_String( "number1 error\r\n", sizeof("number1 error\r\n") );
        return 0;
    }

    if ( direction == FORWARD )
    {
        TIM_SetCompare3( TIM5, 0);
        TIM_SetCompare4( TIM5, speed);
    }
    else if ( direction == BACK )
    {
        TIM_SetCompare3( TIM5, speed);
        TIM_SetCompare4( TIM5, 0);
    }
    else
    {
        USART1_Write_String( "direction error\r\n", sizeof("direction error\r\n") );
    }
	
	return 1;
}

// ֱ�߿��Ƶ��ǰת������ת
u8 Motor_Control( u8 direction, u32 speed )
{
    if ( Motor_Right_Control( direction, speed ) && Motor_Left_Control( direction, speed ))
		return 1;
	
	return 0;
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

/* TIM1 ��Ϊ������ */
void TIM1_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    EXTI_InitTypeDef EXTI_InitStructure;

}

#if 0

//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
    TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5

 
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 		    

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//���
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_Cmd(TIM5,DISABLE ); 	//�رն�ʱ��5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}

#endif
