#include "s3c2440_soc.h"

void bank0_Tacc_set(int val)
{
	BANKCON0 = val << 8;
}
	
