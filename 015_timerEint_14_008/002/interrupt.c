#include"s3c2440_soc.h"

typedef void(*irq_func)(int);
irq_func irq_array[32];


void register_irq(int irq,irq_func func)
{

		irq_array[irq] = func;
		INTMSK &= ~(1<<irq);

}



void interrupt_init()
{
	/*srcpnd SRCPND(source pend)用来显示哪个中断产生了，需要清除对应位 
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23 读EINTPEND 进一步判断哪个寄存器
	 */

	/*mask来屏蔽中断 1-masked 0-使能中断
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	INTMSK &= ~((1<<0)|(1<<2)|(1<<5));
	;	/*TIMER 0 enble */


	/*INTPND来显示当前优先级最高，正在发生的中断，需要清除对应位
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */


	/*INTOFFSET 显示INTPND中哪个位设置为1
	 */
}


void key_eint_irq(int irq)
{

	unsigned int val = EINTPEND;

	unsigned int val1 = GPFDAT;
	unsigned int val2 = GPGDAT;
	

	if(irq == 0)		/*eint0	: s2*/
	{
	
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


		}
	else if(irq == 2)	/*eint2	: s3*/
	{
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


	}
	else if(irq == 5)	/*eint8_23, eint11 : s4 ,eint19 : s5*/
	{
		if(val & (1<<11))			/*eint11*/		
		 {

			 if(val2& (1<<3)) 		/*2*/
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
		else if(val & (1<<19))		/*eint19*/		
		{

			if(val2 & (1<<11))
			{
				/*松开，全部熄灭*/
				
				GPFDAT |= (1<<4)|(1<<5)|(1<<6);

			}
			else
			{
				/*按下:全部点亮*/
				GPFDAT &= ~((1<<4)|(1<<5)|(1<<6));


			}


		}
		

	}

	EINTPEND = val;

	
}

void handle_irq_c()
{
	/*分辨中断源*/
	int bit = INTOFFSET ;

	/*调用对应的处理函数*/

	irq_array[bit](bit);

	/*清中断*/
	SRCPND = (1<<bit);
	INTPND = (1<<bit);

}

/*按键中断源初始化*/
void key_eint_init()
{
 /*配置GPIO中断引脚*/
 GPFCON &= ~((3<<0)|(3<<4)); //清零
 GPFCON |=  ((2<<0)|(2<<4)); //设置为中断引脚

 GPGCON &= ~((3<<6)|(3<<22)); //清零
 GPGCON |=  ((2<<6)|(2<<22)); //设置为中断引脚
 
 /*配置中断控制寄存器，设置:双边沿触发*/

 EXTINT0 |= ((7<<0)|(7<<8));
 EXTINT1 |= (7<<12);
 EXTINT2 |= (7<<12);

 /*设置EINTMASK使能eint11,19 : eint0 、eint1 一直处于使能状态*/
  EINTMASK &= ~((1<<11)|(1<<19));
 
/*EINTPEND 分辨哪个EINT产生(EINT4~23)
*清除中断时，置EINTPEND的相应位 1
*/
register_irq(0,key_eint_irq);
register_irq(2,key_eint_irq);
register_irq(5,key_eint_irq);
}


