#include "usart.h"

#define RESERVE_MAX     1024*50

u8 flag_frame = 0;    /* 接收字节完成标志位 */
u8 cnt_rxd = 0;       /* 接收字节计数器，用于记录接收到的数据 */
u8 buf_rxd[256];      /* 接受字节缓冲区 */


void USART1_Config(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

    //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
    USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

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

    cnt_rxd = 0;  /* 清零接收的计数位 */

    return len;   /* 返回实际接收到的长度 */
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

