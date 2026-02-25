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
	
	/* Fibonacci sequence */
	static u8 stream[65535] = {
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

	// u8 stream[65535] = {
	//
	// 	0xA0, 0x01,        // A = 1  (result = 1)
	// 	0xA1, 0x05,        // B = 5  (number to factorial)
	//
	// 	// ---- OUTER LOOP START (address 4) ----
	//
	// 	0xA2, 0x00,        // C = 0 (clear C)
	// 	0x38,              // D = A (save current result)
	// 	0xA2, 0x00,        // C = B (inner counter = B)
	// 	0x20,              // A = 0 (reset result to 0 before multiply)
	//
	// 	// ---- INNER LOOP START (address 10) ----
	// 	0x10,              // A = A + D  (add saved result)
	// 	0xB2,              // DEC C
	// 	0xC1, 0x00, 0x0A,  // JNZ 10 (repeat inner loop)
	//
	// 	0xB1,              // DEC B (outer counter--)
	// 	0xC1, 0x00, 0x04,  // JNZ 4 (repeat outer loop)
	//
	// 	0xFE,              // PRINT result
	// 	0x00               // EXIT
	// };
	
	static Memory mem;
	memcpy(mem.stream, stream, sizeof(stream));

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

// entry point for esp
void app_main()
{
	main();
}

