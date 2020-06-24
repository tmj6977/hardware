.text
.global _start
_start:
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

	/*重定位data*/
	ldr r1, =data_load_adrr /*data段在bin文件中的地址，加载地址*/
	ldr r2, =data_start 	/*data段在重定位地址，运行时的地址*/
	ldr r3, =data_end		/*data段结束地址*/


cpy:
	ldrb r4, [r1]
	strb r4, [r2]
	add r1, r1, #1
	add r2, r2, #1
	cmp r2, r3
	bne cpy


	/*清除BSS,变量初始值为0,要清零*/
	ldr r1, =bss_start
	ldr r2, =bss_end
	mov r3,#0
clean:
	strb r3,[r1]
	add r1,r1,#1
	cmp r1, r2
	bne clean
	

	
	/*调用main*/
	bl main

halt:
	b halt
