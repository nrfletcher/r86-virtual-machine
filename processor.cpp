#include <iostream>
#include <cstdint>
#include <vector>

std::vector<uint8_t> memory(64 * 1024);

uint32_t pc_reg = 0x0;
uint32_t rsp_reg = 0x0;
uint32_t rt_reg = 0x0;
uint32_t r0_reg = 0x0;
uint32_t r1_reg = 0x0;
uint32_t r2_reg = 0x0;
uint32_t r3_reg = 0x0;
uint32_t r4_reg = 0x0;
uint32_t r5_reg = 0x0;
uint32_t r6_reg = 0x0;
uint32_t r7_reg = 0x0;
uint32_t r8_reg = 0x0;
uint32_t r9_reg = 0x0;
uint32_t r10_reg = 0x0;
uint32_t r11_reg = 0x0;
uint32_t r12_reg = 0x0;
uint32_t r13_reg = 0x0;
uint32_t r14_reg = 0x0;
uint32_t r15_reg = 0x0;

void display_registers() {
    printf("PC:  0x%04X  RSP: 0x%04X  RT:  0x%04X  R0:  0x%04X  R1:  0x%04X R2: 0x%04X  R3:  0x%04X\n", pc_reg, rsp_reg, rt_reg, r0_reg, r1_reg, r2_reg, r3_reg);
    printf("R4:  0x%04X  R5:  0x%04X  R6:  0x%04X  R7:  0x%04X  R8:  0x%04X R9: 0x%04X  R10: 0x%04X\n", r4_reg, r5_reg, r6_reg, r7_reg, r8_reg, r9_reg, r10_reg);
    printf("R11: 0x%04X  R12: 0x%04X  R13: 0x%04X  R14: 0x%04X  R15: 0x%04X\n", r11_reg, r12_reg, r13_reg, r14_reg, r15_reg);
}

void display_register(std::string reg) {
// Implement
}

void fetch_instruction() {
// Implement
}

void decode_instruction() {
// Implement
}

void execute_instruction() {
// Implement
}

void read_memory() {
// Implement
}

void memory_writeback() {
// Implement
}

/* Loads a set of CPU instructions into memory */
void load_program() {
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
