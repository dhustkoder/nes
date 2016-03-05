#ifndef _NESLIB_H_
#define _NESLIB_H_
#include "nesint.h"
#include "ppu.h"

/* Write a byte to a given address: */
#define poke(addr, data)        (*((uint8_t*)addr) = data)

/* Write a pair of bytes to the PPU VRAM Address 2. */
#define ppu_2(a, b)             { poke(PPU_VRAM_ADDR2, a); poke(PPU_VRAM_ADDR2, b); }

/* Set the nametable x/y position. The top-left corner is 0x2000, and each row
 * is 32 bytes wide. Hence:
 *  (0,0)   => 0x2000;
 *  (1,2)   => 0x2000 + 2*32 + 1 => 0x2041;
 *  (20,16) => 0x2000 + 16*32 + 20 => 0x2214;
 */
#define ppu_set_cursor(x, y)    ppu_2(0x20+((y)>>3), ((y)<<5)+(x))

/* Set the screen scroll offsets: */
#define ppu_set_scroll(x, y)    { poke(PPU_VRAM_ADDR1, x); poke(PPU_VRAM_ADDR1, y); }

/* Set "foreground colour"...
 * i.e. write color 'c' value into VRAM address 0x3F03
 * ...which is colour no. 3 in "background palette 0".
 * See: http://wiki.nesdev.com/w/index.php/PPU_palettes */
#define ppu_set_color_text(c)   { ppu_2(0x3F, 0x03); ppu_io(c); }

/* Set "background colour"...
 * i.e. write color 'c' value into VRAM address 0x3F00
 * ...which is the "Universal background color" palette entry.
 * See: http://wiki.nesdev.com/w/index.php/PPU_palettes */
#define ppu_set_color_back(c)   { ppu_2(0x3F, 0x00); ppu_io(c); }

/* Write to the PPU IO port, e.g. to write a byte at the nametable 'cursor' position: */
#define ppu_io(c)               poke(PPU_VRAM_IO, (c))

/* Write to APU_STATUS register: */
#define apu_status(c)           poke(APU_STATUS, (c))

/* Write to one of the APU pulse registers.
 * Parameter 'ch' is the channel (pulse channel 0 or 1),
 * 'r' is the register (0-4), and 'c' is the data to write. */
#define apu_pulse(ch, r, c)     poke(APU_PULSE+((ch)<<2)+(r), (c))



/* static assert */
#define static_assert(x) const static_assert_arr[x ? -1 : 1];






 










#endif
