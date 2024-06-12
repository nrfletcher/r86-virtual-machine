#ifndef PROGRAM_H
#define PROGRAM_H

#include <cstdint>

// Memory regions for a program
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

#endif