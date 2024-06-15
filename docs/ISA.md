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
    * MOV REG, REG
    * MOV REG, MEM
    * MOV MEM, REG
    * MOV 
* PUSH
* POP
* ADD REG, REG
* SUB REG, REG
* MUL
* DIV
* AND
* OR
* XOR
* NOT
* SHL
* SHR
* JMP (any conditional variations)
* CALL
* RET
* CMP

Registers
* PC (Program Counter)
* RT (Return value of function call)
* SP (Stack pointer)
* R0 - R5 (First 6 arguments)
* R6 - R15 (General purpose registers)