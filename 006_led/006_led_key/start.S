.text
.global _start

_start:
	/*关闭看门狗*/
	ldr r0,=0x5300000
	ldr r1,=0
	str r1,[r0]
	
	/*设置内存: SP 栈 */
	/*分辨是nor/nand启动
	 *写0到0地址，再读出来
	 *如果得到0，表示0地址上的内容被修改了，它对应ram，这就是nand启动
	 *否则就是nor启动
	 */
	 mov r1,#0
	 ldr r0,[r1]
	 str r1,[r1]
	 ldr r2,[r1]
	 cmp r1,r2
	 ldr sp,=0x40000000+4096
	 moveq sp,#4096
     streq r0,[r1]
	


	 bl main

halt:
	b halt

