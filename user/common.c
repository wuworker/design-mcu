#include "common.h"

void Delay_MS(u16 time)
{    
	 u16 i=0;
	 while(time--)
	 {
		i=14000;
		while(i--) ;    
	 }
}
