;
; File generated by cc65 v 2.15 - Git 60958f0
;
	.fopt		compiler,"cc65 v 2.15 - Git 60958f0"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.import		_itoa
	.export		___ppu_str
	.export		___cbuff
	.export		___iskey_pressed_pad1
	.export		___iskey_pressed_pad2
	.export		___wait_key_press_pad1
	.export		___wait_key_press_pad2
	.export		___write_string
	.export		___write_fmtstring

.segment	"BSS"

___ppu_str:
	.res	2,$00
___cbuff:
	.res	6,$00
_args:
	.res	2,$00

; ---------------------------------------------------------------
; int __near__ __fastcall__ __iskey_pressed_pad1 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___iskey_pressed_pad1: near

.segment	"CODE"

	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L0105:	lda     ___cbuff+3
	cmp     #$08
	bcs     L000E
	lda     ___cbuff
	cmp     ___cbuff+3
	bne     L001B
	lda     $4016
	and     #$01
	beq     L0107
	lda     #$01
	rts
L0107:	rts
L001B:	inc     ___cbuff+3
	jmp     L0105
L000E:	rts

.endproc

; ---------------------------------------------------------------
; int __near__ __fastcall__ __iskey_pressed_pad2 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___iskey_pressed_pad2: near

.segment	"CODE"

	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L0109:	lda     ___cbuff+3
	cmp     #$08
	bcs     L0038
	lda     ___cbuff
	cmp     ___cbuff+3
	bne     L0045
	lda     $4017
	and     #$01
	beq     L010B
	lda     #$01
	rts
L010B:	rts
L0045:	inc     ___cbuff+3
	jmp     L0109
L0038:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __wait_key_press_pad1 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___wait_key_press_pad1: near

.segment	"CODE"

L0059:	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
L010D:	lda     ___cbuff+3
	cmp     #$08
	bcs     L0063
	lda     ___cbuff
	cmp     ___cbuff+3
	bne     L010E
	lda     $4016
	and     #$01
	beq     L0059
	rts
L010E:	inc     ___cbuff+3
	lda     $4016           ; hand written, advance to next key
	jmp     L010D
L0063:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __wait_key_press_pad2 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___wait_key_press_pad2: near

.segment	"CODE"

L0081:	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
L0110:	lda     ___cbuff+3
	cmp     #$08
	bcs     L008B
	lda     ___cbuff
	cmp     ___cbuff+3
	bne     L0111
	lda     $4017
	and     #$01
	beq     L0081
	rts
L0111:	inc     ___cbuff+3
	lda     $4017          ; hand written, advance to next key
	jmp     L0110
L008B:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __write_string (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___write_string: near

.segment	"CODE"

	jmp     L00AB
L00A9:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00AB
	inc     ___ppu_str+1
L00AB:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L00A9
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __write_fmtstring (__near__ const unsigned char *)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___write_fmtstring: near

.segment	"CODE"

	jsr     enter
	ldy     #$00
	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	sta     _args
	stx     _args+1
	jmp     L0116
L0113:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	cmp     #$25
	beq     L0114
	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	jmp     L0117
L0114:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     pushax
	jsr     ldaxi
	jsr     incax1
	ldy     #$00
	jsr     staxspidx
	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	cmp     #$63
	jeq     L00F7
	cmp     #$69
	beq     L00C9
	cmp     #$73
	beq     L00E2
	jmp     L0115
L00C9:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L00D1
	dec     _args+1
L00D1:	ldx     _args+1
	sta     ptr1
	stx     ptr1+1
	lda     (ptr1),y
	jsr     pusha0
	lda     #<(___cbuff)
	ldx     #>(___cbuff)
	jsr     pushax
	ldx     #$00
	lda     #$0A
	jsr     _itoa
	lda     #<(___cbuff)
	sta     ___ppu_str
	lda     #>(___cbuff)
	sta     ___ppu_str+1
	jmp     L00D8
L00D6:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00D8
	inc     ___ppu_str+1
L00D8:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L00D6
	jmp     L0115
L00E2:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L00EA
	dec     _args+1
L00EA:	ldx     _args+1
	jsr     ldaxi
	sta     ___ppu_str
	stx     ___ppu_str+1
	jmp     L00ED
L00EB:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00ED
	inc     ___ppu_str+1
L00ED:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L00EB
	jmp     L0115
L00F7:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L0102
	dec     _args+1
L0102:	ldx     _args+1
	sta     ptr1
	stx     ptr1+1
L0117:	lda     (ptr1),y
	sta     $2007
L0115:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     pushax
	jsr     ldaxi
	jsr     incax1
	ldy     #$00
	jsr     staxspidx
L0116:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	ldx     #$00
	lda     (ptr1),y
	jne     L0113
	jmp     leave

.endproc

