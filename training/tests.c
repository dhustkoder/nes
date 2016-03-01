#include <neslib.h>
#include <conio.h>

extern void __fastcall__ func(void);

static unsigned char x;
static const char* dhust = "DhustKoder!";

static unsigned char colors[] = {RED, GREEN, BLUE};


void main(void) 
{

	

 	   /* We have to wait for VBLANK or we can't even use the PPU */
    waitvblank(); /* This is found in nes.h */

    /* Now set basic colours which we'll use for foreground and background.
     * This is based on the NES palette:
     * http://en.wikipedia.org/wiki/List_of_video_game_console_palettes#NES */
    /* Set the background color (0x11 => medium blue): */
    ppu_set_color_back(LBROWN);
    /* Set the text colour: */
    /* Then, we need to set the text color (0x10 => light grey): */
    ppu_set_color_text(BLUE);


    
    /* Reset the screen scroll position: */
    func();
    ppu_set_scroll(0, 0);
	poke(PPU_CTRL2, 8);

	while(1);
}