; Assembler include file that imports the runtime zero page locations used
; by the compiler, ready for usage in asm code.


        .globalzp       sp, sreg, regsave
        .globalzp       ptr1, ptr2, ptr3, ptr4
        .globalzp       tmp1, tmp2, tmp3, tmp4
        .globalzp       regbank
        .globalzp       _joypads                ; NES joypads
        .globalzp 		_u8_arg, _u16_arg       ; used for C code arguments
  
; The size of the register bank
regbanksize     = 6

; The total amount of zero page space used
zpspace         = 31

; The amount of space that needs to be saved by an interrupt handler that
; calls C code (does not include the register bank, which is saved by the
; generated C code if required).
zpsavespace     = zpspace - regbanksize

