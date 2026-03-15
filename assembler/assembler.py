import sys
import string

INSTRUCTION_FILE = "instructions"
ASCII_LETTER = string.ascii_lowercase
COMMENT = ';' 

def read_instruction_file()-> dict[tuple[str,str]:int]: 
    ''' Reads which instruction means which opcode '''
    with open(INSTRUCTION_FILE,"r") as file:
        whole_content = file.readlines()
    
    instruction_hash = {}
    for lines in whole_content:
        if lines.startswith("0x"): 
            opcode = lines[0:4]
            instr = lines.split(" - ")[1].split(" ")
            instr_full = instr[0]
            instr_args = []
            for i in instr[1:]:
                instr_args.append(i)
            print(instr_args)

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

# print(inst_hash)

# read source file
with open(sys.argv[1], 'r') as file:
    content = file.readlines()

# first pass
for i in range(len(content)):
    line_no = i + 1
    line_cont = content[i].lstrip().rstrip().lower()
    line_tok = line_cont.split(" ")

    # go through these tokens
    j = 0
    while j < len(line_tok): 
        tok = line_tok[j]

        if tok == COMMENT:
            break
        elif tok in ASCII_LETTER:
            word = ""
            
            while tok in ASCII_LETTER:
                word += tok
                if j+1 < len(line_tok): j+=1
                else: break
                tok = line_tok[j]
        j += 1
    print(line_tok)

