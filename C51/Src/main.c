#include<stdio.h>
#include<reg52.h>
#include<intrins.h>
#include<uart.h>
#include"DS18B20.h"
#include"delay.h"
#include"ADC0809.h"
#include"time.h"
#include"BH1750FVI.h"

#define uint unsigned int
#define uchar unsigned char

//����float�洢����
float temperature;
float smoke;
float light;

void main()
{
	uart_init();			//���ڳ�ʼ��
	Time_Init();			//��ʱ����ʼ��
	ADC_Init();				//ADC��ʼ��
	DS18B20_init();		//DS18B20��ʼ��
	while(1)
	{		
		temperature=temper_change();		//���ת����¶�����
		light = Get_BH1750_Data();			//��ù�ǿ����
		smoke=Get_AdcData();						//���ADCģ��ת��������ݣ��������ѹ
		printf("temperature = %6.2f,light = %6.2f,smoke = %6.2f\r\n",temperature,light,smoke);		//���ڷ���
		delay_us(1000);									//��ʱ
	}
}