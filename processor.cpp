#include <iostream>
#include <cstdint>
#include <vector>

/** Implementation of an in-order processor
 *  Supports fetch-decode-execute-writeback cycle
 *  ISA supports 32-bit instruction encoding; 64KB system memory
 *  Docs for this file in <MEMORY.md> and <ISA.md>
 */

std::vector<uint8_t> memory(64 * 1024);

const uint32_t STACK_SEGMENT_BEGIN = 0xFA00;
const uint32_t STACK_SEGMENT_END = 0xC800;
const uint32_t HEAP_SEGMENT_BEGIN = 0xC7FF;
const uint32_t HEAP_SEGMENT_END = 0x9600;
const uint32_t BSS_SEGMENT_BEGIN = 0x95FF;
const uint32_t BSS_SEGMENT_END = 0x6400;
const uint32_t DATA_SEGMENT_BEGIN = 0x63FF;
const uint32_t DATA_SEGMENT_END = 0x3200;
const uint32_t TEXT_SEGMENT_BEGIN = 0x31FF;
const uint32_t TEXT_SEGMENT_END = 0x0;

uint32_t pc_reg = TEXT_SEGMENT_END;
uint32_t rsp_reg = STACK_SEGMENT_BEGIN;
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

void fetch_instruction() {

}

void decode_instruction() {

}

void execute_instruction() {

}

void read_memory() {

}

void memory_writeback() {

}

void load_program() {

}