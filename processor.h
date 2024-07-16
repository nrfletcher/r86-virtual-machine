#ifndef PROCESSOR_H
#define PROCESSOR_H

/*  Implementation of an in-order processor.
 *  Supports fetch-decode-execute-memory-writeback cycle.
 *  ISA supports 32-bit instruction encoding. */

#define DEBUG 1 // Enable to print basic debugging statements.
#define DEBUG_V 1 // Enable to print verbose debugging statements.

#if DEBUG
    #define DEBUG_PRINT(x) std::cout << x << std::endl
#else
    #define DEBUG_PRINT(x)
#endif

#if DEBUG_V
    #define DEBUG_PRINT_V(x) std::cout << x << std::endl
#else
    #define DEBUG_PRINT_V(x)
#endif

#include <vector>
#include <cstdint>

/* Supported opcodes. */
enum Opcode {
    MOV_REG_REG_OPCODE = 0,
    MOV_REG_MEM_OPCODE,
    MOV_MEM_REG_OPCODE,
    MOV_REG_IMM_OPCODE,
    MOV_MEM_IMM_OPCODE,
    ADD_REG_REG_OPCODE,
    ADD_REG_IMM_OPCODE,
    SUB_REG_REG_OPCODE,
    SUB_REG_IMM_OPCODE,
    MUL_REG_REG_OPCODE,
    MUL_REG_IMM_OPCODE,
    DIV_REG_REG_OPCODE,
    DIV_REG_IMM_OPCODE,
    AND_REG_REG_OPCODE,
    OR_REG_REG_OPCODE,
    XOR_REG_REG_OPCODE,
    NOT_REG_OPCODE,
    SHL_REG_OPCODE,
    SHR_REG_OPCODE,
    JMP_OPCODE,
    JE_OPCODE,
    JNE_OPCODE,
    JLE_OPCODE,
    JGE_OPCODE,
    JG_OPCODE,
    JL_OPCODE,
    PUSH_OPCODE,
    POP_OPCODE,
    CALL_OPCODE,
    RET_OPCODE,
    CMP_OPCODE,
    HALT_OPCODE,
};

/* Supported trap routines. */
enum TrapRoutine {
    GETC_TRAP = 200,
    OUTC_TRAP,
    PUTS_TRAP,
    GETS_TRAP,
};

/* Register identifiers. */
enum Register {
    PC_REGISTER = 0,
    RSP_REGISTER,
    RET_REGISTER,
    REGISTER_0,
    REGISTER_1,
    REGISTER_2,
    REGISTER_3,
    REGISTER_4,
    REGISTER_5,
    REGISTER_6,
    REGISTER_7,
    REGISTER_8,
    REGISTER_9,
    REGISTER_10,
    REGISTER_11,
    REGISTER_12,
    REGISTER_13,
    REGISTER_14,
    REGISTER_15,
};

void display_registers();
void display_register(std::string reg);
void init_registers(uint32_t stack_begin, uint32_t program_begin);

void set_pc(uint32_t val);
void set_rsp(uint32_t val);
void set_ret(uint32_t val);
void set_register(int reg, uint32_t val);
uint32_t get_pc();
uint32_t get_rsp();
uint32_t get_ret();
uint32_t get_register(int reg);

uint32_t read_4_bytes(uint32_t address);
uint32_t read_3_bytes(uint32_t address);
uint32_t read_2_bytes(uint32_t address);
uint32_t read_byte(uint32_t address);
void write_4_bytes(uint32_t address, uint32_t value);
void write_3_bytes(uint32_t address, uint32_t value);
void write_2_bytes(uint32_t address, uint32_t value);
void write_byte(uint32_t address, uint32_t value);

uint32_t fetch_instruction();
void execute_instruction();
void execute_program(bool interactive_mode);

#endif