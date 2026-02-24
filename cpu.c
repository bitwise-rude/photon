// executing single byte opcode instructions
#include "main.h"

#define FLAG_Z 0
#define FLAG_C 1

u8 get_flag(Machine *vm, u8 flag){
	return 	((vm -> AF.lo) >> (7 - flag)) & 1 ;
}

// TODO: Might Fail
void set_flag (Machine *vm, u8 flag) {
	u8 old = vm -> AF.lo;
	vm -> AF.lo = old | (1 << (7 - flag));
}

void reset_flag (Machine *vm, u8 flag) {
	u8 old = vm -> AF.lo;
	vm -> AF.lo = old & ~(1 << (7 - flag));
}

void execute(u8 opcode, Machine* vm) {
	switch (opcode) {
		// Movs
		case 0x20:
			DPRINTF("MOV A,B");
			vm->AF.hi = vm->BC.hi;
			break;

		case 0x21:
			DPRINTF("MOV A,C");
			vm->AF.hi = vm->BC.lo;
			break;

		case 0x22:
			DPRINTF("MOV A,D");
			vm->AF.hi = vm->DE.hi;
			break;

		case 0x23:
			DPRINTF("MOV A,E");
			vm->AF.hi = vm->DE.lo;
			break;

		case 0x24:
			DPRINTF("MOV A,H");
			vm->AF.hi = vm->HL.hi;
			break;

		case 0x25:
			DPRINTF("MOV A,L");
			vm->AF.hi = vm->HL.lo;
			break;

		case 0x26:
			DPRINTF("MOV A,F");
			vm->AF.hi = vm->AF.lo;
			break;

		case 0x27:
			DPRINTF("MOV A,M");
			vm->AF.hi = vm->AF.lo; // TODO: IMplement
			break;

		case 0x28:
			DPRINTF("MOV B,A");
			vm->BC.hi = vm->AF.hi;
			break;

		case 0x29:
			DPRINTF("MOV B,C");
			vm->BC.hi = vm->BC.lo;
			break;

		case 0x2A:
			DPRINTF("MOV B,D");
			vm->BC.hi = vm->DE.hi;
			break;

		case 0x2B:
			DPRINTF("MOV B,E");
			vm->BC.hi = vm->DE.lo;
			break;

		case 0x2C:
			DPRINTF("MOV B,H");
			vm->BC.hi = vm->HL.hi;
			break;

		case 0x2D:
			DPRINTF("MOV B, L");
			vm->BC.hi = vm->HL.lo;
			break;

		case 0x2E:
			DPRINTF("ADD A, F");
			vm->BC.hi = vm->AF.lo;
			break;

		case 0x2F:
			DPRINTF("MOV B,M");
			vm->BC.hi = vm->AF.lo; // TODO: IMplement
			break;

			// Adds
		case 0x10:
			DPRINTF("ADD A, B");
			vm->AF.hi += vm->BC.hi;
			break;

		case 0x11:
			DPRINTF("ADD A, C");
			vm->AF.hi += vm->BC.lo;
			break;

		case 0x12:
			DPRINTF("ADD A, D");
			vm->AF.hi += vm->DE.hi;
			break;

		case 0x13:
			DPRINTF("ADD A, E");
			vm->AF.hi += vm->DE.lo;
			break;

		case 0x14:
			DPRINTF("ADD A, H");
			vm->AF.hi += vm->HL.hi;
			break;

		case 0x15:
			DPRINTF("ADD A, L");
			vm->AF.hi += vm->HL.lo;
			break;

		case 0x16:
			DPRINTF("ADD A, F");
			vm->AF.hi += vm->AF.lo;
			break;

		// SUBS
		case 0x30:
			DPRINTF("SUB A, B");
			vm->AF.hi -= vm->BC.hi;
			if (vm -> AF.hi < vm -> BC.hi) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm -> BC.hi) { 
				set_flag(vm, FLAG_Z);
			}
			break;
		
		// CMPS
		case 0x40:
			DPRINTF("CMP A, B");
			
			if (vm -> AF.hi < vm -> BC.hi) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> BC.hi){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;
	
		case 0xA0:
			DPRINTF("JZ addr");
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
}
