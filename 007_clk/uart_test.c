#include<stdio.h>
#include"s3c2440_soc.h"

void uart_init()
{
    /*设置引脚用于串口*/
	GPHCON &=~((3<<4)|(3<<6));//先清零
	GPHCON |= ((2<<4)|(2<<6));//设置为串口

	GPHUP  &= ~((1<<2)|(1<<3));//内部上拉

	/* 设置波特率*/
	//UBRDIVn  = (int)( UART clock / ( buad rate x 16) ) –1 
	//UART clock =50Mhz  UBRDIVn= 50000000/(115200x16)-1 =26
	UCON0=0x00000005;
	UFCON0=0;
	UMCON0=0;
	UBRDIV0 = 26;

	/*设置数据格式*/
	ULCON0 |=0x00000003;
	
}

int putchar(unsigned char c)
{
	//UTRSTAT0  UTXH0 
	while(!(UTRSTAT0&(1<<2)));//当寄存器为空时
	UTXH0 = c;
}

unsigned char getchar(void)
{
	//UTRSTAT0  
	while(!(UTRSTAT0&(1<<0)));

	return URXH0;
}

int puts(const char *s)
{
	while(*s)
	{
	putchar(*s);
		s++;
	}

}

