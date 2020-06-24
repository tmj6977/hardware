#include "s3c2440_soc.h"


void timer_init()
{
	/*����timer0��ʱ��*/
	/*Timer clk = PCLK/(prescaler value + 1) /(divider value)
				= 50000000/(99+1)/16
				=31250
	*/
	TCFG0 = 99;
	TCFG1 &= ~0xf;
	TCFG1 |= 3;
	
	/*���ó�ֵ*/
	TCNTB0 = 15625;
	

	/*���س�ֵ������TIMER0*/
	TCON |=(1<<1);		//�ֹ�����
	

	/*����Ϊ�Զ����أ�������*/
	TCON &=~(1<<1);
	TCON |= (1<<0)|(1<<3); //bit0 : start , bit3 : auto reload


	
	/*�����ж�*/

}


void timer_irq()
{

	/*���*/

		static int cnt = 0;
		int tmp;

		cnt++;	

		tmp = ~cnt;
	    tmp &= 7;
		GPFDAT &= ~(7<<4);
		GPFDAT |= (tmp<<4);





}

