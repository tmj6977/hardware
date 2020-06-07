.text
.global _start
_start:
	//关闭看门狗
	ldr r0,=0x54000000
	ldr r1,=0x0
	str r1,[r0]

	
	/*设置内存:sp栈*/
	/*分辨是nor/nand启动
	 *写0到0地址，再读出来
	 *如果得到0，表示0地址上的内容被修改了，这就是nand启动
	 *否则就是nor启动
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
	
	/*调用main*/
	bl main

halt:
	b halt
