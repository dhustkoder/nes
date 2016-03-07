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
	.import		__write_val
	.import		__ppu_set_cursor_exact
	.importzp	_joypads
	.import		_update_pad1
	.export		_main

.segment	"RODATA"

_alreadyPrinted:
	.byte	$00
_words:
	.addr	L0007
	.addr	L0009
	.addr	L000B
	.addr	L000D
	.addr	L000F
	.addr	L0011
	.addr	L0013
	.addr	L0015
	.addr	L0017
	.addr	L0019
L003F:
	.byte	$2A,$2A,$48,$45,$4C,$4C,$4F,$20,$43,$4E,$45,$53,$4C,$49,$42,$21
	.byte	$2A,$2A,$00
L0095:
	.byte	$55,$4E,$44,$45,$46,$49,$4E,$45,$44,$00
L0009:
	.byte	$20,$50,$52,$45,$53,$53,$45,$44,$00
L000F:
	.byte	$53,$45,$4C,$45,$43,$54,$00
L0011:
	.byte	$53,$54,$41,$52,$54,$00
L0019:
	.byte	$52,$49,$47,$48,$54,$00
L0015:
	.byte	$44,$4F,$57,$4E,$00
L0017:
	.byte	$4C,$45,$46,$54,$00
L0007:
	.byte	$4B,$45,$59,$20,$00
L0013:
	.byte	$55,$50,$00
L000B:
	.byte	$41,$00
L000D:
	.byte	$42,$00

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; waitvblank();
;
	jsr     _waitvblank
;
; PPU_SET_COLOR_BACK(BLUE);
;
	lda     #$3F
	sta     $2006
	lda     #$00
	sta     $2006
	lda     #$01
	sta     $2007
;
; PPU_SET_COLOR_TEXT(WHITE);
;
	lda     #$3F
	sta     $2006
	lda     #$03
	sta     $2006
	lda     #$20
	sta     $2007
;
; ppu_set_cursor_exact(1,1);
;
	tax
	lda     #$21
	jsr     __ppu_set_cursor_exact
;
; write_str("**HELLO CNESLIB!**");
;
	lda     #<(L003F)
	ldx     #>(L003F)
L00A0:	jsr     _write_str
;
; ppu_set_scroll_enable_render(0x0000);
;
	ldx     #$00
	txa
	jsr     _ppu_set_scroll_enable_render
;
; update_pad1();
;
L0049:	jsr     _update_pad1
;
; while(JOYPAD1 == KEY_NULL)
;
	lda     _joypads
	beq     L0049
;
; waitvblank();
;
	jsr     _waitvblank
;
; ppu_set_cursor_exact(1,2);
;
	ldx     #$20
	lda     #$41
	jsr     __ppu_set_cursor_exact
;
; ppu_write_rval('\0', 22);  /* erase */
;
	lda     #$00
	ldx     #$16
	jsr     __write_val
;
; ppu_set_cursor_exact(1,2);
;
	ldx     #$20
	lda     #$41
	jsr     __ppu_set_cursor_exact
;
; write_str(words[WKey]);    /* write KEY */
;
	lda     _words
	ldx     _words+1
	jsr     _write_str
;
; switch(JOYPAD1)
;
	lda     _joypads
;
; }
;
	cmp     #$01
	beq     L006C
	cmp     #$02
	beq     L0071
	cmp     #$04
	beq     L0076
	cmp     #$08
	beq     L007B
	cmp     #$10
	beq     L0080
	cmp     #$20
	beq     L0085
	cmp     #$40
	beq     L008A
	cmp     #$80
	beq     L008F
	jmp     L0093
;
; case KEY_A:      write_str(words[WA]);      break;
;
L006C:	lda     _words+4
	ldx     _words+4+1
	jmp     L009C
;
; case KEY_B:      write_str(words[WB]);      break;
;
L0071:	lda     _words+6
	ldx     _words+6+1
	jmp     L009C
;
; case KEY_SELECT: write_str(words[WSelect]); break;
;
L0076:	lda     _words+8
	ldx     _words+8+1
	jmp     L009C
;
; case KEY_START:  write_str(words[WStart]);  break;
;
L007B:	lda     _words+10
	ldx     _words+10+1
	jmp     L009C
;
; case KEY_UP:     write_str(words[WUp]);     break;
;
L0080:	lda     _words+12
	ldx     _words+12+1
	jmp     L009C
;
; case KEY_DOWN:   write_str(words[WDown]);   break;
;
L0085:	lda     _words+14
	ldx     _words+14+1
	jmp     L009C
;
; case KEY_LEFT:   write_str(words[WLeft]);   break;
;
L008A:	lda     _words+16
	ldx     _words+16+1
	jmp     L009C
;
; case KEY_RIGHT:  write_str(words[WRight]);  break;
;
L008F:	lda     _words+18
	ldx     _words+18+1
	jmp     L009C
;
; default:         write_str("UNDEFINED");    break;
;
L0093:	lda     #<(L0095)
	ldx     #>(L0095)
L009C:	jsr     _write_str
;
; write_str(words[WPressed]); /* write PRESSED */
;
	lda     _words+2
	ldx     _words+2+1
;
; while(true)
;
	jmp     L00A0

.endproc

