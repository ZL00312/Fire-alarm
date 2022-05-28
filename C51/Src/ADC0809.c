#include"ADC0809.h"
#include<reg52.h>
#include"delay.h"
#include"uart.h"

sbit ADDA=P1^0;			   // ��ַA
sbit ADDB=P1^1;			   //	��ַB
sbit ADDC=P1^2;			   //	��ַC
sbit START_ALE=P1^4;	 //	��ַװ�أ�ת��������
sbit OE=P1^5;			     //	���ʹ��
sbit EOC=P1^6;			   //	ת����־λ

//ADC��ʼ��
void ADC_Init()
{
   ADDA=0;
   ADDB=0;
   ADDC=0;
   START_ALE=0;
}


//ADCת����ʼ����
void ADC_START()		  
{
	START_ALE=0;
	delay_us(2);
	START_ALE=1;				  //һ��������
	delay_us(20);
	START_ALE=0;
	while(EOC==0);
	OE=1;
}

//���ģ��ת���������
float Get_AdcData()
{
	unsigned int ADC_Data;
	 float temp;
   ADC_START();
   ADC_Data=P0;	
	 OE=0;
	 temp = (float)ADC_Data/51*1.0;
	 return temp;	 
}