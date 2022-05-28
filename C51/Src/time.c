#include<reg52.h>
#include"time.h"
#include <intrins.h>

sbit clk=P1^7;

//��ʱ����ʼ��
void Time_Init()
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


void NOP()
{
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
}

void Delay(unsigned int i)
{
		unsigned int j,k;
		for(j=i;j>0;j--)
		for(k=110;k>0;k--);
}


//�жϣ��ṩADC0809��ʱ��
void pick() interrupt 1
{
		TH0=0xff;
	  TL0=0xfe;
		clk=!clk;
}

