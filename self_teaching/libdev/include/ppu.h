#ifndef __NESLIB_PPU_H__
#define __NESLIB_PPU_H__
#include "nesint.h"
// PPU:

/* PPU_CRTL: $2000
* BITS: VPHB SINN	
* NMI enable (V), 
* PPU master/slave (P), 
* sprite height (H), 
* background tile select (B), 
* sprite tile select (S), 
* increment mode (I), 
* nametable select (NN)
*
*/ 



/* PPU_MASK $2001   
* BITS: BGRs bMmG 
* color emphasis (BGR), 
* sprite enable (s), 
* background enable (b), 
* sprite left column enable (M), 
* background left column enable (m), 
* greyscale (G)
*
*/



/* PPU_STATUS $2002   
* BITS: VSO- ----   
* vblank (V), 
* sprite 0 hit (S), 
* sprite overflow (O), 
* read resets write pair for $2005/2006
*/



/* OAM_ADDR $2003   
* BITS: aaaa aaaa   
* OAM read/write address
*/

/* OAM_DATA $2004   
* BITS: dddd dddd   
* OAM data read/write
*/

/* PPUS_CROLL $2005   
* BITS: xxxx xxxx   
* fine scroll position (two writes: X, Y)
*/


/* PPU_ADDR  $2006   
* BITS: aaaa aaaa   
* PPU read/write address (two writes: MSB, LSB)
*/


/* PPU_DATA  $2007   
* BITS: dddd dddd   
* PPU data read/write
*/

/* OAM_DMA $4014
* BITS: aaaa aaaa   
* OAM DMA high address
*/

struct __ppu
{
	uint8_t ctrl;                       /* $2000 */
	uint8_t mask;                       /* $2001 */
	signed char volatile const status;  /* $2002 */

	struct {
		uint8_t addr;                   /* $2003 */
		uint8_t data;                   /* $2004 */
	} sprite;
    

	struct {
		uint8_t scroll;                 /* $2005 */
		uint8_t addr;                   /* $2006 */
		uint8_t data;                   /* $2007 */
	} vram;
	
};

#define PPU (*((struct __ppu volatile*)0x2000))

/* these functions don't take parameters by stack, but by registers */
extern void __fastcall__ waitvblank(void);


/* x -> A REGISTER,  y -> X RESGISTER */
extern void __fastcall__ ppu_set_scroll_enable_render(const uint16_t xy); 


/* str's characters address: 
 * low byte -> A REGISTER
 * high byte -> X REGISTER */
extern void __fastcall__ write_str(const uint8_t* const str);  

/* _write_val: write a value (stored on register A) in 
 * PPU.vram.data, decrementing X until 0, then return.
 * must be used with ppu_write_rval and ppu_write_lval macros */
extern void __fastcall__ _write_val(const uint16_t val_and_times);




/* Calculates x/y position. The top-left corner is 0x2000, and each row
 * is 32 bytes wide. Hence:
 *  (0,0)   => 0x2000;
 *  (1,2)   => 0x2000 + 2*32 + 1 => 0x2041;
 *  (20,16) => 0x2000 + 16*32 + 20 => 0x2214;
 */
extern void __fastcall__ _ppu_set_cursor_exact(uint16_t xy); /* lowbyte -> A register, high byte -> X register 
                                                              * stores these bytes to the PPU.vram.addr        
                                                              */

extern void __fastcall__ _ppu_set_cursor_calc(uint16_t xy);  /* calculate the screen spot based on x, y
                                                              * x -> X register
                                                              * y -> A register
                                                              */



/* macros for functions, used to optimize the function call or make it easier to use */

/* value and times are rvalues */
#define ppu_write_rval(value, times) { __asm__("LDA #%b", value); __asm__("LDX #%b", times); \
                                       __asm__("JSR %v", _write_val); }
/* value and times are lvalues */
#define ppu_write_lval(value, times) { __asm__("LDA %v", value); __asm__("LDX %v", times); \
                                       __asm__("JSR %v", _write_val); }
/* value is rvalue , times is lvalue */
#define ppu_write_rlval(value, times) { __asm__("LDA #%b", value); __asm__("LDX %v", times); \
                                        __asm__("JSR %v", _write_val); }
/*value is lvalue, times is rvalue */
#define ppu_write_lrval(value, times) { __asm__("LDA %v", value); __asm__("LDX #%b", times); \
                                        __asm__("JSR %v", _write_val); }


#define ppu_set_cursor_exact(x, y) { _ppu_set_cursor_exact((0x2000|((y)<<5)|x)); }

#define ppu_set_cursor_calc(x, y)  { __asm__("LDX %v", x); __asm__("LDA %v", y); \
                                     __asm__("JSR %v", _ppu_set_cursor_calc); }






/* Colors , not all colors, but some most used */

#define GRAY     0x00
#define BLUE     0x01
#define DBLUE    0x02
#define PURPLE   0x03
#define DPINK    0x04
#define RED      0x05
#define DRED1    0x06
#define DRED2    0x07
#define BROWN    0x08
#define GREEN    0x09
#define DGREEN1  0x0a
#define DGREEN2  0x0b
#define NBLUE    0x0c
#define BLACK    0x0d
#define LGRAY    0x10
#define LBLUE    0x11
#define LBLUE2   0x12
#define LPURPLE  0x13
#define PINK     0x14
#define REDPINK  0x15
#define ORANGE   0x16
#define DYELLOW  0x17
#define LBROWN   0x18
#define LGREEN   0x19
#define LGREEN2  0x1a
#define LGREEN3  0x1b
#define LNBLUE   0x1c
#define DGRAY    0x1d
#define WHITE    0x20
#define LBLUE3   0x21
#define LPURPLE2 0x22
#define LPURPLE3 0x23
#define LPINK    0x25
#define LPINK2   0x24
#define LBEGE    0x26
#define LBEGE2   0x27
#define YELLOW   0x28
#define LYELLOW  0x29




#define PPU_SET_VRAM_ADDR(byte1, byte2) ( (PPU.vram.addr = byte1, PPU.vram.addr = byte2) )


/* Set the screen scroll offsets: */

#define PPU_SET_SCROLL(x, y) { PPU_SET_VRAM_ADDR(x, y); }


/* Set "foreground colour"...
 * i.e. write color 'c' value into VRAM address 0x3F03
 * ...which is colour no. 3 in "background palette 0".
 * See: http://wiki.nesdev.com/w/index.php/PPU_palettes */
#define PPU_SET_COLOR_TEXT(c)   { PPU_SET_VRAM_ADDR(0x3F, 0x03); PPU_IO(c); }

/* Set "background colour"...
 * i.e. write color 'c' value into VRAM address 0x3F00
 * ...which is the "Universal background color" palette entry.
 * See: http://wiki.nesdev.com/w/index.php/PPU_palettes */
#define PPU_SET_COLOR_BACK(c)   { PPU_SET_VRAM_ADDR(0x3F, 0x00); PPU_IO(c); }

/* Write to the PPU IO port, e.g. to write a byte at the nametable 'cursor' position: */
#define PPU_IO(c)               { PPU.vram.data = c; }











#endif
