#ifndef _NESLIB_H_
#define _NESLIB_H_

#include "nesint.h"
#include "ppu.h"

#define poke (addr, data) ((*(uint8_t*)addr) = data)

/* Write to APU_STATUS register: */
#define apu_status(c)           poke(APU_STATUS, (c))

/* Write to one of the APU pulse registers.
 * Parameter 'ch' is the channel (pulse channel 0 or 1),
 * 'r' is the register (0-4), and 'c' is the data to write. */
#define apu_pulse(ch, r, c)     poke(APU_PULSE+((ch)<<2)+(r), (c))










 










#endif
