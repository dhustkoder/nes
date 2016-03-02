#ifndef _NESLIB_H_
#define _NESLIB_H_
/*
    Hello, NES!
    Writes a message to the screen and plays a tone.

    Originally written by WolfCoder (2010). See:
    http://www.dreamincode.net/forums/topic/152401-nes-game-programming-part-1/

    Modified slightly by Anton Maurovic (2013) for:
    http://anton.maurovic.com/posts/nintendo-nes-gamedev-part-1-setting-up/

    Build with cc65 as follows:
        cl65 -t nes hello-nes.c -o hello.nes

    This example will use a default CHR ROM that comes with the cc65
    target files for NES.
*/


/* Contribution by DhustKoder, extending this file */

/* Includes */
#include <nes.h>


/* For more information on these PPU registers, see:
 * http://wiki.nesdev.com/w/index.php/PPU_registers */
#define PPU_CTRL2       0x2001  /* Aka PPUMASK: Turns features of the PPU on or off. */
#define PPU_VRAM_ADDR1  0x2005  /* Aka PPUSCROLL: Used for X/Y scroll */
#define PPU_VRAM_ADDR2  0x2006  /* Aka PPUADDR: Nametable 'cursor' */
#define PPU_VRAM_IO     0x2007  /* Aka PPUDATA: Access data pointed to by last PPUADDR write. */

/* For more information on these APU registers, see:
 * http://wiki.nesdev.com/w/index.php/APU_Status */
#define APU_STATUS      0x4015  /* Used for activating APU "voices". */
#define APU_PULSE       0x4000  /* 0x4000-0x4003: Registers for pulse 1. 0x4004-0x4007 for pulse 2. */

/* Write a byte to a given address: */
#define poke(addr, data)        (*((unsigned char*)addr) = data)

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



// static assert
#define static_assert(x) static const static_assert_arr[x];



 // typedefs
 typedef unsigned char uint8_t;
 typedef char int8_t;


 // Colors , not all colors, but some most used

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

extern const unsigned char* __ppu_str; // a u character ptr, point to strs
extern uint8_t __cbuff[6]; // a buffer of 6, 8bit values to be used for general purpose

// read input functions:
int __fastcall__ __iskey_pressed_pad1(void);
int __fastcall__ __iskey_pressed_pad2(void);
void __fastcall__ __wait_key_press_pad1(void);
void __fastcall__ __wait_key_press_pad2(void);

// write strings
                 // used to store the string or fmtstring address then write to ppu_io();
void __fastcall__ __write_string(void);       // writes the bytes pointed by __ppu_str to APU.vram.data
void __write_fmtstring(const char* str, ...); // write string with fmt like prinf , (support %i, %s, %c), can hold 4 variadic arguments

/* the macros are to avoid passing arguments to functions, as this can be a heavy operation */

// input functions:
#define iskey_pressed_pad1(key)  ( (__cbuff[0] = key), (__iskey_pressed_pad1()) )
#define iskey_pressed_pad2(key)  ( (__cbuff[0] = key), (__iskey_pressed_pad2() ) )
#define wait_key_press_pad1(key) { __cbuff[0] = key; __wait_key_press_pad1(); }
#define wait_key_press_pad2(key) { __cbuff[0] = key; __wait_key_press_pad2(); }

// write strings functions:
#define write_str(x, y, str) { ppu_set_cursor(x, y); __ppu_str = str; __write_string();  }
#define write_fmtstr(x, y, str, ...) { ppu_set_cursor(x, y); __write_fmtstring(str, __VA_ARGS__); }








#endif
