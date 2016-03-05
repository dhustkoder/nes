.import _waitvblank

.include "../../libdev/src/nes.inc" ; macros to help code for nes ;


; The INES Header is used to let the Emulator know the specifications of the NES Rom that you're trying to load. 
; The first three bytes of any nes file contain the characters "NES" followed by the hex 0x1A. 
; Note that hex values for the P65 begin with a '$'. 
; After this initial information are two bytes representing the number of 16K Prg-Rom blocks and 8K Chr-Rom blocks respectively. 
; Without mappers there can be up to two Prg-Rom blocks.



 ; header segment 16 bytes ;
.segment        "HEADER"
        .byte   $4e,$45,$53,$1a ; "NES"^Z ; NES ^Z  signature to NES 
        .byte   2               ; ines prg  - Specifies the number of 16k prg banks.
        .byte   1               ; ines chr  - Specifies the number of 8k chr banks.
        .byte   %00000011       ; ines mir  - Specifies VRAM mirroring of the banks.
        .byte   %00000000       ; ines map  - Specifies the NES mapper used.
        .byte   0,0,0,0,0,0,0,0 ; 8 zeroes

; Interrupt Vectors[edit]
; The NES has three interrupt vectors which represent locations within the program code that the CPU jumps to when certain types of interrupts occur. 
; There are three different interrupts for the NES: 

; The Non-Maskable Interrupt or NMI ($FFFA), 
; The Reset Vector (; $FFFC), 
; And the IRQ/BRK Vector ($FFFE). 
; The hex values that are in parenthesis are where the *** NES looks to find the 16 bit location of where to jump to within the NES ***.

; Normally the Reset vector will point to the beginning of your code 
; which depending on the number of Prg-Rom blocks you have can be either be somewhere in 
; addresses $8000 to $BFFF or $C000 to $FFFF.

; The Non-Maskable interrupt (NMI) refers to the interrupt that occurs when the PPU refreshes the screen 
; (also known as the V-Blank period). 
; During this time the screen can be updated without any flicker effect occurring.

; Finally the IRQ/BRK interrupt (which I like to call the maskable interrupt) 
; is used when the BRK command occurs. Often it is used by the programmer for various purposes.

.segment "VECTORS"
	.word NMI
	.word RESET
	.word IRQ



; characters to use ;
.segment "CHARS"
	.include "../../libdev/src/neschar.inc" ; include just like C's #include 



.segment "BSS" ; BSS - data to NES's RAM
	_str_idx: .byte $00
	_y_pos:   .byte $00
	_x_pos:   .byte $00
	_tmp:	  .byte $00

.segment "RODATA" ; constant data ( from ROM )
	_str: .byte "HELLO WORLD", $00





.segment "CODE"
; initialize BSS ;
RESET:  
	LDA 	#$00
	STA 	_str_idx
	LDA 	#$01
	STA 	_y_pos
	LDA 	#01
	STA		_x_pos

	JMP 	_main
IRQ:
NMI: 
	RTS




.segment "CODE"
	.proc _set_text_color: near
.segment "CODE"
	LDA 	#$3F
	STA 	PPU_VRAM_ADDR
	LDA 	#$03
	STA 	PPU_VRAM_ADDR
	LDA 	#$20
	STA 	PPU_VRAM_DATA
	RTS
.endproc





.segment "CODE"
	.proc _set_cursor_pos: near
.segment "CODE"
	; set pos ;
	LDA 	_y_pos
	LSR		A
	LSR		A
	LSR		A
	CLC 	; clear carry ;
	ADC		#$20
	STA 	PPU_VRAM_ADDR
	LDA 	_y_pos
	ASL 	A
	ASL 	A
	ASL 	A
	ASL 	A
	ASL 	A
	CLC 	; clear carry ;
	ADC 	_x_pos
	STA 	PPU_VRAM_ADDR
	RTS
.endproc





.segment "CODE"
  .proc _put_char: near
.segment "CODE"
	LDY		_str_idx
	CPY		#11
	BEQ		RESET_IDX
LOAD_AND_STORE:
	LDA 	_str, Y
	STA 	PPU_VRAM_DATA
	CLC
	INC 	_str_idx
	INC 	_x_pos

EXIT:	RTS


RESET_IDX:
	LDA 	#$00
	STA 	_str_idx
	LDA 	#$01
	STA 	_x_pos
	JSR 	_set_cursor_pos
	; clear text ;
	LDA 	#$00
	LDY 	#$00
CLEAR_LOOP:
	STA 	PPU_VRAM_DATA
 	INY
	CPY 	#11
	BEQ 	EXIT
	JMP 	CLEAR_LOOP
.endproc




.segment "CODE"
  .proc _set_background_color: near
.segment "CODE"
	; disable rendering
	LDA 	#$00	
	STA		PPU_MASK

	; set background blue 
	LDA		#$3F
	STA		PPU_VRAM_ADDR
	LDA		#$00
	STA		PPU_VRAM_ADDR
	LDA		#$03
	STA		PPU_VRAM_DATA
	RTS
.endproc	



.segment "CODE"
  .proc _enable_rendering: near
.segment "CODE"
	; set scroll and set rendering
	LDA		#$00
	STA		PPU_VRAM_SCROLL
	STA		PPU_VRAM_SCROLL
	LDA		#$08
	STA		PPU_MASK
	RTS
.endproc


.segment "CODE"
  .proc _main: near
.segment "CODE"
	JSR 	_waitvblank
	JSR 	_set_background_color
	JSR 	_set_text_color
LOOP:
	JSR 	_set_cursor_pos
	JSR 	_put_char
	JSR 	_enable_rendering
	JSR 	_waitvblank
	JMP 	LOOP

.endproc




