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
	.forceimport	__STARTUP__
	.import		_waitvblank
	.export		_foo
	.export		_main

.segment	"RODATA"

_x:
	.byte	$41
	.byte	$42
	.byte	$43

; ---------------------------------------------------------------
; void __near__ foo (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_foo: near

.segment	"CODE"

	lda     #$20
	sta     $2006
	lda     #$00
	sta     $2006
	lda     #$20
	sta     $2006
	lda     #$21
	sta     $2006
	lda     #$3F
	sta     $2005
	lda     #$03
	sta     $2005
	lda     #$01
	sta     $2007
	lda     #$41
	sta     $2007
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	jsr     _waitvblank
	jsr     _foo
	lda     #$3F
	sta     $2006
	lda     #$00
	sta     $2006
	lda     #$03
	sta     $2007
	jsr     _foo
	lda     #$00
	sta     $2005
	sta     $2005
	lda     #$08
	sta     $2001
L0042:	jmp     L0042

.endproc
