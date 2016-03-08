#include "../libdev/include/neslib.h"

static const uint8_t* const arr = "HELLO MY LIB!";

bool __fastcall__ test_case(uint8_t x)
{
	return x >= 11 ? true : false;
}


void main(void)
{
	waitvblank();
	PPU_SET_COLOR_BACK(BLUE);
	PPU_SET_COLOR_TEXT(WHITE);
	ppu_set_cursor_exact(1,1);
	write_str(arr);
	
	ppu_set_cursor_exact(1,2);
	

	if(test_case(11))
		write_str("MORE THAN 10");
	else
		write_str("LESS THAN 10");

	ppu_set_scroll_enable_render(0x0000);
	while(1);
}
