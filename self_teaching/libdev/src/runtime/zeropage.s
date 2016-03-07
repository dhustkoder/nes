.include "../inc/zeropage.inc"

; ------------------------------------------------------------------------

.segment "ZEROPAGE"

sp:             .res    2       ; Stack pointer
sreg:           .res    2       ; Secondary register/high 16 bit for longs
regsave:        .res    4       ; Slot to save/restore (E)AX into
ptr1:           .res    2
ptr2:           .res    2
ptr3:           .res    2
ptr4:           .res    2
tmp1:           .res    1
tmp2:           .res    1
tmp3:           .res    1
tmp4:           .res    1
_u8_arg:        .res 	1
_u16_arg:       .res    2 
regbank:        .res    regbanksize     ; Register bank
