#include <stdarg.h>
#include <stdlib.h>
#include "neslib.h"

// definitions: 
const unsigned char* __ppu_str; 
uint8_t __cbuff[6];

static va_list args; // variadic args for __write_fmtstring

// MACROS:
// naming
#define ppu_str __ppu_str
#define cbuff __cbuff


// loop iterators
#define i ( cbuff[3] )
#define j ( cbuff[4] )
#define k ( cbuff[5] )

// key, is stored at __cbuff[0] 
#define key ( cbuff[0] )


int __fastcall__ __iskey_pressed_pad1(void)
{
	__asm__("LDA #$01");  // 01 into A reg
	__asm__("STA $4016"); // store A into controller port 1 
	__asm__("LDA #$00");  // then load 0 into A reg
	__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status
	
	// here I'll use cbuff[0] as a counter, to save memory
	for(i = 0; i < 8; ++i )
	{
		if( i == key )
		{
			if(( JOYPAD[0] & 0x1 ) != 0) return 1;
			else return 0;
		}
		else __asm__("LDA $4016"); // advance key
	}
}



int __fastcall__ __iskey_pressed_pad2(void)
{
	__asm__("LDA #$01");  // 01 into A reg
	__asm__("STA $4016"); // store A into controller port 1 
	__asm__("LDA #$00");  // then load 0 into A reg
	__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status
	
	// here I'll use cbuff[0] as a counter, to save memory
	for(i = 0; i < 8 ; ++i )
	{
		if( i == key )
		{
			if(( JOYPAD[1] & 0x1 ) != 0) return 1;
			else return 0;
		}
		else __asm__ ("LDA $4017"); // advance key
	}
}



void __fastcall__ __wait_key_press_pad1(void)
{

	ready_controller:
		__asm__("LDA #$01");  // 01 into A reg
		__asm__("STA $4016"); // store A into controller port 1 
		__asm__("LDA #$00");  // then load 0 into A reg
		__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status
	
	
	for(i = 0; i < 8; ++i, __asm__("LDA $4016")) // increment i and advance to next key
	{
		if(i == key)
		{
			if( ( JOYPAD[0] & 0x1 ) != 0) return;
			else goto ready_controller;
		}


	}

}



void __fastcall__ __wait_key_press_pad2(void)
{

	ready_controller:
		__asm__("LDA #$01");  // 01 into A reg
		__asm__("STA $4016"); // store A into controller port 1 
		__asm__("LDA #$00");  // then load 0 into A reg
		__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status
	
	for(i = 0; i < 8; ++i, __asm__("LDA $4017")) // increment i and advance to next key
	{
		if(i == key)
		{
			if( ( JOYPAD[1] & 0x1 ) != 0) return;
			else goto ready_controller;
		}
	}

}



void __fastcall__ __write_string(void)
{
        while(*ppu_str)
        {
                PPU.vram.data = *ppu_str;
                ++ppu_str;
        }
}



void __write_fmtstring(const char* str, ...)
{
	va_start(args, str);
	while(*str)
	{
	    if( (*str) != '%')
	            ppu_io(*str);

		else
		{
			++str;
			switch(*str)
			{
			    case 'i': 
			        itoa(va_arg(args, uint8_t), cbuff, 10); 
			        ppu_str = cbuff;
			        while(*ppu_str) { ppu_io(*ppu_str); ++ppu_str; } 
			        break;
			    
			    case 's': 
			        ppu_str = va_arg(args, unsigned char*); 
			        while(*ppu_str) { ppu_io(*ppu_str); ++ppu_str; } 
			        break;


			    case 'c': 
			        ppu_io(va_arg(args, uint8_t));
			        break;
			}
		}
		
		++str;
	}

	va_end(args);
}
