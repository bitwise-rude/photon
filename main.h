#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define get_nibble_hi(val) ((val & 0b11110000) >> 4)
#define get_nibble_lo(val) (val & 0b00001111)

// Uncomment the below line when in production
// #define NDEBUG 

#ifndef NDEBUG
    #define DPRINTF(fmt, ...) \
        fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else
    #define DPRINTF(fmt, ...)
#endif

typedef uint8_t u8 ;
typedef uint16_t u16 ;

typedef struct {
	u8 stream[1024];
} Memory;


typedef union {
	struct {
		u8 hi;
		u8 lo;
	};
	u16 val;
}REG16;	

typedef struct {
	REG16 AF;
	REG16 BC;
	REG16 DE;
	REG16 HL;

	REG16 PC;
	REG16 SP;

	size_t cycles;

	Memory* mem;
}Machine;

