#include "userExp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void)
{
	int i=0;
	while (i<10)
	{
		puts("This is a shared library test...");
    	add();
    	sleep(1);
    	i++;
	}
    
    return 0;
}