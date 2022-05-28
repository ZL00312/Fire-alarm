/*
	这里建议不要直接借鉴
	虽然能运行，但个人建议最好阅读芯片或者器件的数据手册
	这样像遇到新的传感器或者器件，都可以快速上手
*/

#include"DS18B20.h"
#include"reg52.h"
#include"delay.h"
#include"uart.h"
#include"time.h"

sbit DQ=P2^2;  //定义数据线

//DS18B20初始化
bit DS18B20_init()
{	
	 bit dat=0;
	 DQ = 1;    		//DQ复位
	 delay_us(5);   //稍做延时
	 DQ = 0;         //单片机将DQ拉低
	 delay_us(200); //精确延时 大于 480us 小于960us
	 delay_us(200);
	 DQ = 1;        //拉高总线
	 delay_us(50);  //15~60us 后 接收60-240us的存在脉冲
	 dat=DQ;        //如果x=0则初始化成功, x=1则初始化失败
	 delay_us(25);  //稍作延时返回
	 return dat;
}

//写入一个字节
void write_byte(unsigned char dat)   //写一个字节
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

//读一个字节
unsigned char read_byte()    
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	 {
		DQ = 0; // 给脉冲信号
		dat>>=1;
		DQ = 1; // 给脉冲信号
		if(DQ)
		dat|=0x80;
		delay_us(25);
	 }
	 return(dat);

}

//读取温度（未转换后的）
//这里主要是看数据手册进行操作，按照正确的时序来读取数据
unsigned int read_temper ()
{
	unsigned char a=0;
	unsigned int b=0;
	unsigned int t=0;
	DS18B20_init();
	write_byte(0xCC); // 跳过读序号列号的操作
	write_byte(0x44); // 启动温度转换
	DelayMs(10);
	DS18B20_init();
	write_byte(0xCC); //跳过读序号列号的操作
	write_byte(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=read_byte();    //低位
	b=read_byte();    //高位
	b<<=8;
	t=a+b;	
	return(t);
}

//温度转换，并返回转换后的温度
float temper_change()
{
    float temper;
    float tp;
		EA=0; 								//关闭中断，因为ADC用到了定时器中断，若不关中断会影响DS18B20的时序，获得错误数据
    temper=read_temper();
		if(temper>61400)			//考虑负温度的情况
    {
			temper-=61400;
			tp=temper*0.0625;  	//16位温度转换成10进制的温度
			temper=tp*100+0.5;  //留两个小数点，并四舍五入
			temper*=-1;
    }
    else									//温度为正
    {
        tp=temper*0.0625; //16位温度转换成10进制的温度
    }
		EA=1; 								//打开中断
    return temper;
}
