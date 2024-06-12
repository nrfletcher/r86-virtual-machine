#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>

void display_registers();
void display_register(std::string register);

void fetch_instruction();
void decode_instruction();
void execute_instruction();
void memory_read();
void memory_writeback();
void load_program();

uint32_t read_4_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_3_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_2_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_byte(const std::vector<uint8_t>& memory, uint32_t address);

void write_4_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_3_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_2_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_byte(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);

#endif