#include <iostream>
#include <cstdint>
#include <vector>

/** Implementation of an in-order processor
 *  Supports fetch-decode-execute-writeback cycle
 *  ISA supports 32-bit instruction encoding
 *  Docs for this file in <MEMORY.md> and <ISA.md>
 */

/* 64KB of system memory */
std::vector<uint8_t> memory(64 * 1024);

/* Data segments */
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

/* Registers */
uint32_t pc_reg;
uint32_t rsp_reg;
uint32_t rt_reg;
uint32_t r0_reg;
uint32_t r1_reg;
uint32_t r2_reg;
uint32_t r3_reg;
uint32_t r4_reg;
uint32_t r5_reg;
uint32_t r6_reg;
uint32_t r7_reg;
uint32_t r8_reg;
uint32_t r9_reg;
uint32_t r10_reg;
uint32_t r11_reg;
uint32_t r12_reg;
uint32_t r13_reg;
uint32_t r14_reg;
uint32_t r15_reg;

void display_registers() {
    
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