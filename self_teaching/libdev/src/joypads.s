.include "inc/nes.inc"


.importzp _joypads   ; import _joypads from zeropage

.export _update_pad1
.export _update_pad1
  
                        
.segment 	"CODE"

prepare_pads_for_read:
	LDA 	#$01	 ; strobe the joypad before read
	STA 	APU_PAD1
	LDA 	#$00
	STA 	APU_PAD1
	LDX     #8       ; counter
	rts




;---------------------------------------------;
; extern void __fastcall__ update_pad1(void)  ;
;---------------------------------------------;
.proc _update_pad1
	JSR 	prepare_pads_for_read
Loop:  
	LDA     APU_PAD1
    ROR     a
    ROR     _joypads
    DEX
    BNE     Loop
    RTS

.endproc




;---------------------------------------------;
; extern void __fastcall__ update_pad2(void)  ;
;---------------------------------------------;
.proc _update_pad2
	JSR 	prepare_pads_for_read
Loop:  
	LDA     APU_PAD2
    ROR     a
    ROR     _joypads+1
    DEX
    BNE     Loop
    RTS

.endproc