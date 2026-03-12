#include <string.h>
#include "main.h"
#include "memory.h"
#include "ppu.h"

// Machine + CPU related function
u8 get_val_at_pc(Machine* vm) {
	// returns the value pointed by PC and increments the PC
	 return vm->mem->stream[vm->PC.val ++];
}
void execute(Machine* vm, u8 opcode);

int main()
{static u8 stream[] = {
    // --- 'B' ---
    0xa1, 0x00, 0xa2, 0x00, 0xd0, // B=0, C=0, PON
    0xa2, 0x01, 0xd0,             // C=1
    0xa2, 0x02, 0xd0,             // C=2
    0xa2, 0x03, 0xd0,             // C=3
    0xa2, 0x04, 0xd0,             // C=4
    0xa1, 0x01, 0xa2, 0x00, 0xd0, // B=1, C=0
    0xa2, 0x02, 0xd0,             // C=2
    0xa2, 0x04, 0xd0,             // C=4
    0xa1, 0x02, 0xa2, 0x01, 0xd0, // B=2, C=1
    0xa2, 0x03, 0xd0,             // C=3

    // --- 'i' ---
    0xa1, 0x04, 0xa2, 0x00, 0xd0, // B=4, C=0 (Dot)
    0xa2, 0x02, 0xd0,             // C=2 (Body)
    0xa2, 0x03, 0xd0,             // C=3
    0xa2, 0x04, 0xd0,             // C=4

    // --- 'm' ---
    0xa1, 0x06, 0xa2, 0x02, 0xd0, // B=6
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,
    0xa1, 0x07, 0xa2, 0x02, 0xd0, // B=7
    0xa1, 0x08, 0xa2, 0x02, 0xd0, // B=8
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,
    0xa1, 0x09, 0xa2, 0x02, 0xd0, // B=9
    0xa1, 0x0a, 0xa2, 0x02, 0xd0, // B=10
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,

    // --- 'a' ---
    0xa1, 0x12, 0xa2, 0x02, 0xd0, // B=12
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,
    0xa1, 0x13, 0xa2, 0x02, 0xd0, // B=13
    0xa2, 0x04, 0xd0,
    0xa1, 0x14, 0xa2, 0x02, 0xd0, // B=14
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,

    // --- 'l' ---
    0xa1, 0x16, 0xa2, 0x00, 0xd0, // B=16
    0xa2, 0x01, 0xd0,
    0xa2, 0x02, 0xd0,
    0xa2, 0x03, 0xd0,
    0xa2, 0x04, 0xd0,

    0xc2, 0x00, 0x00
};
	// creating the memory
// static u8 stream[65535] = { 
	// 0xa0,  0x1
	// 	,
	// 0xa1,  0x1
	// 	,
	// 0xa2,  0xa ,
	// 0x38,
	// 0x10,
	// 0x2A,
	// 0xfe,
	// 0xb2,
	// 0xc1,  0x00,  0x06,
	// 0xc2, 0x00, 0x00

// };

	/* Timer Test */
	// static u8 stream[65535] = {
	// 	0xa5, 0xFF,     // MVI H,FF
	// 	0xa6, 0x00,     // MVI L,00
	// 	0xa0, 0xFF,	// MVI A, FF
	// 	0x58,		// MOV M,A
	// 	0xBE,		// INC L
	// 	0x58,		// MOV M,A
	// 	0xA1, 0x0a,	// MVI B,10
	//
	// 	// loop_start (address 6)
	// 	0x27,		// MOV A,M
	// 	0xfe,		// PRINT
	// 	0x90, 		// CMP A,B
	// 	0xc1, 0x00,0x0b,// JNZ a       ; jump to loop_start
	// 	0x00 // EXITS
	// };

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
	init_memory();
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
		.frame_buffer = {0},
	};

	// temp graphics init
	graphics_init();
			
	// the fetch, decode and execute loop
	
	for (int i=0;i<=500000000000000;i++){
		// fetch
		u8 opcode = get_val_at_pc(&vm);
		DPRINTF("\nTHE OPCODE FETCHED IS 0x%x", opcode);
		execute(&vm, opcode);
		vm.cycles += 1;
		// TEMP framebuffer to screen
		// TODO: FPS
		
		// memory mappings to framebuffer
		// int pixel = 0;

		// for(u16 j = 0xFB00; j <= 0xFEFF; j++)
		// {
		// 	u8 byte = memory_read_8(vm.mem, j);
		//
		// 	for(int k = 0; k < 8; k++)
		// 	{
		// 		int x = pixel % 128;
		// 		int y = pixel / 128;
		//
		// 		if(y >= 64)
		// 		{
		// 			printf("Framebuffer overflow\n");
		// 			exit(1);
		// 		}
		//
		// 		vm.frame_buffer[y][x] = (byte >> k) & 1;
		//
		// 		pixel++;
		// 	}
		// }
		
		int shouldClose = show_buffer(vm.frame_buffer);
		if (shouldClose) {
			DPRINTF("USER CLOSED THE DISPLAY\n");
			break;
		}
		// printf("The value at regiser A is %x and B is %x\n",vm.AF.hi, vm.BC.hi);
	}

	return 0;
}

// entry point for esp
void app_main()
{
	main();
}

