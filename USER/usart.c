#include "usart.h"

#define RESERVE_MAX     1024*50

u8 flag_frame = 0;    /* æŽ¥æ”¶å­—èŠ‚å®Œæˆæ ‡å¿—ä½ */
u8 cnt_rxd = 0;       /* æŽ¥æ”¶å­—èŠ‚è®¡æ•°å™¨ï¼Œç”¨äºŽè®°å½•æŽ¥æ”¶åˆ°çš„æ•°æ® */
u8 buf_rxd[256];      /* æŽ¥å—å­—èŠ‚ç¼“å†²åŒº */


void USART1_Config(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //Ê¹ÄÜGPIOAÊ±ÖÓ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//Ê¹ÄÜUSART1Ê±ÖÓ
 
	//´®¿Ú1¶ÔÓ¦Òý½Å¸´ÓÃÓ³Éä
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9¸´ÓÃÎªUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10¸´ÓÃÎªUSART1
	
	//USART1¶Ë¿ÚÅäÖÃ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9ÓëGPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//ËÙ¶È50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure); //³õÊ¼»¯PA9£¬PA10

    //USART1 ³õÊ¼»¯ÉèÖÃ
	USART_InitStructure.USART_BaudRate = bound;//²¨ÌØÂÊÉèÖÃ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½
    USART_Init(USART1, &USART_InitStructure); //³õÊ¼»¯´®¿Ú1
	
    USART_Cmd(USART1, ENABLE);  //Ê¹ÄÜ´®¿Ú1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//¿ªÆôÏà¹ØÖÐ¶Ï

	//Usart1 NVIC ÅäÖÃ
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//´®¿Ú1ÖÐ¶ÏÍ¨µÀ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷¡¢

}

void USART1_Driver(void)
{
    u8 len = 0;
    u8 buf[40];

    if (flag_frame)
    {
        flag_frame = 0;
        len = USART1_Read_String( buf, sizeof(buf) );
        USART1_Action( buf, len );
    }
}

void USART1_Write_String( u8 *buf, u8 len )
{
    while ( len-- )
    {
        USART_SendData( USART1, *buf++ );
        while ( !USART_GetFlagStatus( USART1, USART_FLAG_TXE ) );
    }
}

u8 USART1_Read_String( u8 *buf, u8 len )
{
    u8 i = 0;

    if ( len > cnt_rxd )
    {
        len = cnt_rxd;
    }
    for ( i = 0; i < len; i++ )
    {
        *buf++ = buf_rxd[i];
    }

    cnt_rxd = 0;  /* æ¸…é›¶æŽ¥æ”¶çš„è®¡æ•°ä½ */

    return len;   /* è¿”å›žå®žé™…æŽ¥æ”¶åˆ°çš„é•¿åº¦ */
}

void USART1_Rx_Monitor(u16 ms)
{
    static u16 cnt_bkp = 0;
    static u16 idle_tmr = 0;

    if ( cnt_rxd > 0 )
    {
        if ( cnt_bkp != cnt_rxd )
        {
            cnt_bkp = cnt_rxd;
            idle_tmr = 0;
        }
        else
        {
            if ( idle_tmr < 300 )
            {
                idle_tmr += ms;
                if (idle_tmr >= 300)
                {
                    flag_frame = 1;				
                }
            }
        }
    }
    else
    {
        cnt_bkp = 0;
    }
}

u8 Cmp_Memory( u8 *ptr1, u8 *ptr2, u8 len )
{
    while (len--)
    {
        if ( *ptr1++ != *ptr2++ )
        {
            return 0;
        }
    }

    return 1;
}

void USART1_Action( u8 *buf, u8 len )
{
    u8 i = 0;
//    u8 j = 0;

//    u16 data_buf = 0;
    u8 cmd0[] = "11";
    u8 cmd1[] = "22";
    u8 cmd2[] = "AT-=";
    u8 cmd3[] = "AT+=";
//    u8 send_buf[ 20 ];

    u8 cmd_len[] = {
        sizeof(cmd0) - 1, sizeof(cmd1) - 1,  sizeof(cmd2) - 1, sizeof(cmd3) - 1,
    };
    u8 *cmd_ptr[] = {
        &cmd0[0], &cmd1[0], &cmd2[0], &cmd3[0],
    };

    /*
    for ( i = 4, j = 0; i < len; i++, j++ )
    {
        send_buf[j] = *(buf + i);
    }

	USART1_Write_String( "\r\n" , 2 );
    USART1_Write_String( send_buf, 2 );
    USART1_Write_String( "\r\n" , sizeof("\r\n") );
	
	data_buf = (send_buf[0]) + (send_buf[1] * 256);
    */

    for ( i = 0; i < sizeof(cmd_len); i++ )
    {
        if (len >= cmd_len[i] )
        {
            if ( Cmp_Memory( buf, cmd_ptr[i], cmd_len[i] ) )
            {
                break;
            }
        }
    }

    switch(i)
    {
    case 0:
        USART1_Write_String( "11\r\n" , 4 );
        break;
    case 1:
        USART1_Write_String( "22\r\n" , 4 );
        break;
    case 2:
        USART1_Write_String( "AT-=\r\n" , 6 );
        break;
    case 3:
        USART1_Write_String( "AT+=\r\n" , 6 );
        break;
    default:
        break;
    }
}

void USART1_IRQHandler()
{
    if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )
    {
        USART_ClearITPendingBit( USART1, USART_IT_RXNE );
        buf_rxd[cnt_rxd++] = USART_ReceiveData( USART1 );
    }
}

