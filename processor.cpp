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

void init_registers(uint32_t stack_begin, uint32_t program_begin) {
    rsp_reg = stack_begin;
    pc_reg = program_begin;
}

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

void display_registers() {
    printf("PC:  0x%04X  RSP: 0x%04X  RT:  0x%04X  R0:  0x%04X  R1:  0x%04X R2: 0x%04X  R3:  0x%04X\n", 
        pc_reg, rsp_reg, ret_reg, general_registers[0], general_registers[1], general_registers[2], general_registers[4]);
    printf("R4:  0x%04X  R5:  0x%04X  R6:  0x%04X  R7:  0x%04X  R8:  0x%04X R9: 0x%04X  R10: 0x%04X\n", 
        general_registers[5], general_registers[6], general_registers[7], general_registers[8], general_registers[9], general_registers[10], general_registers[11]);
    printf("R11: 0x%04X  R12: 0x%04X  R13: 0x%04X  R14: 0x%04X  R15: 0x%04X\n", 
        general_registers[12], general_registers[13], general_registers[14], general_registers[15], general_registers[16]);
    std::cout << std::endl;
}

void display_register(std::string reg) {
// Implement
}

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

uint32_t fetch_instruction() {
    uint32_t instruction = read_4_bytes(pc_reg);
    pc_reg += 4;
    return instruction;
}

/** Main execution function.
 *  Responsible for taking an instruction, and executing the appropriate
    opcode depending on what the instruction provides. */ 
void execute_instruction() {
    uint32_t instruction = fetch_instruction();
    uint32_t opcode = 0;
    
    switch (opcode) {
        case MOV_REG_REG_OPCODE:
            break;
        case MOV_REG_IMM_OPCODE:
            break;
            
        default:
            std::cerr << "Invalid opcode: " << opcode << std::endl; 
    }

}

void execute_program() {
    
}
