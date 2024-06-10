#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>

uint32_t read_4_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_3_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_2_bytes(const std::vector<uint8_t>& memory, uint32_t address);
uint32_t read_byte(const std::vector<uint8_t>& memory, uint32_t address);

void write_4_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_3_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_2_bytes(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);
void write_byte(std::vector<uint8_t>& memory, uint32_t address, uint32_t value);

#endif