# Instruction Set Architecture Design
ISA supports 32-bit von-Neumann architecture
## Instruction Format
Supported Architecture
* 32-bit instruction length
* 32-bit immediate value if specified by opcode

Instruction Format
* [TOP 13 BITS UNUSED] [NEXT 5 OPCODE] [NEXT 4 OPCODE FLAGS] [NEXT 5 OPERAND 1] [NEXT 5 OPERAND 2]
* 5 bits for two operand definers (two registers, 32 possibilities) each (10 bits total)
* 6 opcode bits (64 total opcodes available)
* 32 bit for an immediate (meaning a max value of 2^32 and a max address of 2^32)

Supported Opcodes
* MOV (between registers, memory, and immediates)
    * MOV REGX, REGY | OPCODE 0  | moves value in REGY into REGX
    * MOV REG, MEM   | OPCODE 1  | moves value stored at MEM address into REG
    * MOV MEM, REG   | OPCODE 2  | moves value stored in REG into MEM address
    * MOV REG, IMM   | OPCODE 3  | moves value stored in IMM into register REG
    * MOV MEM, IMM   | OPCODE 4  | moves value stored in IMM into MEM address
* ADD REGX, REGY     | OPCODE 5  | adds value of REGY to REGX 
* ADD REG, IMM       | OPCODE 6  | adds value of IMM to REG
* SUB REGX, REGY     | OPCODE 7  | subtracts 
* SUB REG, IMM       | OPCODE 8  | subtracts 
* MUL REGX, REGY     | OPCODE 9  | multiplies
* MUL REG, IMM       | OPCODE 10 | multiplies
* DIV REGX, REGY     | OPCODE 11 | divides 
* DEV REG, IMM       | OPCODE 12 | divides 
* AND REGX, REGY     | OPCODE 13 | performs AND operation
* OR  REGX, REGY     | OPCODE 14 | performs OR operation
* XOR REGX, REGY     | OPCODE 15 | performs XOR operation
* NOT REG            | OPCODE 16 | performs NOT operation
* SHL REG, AMT       | OPCODE 17 | performs a shift left
* SHR REG, AMT       | OPCODE 18 | performs a shift right
* JMP ADDRESS        | OPCODE 19 | performs an unconditional jump to ADDRESS
* JE  ADDRESS        | OPCODE 20 | performs a conditional jump
* JNE ADDRESS        | OPCODE 21 | performs a conditional jump
* JLE ADDRESS        | OPCODE 22 | performs a conditional jump
* JGE ADDRESS        | OPCODE 23 | performs a conditional jump
* JG  ADDRESS        | OPCODE 24 | performs a conditional jump
* JL  ADDRESS        | OPCODE 25 | performs a conditional jump
* PUSH REG           | OPCODE 26 | pushes content of REG onto the stack
* POP REG            | OPCODE 27 | pops the content of the RSP into REG
* CALL ADDRESS       | OPCODE 28 | jumps to ADDRESS, and pushes ADDRESS + 1 onto the stack
* RET                | OPCODE 29 | pops the stack and sets PC to the popped value
* CMP REGX, REGY     | OPCODE 30 | compares REGX and REGY   
* HALT               | OPCODE 31 | terminates the program

Trap Routines
* GETC   |  Get a singular character.
* OUTC   |  Output a singular character.
* PUTS   |  Outputs a string at an address.
* GETS   |  Stored a given string at a memory location.

Registers
* PC (Program Counter)
* RT (Return value of function call)
* SP (Stack pointer)
* R0 - R5 (First 6 arguments)
* R6 - R15 (General purpose registers)