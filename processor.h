#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>

void display_registers();
void display_register(std::string reg);

void fetch_instruction();
void decode_instruction();
void execute_instruction();
void memory_read();
void memory_writeback();
void load_program();

uint32_t read_4_bytes(uint32_t address);
uint32_t read_3_bytes(uint32_t address);
uint32_t read_2_bytes(uint32_t address);
uint32_t read_byte(uint32_t address);

void write_4_bytes(uint32_t address, uint32_t value);
void write_3_bytes(uint32_t address, uint32_t value);
void write_2_bytes(uint32_t address, uint32_t value);
void write_byte(uint32_t address, uint32_t value);

#endif