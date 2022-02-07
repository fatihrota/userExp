#include <stdio.h>
 

int addTest(int x1, int x2)
{
	return x1+x2;
} 
 
void add(void)
{
	int a = 3;
	int b = 5;
	int c = addTest(a,b);
	printf ( "Result : %d\n", c);
    puts("Hello, process shared library ");
}