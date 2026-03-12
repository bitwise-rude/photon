#include "main.h"
#include "timer.h"
// Memory Mappings explained in `instructions` 

#define TIMER_CTRL 0xFF00
#define TIMER_VAL 0xFF01

/* 
 * Program ROM = Single Dimensional Array in both ESP and PC port
 */

void init_memory() {
	// Initializes memory and all the mappings
	timer_init();
}
u8 memory_read_8(Memory* mem, u16 addr){
	DPRINTF("[MEMORY READ AT %.04x]", addr);

	if (addr <= 0xFEFF) return mem->stream[addr];
	
	else if (addr==TIMER_VAL){
		return timer_val_read();
	}
	else {
		printf("[MEMORY READ AT UNIMPLEMENTED SECTION %.04x ]", addr);
		exit(0);
	}
}

void memory_write_8(Memory* mem, u16 addr, u8 val){
	DPRINTF("[MEMORY WRITE AT %.04x WITH VALUE %.02x]\n", addr, val);

	if (addr <= 0xFEFF) mem->stream[addr] = val;
	

	else if (addr == TIMER_CTRL)
	{
		// timer control
		timer_control_write(val);
	} else if (addr==TIMER_VAL){
		timer_val_write(val);
	} else {
		printf("[MEMORY WRITE AT UNIMPLEMENTED SECTION %.04x WITH DATA %.02x]\n", addr, val);
		exit(0);
	}

}
