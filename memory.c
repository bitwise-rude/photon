#include "memory.h"

u8 memory_read_8(Memory* mem, u16 addr){
	 return mem->stream[addr];
}

void memory_write_8(Memory* mem, u16 addr, u8 val){
	 mem->stream[addr] = val;
}
