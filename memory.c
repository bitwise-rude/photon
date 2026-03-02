#include "memory.h"

// Memory Mappings explained in `instructions` 

/* 
 * Program ROM = Single Dimensional Array in both ESP and PC port
 */

u8 memory_read_8(Memory* mem, u16 addr){
	if (addr >= 0x0000 && addr <= 0xFEFF) return mem->stream[addr];
	else {
		printf("[MEMORY READ AT UNIMPLEMENTED SECTION %.04x ]", addr);
		exit(0);
	}
}

void memory_write_8(Memory* mem, u16 addr, u8 val){
	if (addr >= 0x0000 && addr <= 0xFEFF) mem->stream[addr] = val;
	else {
		printf("[MEMORY WRITE AT UNIMPLEMENTED SECTION %.04x WITH DATA %.02x]", addr, val);
		exit(0);
	}
}
