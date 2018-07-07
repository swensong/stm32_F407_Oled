/************************************************
	 名    称：定时器驱动 
	 
	 修改日期：2018/6/1
************************************************/


/*Include--------------------------------------*/
#include "TIM.h"


/************************************************/
/*	函数名：TIM3_Init														*/
/*	描  述：定时器3初始化函数 									*/
/*	输  入：arr-----计数值											*/
/*					psc-----分频系数										*/
/*					CCR2_Val--设置占空比								*/
/*	输  出：无																	*/
/************************************************/

void TIM3_Init(u16 arr, u16 psc, u16 CCR1_Val, u16 CCR2_Val)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO时钟
	 
 
    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.7
    //这个函数每次只能对应初始化一个IO口
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6 ,GPIO_AF_TIM3); //GPIOA7复用为定时器3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7 ,GPIO_AF_TIM3); //GPIOA7复用为定时器3
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8 ,GPIO_AF_TIM3); //GPIOA7复用为定时器3
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_TIM3); //GPIOA7复用为定时器3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;           //GPIOA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA7
 
    
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc - 1; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel1 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//设置占空比
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1

    TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );  //使能TIM3在CCR1上的预装载寄存器
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;//设置占空比
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器

	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}
