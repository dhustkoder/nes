#include <neslib.h>
#include <conio.h>
#include "../cc65/include/time.h"
extern void __fastcall__ func(void);

static unsigned char x, linex = 1;
static const char* strs[2] = { "A", "B" };
static unsigned char colors[] = {RED, GREEN, BLUE};

void main(void) 
{

	waitvblank(); 

	ppu_set_color_back(RED);
	ppu_set_color_text(BLUE);

	wait_keypress_pad1( 3 );

	write_fmtstr(1, 2, " %c ", *strs);		
	
	
	ppu_set_scroll(0, 0);
	poke(PPU_CTRL2, 8);

	

	while(1);
}
