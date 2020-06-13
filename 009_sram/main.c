#include"s3c2440_soc.h"
#include"uart.h"
#include"init.h"

int main(void)
{
	unsigned char c;
	uart0_init();
	
	puts("Enter Tacc Val:\n\r");	
	
	

	while(1)
	{
		c =getchar();
		putchar(c);
		   
		if(c>='0'&&c<='7')
			{
				bank0_Tacc_set(c-'0');

				led_test();
				
			}	
		
	}

	return 0;
} 

