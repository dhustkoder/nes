
/* 
 *	these are the memory addresses that we're going to need
 *	they correspond to PPU inside NES 
 */

#define PPU_VRAM_SCROLL (*((uint8_t*)0x2005))   /* this PPU SCROLL , can be used for scroll the screen                  */
#define PPU_VRAM_ADDR   (*((uint8_t*)0x2006))	/* this PPU ADDR, can be use to set the cursor , x/y offset              */
#define PPU_VRAM_DATA   (*((uint8_t*)0x2007))	/* this PPU IO, can be used to write to the last addr puted in  PPU ADR */


extern void waitvblank(void);
typedef unsigned char uint8_t;
static const unsigned char str[] = { 'A' , 'B', 'C' }; // using static const  arrays produce better code than const pointers to "ABC"

void foo(void)
{
	// Sadly cc65 does not generate good assembly for the nes.
	// somethings we're better of doing manualy, or even written all in assembly.

	//PPU_VRAM_ADDR = 0x20;
	//PPU_VRAM_ADDR = 0x00;

	// lets replace the above for.

	__asm__("LDA #$20");
	__asm__("LDX #$00");
	__asm__("STA $2006");
	__asm__("STX $2006");


	#define x 0x01
	#define y 0x01


	//PPU_VRAM_ADDR = 0x3F;
	//PPU_VRAM_ADDR = 0x03;

	__asm__("LDA #$3F");
	__asm__("LDX #$03");
	__asm__("STA $2006");
	__asm__("STX $2006");



	//PPU_VRAM_DATA = 0x20; /* WHITE */
	__asm__("LDA #$20");
	__asm__("STA $2007");


	
	// calculate the x, y at compile time if x, y are compile time constant
	PPU_VRAM_ADDR = 0x20;
	PPU_VRAM_ADDR = 0x21;


	PPU_VRAM_DATA = str[0];
	PPU_VRAM_DATA = str[1];
	PPU_VRAM_DATA = str[2];
	
	return;
}



void main(void)
{
	waitvblank();

	/* these 2 instruction set the address where we are going to write our color code 
	 * the address is 2 bytes long, but we need to add 1 byte at time                
	 * the address is 0x3F03, which corresponds to background color */

	PPU_VRAM_ADDR = 0x3F; /* write byte 0x3F to ppu.vram.address */
	PPU_VRAM_ADDR = 0x00; /* write second byte 0x00 ... */

	/* then we can set the background color in ppu.vram.data */
	PPU_VRAM_DATA = 0x03; /* write the purple color to the background */


	/* now lets call our draw function */
	foo();

	/* now we need to enable the screen 
	   first we set the scroll */
	*(uint8_t*)0x2005 = 0x00; /* x */
	*(uint8_t*)0x2005 = 0x00; /* y */

	/* now we enable the bit 7 in PPU MASK to enable the screen on */
	*(uint8_t*)0x2001 = 0x08;
	while(1);

}
