#include"s3c2440_soc.h"

void uart0_init()
{
    /*�����������ڴ���*/
	GPHCON &= ~((3<<4) | (3<<6));
	GPHCON |= ((2<<4) | (2<<6));

	GPHUP &= ~((1<<2) | (1<<3));

	/* ���ò�����*/
	/*UBRDIVn  = (int)( UART clock / ( buad rate x 16) ) �C1
    *UART clock = 50m
    *UBRDIVn  = (int)(50000000/ ( 115200 x 16)-1 =26
	*/

	UCON0 = 0x00000005; /*PCLK,�ж�ģʽ����ѯģʽ*/
	UBRDIV0 = 26;


	/*�������ݸ�ʽ*/
	ULCON0 = 0x00000003;/*8n1:8������λ��û��У��λ��һ��ֹͣλ*/
	
	
}


void putchar(unsigned char c)
{
 	/*UTRSTAT0*/
	/*UTXH0*/

	while(!(UTRSTAT0 & (1<<2))); 
	UTXH0 = c;

}


unsigned char getchar(void )
{
	/*URXH0 */
	while(!(UTRSTAT0 & (1<<0))); 
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

