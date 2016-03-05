.include "nes.inc"
.export _waitvblank

.proc   _waitvblank

wait:   lda     PPU_STATUS
        bpl     wait
        rts

.endproc