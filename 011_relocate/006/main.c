#include"s3c2440_soc.h"
#include"uart.h"
#include"init.h"

 char c_global = 'A';
 char d_global = 'a';

 const char b_global = 'B';
 int g_A = 0;
 int g_B ;

int main(void)
{


	uart0_init();	

	while(1)
	{
		putchar(c_global);
		c_global++;

		putchar(d_global);
		d_global++;

		delay(1000000);
	}
		
	


	return 0;
} 

