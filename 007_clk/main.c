#include"s3c24xx.h"
#include"uart.h"

int main()
{
	unsigned char c;
	uart_init();
	
	puts("hello,world!\n");

	while(1)
	{
		c =getchar();
		putchar(c);
		
		
	}

	return 0;
} 