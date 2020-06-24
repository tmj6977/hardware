#include "s3c2440_soc.h"


void timer_init()
{
	/*设置timer0的时钟*/
	/*Timer clk = PCLK/(prescaler value + 1) /(divider value)
				= 50000000/(99+1)/16
				=31250
	*/
	TCFG0 = 99;
	TCFG1 &= ~0xf;
	TCFG1 |= 3;
	
	/*设置初值*/
	TCNTB0 = 15625;
	

	/*加载初值，启动TIMER0*/
	TCON |=(1<<1);		//手工更新
	

	/*设置为自动加载，并启动*/
	TCON &=~(1<<1);
	TCON |= (1<<0)|(1<<3); //bit0 : start , bit3 : auto reload


	
	/*设置中断*/

}


void timer_irq()
{

	/*点灯*/

		static int cnt = 0;
		int tmp;

		cnt++;	

		tmp = ~cnt;
	    tmp &= 7;
		GPFDAT &= ~(7<<4);
		GPFDAT |= (tmp<<4);





}

