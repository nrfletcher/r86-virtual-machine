#ifndef PROCESSOR_H
#define PROCESSOR_H

/*  Implementation of an in-order processor.
 *  Supports fetch-decode-execute-memory-writeback cycle.
 *  ISA supports 32-bit instruction encoding. */

#include <vector>
#include <cstdint>
#include <array>
#include <unordered_map>

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
    TEST_OPCODE,
};

const std::array<std::string, 33> OPCODE_NAMES = {
    "MOV_REG_REG", "MOV_REG_MEM", "MOV_MEM_REG", "MOV_REG_IMM", "MOV_MEM_IMM",
    "ADD_REG_REG", "ADD_REG_IMM", "SUB_REG_REG", "SUB_REG_IMM", "MUL_REG_REG",
    "MUL_REG_IMM", "DIV_REG_REG", "DIV_REG_IMM", "AND_REG_REG", "OR_REG_REG",
    "XOR_REG_REG", "NOT_REG", "SHL_REG", "SHR_REG", "JMP",
    "JE", "JNE", "JLE", "JGE", "JG",
    "JL", "PUSH", "POP", "CALL", "RET",
    "CMP", "HALT", "TEST"
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
    REGISTER_0 = 0,
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
    PC_REGISTER,
    RSP_REGISTER,
    RET_REGISTER,
};

class RegisterParser {
    private:
        static const std::unordered_map<std::string, int> registerMap;

    public:
        static int parse_register(const std::string& input);
};

void display_registers();
void display_register(uint32_t reg);
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

int execute_instruction();
uint32_t string_to_register(const std::string& reg);

#endif