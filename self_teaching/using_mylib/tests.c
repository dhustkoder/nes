#include "../libdev/include/neslib.h"

static const uint8_t* const words[] = 
{
	"KEY ", " PRESSED", "A", "B", "SELECT", 
	"START", "UP", "DOWN", "LEFT", "RIGHT"
};

enum Words
{
	WKey, WPressed, WA, WB, WSelect, WStart, 
	WUp, WDown, WLeft, WRight, WErase
};



void main(void)
{
	waitvblank();
	PPU_SET_COLOR_BACK(BLUE);
	PPU_SET_COLOR_TEXT(WHITE);
	ppu_set_cursor_exact(1,1);
	write_str("**HELLO CNESLIB!**");
	
	ppu_set_scroll_enable_render(0x0000);

	while(true)
	{
		/* hold until start is pressed */
		update_pad1();
		while(JOYPAD1 == KEY_NULL)
			update_pad1();

		waitvblank();
		ppu_set_cursor_exact(1,2);
		ppu_write_rval('\0', 22);  /* erase */
		ppu_set_cursor_exact(1,2);
		write_str(words[WKey]);    /* write KEY */
		
		switch(JOYPAD1)
		{
			case KEY_A:      write_str(words[WA]);      break;
			case KEY_B:      write_str(words[WB]);      break;
			case KEY_SELECT: write_str(words[WSelect]); break;
			case KEY_START:	 write_str(words[WStart]);  break;
			case KEY_UP:     write_str(words[WUp]);     break;
			case KEY_DOWN:   write_str(words[WDown]);   break;
			case KEY_LEFT:   write_str(words[WLeft]);   break;
			case KEY_RIGHT:  write_str(words[WRight]);  break;
			default:         write_str("UNDEFINED");    break;
		}
		
		write_str(words[WPressed]); /* write PRESSED */
		ppu_set_scroll_enable_render(0x0000);
		
	}
}
