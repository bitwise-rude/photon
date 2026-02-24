#include <stdint.h>

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
	REG8 regA;
	REG8 regB;

	REG16 PC;
	REG16 SP;

	Memory* mem;
}Machine;

