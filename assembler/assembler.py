import sys

INSTRUCTION_FILE = "instructions"

def read_instruction_file()-> dict[tuple[str,str]:int]: 
    ''' Reads which instruction means which opcode '''
    with open(INSTRUCTION_FILE,"r") as file:
        whole_content = file.readlines()
    
    instruction_hash = {}
    for lines in whole_content:
        if lines.startswith("0x"): 
            opcode = lines[0:4]
            instr_full = lines.split(" - ")[1]

            if "<" in instr_full:
                op_type = instr_full.split("<")[1].split(">")[0]
                instr_full = instr_full.replace(f'<{op_type}>',"")
            else: op_type = "normal"

            instruction_hash.update({(instr_full,op_type):opcode})

    return instruction_hash

if len(sys.argv) < 2:
    print("Need an argument <filename>")
    quit()

inst_hash = read_instruction_file()

# read source
with open(sys.argv[1], 'r') as file:
    source = file.readlines()

# first pass
code_gen = "static u8 stream[65535] = { \n"

line_index = 0
source_len = len(source)
while line_index < source_len:
    line = source[line_index]

    for insts in inst_hash.keys():
        if line.startswith(";"):
            break
        if insts[0] in line:
            if insts[1] == 'normal': code_gen+=inst_hash[insts] + ",\n"
            elif insts[1] == 'data': code_gen+=inst_hash[insts] + ",  0x" + line.replace(insts[0],"")[0:2] + ",\n"
            elif insts[1] == 'addr': code_gen+=inst_hash[insts] + ",  0x" + line.replace(insts[0],"")[0:2] + ",  0x" + line.replace(insts[0],"")[2:4]+",\n"
            break
    else:
            print(insts[0], line)
            print("ERROR, UNKNOWN INSTRUCTION AT LINE", line_index+1)
            quit()

    line_index+=1
code_gen += "\n};"
print(code_gen)

