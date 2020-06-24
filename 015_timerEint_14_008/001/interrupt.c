#include"s3c2440_soc.h"


void interrupt_init()
{
	/*srcpnd SRCPND(source pend)������ʾ�ĸ��жϲ����ˣ���Ҫ�����Ӧλ 
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23 ��EINTPEND ��һ���ж��ĸ��Ĵ���
	 */

	/*mask�������ж� 1-masked 0-ʹ���ж�
	 *bit0-eint0
	 *bit2-eint2
	 *bit5-eint8_23
	 */

	INTMSK &= ~((1<<0)|(1<<2)|(1<<5));
	INTMSK &= ~(1<<10);	/*TIMER 0 enble */


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

 /*����EINTMASKʹ��eint11,19 : eint0 ��eint1 һֱ����ʹ��״̬*/
  EINTMASK &= ~((1<<11)|(1<<19));
 
/*EINTPEND �ֱ��ĸ�EINT����(EINT4~23)
*����ж�ʱ����EINTPEND����Ӧλ 1
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
			/*�ɿ�*/
				GPFDAT |= (1<<6);
		}
	 	else
		{
			/*����*/
			GPFDAT &= ~(1<<6);
		}


		}
	else if(irq == 2)	/*eint2	: s3*/
	{
		if(val1 & (1<<2)) /*2*/
		{
			/*�ɿ�*/
			GPFDAT |= (1<<5);
		}
	 	else
		{
			/*����*/
			GPFDAT &= ~(1<<5);
		}


	}
	else if(irq == 5)	/*eint8_23, eint11 : s4 ,eint19 : s5*/
	{
		if(val & (1<<11))			/*eint11*/		
		 {

			 if(val2& (1<<3)) 		/*2*/
			{
				/*�ɿ�*/
				GPFDAT |= (1<<4);
			}
	 		else
			{
				/*����*/
				GPFDAT &= ~(1<<4);
			}


		}
		else if(val & (1<<19))		/*eint19*/		
		{

			if(val2 & (1<<11))
			{
				/*�ɿ���ȫ��Ϩ��*/
				
				GPFDAT |= (1<<4)|(1<<5)|(1<<6);

			}
			else
			{
				/*����:ȫ������*/
				GPFDAT &= ~((1<<4)|(1<<5)|(1<<6));


			}


		}
		

	}

	EINTPEND = val;

	
}

void handle_irq_c()
{
	/*�ֱ��ж�Դ*/
	int bit = INTOFFSET ;

	/*���ö�Ӧ�Ĵ�����*/
	if(bit == 0 | bit == 2 | bit == 5)
	{
		key_eint_irq(bit); //�����жϣ������ж�Դ EINTPEND����Դͷ��ʼ���ж�
	}
	else if(bit == 10)
	{
		timer_irq();
	

	}	

	/*���ж�*/
	SRCPND = (1<<bit);
	INTPND = (1<<bit);

}

