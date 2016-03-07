#ifndef _NESLIB_H_
#define _NESLIB_H_
/* note: _REMOVE in assembly inline is a way to prevent earlier inline assembly from being remove 
 * these instructions with _REMOVE should be removed from the .s file for a better yet perfomance 
 * you can come up with a shell function which compile and remove the _REMOVE lines with grep -v
 * any way, check the code for these _REMOVE lines 
 */


#include "nesint.h"
#include "ppu.h"
#include "joypads.h"



/* zero page u8 and u16 , use these variables 
 * instead of functions parameters whenever possible 
 * this will minimize the overhead from stack pushing
 * and poping, also as zeropage variables are faster
 */
extern uint8_t u8_arg;
extern uint16_t u16_arg;
#pragma zpsym ("u8_arg");
#pragma zpsym ("u16_arg");








 










#endif
