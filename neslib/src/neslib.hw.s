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
L00FA:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L00FB
	lda     $4016
	; <= REMOVE ME ;
	inc     ___cbuff+3
	jmp     L00FA
L00FB:	lda     $4016
	and     #$01
	beq     L00FD
	lda     #$01
	rts
L00FD:	rts

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
L00FE:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L00FF
	lda     $4017
	; <= REMOVE ME ;
	inc     ___cbuff+3
	jmp     L00FE
L00FF:	lda     $4016
	and     #$01
	beq     L0101
	lda     #$01
	rts
L0101:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __wait_key_press_pad1 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___wait_key_press_pad1: near

.segment	"CODE"

L0053:	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L0102:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L0103
	lda     $4017
	; <= REMOVE ME ;
	inc     ___cbuff+3
	jmp     L0102
L0103:	lda     $4016
	and     #$01
	beq     L0053
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __wait_key_press_pad2 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___wait_key_press_pad2: near

.segment	"CODE"

L0079:	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L0104:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L0105
	lda     $4017
	; <= REMOVE ME ;
	inc     ___cbuff+3
	jmp     L0104
L0105:	lda     $4016
	and     #$01
	beq     L0079
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ __fastcall__ __write_string (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	___write_string: near

.segment	"CODE"

	jmp     L00A1
L009F:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00A1
	inc     ___ppu_str+1
L00A1:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L009F
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
	jmp     L010A
L0107:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	cmp     #$25
	beq     L0108
	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	jmp     L010B
L0108:	lda     (sp),y
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
	jeq     L00ED
	cmp     #$69
	beq     L00BF
	cmp     #$73
	beq     L00D8
	jmp     L0109
L00BF:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L00C7
	dec     _args+1
L00C7:	ldx     _args+1
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
	jmp     L00CE
L00CC:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00CE
	inc     ___ppu_str+1
L00CE:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L00CC
	jmp     L0109
L00D8:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L00E0
	dec     _args+1
L00E0:	ldx     _args+1
	jsr     ldaxi
	sta     ___ppu_str
	stx     ___ppu_str+1
	jmp     L00E3
L00E1:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	lda     (ptr1),y
	sta     $2007
	inc     ___ppu_str
	bne     L00E3
	inc     ___ppu_str+1
L00E3:	lda     ___ppu_str
	sta     ptr1
	lda     ___ppu_str+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	bne     L00E1
	jmp     L0109
L00ED:	lda     _args
	sec
	sbc     #$02
	sta     _args
	bcs     L00F8
	dec     _args+1
L00F8:	ldx     _args+1
	sta     ptr1
	stx     ptr1+1
L010B:	lda     (ptr1),y
	sta     $2007
L0109:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     pushax
	jsr     ldaxi
	jsr     incax1
	ldy     #$00
	jsr     staxspidx
L010A:	lda     (sp),y
	jsr     leaa0sp
	jsr     decax1
	jsr     ldaxi
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	ldx     #$00
	lda     (ptr1),y
	jne     L0107
	jmp     leave

.endproc

