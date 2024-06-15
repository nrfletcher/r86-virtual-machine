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
    * MOV REGX, REGY | OPCODE 1 | moves value in REGY into REGX
    * MOV REG, MEM | OPCODE 2 | moves value stored at MEM address into REG
    * MOV MEM, REG | OPCODE 3 | moves value stored in REG into MEM address
    * MOV REG, IMM | OPCODE 4 | 
* ADD REG, REG | OPCODE 5
* ADD REG, IMM | OPCODE 6
* SUB REG, REG | OPCODE 7
* SUB REG, IMM | OPCODE 8
* MUL REG, REG | OPCODE 9
* MUL REG, IMM | OPCODE 10
* DIV REG, REG | OPCODE 11
* DEV REG, IMM | OPCODE 12
* AND
* OR
* XOR
* NOT
* SHL
* SHR
* JMP (any conditional variations)
* PUSH
* POP
* CALL
* RET
* CMP

Registers
* PC (Program Counter)
* RT (Return value of function call)
* SP (Stack pointer)
* R0 - R5 (First 6 arguments)
* R6 - R15 (General purpose registers)