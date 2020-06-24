#include "uart.h"


void printException(unsigned int cpsr ,char *str)
{
	puts("Excetion! cpsr=");
	printHex(cpsr);
	puts("\n\r");
	puts(str);
	puts("\n\r");


}


void printSWIval(unsigned int *pSWI)
{

    puts("SWI val = ");
	printHex(*pSWI );
	puts("\n\r");
	

}


