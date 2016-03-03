
.segment	"CODE"

.proc	_loadkey: near

.segment	"CODE"

	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     ___cbuff+3
	tax
L00B9:	lda     ___cbuff+3
	cmp     ___cbuff
	txa
	sbc     #$00
	bcs     L000E
	lda     $4016
	sta     ___cbuff + 5 ; REMOVE ME ;
	inc     ___cbuff+3
	jmp     L00B9
L000E:	rts

.endproc
