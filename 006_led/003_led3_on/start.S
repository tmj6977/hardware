.text
.global _start
_start:
	//�رտ��Ź�
	ldr r0,=0x54000000
	ldr r1,=0x0
	str r1,[r0]

	
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