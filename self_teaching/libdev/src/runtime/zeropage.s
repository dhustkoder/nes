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
_joypads:       .res    2       ; NES joypads states -> extern uint8_t joypads[2]
_u8_arg:        .res 	1       ; u8 arg temp for c code
_u16_arg:       .res    2       ; u16 arg temp for c code
regbank:        .res    regbanksize     ; Register bank
