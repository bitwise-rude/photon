#include <string.h>
#include "main.h"

// Machine + CPU related function
u8 get_val_at_pc(Machine* vm) {
	// returns the value pointed by PC and increments the PC
	 return vm->mem->stream[vm->PC.val ++];
}
void execute(Machine* vm, u8 opcode);

int main()
{
	// creating the memory
	u8 stream[65535] = {
		0xa0, 0x00,      // MVI A,0
		0xa1, 0x01,      // MVI B,1
		0xa2, 0x0A,      // MVI C,10   ; loop counter = 10

		// loop_start (address 6)
		0x38,		 // MOV D,A
		0x10,            // ADD A,B    ; A = A+B
		0x2A,		// MOV B,D
		0xb2, 		// DEC C
		0xfe,			// PRINT
		0xc1, 0x00,0x06,       // JNZ 6       ; jump to loop_start
		0x00 // EXITS
	};
	Memory mem = (Memory) {
		.stream = 0,
	};
	memcpy(mem.stream, stream, 65535);

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
	
	for (int i=0;i<99;i++) {
		// fetch
		u8 opcode = get_val_at_pc(&vm);

		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);
		execute(&vm, opcode);
		vm.cycles += 1;
		// printf("The value at regiser A is %x and B is %x\n",vm.AF.hi, vm.BC.hi);
	}

	return 0;
}
