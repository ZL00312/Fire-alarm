#ifndef __BH1750FVI__
#define __BH1750FVI__


void BH1750_init();
void BH1750_Start();
void BH1750_Stop();
void BH1750_Write_Byte(unsigned char dat);
unsigned char BH1750_Read_Byte();
void Responds();
void No_Responds();
void Single_Write_BH1750(unsigned char reg_address);
void Multiple_Read_BH1750(void);
float Get_BH1750_Data();


#endif