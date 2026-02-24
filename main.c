#include <stdio.h>
#include <stdlib.h>
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
		.regA = {0},
		.regB = {0},
		.regC = {0},
		.regD = {0},
		.regH = {0},
		.regL = {0},
		.regF = {0},

		.PC.val = 0,
		.SP.val = 0,

		.cycles=0,
		.mem = &mem,
	};
			
	// the fetch, decode and execute loop
	
	for (int i=0;i<9;i++) {
		// fetch
		u8 opcode = get_val_at_pc(&vm);

		u8 opcode_hi = get_nibble_hi(opcode);
		u8 opcode_lo = get_nibble_lo(opcode);

		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);

		// executing register based instructions
		switch (opcode_hi) {
			case 0x1:
				DPRINTF("ADD Instruction Executed");
				break;
			default:
				break;
				
		}

		// executing other single byte opcode instructions
		switch (opcode) {
			case 0xEA:
				DPRINTF("NOP EXECUTED");
				break;
			default:
				printf("INSTRUCTION NOT IMPLEMENTED\n");
				exit(69);
				break;
		}

		vm.cycles += 1;
	}

	return 0;
}
