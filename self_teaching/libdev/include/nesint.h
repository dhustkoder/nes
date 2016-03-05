#ifndef _NESINT_H
#define _NESINT_H


/* integers for NES */
typedef signed char         int8_t;
typedef int                 int16_t;
typedef unsigned char       uint8_t;
typedef unsigned            uint16_t;

#define INT8_MIN            ((int8_t) 0x80)
#define INT8_MAX            ((int8_t) 0x7F)
#define INT16_MIN           ((int16_t) 0x8000)
#define INT16_MAX           ((int16_t) 0x7FFF)
#define UINT8_MAX           ((uint8_t) 0xFF)
#define UINT16_MAX          ((uint16_t) 0xFFFF)


#endif



