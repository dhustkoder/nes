#include <neslib.h>
#include <conio.h>
#include "../cc65/include/time.h"
extern void __fastcall__ func(void);

static unsigned char x, linex = 1;
static const char* amanda = "Te amo Amanda Sa!";
static unsigned char colors[] = {RED, GREEN, BLUE};

void main(void) 
{

	waitvblank(); 

	ppu_set_color_back(RED);
	ppu_set_color_text(BLUE);
	
	

	wait_key_press_pad1(3);
	write_str(5,4, amanda);


	ppu_set_scroll(0, 0);
	poke(PPU_CTRL2, 8);

	

	while(1);
}
