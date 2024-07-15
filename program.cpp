#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "program.h"
#include "processor.h"

void memread(uint32_t addr, uint32_t num_bytes) {
	switch(num_bytes) {
		case 1:
			std::cout << std::hex << "0x" << read_byte(addr) << std::endl;
			break;
		case 2:
			std::cout << std::hex << "0x" << read_2_bytes(addr) << std::endl;
			break;
		case 3:
			std::cout << std::hex << "0x" << read_3_bytes(addr) << std::endl;
			break;
		case 4:
			std::cout << std::hex << "0x" << read_4_bytes(addr) << std::endl;
			break;
		default:
			std::cout << "Invalid number of bytes to read provided: " << num_bytes << std::endl;
			break;
	}
}

void memwrite(uint32_t addr, uint32_t num_bytes, uint32_t data) {
	switch(num_bytes) {
		case 1:
			write_byte(addr, data);
			break;
		case 2:
			write_2_bytes(addr, data);
			break;
		case 3:
			write_3_bytes(addr, data);
			break;
		case 4:
			write_4_bytes(addr, data);
			break;
		default:
			std::cout << "Invalid number of bytes to write provided: " << num_bytes << std::endl;
			break;
	}
}

void display_memory(uint32_t addr, uint32_t num_32_blocks) {
	uint32_t curr_addr = addr;
	for(uint32_t i = 0; i < num_32_blocks; i++) {
		std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << curr_addr << ": ";
		for(int i = 0; i < 32; i++) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << read_byte(curr_addr) << " ";
			curr_addr++;
		}
		std::cout << std::endl;
	}
}

void load_program(const std::string& filename) {
	std::string filepath = "programs/" + filename + ".txt";
	std::ifstream MyReadFile(filepath);

	if(!MyReadFile.is_open()) {
		std::cerr << "Error: Unable to open file." << filepath << std::endl;
		exit(1);
	}

	std::string line;
	// For each line, parse the instruction and ensure it is a valid length string
	while(getline(MyReadFile, line)) {
		std::cout << line << std::endl;
		std::string instruction;

		for(char& c : line) {
			if(c == '0' || c == '1') instruction.push_back(c);
		}

		if(instruction.length() != 32) {
			std::cerr << "Invalid instruction length: " << instruction.length() << std::endl;
			exit(1);
		}
	}

	MyReadFile.close();
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
	}

	std::string filename = argv[1];
	load_program(filename);

	init_registers(STACK_SEGMENT_BEGIN, TEXT_SEGMENT_BEGIN);
	execute_program();

	return 0;
}
