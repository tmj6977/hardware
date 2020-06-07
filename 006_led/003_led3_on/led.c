#include "s3c24xx.h"



int main()
{
int val1,val2;




 //led f5 f6 f7为输入模式 01
 GPFCON &=~((3<<10)|(3<<12));
 GPFCON |= ((1<<8)|(1<<10)|(1<<12));

 GPFCON &=~((3<<0)|(3<<4));
 GPGCON &=~((3<<6));

while(1)
 	{
 	   val1=GPFDAT;
	   val2=GPGDAT;

	   /*************************************/    
 	   if(val1 & (1<<2))//s3(gpf2) ->gpf5
	   	{
      		//松开
      		GPFCON |=(1<<5);
			
        }
	   else
	   	{
	   		//按下
	   		GPFCON &= ~(1<<5);
	   	}
	   /*************************************/ 
	    if(val2 & (1<<3))//s4(gpg3) ->gpf4
	   	{
      		//松开
      		GPFCON |=(1<<4);
			
        }
	   else
	   	{
	   		//按下
	   		GPFCON &= ~(1<<4);
	   	}
	}
 
 

 return 0;
  
}


