#ifndef __JOYPADS_H__
#define __JOYPADS_H__
#include "nesint.h"

#define KEY_NULL     0x00
#define KEY_A        0x01
#define KEY_B        0x02
#define KEY_SELECT   0x04
#define KEY_START    0x08
#define KEY_UP       0x10
#define KEY_DOWN     0x20
#define KEY_LEFT     0x40
#define KEY_RIGHT    0x80


extern uint8_t joypads[2];
#pragma zpsym("joypads");

extern void __fastcall__ update_pad1(void);
extern void __fastcall__ update_pad2(void);

#define JOYPAD1 (joypads[0])
#define JOYPAD2 (joypads[1])

#define IS_KEY_DOWN(pad, key) (((pad & key) != 0))
#define IS_KEY_UP(pad, key)   (((pad & key) == 0))

#endif