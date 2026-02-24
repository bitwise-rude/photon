#include <string.h>
#include "main.h"

// Machine + CPU related function
u8 get_val_at_pc(Machine* vm) {
	// returns the value pointed by PC and increments the PC
	 return vm->mem->stream[vm->PC.val ++];
}

int main()
{
	// creating the memory
	u8 stream[1024] = {0xea, 0xea, 0x10};
	Memory mem = (Memory) {
		.stream = 0,
	};
	memcpy(mem.stream, stream, 1024);

	// creating the virtual machine
	Machine vm = (Machine) {
		.AF = {},
		.BC = {},
		.DE = {},
		.HL = {},

		.PC.val = 0,
		.SP.val = 0,

		.cycles=0,
		.mem = &mem,
	};
			
	// the fetch, decode and execute loop
	
	for (int i=0;i<9;i++) {
		// fetch
		u8 opcode = get_val_at_pc(&vm);

		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);

		vm.cycles += 1;
	}

	return 0;
}
