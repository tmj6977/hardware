#include "s3c24xx.h"

void delay(volatile int d)
{
	
	while(d--);

}


int main(void)
{

	int val1,val2 ;
	
	
	
	/*设置GPFCON让GPF4/5/6配置为输出引脚*/
	GPFCON &= ~((3<<8)|(3<<10)|(3<<12));
	GPFCON |=  ((1<<8)|(1<<10)|(1<<12));

	/*配置3个按键引脚输入
	 *GPF0(S2),GPF2(S3),GPG3(S4)
	 */
	GPFCON &=~((3<<0)|(3<<4));
	GPGCON &=~(3<<6);

	/*循环点亮*/
	while(1)
	{
		val1 = GPFDAT;
		val2 = GPGDAT;

		if(val1 & (1<<0)) /*2*/
		{
			/*松开*/
				GPFDAT |= (1<<6);
		}
	 	else
		{
			/*按下*/
			GPFDAT &= ~(1<<6);
		}

		if(val1 & (1<<2)) /*2*/
		{
			/*松开*/
			GPFDAT |= (1<<5);
		}
	 	else
		{
			/*按下*/
			GPFDAT &= ~(1<<5);
		}

		if(val2& (1<<3)) /*2*/
		{
			/*松开*/
				GPFDAT |= (1<<4);
		}
	 	else
		{
			/*按下*/
			GPFDAT &= ~(1<<4);
		}
		
	}

	return 0;
}

