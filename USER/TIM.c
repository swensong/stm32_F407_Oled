/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/


/*Include--------------------------------------*/
#include "TIM.h"
#include "usart.h"
#include "sin.h"
#include "DataScope_DP.h"
#include "oled.h"


/************************************************/
/*	函数名：TIM3_Init														*/
/*	描  述：定时器3初始化函数 									*/
/*	输  入：arr-----计数值											*/
/*					psc-----分频系数										*/
/*					CCR2_Val--设置占空比								*/
/*	输  出：无																	*/
/************************************************/

u16 cnt = 0;
extern __IO uint32_t Frequency1;

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
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); //GPIOB?′
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); //GPIOB?

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  //GPIOB
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //
    GPIO_Init(GPIOA,&GPIO_InitStructure);               //
     
    TIM_TimeBaseStructure.TIM_Prescaler=psc - 1;  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_Period=arr - 1;                       
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);                  


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_Pulse = 90;//设置占空比

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
    TIM_OCInitStructure.TIM_Pulse = 6000;//设置占空比

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

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}

void TIM2_IRQHandler()
{
    static u16 cnt = 0;
	static u16 cnt1 = 0;
//    static u8 data[1];
    static u16 cnt_data = 0;
    u16 i = 0;
    u16 Send_Count = 0;
        
    if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET )
    {
        if (cnt_data >= 361)
            cnt_data = 0;

//        data[0] = (sin1[cnt++]+1) * 256;

        USART1_Rx_Monitor( 1 );

        if ( cnt++ > 50 )
        {
            cnt = 0;

            DataScope_Get_Channel_Data( sin1[cnt_data++] , 1 ); //½«Êý¾Ý 1.0  Ð´ÈëÍ¨µÀ 1
            /*
            DataScope_Get_Channel_Data( 2.0 , 2 ); //½«Êý¾Ý 2.0  Ð´ÈëÍ¨µÀ 2
            DataScope_Get_Channel_Data( 3.0 , 3 ); //½«Êý¾Ý 3.0  Ð´ÈëÍ¨µÀ 3
            DataScope_Get_Channel_Data( 4.0 , 4 ); //½«Êý¾Ý 4.0  Ð´ÈëÍ¨µÀ 4
            DataScope_Get_Channel_Data( 5.0 , 5 ); //½«Êý¾Ý 5.0  Ð´ÈëÍ¨µÀ 5
            DataScope_Get_Channel_Data( 6.0 , 6 ); //½«Êý¾Ý 6.0  Ð´ÈëÍ¨µÀ 6
            DataScope_Get_Channel_Data( 7.0 , 7 ); //½«Êý¾Ý 7.0  Ð´ÈëÍ¨µÀ 7
            DataScope_Get_Channel_Data( 8.0 , 8 ); //½«Êý¾Ý 8.0  Ð´ÈëÍ¨µÀ 8
            DataScope_Get_Channel_Data( 9.0 , 9 ); //½«Êý¾Ý 9.0  Ð´ÈëÍ¨µÀ 9
            DataScope_Get_Channel_Data( 10.0 , 10); //½«Êý¾Ý 10.0 Ð´ÈëÍ¨µÀ 10
            */
            
            Send_Count = DataScope_Data_Generate(1); //Éú³É10¸öÍ¨µÀµÄ ¸ñÊ½»¯Ö¡Êý¾Ý£¬·µ»ØÖ¡Êý¾Ý³¤¶È
	
            for( i = 0 ; i < Send_Count; i++)  //Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
            {
                while((USART1->SR&0X40)==0);  
                USART1->DR = DataScope_OutPut_Buffer[i]; //´Ó´®¿Ú¶ªÒ»¸ö×Ö½ÚÊý¾Ý³öÈ¥      
            }

            
        }
		
		if (cnt1++ > 500)
		{
			cnt1 = 0;
			OLED_ShowNum(0, 32, Frequency1, 10, 12);
		}
    }
    TIM_ClearITPendingBit( TIM2, TIM_IT_Update );
}
