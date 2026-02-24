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

		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);

		// executing single byte opcode instructions
		switch (opcode) {
			// Movs
			case 0x20:
				DPRINTF("MOV A,B");
				vm.AF.hi = vm.BC.hi;
				break;

			case 0x21:
				DPRINTF("MOV A,C");
				vm.AF.hi = vm.BC.lo;
				break;

			case 0x22:
				DPRINTF("MOV A,D");
				vm.AF.hi = vm.DE.hi;
				break;

			case 0x23:
				DPRINTF("MOV A,E");
				vm.AF.hi = vm.DE.lo;
				break;

			case 0x24:
				DPRINTF("MOV A,F");
				vm.AF.hi = vm.AF.lo;
				break;

			case 0x25:
				DPRINTF("MOV B,A");
				vm.BC.hi = vm.AF.hi;
				break;

			case 0x26:
				DPRINTF("MOV B,C");
				vm.BC.hi = vm.BC.lo;
				break;
				
			case 0x27:
				DPRINTF("MOV B,D");
				vm.BC.hi = vm.DE.hi;
				break;

			case 0x28:
				DPRINTF("MOV B,E");
				vm.BC.hi = vm.DE.lo;
				break;

			case 0x29:
				DPRINTF("MOV B,H");
				vm.BC.hi = vm.HL.hi;
				break;

			case 0x30:
				DPRINTF("MOV B, L");
				vm.BC.hi = vm.HL.lo;
				break;

			case 0x31:
				DPRINTF("ADD A, F");
				vm.BC.hi = vm.AF.lo;
				break;

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
				DPRINTF("ADD A, H");
				vm.AF.hi += vm.HL.hi;
				break;

			case 0x15:
				DPRINTF("ADD A, L");
				vm.AF.hi += vm.HL.lo;
				break;

			case 0x16:
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
