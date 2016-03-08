#include "../libdev/include/neslib.h"

static const uint8_t* const arr = "HELLO MY LIB!";


bool test_case(const uint8_t x)
{
	if(x == 10) {
		
		return true;
	}
	
	return false;
}

void main(void)
{
	waitvblank();
	PPU_SET_COLOR_BACK(BLUE);
	PPU_SET_COLOR_TEXT(WHITE);
	ppu_set_cursor_exact(1,1);
	write_str(arr);
	
	ppu_set_cursor_exact(1,2);
	

	if(test_case(10) == true) { write_str("EQUAL TO 10"); }

	else if(test_case(10) == false) { write_str("NOT EQUAL TO 10"); } 


	ppu_set_scroll_enable_render(0x0000);
	while(1);
}
