#include<stdio.h>
#include"s3c2440_soc.h"

void uart_init()
{
    /*�����������ڴ���*/
	GPHCON &=~((3<<4)|(3<<6));//������
	GPHCON |= ((2<<4)|(2<<6));//����Ϊ����

	GPHUP  &= ~((1<<2)|(1<<3));//�ڲ�����

	/* ���ò�����*/
	//UBRDIVn  = (int)( UART clock / ( buad rate x 16) ) �C1 
	//UART clock =50Mhz  UBRDIVn= 50000000/(115200x16)-1 =26
	UCON0=0x00000005;
	UFCON0=0;
	UMCON0=0;
	UBRDIV0 = 26;

	/*�������ݸ�ʽ*/
	ULCON0 |=0x00000003;
	
}

int putchar(unsigned char c)
{
	//UTRSTAT0  UTXH0 
	while(!(UTRSTAT0&(1<<2)));//���Ĵ���Ϊ��ʱ
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

