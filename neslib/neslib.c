#include <stdarg.h>
#include <stdlib.h>
#include "neslib.h"

const char* __ppu_str;
static char* _s; 
static char cbuff[6];
static va_list args;


void __fastcall__ __write_string(void)
{

        while(*__ppu_str)
        {
                PPU.vram.data = *__ppu_str;
                ++__ppu_str;
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
			        _s = cbuff; 
			        while(*_s) { ppu_io(*_s); ++_s; } 
			        break;
			    
			    case 's': 
			        _s = va_arg(args, char*); 
			        while(*_s) { ppu_io(*_s); ++_s; } 
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
