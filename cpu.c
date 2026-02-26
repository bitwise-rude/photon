// executing single byte opcode instructions
#include "main.h"
#include "memory.h"

#define FLAG_Z 0
#define FLAG_C 1

#define combine_bytes(hi, lo) (hi << 8) | lo

static inline u8 get_pc_8(Machine* vm) {
	// returns the 8bit value pointed by PC and increments the PC
	 return memory_read_8(vm->mem,vm->PC.val++);
}

static inline u16 get_pc_16(Machine* vm) {
	// returns the simultaneous 16 bit value pointed by PC and increments the PC twice
	u8 hi = memory_read_8(vm->mem, vm->PC.val ++);
	u8 lo = memory_read_8(vm->mem, vm->PC.val ++);

	return combine_bytes(hi,lo);
}

static inline u8 get_flag(Machine *vm, u8 flag){
	return 	((vm -> AF.lo) >> (7 - flag)) & 1 ;
}

static inline void set_flag (Machine *vm, u8 flag) {
	u8 old = vm -> AF.lo;
	vm -> AF.lo = old | (1 << (7 - flag));
}

static inline void reset_flag (Machine *vm, u8 flag) {
	u8 old = vm -> AF.lo;
	vm -> AF.lo = old & ~(1 << (7 - flag));
}

void execute(Machine* vm, u8 opcode ) {
	switch (opcode) {
		// Decs
		case 0xb0:
			DPRINTF("DEC A");
			vm->AF.lo --;
			break;

		case 0xb2:
			DPRINTF("DEC C");
			vm->BC.lo --;
			break;

		case 0xb1:
			DPRINTF("DEC B");
			vm->BC.hi --;
			break;

		case 0xb3:
			DPRINTF("DEC D");
			vm->DE.hi --;
			break;

		case 0xb4:
			DPRINTF("DEC E");
			vm->DE.lo --;
			break;

		case 0xb5:
			DPRINTF("DEC H");
			vm->HL.hi --;
			break;

		case 0xb6:
			DPRINTF("DEC L");
			vm->HL.lo --;
			break;

		case 0xb7:
			DPRINTF("DEC M");
			u8 val = memory_read_8(vm->mem, vm->HL.val);
			memory_write_8(vm->mem, vm->HL.val, val-1);
			break;

		// INCS
		case 0xb8:
			DPRINTF("INC A");
			vm->AF.lo ++;
			break;

		case 0xba:
			DPRINTF("INC C");
			vm->BC.lo ++;
			break;

		case 0xb9:
			DPRINTF("INC B");
			vm->BC.hi ++;
			break;

		case 0xbb:
			DPRINTF("INC D");
			vm->DE.hi ++;
			break;

		case 0xbc:
			DPRINTF("INC E");
			vm->DE.lo ++;
			break;

		case 0xbd:
			DPRINTF("INC H");
			vm->HL.hi ++;
			break;

		case 0xbe:
			DPRINTF("INC L");
			vm->HL.lo ++;
			break;

		case 0xbf:
			DPRINTF("INC M");
			u8 val2 = memory_read_8(vm->mem, vm->HL.val);
			memory_write_8(vm->mem, vm->HL.val, val2+1);
			break;
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
			vm->AF.hi = memory_read_8(vm->mem,vm->HL.val);
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
			DPRINTF("MOV B, F");
			vm->BC.hi = vm->AF.lo;
			break;

		case 0x2F:
			DPRINTF("MOV B, M"); 
			vm->BC.hi = memory_read_8(vm->mem,vm->HL.val);
			break;

		case 0x30:
			DPRINTF("MOV C,A");
			vm->BC.lo = vm->AF.hi;
			break;

		case 0x31:
			DPRINTF("MOV C,B");
			vm->BC.lo = vm->BC.lo;
			break;

		case 0x32:
			DPRINTF("MOV C,D");
			vm->BC.lo = vm->DE.hi;
			break;

		case 0x33:
			DPRINTF("MOV C,E");
			vm->BC.lo = vm->DE.lo;
			break;

		case 0x34:
			DPRINTF("MOV C,H");
			vm->BC.lo = vm->HL.hi;
			break;

		case 0x35:
			DPRINTF("MOV C, L");
			vm->BC.lo = vm->HL.lo;
			break;

		case 0x36:
			DPRINTF("MOV C, F");
			vm->BC.lo = vm->AF.lo;
			break;

		case 0x37:
			DPRINTF("MOV C, M"); 
			vm->BC.lo = memory_read_8(vm->mem,vm->HL.val);
			break;

		case 0x38:
			DPRINTF("MOV D,A");
			vm->DE.hi = vm->AF.hi;
			break;

		case 0x39:
			DPRINTF("MOV D,B");
			vm->DE.hi = vm->BC.lo;
			break;

		case 0x3a:
			DPRINTF("MOV D,C");
			vm->DE.hi = vm->DE.hi;
			break;

		case 0x3b:
			DPRINTF("MOV D,E");
			vm->DE.hi = vm->DE.lo;
			break;

		case 0x3c:
			DPRINTF("MOV D,H");
			vm->DE.hi = vm->HL.hi;
			break;

		case 0x3d:
			DPRINTF("MOV D, L");
			vm->DE.hi = vm->HL.lo;
			break;

		case 0x3e:
			DPRINTF("MOV D, F");
			vm->DE.hi = vm->AF.lo;
			break;

		case 0x3f:
			vm->DE.hi = memory_read_8(vm->mem,vm->HL.val);
			DPRINTF("MOV D, M"); 
			break;

		case 0x40:
			DPRINTF("MOV E,A");
			vm->DE.lo = vm->AF.hi;
			break;

		case 0x41:
			DPRINTF("MOV E,B");
			vm->DE.lo = vm->BC.lo;
			break;

		case 0x42:
			DPRINTF("MOV E,C");
			vm->DE.lo = vm->DE.hi;
			break;

		case 0x43:
			DPRINTF("MOV E,D");
			vm->DE.lo = vm->DE.hi;
			break;

		case 0x44:
			DPRINTF("MOV E,H");
			vm->DE.lo = vm->HL.hi;
			break;

		case 0x45:
			DPRINTF("MOV E, L");
			vm->DE.lo = vm->HL.lo;
			break;

		case 0x46:
			DPRINTF("MOV E, F");
			vm->DE.lo = vm->AF.lo;
			break;

		case 0x47:
			vm->DE.lo = memory_read_8(vm->mem,vm->HL.val);
			DPRINTF("MOV E, M"); 
			break;

		case 0x48:
			DPRINTF("MOV H,A");
			vm->HL.hi = vm->AF.hi;
			break;

		case 0x49:
			DPRINTF("MOV H,B");
			vm->HL.hi = vm->BC.lo;
			break;

		case 0x4a:
			DPRINTF("MOV H,C");
			vm->HL.hi = vm->DE.hi;
			break;

		case 0x4b:
			DPRINTF("MOV H,D");
			vm->HL.hi = vm->DE.hi;
			break;

		case 0x4c:
			DPRINTF("MOV H,E");
			vm->HL.hi = vm->DE.lo;
			break;

		case 0x4d:
			DPRINTF("MOV H, L");
			vm->HL.hi = vm->HL.lo;
			break;

		case 0x4e:
			DPRINTF("MOV H, F");
			vm->HL.hi = vm->AF.lo;
			break;

		case 0x4f:
			vm->HL.hi = memory_read_8(vm->mem,vm->HL.val);
			DPRINTF("MOV H, M"); 
			break;

		case 0x50:
			DPRINTF("MOV L,A");
			vm->HL.lo = vm->AF.hi;
			break;

		case 0x51:
			DPRINTF("MOV L,B");
			vm->HL.lo = vm->BC.lo;
			break;

		case 0x52:
			DPRINTF("MOV L,C");
			vm->HL.lo = vm->DE.hi;
			break;

		case 0x53:
			DPRINTF("MOV L,D");
			vm->HL.lo = vm->DE.hi;
			break;

		case 0x54:
			DPRINTF("MOV L,E");
			vm->HL.lo = vm->DE.lo;
			break;

		case 0x55:
			DPRINTF("MOV L,H");
			vm->HL.lo = vm->HL.lo;
			break;

		case 0x56:
			DPRINTF("MOV L,F");
			vm->HL.lo = vm->AF.lo;
			break;

		case 0x57:
			vm->HL.lo = memory_read_8(vm->mem,vm->HL.val);
			DPRINTF("MOV L,M"); 
			break;

		case 0x58:
			DPRINTF("MOV M,A");
			memory_write_8(vm->mem,vm->HL.val, vm->AF.hi);
			break;

		case 0x59:
			DPRINTF("MOV M,B");
			memory_write_8(vm->mem,vm->HL.val, vm->BC.lo);
			break;

		case 0x5a:
			DPRINTF("MOV M,C");
			memory_write_8(vm->mem,vm->HL.val, vm->DE.hi);
			break;

		case 0x5b:
			DPRINTF("MOV M,D");
			memory_write_8(vm->mem,vm->HL.val, vm->DE.hi);
			break;

		case 0x5c:
			DPRINTF("MOV M,E");
			memory_write_8(vm->mem,vm->HL.val, vm->DE.lo);
			break;

		case 0x5d:
			DPRINTF("MOV M,H");
			memory_write_8(vm->mem,vm->HL.val, vm->HL.lo);
			break;

		case 0x5e:
			DPRINTF("MOV M,L");
			memory_write_8(vm->mem,vm->HL.val, vm->HL.lo);
			break;

		case 0x5f:
			memory_write_8(vm->mem,vm->HL.val, vm->AF.lo);
			DPRINTF("MOV M,L");
			break;

		case 0xa0:
			DPRINTF("MVI A, im");
			vm->AF.hi = get_pc_8(vm);
			break;

		case 0xa1:
			DPRINTF("MVI B, im");
			vm->BC.hi = get_pc_8(vm);
			break;

		case 0xa2:
			DPRINTF("MVI C, im");
			vm->BC.lo = get_pc_8(vm);
			break;

		case 0xa3:
			DPRINTF("MVI D, im");
			vm->DE.hi = get_pc_8(vm);
			break;

		case 0xa4:
			DPRINTF("MVI E, im");
			vm->DE.lo = get_pc_8(vm);
			break;

		case 0xa5:
			DPRINTF("MVI H, im");
			vm->HL.hi = get_pc_8(vm);
			break;

		case 0xa6:
			DPRINTF("MVI L, im");
			vm->HL.lo = get_pc_8(vm);
			break;

		case 0xa7:
			DPRINTF("MVI M, im");
			memory_write_8(vm->mem,vm->HL.val, get_pc_8(vm));
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
		case 0x80:
			DPRINTF("SUB A,B"); 
			vm->AF.hi -= vm->BC.hi;
			if (vm -> AF.hi < vm -> BC.hi) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm -> BC.hi) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		case 0x81:
			DPRINTF("SUB A,C"); 
			vm->AF.hi -= vm->BC.lo;
			if (vm -> AF.hi < vm -> BC.lo) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm -> BC.lo) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		case 0x82:
			DPRINTF("SUB A,D"); 
			vm->AF.hi -= vm->DE.hi;
			if (vm -> AF.hi < vm->DE.hi) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm->DE.hi) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		case 0x83:
			DPRINTF("SUB A,E"); 
			vm->AF.hi -= vm->DE.lo;
			if (vm -> AF.hi < vm->DE.lo) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm->DE.lo) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		case 0x84:
			DPRINTF("SUB A,H"); 
			vm->AF.hi -= vm->HL.hi;
			if (vm -> AF.hi < vm->HL.hi) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm->HL.hi) { 
				set_flag(vm, FLAG_Z);
			}
			break;
			
		case 0x85:
			DPRINTF("SUB A,L"); 
			vm->AF.hi -= vm->HL.lo;
			if (vm -> AF.hi < vm->HL.lo) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == vm->HL.lo) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		case 0x86:
			DPRINTF("SUB A,M"); 
			u8 val_sub = memory_read_8(vm->mem,vm->HL.val);
			vm->AF.hi -= val_sub;
			if (vm -> AF.hi < val_sub) {
				set_flag(vm, FLAG_C); 
			} else if (vm -> AF.hi == val_sub) { 
				set_flag(vm, FLAG_Z);
			}
			break;

		// CMPS
		case 0x90:
			DPRINTF("CMP A, B");

			if (vm -> AF.hi < vm -> BC.hi) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> BC.hi){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x91:
			DPRINTF("CMP A, C");

			if (vm -> AF.hi < vm -> BC.lo) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> BC.lo){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x92:
			DPRINTF("CMP A, D");

			if (vm -> AF.hi < vm->DE.hi) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm->DE.hi){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x93:
			DPRINTF("CMP A, E");

			if (vm -> AF.hi < vm -> DE.lo) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> DE.lo){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x94:
			DPRINTF("CMP A, H");

			if (vm -> AF.hi < vm -> HL.hi) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> HL.hi){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x95:
			DPRINTF("CMP A, L");

			if (vm -> AF.hi < vm -> HL.lo) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == vm -> HL.lo){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;

		case 0x96:
			DPRINTF("CMP A, C");
			u8 val_cmp = memory_read_8(vm->mem,vm->HL.val);
			if (vm -> AF.hi < val_cmp) {
				// carry flag on
				set_flag(vm, FLAG_C);
			} else if ( vm -> AF.hi == val_cmp){
				// zero flag on
				set_flag(vm, FLAG_Z);
			}

			break;
			
		// JMPS
		case 0xc0:
			DPRINTF("JZ addr");
			if (get_flag(vm, FLAG_Z)) vm-> PC.val = get_pc_16(vm);
			break;

		case 0xc1:
			DPRINTF("JNZ addr");
			if (!get_flag(vm, FLAG_Z)) vm-> PC.val = get_pc_16(vm);
			break;
			
		case 0xFE:
			DPRINTF("PNT");
			// TODO: REMOVE THIS
			printf("%x\n",vm->AF.hi);
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
