# Instruction Set Architecture Design
ISA supports 32-bit von-Neumann architecture
## Instruction Format
Supported Architecture
* 32-bit instruction length
* 32-bit immediate value if specified by opcode

Instruction Format
* [TOP 12 BITS UNUSED] [NEXT 6 OPCODE] [NEXT 4 OPCODE FLAGS] [NEXT 5 OPERAND X] [NEXT 5 OPERAND Y]
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
* SUB REGX, REGY     | OPCODE 7  | subtracts REGY from REGX
* SUB REG, IMM       | OPCODE 8  | subtracts IMM from REG
* MUL REGX, REGY     | OPCODE 9  | multiplies REGX and REGY and stores result in REGX
* MUL REG, IMM       | OPCODE 10 | multiplies REG and IMM and stores result in REG
* DIV REGX, REGY     | OPCODE 11 | divides REGX by REGY and stores in REGX
* DEV REG, IMM       | OPCODE 12 | divides REG by IMM and stores in REG
* AND REGX, REGY     | OPCODE 13 | performs AND operation on REGX and REGY and stores in REGX
* OR  REGX, REGY     | OPCODE 14 | performs OR operation on REGX and REGY and stores in REGX
* XOR REGX, REGY     | OPCODE 15 | performs XOR operation on REGX and REGY and stores in REGX
* NOT REG            | OPCODE 16 | performs NOT operation on REG
* SHL REG, AMT       | OPCODE 17 | performs a shift left of AMT on REG
* SHR REG, AMT       | OPCODE 18 | performs a shift right of AMT on REG
* JMP ADDRESS        | OPCODE 19 | performs an unconditional jump to ADDRESS
* JE  ADDRESS        | OPCODE 20 | performs a conditional jump if 
* JNE ADDRESS        | OPCODE 21 | performs a conditional jump if 
* JLE ADDRESS        | OPCODE 22 | performs a conditional jump if 
* JGE ADDRESS        | OPCODE 23 | performs a conditional jump if 
* JG  ADDRESS        | OPCODE 24 | performs a conditional jump if 
* JL  ADDRESS        | OPCODE 25 | performs a conditional jump if
* PUSH REG           | OPCODE 26 | pushes content of REG onto the stack
* POP REG            | OPCODE 27 | pops the content of the RSP into REG
* CALL ADDRESS       | OPCODE 28 | jumps to ADDRESS, and pushes ADDRESS + 1 onto the stack
* RET                | OPCODE 29 | pops the stack and sets PC to the popped value
* CMP REGX, REGY     | OPCODE 30 | sets flags by doing a REGX - REGY subtraction
* HALT               | OPCODE 31 | terminates the program
* TEST REGX, REGY    | OPCODE 32 | sets flags by doing a REGX bitwise AND with REGY

Flags (Which are set by prior arithmetic actions)
Additional documentation on specifics of flags set found below.
* OVERFLOW | Set if there's an unsigned overflow or underflow.
* CARRY    | Set if the result is zero.
* ZERO     | Set if the result is negative (highest order bit is 1).
* SIGN     | Set if there's a signed overflow or underflow.

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