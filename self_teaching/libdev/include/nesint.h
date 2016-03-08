#ifndef _NESINT_H
#define _NESINT_H


/* integers types for NES */
typedef char                int8_t;
typedef unsigned char       uint8_t;
typedef int                 int16_t;
typedef unsigned int        uint16_t;

#define INT8_MIN            ((int8_t) 0x80)
#define INT8_MAX            ((int8_t) 0x7F)
#define UINT8_MAX           ((uint8_t) 0xFF)
#define UINT16_MAX          ((uint16_t) 0xFFFF)
#define INT16_MIN           ((int16_t) 0x8000)
#define INT16_MAX           ((int16_t) 0x7FFF)

#define MAX(x, y)           ( x > y ? x : y)
#define MIN(x, y)           ( x < y ? y : x)


/* boolean */
typedef uint8_t bool;
#define true  1
#define false 0


#endif



