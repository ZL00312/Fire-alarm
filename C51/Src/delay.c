#include"reg52.h"
#include"delay.h"

void delay_us(unsigned char n)    
{
    while(n--);
}

void DelayMs(unsigned char t)
{     
 while(t--)
 {
     //¥Û÷¬—” ±1mS
     delay_us(245);
	   delay_us(245);
 }
}