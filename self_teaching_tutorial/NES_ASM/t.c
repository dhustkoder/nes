#include <nes.h>
#include <conio.h>

#define TICKLE(addr) __asm__("bit %w", (unsigned)&(addr))


#define PPU_VRAM_DATA (*((unsigned char*)0x2007))

const char* str = "BARON";

void main(void)
{
    PPU_VRAM_DATA = str[0];
    PPU_VRAM_DATA = str[1];
    PPU_VRAM_DATA = str[2];
    return;
}