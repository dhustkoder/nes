.include "inc/nes.inc"

.export _joypads
.export _update_pad1
.export _update_pad1

.segment "BSS"
	_joypads: .res 2



.segment 	"CODE"

;---------------------------------------------;
; extern bool __fastcall__ update_pad1(void)  ;
;---------------------------------------------;
.proc _update_pad1
	LDA 	#$01	; strobe the joypad before read
	STA 	APU_PAD1
	LDA 	#$00
	STA 	APU_PAD1

	LDX     #8       ; counter
Loop:  
	LDA     APU_PAD1
    ROR     a
    ROR     _joypads
    DEX
    BNE     Loop
    RTS

.endproc




;---------------------------------------------;
; extern bool __fastcall__ update_pad2(void)  ;
;---------------------------------------------;
.proc _update_pad2
	LDA 	#$01	 ; strobe the joypad before read
	STA 	APU_PAD1
	LDA 	#$00
	STA 	APU_PAD1

	LDX     #8       ; counter
Loop:  
	LDA     APU_PAD2
    ROR     a
    ROR     _joypads+1
    DEX
    BNE     Loop
    RTS

.endproc