#include <conio.h>

unsigned char x;


#pragma optimize(push, off)

void LDA_0x4016(void)
{
	__asm__ ("LDA $4016");
};
#pragma optimize(pop)

void main(void)
{
	LDA_0x4016();
	x = 10;	
	cputc(x);
}

