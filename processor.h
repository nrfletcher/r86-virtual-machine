#ifndef PROCESSOR_H
#define PROCESSOR_H

void display_registers();
void fetch_instruction();
void decode_instruction();
void execute_instruction();
void read_memory();
void memory_writeback();
void load_program();

#endif