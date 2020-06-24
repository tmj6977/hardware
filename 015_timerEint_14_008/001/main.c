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

	led_init();
	interrupt_init();
	key_eint_init();
	timer_init();


	puts("\n\rg_A = ");
	printHex(g_A);
	puts("\n\r");
		

	while(1)
	{
#if 0
	puts("\n\rc_global = ");
	printHex(c_global);
	puts("\n\r");
		c_global++;

	puts("\n\rd_global = ");
	printHex(d_global);
	puts("\n\r");
		d_global++;
#endif

	putchar(c_global);
	c_global++;

	putchar(d_global);
	d_global++;
	

		delay(1000000);
	}
		
	


	return 0;
} 

