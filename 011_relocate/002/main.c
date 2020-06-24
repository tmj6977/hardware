#include"s3c2440_soc.h"
#include"uart.h"
#include"init.h"

 char c = 'A';

int main(void)
{


	uart0_init();	

	while(1)
	{
		putchar(c);
		c++;
		delay(1000000);
	}
		
	


	return 0;
} 

