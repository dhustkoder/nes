#include <stdarg.h>
#include <stdlib.h>
#include "neslib.h"

// definitions: 
const unsigned char* __ppu_str; 
uint8_t __cbuff[6];

// static locals
static va_list args; // variadic args for __write_fmtstring
static uint8_t pad_status[2] = { 0, 0 }; // pad bit info  [ A ] [ B ] [ SELECT ] [ START ] [ UP ] [ DOWN ] [ LEFT ] [ RIGHT ]

// MACROS:
// naming
#define ppu_str __ppu_str
#define cbuff __cbuff
#define pad1 ( pad_status[0] ) 
#define pad2 ( pad_status[1] )

// loop iterators
#define i ( cbuff[3] )
#define j ( cbuff[4] )
#define k ( cbuff[5] )

// key, is stored at __cbuff[0] 
#define key ( cbuff[0] )
#define controller_port ( cbuff[1] )




void __fastcall__ loadkey_pad1(void)
{
	__asm__("LDA #$01");  // 01 into A reg
	__asm__("STA $4016"); // store A into controller port 1 
	__asm__("LDA #$00");  // then load 0 into A reg
	__asm__("STA $4016"); // store A into controller port 1 ; tells the cpu to get controller new status

	for(i = 0; i < key ; ++i ) 
	{
		__asm__("LDA $4016"); 
		__asm__("STA %v + 5 ; REMOVE ME ;", __cbuff);
	}	
}


int __fastcall__ __iskey_pressed_pad1(void)
{
	
	loadkey_pad1();
	if(( pad1 & KEY_A ) != 0) return 1;
	else return 0;
}



int __fastcall__ __iskey_pressed_pad2(void)
{
	// TODO
	if(( JOYPAD[1] & 0x1 ) != 0 ) return 1;
	else return 0;
}



void __fastcall__ __wait_key_press_pad1(void)
{
	while(1)
	{
		loadkey_pad1();
		if( ( JOYPAD[0] & 0x1 ) != 0) return;
	}
}



void __fastcall__ __wait_key_press_pad2(void)
{
	while(1)
	{ 
		// TODO
		if( ( JOYPAD[1] & 0x1 ) != 0 ) return;
	}
}







void __fastcall__ __write_string(void)
{
	do{
		PPU.vram.data = *ppu_str++;
	}while(*ppu_str);
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
			        __write_string();
			        break;
			    
			    case 's': 
			        ppu_str = va_arg(args, uint8_t*); 
			        __write_string();
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
