#include "../libdev/include/neslib.h"


static const unsigned char arr[] = {1, '\0'};


void put_string(void) {
	write_str((uint8_t*)arr);
}



static unsigned char x = 0;
static unsigned char y = 0;

void main(void)
{
	x = 30;
	y = 28;
	waitvblank();
	PPU_SET_COLOR_BACK(BLUE);
	PPU_SET_COLOR_TEXT(WHITE);
	
	ppu_set_cursor_calc(x, y);
	put_string();
	ppu_set_scroll_enable_render(0x0000);
	while(1);
}