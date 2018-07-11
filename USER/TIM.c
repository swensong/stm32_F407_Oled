/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/


/*Include--------------------------------------*/
#include "TIM.h"
#include "usart.h"


/************************************************/
/*	函数名：TIM3_Init														*/
/*	描  述：定时器3初始化函数 									*/
/*	输  入：arr-----计数值											*/
/*					psc-----分频系数										*/
/*					CCR2_Val--设置占空比								*/
/*	输  出：无																	*/
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
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); //GPIOB?′
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
    TIM_OCInitStructure.TIM_Pulse = 6000;//设置占空比

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
    
    // 测量出来的值 900 向前， 1025左转， 775 右转
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
// 控制左侧电机
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
// 控制右侧电机
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

// 直线控制电机前转或者右转
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

/* TIM1 作为计数器 */
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

//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
    TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5

 
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//溢出
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获取当前的捕获值.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM5,DISABLE ); 	//关闭定时器5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

#endif
