#include <neslib.h>

void  __fastcall__ func(void)
{
	write_fmtstr(1,6, "%i", &__ppu_str);
}
