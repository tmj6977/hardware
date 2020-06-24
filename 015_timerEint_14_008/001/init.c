#include "s3c2440_soc.h"

void sdram_init(void)
{
	BWSCON = 0x22000000;

	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;

	REFRESH = 0x8404f5;

	BANKSIZE = 0xb1;

	MRSRB6 = 0x20;
	MRSRB7 = 0x20;
}

int sdram_test()
{
		volatile unsigned char *p = (volatile unsigned char *)0x30000000;
		int i;

		//write sdram
		for(i = 0 ; i < 1000 ; i++)
		{
			p[i] = 0x55;	

		}

		//read sdram
		for(i = 0; i < 1000; i++)
		{
			if(p[i] != 0x55)
				return -1;

			
		}
		return 0;


}

void copy2sdram()
{

 	/*要从lds文件中获得 __code_start ,__bss_start
 	 *然后从0地址把地址复制到_code_start
 	 */
 	 extern int __code_start,__bss_start; 
 	 volatile unsigned int *dest =  (volatile unsigned int *) &__code_start;
	 volatile unsigned int *src =  (volatile unsigned int *) 0;
	 volatile unsigned int *end =  (volatile unsigned int *) &__bss_start;


		while(dest<end)
	{	
		*dest++ = *src++;
	}

}


void clean_bss( )
{
 	/*要从lds文件中获得 __bss_start ,_end
 	 */
 	 extern __bss_start,_end;
	
	 volatile unsigned int *start =( volatile unsigned int *)&__bss_start;
	 volatile unsigned int *end =( volatile unsigned int *)&_end;
	 

	while(start < end)
	{	
		*start++ = 0;
	}

}
