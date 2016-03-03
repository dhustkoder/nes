

.segment "CHARS"
    ;.incbin "chr.bin" ; if you have one
.segment "HEADER"
    .byte "NES",26,2,1 ; 32K PRG, 8K CHR
.segment "VECTORS"
    .word 0, 0, 0, nmi, reset, irq

.segment "STARTUP" ; avoids warning


.segment "CODE"








.segment "CODE"

nmi:
irq:
reset:
    lda #$01 ; play short tone
    sta $4015
    lda #$9F
    sta $4000
    lda #$22
    sta $4003
forever:
    jmp forever