#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>

/*  Implementation of an in-order processor.
 *  Supports fetch-decode-execute-memory-writeback cycle.
 *  ISA supports 32-bit instruction encoding. */

void display_registers();
void display_register(std::string reg);

void init_registers(uint32_t stack_begin, uint32_t program_begin);
void fetch_instruction();
void decode_instruction();
void execute_instruction();
void memory_writeback();

uint32_t read_4_bytes(uint32_t address);
uint32_t read_3_bytes(uint32_t address);
uint32_t read_2_bytes(uint32_t address);
uint32_t read_byte(uint32_t address);

void write_4_bytes(uint32_t address, uint32_t value);
void write_3_bytes(uint32_t address, uint32_t value);
void write_2_bytes(uint32_t address, uint32_t value);
void write_byte(uint32_t address, uint32_t value);

#endif