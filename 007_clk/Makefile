all:
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o uart_test.o uart_test.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-ld -Ttext 0x00000000 start.o uart_test.o main.o -o uart_test.elf
	arm-linux-objcopy -O binary -S uart_test.elf uart_test.bin
	arm-linux-objdump -D uart_test.elf > uart_test.dis
clean:
	rm *.bin *.o *.elf *.dis
