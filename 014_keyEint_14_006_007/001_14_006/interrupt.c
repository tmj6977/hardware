



void interrupt_init()
{
	/*srcpnd (source pend)用来显示哪个中断产生了，需要清除对应位 
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	/*mask来屏蔽中断 1-masked 0-使能中断
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	INTMSK &= ~((1<<0)|(1<<2)|(1<<5));


	/*INTPND来显示当前优先级最高，正在发生的中断，需要清除对应位
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */


	/*INTOFFSET 显示INTPND中哪个位设置为1
	 */
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

 /*设置EINTMASK使能eint11,19*/
  EINTMASK &= ~((1<<11)|(1<<19));
 

}

