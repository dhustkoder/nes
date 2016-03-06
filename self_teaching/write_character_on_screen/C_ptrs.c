



static const unsigned char *str = "HELLO_MYLIB";
static unsigned char _count = 0;
#define ppu_vram_data (*(unsigned char*)0x2007)
void main(void)
{

	while(*(str+_count) != 0x00){
		ppu_vram_data = *(str + _count);
		++_count;
	}
}