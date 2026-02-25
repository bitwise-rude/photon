#pragma once
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16 ;

typedef struct {
	u8 stream[65535];
} Memory;


u8 memory_read_8(Memory* mem, u16 addr);
void memory_write_8(Memory* mem, u16 addr, u8 val);
