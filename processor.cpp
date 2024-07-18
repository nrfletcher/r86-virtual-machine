#include <iostream>
#include <cstdint>
#include <vector>

#include "processor.h"

/* 64KB of program space. */
std::vector<uint8_t> memory(64 * 1024);

/* All our registers are 32-bits wide. */
uint32_t pc_reg = 0x0;
uint32_t rsp_reg = 0x0;
uint32_t ret_reg = 0x0;
uint32_t general_registers[16];

/* Flags. */
bool overflow_flag = 0;
bool sign_flag = 0;
bool carry_flag = 0;
bool zero_flag = 0;

/* Set the beginning of our code segment and stack segment in memory. */
void init_registers(uint32_t stack_begin, uint32_t program_begin) {
    DEBUG_PRINT_V("Stack begin: " << stack_begin << "Program begin: " << program_begin);
    rsp_reg = stack_begin;
    pc_reg = program_begin;
}

/* GETTERS AND SETTERS FOR REGISTERS */
/* ///////////////////////////////// */

uint32_t get_pc() {
    return pc_reg;
}

void set_pc(uint32_t val) {
    pc_reg = val;
}

uint32_t get_rsp() {
    return rsp_reg;
}

void set_rsp(uint32_t val) {
    rsp_reg = val;
}

uint32_t get_ret() {
    return ret_reg;
}

void set_ret(uint32_t val) {
    ret_reg = val;
}

uint32_t get_register(int reg) {
    return general_registers[reg];
}

void set_register(int reg, uint32_t val) {
    general_registers[reg] = val;
}

/* GETTERS AND SETTERS FOR REGISTERS */
/* ///////////////////////////////// */

void display_registers() {
    printf("PC:  0x%04X  RSP: 0x%04X  RT:  0x%04X  R0:  0x%04X  R1:  0x%04X R2: 0x%04X  R3:  0x%04X\n", 
        pc_reg, rsp_reg, ret_reg, general_registers[0], general_registers[1], general_registers[2], general_registers[4]);
    printf("R4:  0x%04X  R5:  0x%04X  R6:  0x%04X  R7:  0x%04X  R8:  0x%04X R9: 0x%04X  R10: 0x%04X\n", 
        general_registers[5], general_registers[6], general_registers[7], general_registers[8], general_registers[9], general_registers[10], general_registers[11]);
    printf("R11: 0x%04X  R12: 0x%04X  R13: 0x%04X  R14: 0x%04X  R15: 0x%04X\n", 
        general_registers[12], general_registers[13], general_registers[14], general_registers[15], general_registers[16]);
    std::cout << std::endl;
}

void display_register(uint32_t reg) {
    switch(reg) {
        case PC_REGISTER:
            printf("PC: 0x%04X\n", pc_reg);
            break;
        case RET_REGISTER:
            printf("RET: 0x%04X\n", ret_reg);
            break;
        case RSP_REGISTER:
            printf("RET: 0x%04X\n", rsp_reg);
            break;
        default:
            if(reg <= REGISTER_15 && reg >= REGISTER_0) {
                printf("R%d: 0x%04X\n", reg, general_registers[reg]);
                return;
            } else {
                std::cerr << "Invalid register: " << reg << std::endl;
                return; 
            }
            break;
    }
}

/* GENERIC MEMORY READ AND WRITE FUNCTIONS */
/* /////////////////////////////////////// */

uint32_t read_4_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8)
                  | ((uint32_t)memory[address + 2] << 16)
                  | ((uint32_t)memory[address + 3] << 24);
    return value;
}

uint32_t read_3_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8)
                  | ((uint32_t)memory[address + 2] << 16);
    return value;
}

uint32_t read_2_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8);
    return value;
}

uint32_t read_byte(uint32_t address) {
    uint32_t value = (uint32_t)memory[address];
    return value;
}

void write_4_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
    memory[address + 2] = (value >> 16) & 0xFF;
    memory[address + 3] = (value >> 24) & 0xFF;
}

void write_3_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
    memory[address + 2] = (value >> 16) & 0xFF;
}

void write_2_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
}

void write_byte(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
}

/* GENERIC MEMORY READ AND WRITE FUNCTIONS */
/* /////////////////////////////////////// */

uint32_t fetch_instruction() {
    uint32_t instruction = read_4_bytes(pc_reg);
    pc_reg += 4;
    return instruction;
}

/* Is the memory block we are attempting to access within program space. */
bool verify_safe_memory_access(uint32_t) {
    return false;
}

/** Main execution function.
 *  Massive switch statement for now, could try to reduce this to a function pointer array later.
 *  Responsible for taking an instruction, and executing the appropriate
    opcode depending on what the instruction provides. */ 
void execute_instruction() {
    uint32_t instruction = fetch_instruction();

    /* Extracting bits according to ISA specification. */
    uint8_t opcode = (instruction >> 14) & 0x3F;
    uint8_t flags = (instruction >> 10) & 0xF;
    uint8_t operand_1 = (instruction >> 5) & 0x1F;
    uint8_t operand_2 = (instruction) & 0x1F;
   
    switch (opcode) {
        case MOV_REG_REG_OPCODE:
            // mov_reg_reg();
            break;
        case MOV_REG_MEM_OPCODE:
            // mov_reg_mem();
            break;
        case MOV_MEM_REG_OPCODE:
            // mov_mem_reg();
            break;
        case MOV_REG_IMM_OPCODE:
            // mov_reg_imm();
            break;
        case MOV_MEM_IMM_OPCODE:
            // mov_mem_imm();
            break;
        case ADD_REG_REG_OPCODE:
            // add_reg_reg();
            break;
        case ADD_REG_IMM_OPCODE:
            // add_reg_imm();
            break;
        case SUB_REG_REG_OPCODE:
            // sub_reg_reg();
            break;
        case SUB_REG_IMM_OPCODE:
            // sub_reg_imm();
            break;
        case MUL_REG_REG_OPCODE:
            // mul_reg_reg();
            break;
        case MUL_REG_IMM_OPCODE:
            // mul_reg_imm();
            break;
        case DIV_REG_REG_OPCODE:
            // div_reg_reg();
            break;
        case DIV_REG_IMM_OPCODE:
            // div_reg_imm();
            break;
        case AND_REG_REG_OPCODE:
            // and_reg_reg();
            break;
        case OR_REG_REG_OPCODE:
            // or_reg_reg();
            break;
        case XOR_REG_REG_OPCODE:
            // xor_reg_reg();
            break;
        case NOT_REG_OPCODE:
            // not_reg();
            break;
        case SHL_REG_OPCODE:
            // shl_reg();
            break;
        case SHR_REG_OPCODE:
            // shr_reg();
            break;
        case JMP_OPCODE:
            // jmp();
            break;
        case JE_OPCODE:
            // je();
            break;
        case JNE_OPCODE:
            // jne();
            break;
        case JLE_OPCODE:
            // jle();
            break;
        case JGE_OPCODE:
            // jge();
            break;
        case JG_OPCODE:
            // jg();
            break;
        case JL_OPCODE:
            // jl();
            break;
        case PUSH_OPCODE:
            // push();
            break;
        case POP_OPCODE:
            // pop();
            break;
        case CALL_OPCODE:
            // call();
            break;
        case RET_OPCODE:
            // ret();
            break;
        case CMP_OPCODE:
            // cmp();
            break;
        case HALT_OPCODE:
            // halt()
            break;
        default:
            std::cerr << "Invalid opcode: " << opcode << std::endl;
    }
}
