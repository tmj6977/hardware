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

int putchar(int c)
{
 	/*UTRSTAT0*/
	/*UTXH0*/

	while(!(UTRSTAT0 & (1<<2))); 
	UTXH0 = (unsigned char)c;

}


int getchar(void)
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

/*0xABCDEF12*/
void printHex(unsigned int val)
{
	int i;
	unsigned char arr[8];

	/*��ȡ��ÿһλ��ֵ*/
	for (i = 0; i < 8; i++)
	{
		arr[i] = val & 0xf;
		val >>= 4;
	}

	/*��ӡ*/
	puts("0x");
	for(i = 7; i >= 0; i--)
	{
		if(arr[i] >= 0 && arr[i] <= 9)
			putchar(arr[i] + '0');

		else if(arr[i] >= 0xA && arr[i] <= 0XF)
			putchar(arr[i] - 0xA + 'A');


	}
	
}

void printf1()
{
	puts("1-------\n\r");

}



void printf2()
{
	puts("2-------\n\r");

}

