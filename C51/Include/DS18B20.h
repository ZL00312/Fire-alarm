#ifndef __DS18B20__
#define __DS18B20__


#define uchar unsigned char
#define uint   unsigned int

bit DS18B20_init();
void write_byte(unsigned char dat); 
unsigned char read_byte();    		
unsigned int read_temper();
float temper_change();


#endif

