#include "../libdev/include/neslib.h"



void main(void)
{

	waitvblank();
	ppu_set_color_back(BLUE);
	ppu_set_color_text(WHITE);
	
	ppu_set_cursor_cpltime(1,1);
	write_str("HELLO MYLIB!");
	ppu_set_scroll_enable_render(0x0000);
	while(1);
}