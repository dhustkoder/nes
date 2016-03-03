
/* 
 *	these are the memory addresses that we're going to need
 *	they correspond to PPU inside NES 
 */

#define PPU_VRAM_ADDR1  (*((uint8_t*)0x2005))   /* this PPU SCROLL , can be used for scroll the screen                  */
#define PPU_VRAM_ADDR2  (*((uint8_t*)0x2006))	/* this PPU ADR, can be use to set the cursor , x/y offset              */
#define PPU_VRAM_DATA   (*((uint8_t*)0x2007))	/* this PPU IO, can be used to write to the last addr puted in  PPU ADR */



extern void waitvblank(void);
typedef unsigned char uint8_t;
const unsigned char *str = "ABC";


void foo(void)
{
	/* we write the addrss 0x2000 in the ppu.vram.addr + 1 
	   the addr 0x2000 is the top left corner, like 0,0 in nowdays APIs */

	/* First we put the first byte in PPU ADR , then the last byte after */
	PPU_VRAM_ADDR2 = 0x20;
	PPU_VRAM_ADDR2 = 0x00;

	/* But the characters seems not to draw properly in 0,0 so lets try in 1,1 */
	/* lets define some x and y macros to demonstrate better */
	#define x 0x01
	#define y 0x01

	/* each row in the screen, is 32 bytes */
	/* so the Y must be multiplied by 32 */
	/* starting of 0x20 of course */
	

	PPU_VRAM_ADDR2 = 0x20 + (y >> 3); /* here, we take only the bit 7 of y and add to 0x20 */
	/* but y is only 1: 0x01 , so 0x20 stays 0x20  */
	/* 0x2000 in ppu.vram.addr + 1 now ...*/

	PPU_VRAM_ADDR2 = (y << 5) + x; /* now we're at other 8 bits of ppu.vram.addr
	then y must be multiplied by 32 and plus x which is 33 too */
	/* 0x2021 now at ppu.vram.addr + 1 */


	/* now we can write one byte at time to ppu.vram.data */
	/* and it will be written at 1,1 and increasing... 2, 1 ... 3, 1 .... */

	/* but before we write, lets set the color of text */

	/*now , to set the text color, we need again, first put the addr which corresponds to text color 
		into the PPU_VRAM_ADDR this time is not + 1 is the 0x2005 itself */

	/* the addr corresponding to text color is 0x3F03 */
	PPU_VRAM_ADDR1 = 0x3F;
	PPU_VRAM_ADDR1 = 0x03;

	/* now we set some color to PPU_VRAM_DATA */

	PPU_VRAM_DATA = 0x01; /* BLUE */

	/* ok now we can write  */

	PPU_VRAM_DATA = str[0];
	PPU_VRAM_DATA = str[1];
	PPU_VRAM_DATA = str[2];


}



void main(void)
{
	waitvblank();
	foo();


	/* these 2 instruction set the address where we are going to write our color code 
	 * the address is 2 bytes long, but we need to add 1 byte at time                
	 * the address is 0x3F03, which corresponds to background color */

	PPU_VRAM_ADDR2 = 0x3F; /* write byte 0x3F to ppu.vram.address */
	PPU_VRAM_ADDR2 = 0x00; /* write second byte 0x00 ... */

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
