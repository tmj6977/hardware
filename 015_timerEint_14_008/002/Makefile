all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o init.o init.c
	arm-linux-gcc -c -o timer.o timer.c
	arm-linux-gcc -c -o uart_test.o uart_test.c
	arm-linux-gcc -c -o interrupt.o interrupt.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o exception.o exception.c
	arm-linux-ld -T sdram.lds start.o led.o uart_test.o init.o timer.o exception.o interrupt.o main.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis
clean:
	rm *.bin *.o *.elf *.dis
