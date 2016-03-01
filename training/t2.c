
extern void write_string(unsigned char, unsigned char, char*);

void  __fastcall__ func(void)
{
	write_string(1,1, "From t2.c func");
}