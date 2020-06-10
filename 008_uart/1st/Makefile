all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o uart_test.o uart_test.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0x00000000 start.o led.o uart_test.o main.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis
clean:
	rm *.bin *.o *.elf *.dis
