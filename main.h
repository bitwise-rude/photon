#include <stdint.h>

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

typedef struct {
	u8 val; 
}REG8;

typedef union {
	REG8 hi;
	REG8 lo;
	u16 val;
}REG16;	

typedef struct {
	REG8 regA; // Accumulator
	REG8 regB;
	REG8 regC;
	REG8 regD;
	REG8 regH;
	REG8 regL;
	REG8 regF; // Flag Register

	REG16 PC;
	REG16 SP;

	size_t cycles;

	Memory* mem;
}Machine;

