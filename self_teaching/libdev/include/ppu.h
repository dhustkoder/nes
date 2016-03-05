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



/* PPUMASK $2001   
* BITS: BGRs bMmG 
* color emphasis (BGR), 
* sprite enable (s), 
* background enable (b), 
* sprite left column enable (M), 
* background left column enable (m), 
* greyscale (G)
*
*/



/* PPUSTATUS $2002   
* BITS: VSO- ----   
* vblank (V), 
* sprite 0 hit (S), 
* sprite overflow (O), 
* read resets write pair for $2005/2006
*/



/* OAMADDR $2003   
* BITS: aaaa aaaa   
* OAM read/write address
*/

/* OAMDATA $2004   
* BITS: dddd dddd   
* OAM data read/write
*/

/* PPUSCROLL $2005   
* BITS: xxxx xxxx   
* fine scroll position (two writes: X, Y)
*/


/* PPUADDR  $2006   
* BITS: aaaa aaaa   
* PPU read/write address (two writes: MSB, LSB)
*/


/* PPUDATA  $2007   
* BITS: dddd dddd   
* PPU data read/write
*/

/* OAM DMA $4014
* BITS: aaaa aaaa   
* OAM DMA high address
*/

struct __ppu
{
	uint8_t ctrl;                        /* $2000 */
	uint8_t mask;                        /* $2001 */
	signed char volatile const status    /* $2002 */

	struct {
		uint8_t addr;                /* $2003 */
		uint8_t data;                /* $2004 */
	} sprite;
    

	struct {
		uint8_t scroll;              /* $2005 */
		uint8_t addr;                /* $2006 */
		uint8_t data;                /* $2007 */
	} vram;
	
};

#define ppu (*((struct __ppu volatile*)0x2000))


void __fastcall__ waitvblank(void);


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



#endif
