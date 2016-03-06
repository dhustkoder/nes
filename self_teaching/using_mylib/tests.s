;
; File generated by cc65 v 2.15 - Git ab1600b
;
	.fopt		compiler,"cc65 v 2.15 - Git ab1600b"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.import		_waitvblank
	.import		_ppu_set_scroll_enable_render
	.import		_write_str
	.import		__ppu_set_cursor_exact
	.export		_main

.segment	"RODATA"

L0025:
	.byte	$48,$45,$4C,$4C,$4F,$20,$4D,$59,$4C,$49,$42,$21,$00

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	jsr     _waitvblank
	lda     #$3F
	sta     $2006
	lda     #$00
	sta     $2006
	lda     #$01
	sta     $2007
	lda     #$3F
	sta     $2006
	lda     #$03
	sta     $2006
	lda     #$20
	sta     $2007
	tax
	lda     #$21
	jsr     __ppu_set_cursor_exact
	lda     #<(L0025)
	ldx     #>(L0025)
	jsr     _write_str
	ldx     #$00
	txa
	jsr     _ppu_set_scroll_enable_render
L002D:	jmp     L002D

.endproc
