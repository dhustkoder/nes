#include "../libdev/include/neslib.h"





void put_string(void) {
	write_str("HELLO MYLIB!");
}



static unsigned char x = 1;
static unsigned char y = 1;

void main(void)
{
	waitvblank();
	ppu_set_color_back(BLUE);
	ppu_set_color_text(WHITE);
	
	ppu_set_cursor_runtime(x,y);
	put_string();
	ppu_set_scroll_enable_render(0x00FF);
	while(1);
}