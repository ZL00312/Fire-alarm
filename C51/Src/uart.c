#include"uart.h"
#include"reg52.h"

char putchar (char c)   
{        
    ES=0;        
    SBUF = c;        
    while(TI==0);        
    TI=0;        
    ES=1;        
    return 0;
}

//串口初始化
void uart_init()
{
	TMOD=0x21;//设置定时器1的工作方式2---8位自动装填
	TH1=0xf3;//设置初始值:使比特率为2400
	TL1=0xf3;
	TH0=0xff;
	TL0=0xfe;
	PCON=0x00;//SMOD=0，不加倍
	TR1=1;//打开定时器中断开关
	TR0=1;
	TF0 = 0;
	ET0 = 1;
	REN=1;//打开允许串行接收位
	SM0=0;//设置串行口通讯方式为方式1
	SM1=1;
	EA=1; //打开总中断
	ES=1; //打开串口通讯中断

}