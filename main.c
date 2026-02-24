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

		u8 opcode_hi = get_nibble_hi(opcode);
		u8 opcode_lo = get_nibble_lo(opcode);

		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);

		// executing single byte opcode instructions
		switch (opcode) {
			// Movs
			case 0x20:
				DPRINTF("MOV A,B");

			// Adds
			case 0x10:
				DPRINTF("ADD A, B");
				vm.AF.hi += vm.BC.hi;
				break;

			case 0x11:
				DPRINTF("ADD A, C");
				vm.AF.hi += vm.BC.lo;
				break;

			case 0x12:
				DPRINTF("ADD A, D");
				vm.AF.hi += vm.DE.hi;
				break;

			case 0x13:
				DPRINTF("ADD A, E");
				vm.AF.hi += vm.DE.lo;
				break;

			case 0x14:
				DPRINTF("ADD A, F");
				vm.AF.hi += vm.AF.lo;
				break;

			// NOPS
			case 0xEA:
				DPRINTF("NOP");
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
