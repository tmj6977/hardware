.text
.global _start
_start:
	//�رտ��Ź�
	ldr r0,=0x53000000
	ldr r1,=0
	str r1,[r0]

	//LOCKTIME (0x4C000000 )=0xFFFFFFFF �޸�PLLʱ������ʱ�� fclk:hclk:pclk=400M:100M:50M	
	ldr r0,=0x4C000000
	ldr r1,=0xFFFFFFFF
	str r1,[r0]

	//CLKDIVN (0x4C000014 )=0x5 Tfclk:Thclk:Tpclk=1:4:8 
	ldr r0,=0x4C000014
	ldr r1,=0x5
	str r1,[r0]


	//����CPUΪ�첽ģʽ������Ĭ��ʹ��HCLK
	 mrc  p15,0,r0,c1,c0,0   
	 orr  r0,r0,#0xc0000000   //#R1_nF:OR:R1_iA   
	 mcr  p15,0,r0,c1,c0,0 

	/*MPLLCON(0x4C000004 ) ����PLL��������cpuƵ������ 
	 m = (MDIV + 8), p = (PDIV + 2), s = SDIV    
	 m = (92 + 8)=100
	 p = (1 + 2)=3
	 s = 1 
	 0x4C000004|=(92<<12)|(2<<4)|(1<<0)
	 Mpll = (2 * m * Fin) / (p * 2^S) 
	*/
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]
	/*һ������PLL���ͻ�����lock timeֱ��PLL����ȶ�
	 *Ȼ��cpu�������µ�Ƶ��
	 */
 	
	
	/*�����ڴ�:spջ*/
	/*�ֱ���nor/nand����
	 *д0��0��ַ���ٶ�����
	 *����õ�0����ʾ0��ַ�ϵ����ݱ��޸��ˣ������nand����
	 *�������nor����
	 */

	 mov r1,#0
	 ldr r0,[r1]
	 str r1,[r1]
	 ldr r2,[r1]
	 cmp r1,r2
	 ldr sp,=0x40000000+4096
	 moveq sp,#4096
	 ldr sp, =4096            /*nand*/
	  streq r0,[r1]
	
	/*����main*/
	bl main

halt:
	b halt