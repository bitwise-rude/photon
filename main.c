#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t u8 ;
typedef uint16_t u16 ;

typedef struct {
	u8 stream[1024];
} Memory;

typedef struct {
	u8 val; 
}REG8;

typedef union {
	REG8 hi;
	REG8 lo;
	u16 val;
}REG16;	

typedef struct {
	REG8 regA;
	REG8 regB;

	REG16 PC;
	REG16 SP;

	Memory* mem;
}Machine;

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
