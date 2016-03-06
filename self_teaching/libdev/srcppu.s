.include "nes.inc"
.export _waitvblank
.export _ppu_set_scroll_enable_render
.export __ppu_set_cursor_exact
.export __ppu_set_cursor_calc
.export _write_str

.importzp tmp1
.importzp ptr1

.segment "CODE"

.proc   _waitvblank

wait:   LDA     PPU_STATUS
        BPL     wait
        RTS

.endproc





.proc 	_ppu_set_scroll_enable_render
	STA 	PPU_VRAM_SCROLL
	STX 	PPU_VRAM_SCROLL
	LDA 	#$08
	STA 	PPU_MASK
	RTS

.endproc






.proc __ppu_set_cursor_calc
	STX		tmp1
	TAX
	LSR 	A
	LSR 	A
	LSR 	A
	CLC
	ADC 	#$20
	STA 	PPU_VRAM_ADDR
	TXA
	ASL 	A
	ASL 	A
	ASL 	A
	ASL 	A
	ASL 	A
	CLC
	ADC 	tmp1
	STA 	PPU_VRAM_ADDR
	RTS
.endproc

.proc __ppu_set_cursor_exact
	STX 	PPU_VRAM_ADDR
	STA 	PPU_VRAM_ADDR
	RTS
.endproc



.proc _write_str
	STA 	ptr1
	STX 	ptr1+1
	LDY 	#$00

WRITE_CHAR:
	LDA 	(ptr1), Y
	CMP 	#$00
	BEQ 	NULL_TERMINATION
	STA 	PPU_VRAM_DATA
	INY
	JMP 	WRITE_CHAR	
NULL_TERMINATION: RTS



.endproc