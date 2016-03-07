#ifndef _NESLIB_H_
#define _NESLIB_H_
/* note: _REMOVE in assembly inline is a way to prevent earlier inline assembly from being remove 
 * these instructions with _REMOVE should be removed from the .s file for a better yet perfomance 
 * I'll come up with a shell function which compile and remove the _REMOVE lines with grep -v 
 */



#include "nesint.h"
#include "ppu.h"
#include "joypads.h"


extern uint8_t u8_arg;
extern uint16_t u16_arg;
#pragma zpsym ("u8_arg");
#pragma zpsym ("u16_arg");








 










#endif
