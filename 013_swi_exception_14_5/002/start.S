.text
.global _start
_start:
	b _reset  		  /*vector 0:reset 0x00000000*/
 	ldr pc, und_addr /*vector 4:und   0x00000004*/
 	ldr pc, swi_addr /*vector 8:swi   0x00000008*/

und_addr:
	.word do_und

swi_addr:
	.word do_swi

do_und:
		/*sp_undδ���ã���������*/
		ldr sp,=0x34000000 //��ջ������ sdram��ߵ�ַ

		/*��und�쳣���������п��ܻ��޸�r0-r12�������ȱ���*/
		stmdb sp!,{r0-r12,lr}


		/*�����ֳ�*/
		
		/*����und�쳣*/

		mrs r0,cpsr
		ldr r1, =und_string
		bl printException

		/*�ָ��ֳ�*/
		ldmia  sp!,{r0-r12, pc}^ /*^���spsr��ֵ�ָ���cpsr��*/

und_string:
		.string "undefined instruction exception"
		.align 4
do_swi:

		/*sp_swiδ���ã���������*/
		ldr sp,=0x33e00000 //��ջ������ sdram��ߵ�ַ

		/*��swi�쳣���������п��ܻ��޸�r0-r12�������ȱ���*/
		stmdb sp!,{r0-r12,lr}

		mov r4,lr
		

		/*�����ֳ�*/
		
		/*����swi�쳣*/

		mrs r0,cpsr
		ldr r1, =swi_string
		bl printException

		sub r0,r4,#4
		bl printSWIval

		/*�ָ��ֳ�*/
		ldmia  sp!,{r0-r12, pc}^ /*^���spsr��ֵ�ָ���cpsr��*/

swi_string:
		.string "swi exception"
		.align 4

_reset:
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
	 streq r0,[r1]

	bl sdram_init
	//bl sdram_init1 �õ����飬����λ���޹���


	/*�ض�λtext,rodata,data����������*/

	bl copy2sdram /*src, dest ,len*/



	/*���BSS,������ʼֵΪ0,Ҫ����*/
	
 	bl clean_bss /*start, end*/

	/*��λ֮��cpu����svcģʽ
	 *���ڣ��л���userģʽ
	 */

		mrs r0,cpsr
		bic r0,r0,#0xf //�޸�M4-M0Ϊ0b10000,����userģʽ 	BLC R0,R0,#0x000f��ʾ R0�ĵ�4λ����(R0 = R0 & (~0x000f))
		msr cpsr,r0

	/*����userģʽ��sp*/
		ldr sp,=0x33f00000

	
	ldr pc, =sdram

sdram:
	bl uart0_init
	/*�������һ��δ����ָ��*/
und_code:
	.word 0xdeadc0de 


	swi 0x123
	
	/*����main*/
	//bl main		/*ʹ��BL���������ת��������Ȼ��NOR/sramִ��*/
	bl printf2
	
	ldr pc, =main /*������ת*/

halt:
	b halt