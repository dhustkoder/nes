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

	ready_controller:
		__asm__("LDA #$01");  // 01 into A reg
		__asm__("STA $4016"); // store A into controller port 1 
		__asm__("LDA #$00");  // then load 0 into A reg
		__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status

	for(x = 0; x < 8; ++x)
	{
		// verify the bit 0 into every button KEY_A to KEY_RIGHT; 8 buttons
		if( !(*amanda) ) goto pressed;
		
		else if( ( JOYPAD[0] & 0x01 ) != 0 && x == 3) 
		{
			write_fmtstr(linex++, 6, "%c ", *(amanda++)); // if pressed goto pressed label
			goto ready_controller;
		}
		
	}
		
	goto ready_controller; // if the code hits here, no button was pressed, the controller needs to be ready again

	pressed:
		ppu_set_scroll(0, 0);
		poke(PPU_CTRL2, 8);

	

	while(1);
}
