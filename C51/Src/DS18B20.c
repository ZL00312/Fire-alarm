/*
	���ｨ�鲻Ҫֱ�ӽ��
	��Ȼ�����У������˽�������Ķ�оƬ���������������ֲ�
	�����������µĴ��������������������Կ�������
*/

#include"DS18B20.h"
#include"reg52.h"
#include"delay.h"
#include"uart.h"
#include"time.h"

sbit DQ=P2^2;  //����������

//DS18B20��ʼ��
bit DS18B20_init()
{	
	 bit dat=0;
	 DQ = 1;    		//DQ��λ
	 delay_us(5);   //������ʱ
	 DQ = 0;         //��Ƭ����DQ����
	 delay_us(200); //��ȷ��ʱ ���� 480us С��960us
	 delay_us(200);
	 DQ = 1;        //��������
	 delay_us(50);  //15~60us �� ����60-240us�Ĵ�������
	 dat=DQ;        //���x=0���ʼ���ɹ�, x=1���ʼ��ʧ��
	 delay_us(25);  //������ʱ����
	 return dat;
}

//д��һ���ֽ�
void write_byte(unsigned char dat)   //дһ���ֽ�
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  delay_us(25);
  DQ = 1;
  dat>>=1;
 }
	delay_us(25);
}

//��һ���ֽ�
unsigned char read_byte()    
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	 {
		DQ = 0; // �������ź�
		dat>>=1;
		DQ = 1; // �������ź�
		if(DQ)
		dat|=0x80;
		delay_us(25);
	 }
	 return(dat);

}

//��ȡ�¶ȣ�δת����ģ�
//������Ҫ�ǿ������ֲ���в�����������ȷ��ʱ������ȡ����
unsigned int read_temper ()
{
	unsigned char a=0;
	unsigned int b=0;
	unsigned int t=0;
	DS18B20_init();
	write_byte(0xCC); // ����������кŵĲ���
	write_byte(0x44); // �����¶�ת��
	DelayMs(10);
	DS18B20_init();
	write_byte(0xCC); //����������кŵĲ���
	write_byte(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	a=read_byte();    //��λ
	b=read_byte();    //��λ
	b<<=8;
	t=a+b;	
	return(t);
}

//�¶�ת����������ת������¶�
float temper_change()
{
    float temper;
    float tp;
		EA=0; 								//�ر��жϣ���ΪADC�õ��˶�ʱ���жϣ��������жϻ�Ӱ��DS18B20��ʱ�򣬻�ô�������
    temper=read_temper();
		if(temper>61400)			//���Ǹ��¶ȵ����
    {
			temper-=61400;
			tp=temper*0.0625;  	//16λ�¶�ת����10���Ƶ��¶�
			temper=tp*100+0.5;  //������С���㣬����������
			temper*=-1;
    }
    else									//�¶�Ϊ��
    {
        tp=temper*0.0625; //16λ�¶�ת����10���Ƶ��¶�
    }
		EA=1; 								//���ж�
    return temper;
}
