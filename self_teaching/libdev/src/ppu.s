.include "nes.inc"
  
; functions that can be called directly from C code ;
.export _waitvblank 
.export _ppu_set_scroll_enable_render
.export _write_str

; functions that are called from C code with macros ;
.export __ppu_set_cursor_exact
.export __ppu_set_cursor_calc


; zeropage variables we need here ;
.importzp tmp1
.importzp ptr1

.segment "CODE"

;-------------------------------------------------;
;   extern void __fastcall__ waitvblank(void)     ;
;-------------------------------------------------;
.proc   _waitvblank

wait:   BIT     PPU_STATUS  ; test PPU_STATUS, modify N flag to BPL instruction
        BPL     wait        ; branch if 7th bit is 1, meaning that is vblank ; 
        RTS

.endproc




;--------------------------------------------------------------------------;
;   extern void __fastcall__ ppu_set_scroll_enable_render(uint16_t xy)     ;
;--------------------------------------------------------------------------;
.proc 	_ppu_set_scroll_enable_render
	STX 	PPU_VRAM_SCROLL    ; store the high byte
	STA 	PPU_VRAM_SCROLL    ; store the low byte
	
	LDA 	#$08               ; set the bit 3 (counting 7 - 0)
	STA 	PPU_MASK           ; at the PPU_MASK
	RTS

.endproc



;-----------------------------------------------------;
; extern void __fastcall__ write_str(uint8_t* str)    ;
;-----------------------------------------------------;
.proc _write_str
	STA 	ptr1                ; store the low byte of the str address
	STX 	ptr1+1              ; store the high byte of the str address
	LDY 	#$00                ; load #$00 as the offset 

WRITE_CHAR:
	LDA 	(ptr1), Y           ; get the character at the ptr1 + Y
	CMP 	#$00                ; if character is a null terminator 
	BEQ 	EXIT                ; if it is, then return from the function
	STA 	PPU_VRAM_DATA       ; send the character to the PPU_VRAM_DATA
	INY                         ; increase the character offset
	JMP 	WRITE_CHAR          ; repeat...

EXIT: 
	RTS

.endproc




;----------------------------------------------------------------------;
; extern void __fastcall__ _ppu_set_cursor_calc(uint8_t x, uint8_t y)  ;
;----------------------------------------------------------------------;

.proc __ppu_set_cursor_exact
	STX 	PPU_VRAM_ADDR    ; store the high byte
	STA 	PPU_VRAM_ADDR    ; store the low byte
	RTS
.endproc






;-----------------------------------------------------------------------;
; extern void __fastcall__ _ppu_set_cursor_calc(uint8_t x, uint8_t y)   ;
;-----------------------------------------------------------------------;
.proc __ppu_set_cursor_calc
	TAY 	              ; save the original y value at Y register
	
	LSR 	A             ; right shift the y value 3 times
	LSR 	A
	LSR 	A

	CLC                   ; clear carry flag
	ADC 	#$20          ; add the hex value #$20 at y
	STA 	PPU_VRAM_ADDR ; store as the high byte
	

	TYA 	              ; recover the original y value from Y register

	
	ASL 	A             ; left shift 5 times
	ASL 	A
	ASL 	A
	ASL 	A
	ASL 	A


	STX 	tmp1          ; store x value to a temporary
	ADC 	tmp1          ; add the x to the left shifted y

	STA 	PPU_VRAM_ADDR ; store as the low byte
	RTS                   ; return

.endproc


