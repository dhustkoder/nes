
PPU_MASK      = $2001
PPU_VRAM_CRTL = $2005
PPU_VRAM_ADDR = $2006
PPU_VRAM_DATA = $2007

.import _waitvblank 

.segment "HEADER"
   .byte "NES" ; signature
   .byte $1A   ; signature
   .byte $01   ; # of 16kb PRG-ROM banks
   .byte $01   ; # of 8kb VROM banks
   .byte $00   ; ROM control byte one
   .byte $00   ; ROM control byte two
   .byte $01   ; # of 8kb RAM banks
   .byte $00   ; reserved



.segment "CODE"

RESET:
	JSR	_waitvblank
	LDA	#$3F
	STA	PPU_VRAM_ADDR
	LDA	#$00
	STA	PPU_VRAM_ADDR
	LDA	#$03
	STA	PPU_VRAM_DATA
	LDA	#$00
	STA	PPU_VRAM_CRTL
	STA	PPU_VRAM_CRTL
	LDA	%10001000
	STA	PPU_MASK
	STA	PPU_MASK
LOOP:
   JMP LOOP

NMI:
IRQ:

.segment "VECTORS"
   .word NMI
   .word RESET
   .word IRQ



