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

//���ڳ�ʼ��
void uart_init()
{
	TMOD=0x21;//���ö�ʱ��1�Ĺ�����ʽ2---8λ�Զ�װ��
	TH1=0xf3;//���ó�ʼֵ:ʹ������Ϊ2400
	TL1=0xf3;
	TH0=0xff;
	TL0=0xfe;
	PCON=0x00;//SMOD=0�����ӱ�
	TR1=1;//�򿪶�ʱ���жϿ���
	TR0=1;
	TF0 = 0;
	ET0 = 1;
	REN=1;//�������н���λ
	SM0=0;//���ô��п�ͨѶ��ʽΪ��ʽ1
	SM1=1;
	EA=1; //�����ж�
	ES=1; //�򿪴���ͨѶ�ж�

}