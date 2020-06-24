



void interrupt_init()
{
	/*srcpnd (source pend)������ʾ�ĸ��жϲ����ˣ���Ҫ�����Ӧλ 
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	/*mask�������ж� 1-masked 0-ʹ���ж�
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	INTMSK &= ~((1<<0)|(1<<2)|(1<<5));


	/*INTPND����ʾ��ǰ���ȼ���ߣ����ڷ������жϣ���Ҫ�����Ӧλ
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */


	/*INTOFFSET ��ʾINTPND���ĸ�λ����Ϊ1
	 */
}

/*�����ж�Դ��ʼ��*/
void key_eint_init()
{
 /*����GPIO�ж�����*/
 GPFCON &= ~((3<<0)|(3<<4)); //����
 GPFCON |=  ((2<<0)|(2<<4)); //����Ϊ�ж�����

 GPGCON &= ~((3<<6)|(3<<22)); //����
 GPGCON |=  ((2<<6)|(2<<22)); //����Ϊ�ж�����
 
 /*�����жϿ��ƼĴ���������:˫���ش���*/

 EXTINT0 |= ((7<<0)|(7<<8));
 EXTINT1 |= (7<<12);
 EXTINT2 |= (7<<12);

 /*����EINTMASKʹ��eint11,19*/
  EINTMASK &= ~((1<<11)|(1<<19));
 

}

