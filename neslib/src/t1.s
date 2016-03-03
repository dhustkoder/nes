
.segment	"CODE"

.proc	_loadkey: near

.segment	"CODE"

	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L00B6:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L000E
	lda     $4016
	jsr     pusha
	jsr     incsp1
	inc     ___cbuff+3
	jmp     L00B6
L000E:	rts

.endproc

