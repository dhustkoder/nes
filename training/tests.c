#include <neslib.h>
#include <conio.h>
#include "../cc65/include/time.h"
extern void __fastcall__ func(void);

static unsigned char x, linex = 1;
static const char* strs[2] = { "Striter Alfa!", "Striter Vegeta!" };
static unsigned char colors[] = {RED, GREEN, BLUE};

void main(void) 
{

	waitvblank(); 

	ppu_set_color_back(RED);
	ppu_set_color_text(BLUE);
	
	while(1)
	{ 	
		if( iskey_pressed_pad1(0) ) // A
		{
			write_str(1, 2, strs[0]);
			break;
		}
		
		if( iskey_pressed_pad1(1) ) // B
		{
			write_str(1, 2, strs[1] );
			break;
		}

	}


	ppu_set_scroll(0, 0);
	poke(PPU_CTRL2, 8);

	

	while(1);
}
