#include <iostream>
#include <iomanip>

#include "program.h"
#include "processor.h"

std::vector<uint8_t> memory(64 * 1024);

void memread(uint32_t addr, uint32_t num_bytes) {
	switch(num_bytes) {
		case 1:
			std::cout << std::hex << "0x" << read_byte(memory, addr) << std::endl;
			break;
		case 2:
			std::cout << std::hex << "0x" << read_2_bytes(memory, addr) << std::endl;
			break;
		case 3:
			std::cout << std::hex << "0x" << read_3_bytes(memory, addr) << std::endl;
			break;
		case 4:
			std::cout << std::hex << "0x" << read_4_bytes(memory, addr) << std::endl;
			break;
		default:
			std::cout << "Invalid number of bytes to read provided: " << num_bytes << std::endl;
			break;
	}
}

void memwrite(uint32_t addr, uint32_t num_bytes, uint32_t data) {
	switch(num_bytes) {
		case 1:
			write_byte(memory, addr, data);
			break;
		case 2:
			write_2_bytes(memory, addr, data);
			break;
		case 3:
			write_3_bytes(memory, addr, data);
			break;
		case 4:
			write_4_bytes(memory, addr, data);
			break;
		default:
			std::cout << "Invalid number of bytes to write provided: " << num_bytes << std::endl;
			break;
	}
}

void display_memory(uint32_t addr, uint32_t num_bytes) {
	
}

int main() {
	memwrite(0x23, 4, 0x11223344);
	memread(0x23, 4);
	return 0;
}
