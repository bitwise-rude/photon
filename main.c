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
	u8 stream[1024] = {0xea, 0xea, 0xea};
	Memory mem = (Memory) {
		.stream = 0,
	};
	memcpy(mem.stream, stream, 1024);

	// creating the virtual machine
	Machine vm = (Machine) {
		.regA = {0},
		.regB = {0},
		.PC.val = 0,
		.mem = &mem,
	};
			
	// the fetch, decode and execute loop
	
	for (int i=0;i<9;i++) {
		// fetch
		u8 opcode = get_val_at_pc(&vm);
		printf("\nThe OPCODE Fetched is 0x%x\n", opcode);

		// execute
		switch (opcode) {
			case 0xEA:
				printf("NOP EXECUTED\n");
				break;
			default:
				printf("INSTRUCTION NOT IMPLEMENTED\n");
				exit(69);
				break;
		}
	}

	return 0;
}
