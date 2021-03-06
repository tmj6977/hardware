.text
.global _start
_start:
	b _reset  		  /*vector 0:reset 0x00000000*/
 	ldr pc, =und_addr /*vector 4:und   0x00000004*/


und_addr:
	.word do_und


do_und:
		/*sp_und未设置，先设置它*/
		ldr sp,=0x33f00000 //将栈设置在 sdram最高地址

		/*在und异常处理函数中可能会修改r0-r12，所以先保存*/
		stmdb sp!,{r0-r12,lr}


		/*保护现场*/
		
		/*处理und异常*/

		mrs r0,cpsr
		ldr r1, =und_string
		bl printException

		/*恢复现场*/
		ldmia  sp!,{r0-r12, pc}^ /*^会把spsr的值恢复到cpsr里*/

und_string:
		.string "undefined instruction exception"
		.align 4


_reset:
	//关闭看门狗
	ldr r0,=0x53000000
	ldr r1,=0
	str r1,[r0]

	//LOCKTIME (0x4C000000 )=0xFFFFFFFF 修改PLL时，锁定时间 fclk:hclk:pclk=400M:100M:50M	
	ldr r0,=0x4C000000
	ldr r1,=0xFFFFFFFF
	str r1,[r0]

	//CLKDIVN (0x4C000014 )=0x5 Tfclk:Thclk:Tpclk=1:4:8 
	ldr r0,=0x4C000014
	ldr r1,=0x5
	str r1,[r0]


	//设置CPU为异步模式，否则默认使用HCLK
	 mrc  p15,0,r0,c1,c0,0   
	 orr  r0,r0,#0xc0000000   //#R1_nF:OR:R1_iA   
	 mcr  p15,0,r0,c1,c0,0 

	/*MPLLCON(0x4C000004 ) 更改PLL，来进行cpu频率设置 
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
	/*一旦设置PLL，就会锁定lock time直到PLL输出稳定
	 *然后cpu工作于新的频率
	 */
 	
	
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
	 streq r0,[r1]

	bl sdram_init
	//bl sdram_init1 用到数组，不是位置无关码


	/*重定位text,rodata,data段整个程序*/

	bl copy2sdram /*src, dest ,len*/



	/*清除BSS,变量初始值为0,要清零*/
	
 	bl clean_bss /*start, end*/

	


	ldr pc, =sdram

sdram:
	bl uart0_init
	/*故意加入一条未定义指令*/
und_code:
	.word 0xe3000000


	
	/*调用main*/
	//bl main		/*使用BL命令相对跳转，程序仍然在NOR/sram执行*/
	
	ldr pc, =main /*绝对跳转*/

halt:
	b halt
