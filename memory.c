#include "memory.h"

/* 
 * Memory.h includes Memory Mappings to several controllers and timers, screen, etc.
 * Memory shouldn't be accessed through other means expect the following two methods
 * Memory mappings are (or will be) done in two functions listed below.
 *
 * Below are the mappings:
 *
 *            Memory Address             |         Mappings
 *
 * 	     0x0000 - 0xFFFF                     Program ROM 
 */

/* 
 * Program ROM = Single Dimensional Array in both ESP and PC port
 */

u8 memory_read_8(Memory* mem, u16 addr){
	 return mem->stream[addr];
}

void memory_write_8(Memory* mem, u16 addr, u8 val){
	 mem->stream[addr] = val;
}
