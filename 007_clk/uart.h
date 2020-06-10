#ifndef _UART_H
#define _UART_H
 
void uart_init();
int putchar(unsigned char c);
unsigned char getchar(void);
int puts(const char *s);

#endif