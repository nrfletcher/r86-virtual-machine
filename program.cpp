#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <vector>

#include "program.h"
#include "processor.h"
#include "macros.h"
#include "strings.h"

uint32_t prog_instruction_count = 0;
uint32_t executed_instructions = 0;

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

/* Displays hex memory of total program */
void display_program() {
	display_memory(TEXT_SEGMENT_BEGIN, prog_instruction_count);
}

/* Loads a 4 byte value into a memory address for our program */
void load_instruction(const std::string& instruction, uint32_t address) {
	if(instruction.length() != 32) {
		throw std::invalid_argument("Instruction is not 32 bits long");
	}

	uint32_t data = 0;
	for(char c : instruction) {
		if(c != '0' && c != '1') {
			throw std::invalid_argument("Invalid character in instruction");
		}
		data = (data << 1) | (c - '0');
	}
	if(address > TEXT_SEGMENT_END || address < TEXT_SEGMENT_BEGIN) {
		throw std::invalid_argument("Address outside text segment");
	} else {
		memwrite(address, 4, data);
		DEBUG_PRINT_V("Wrote: 0x" << std::hex << data << " to 0x" << address);
	}
}

/* Takes the first argument given when running program
 * and loads the binary file into memory. If an instruction
   is malformed the program ends. */
void load_program(const std::string& filename) {
	std::string filepath = "programs/" + filename + ".txt";
	std::ifstream MyReadFile(filepath);
	uint32_t curr_address = TEXT_SEGMENT_BEGIN;

	if(!MyReadFile.is_open()) {
		std::cerr << "Error: Unable to open file: " << filepath << std::endl;
		std::cerr << "Ensure that the program binary you wish to run is in /programs" << std::endl;
		exit(1);
	}

	std::string line;
	// For each line, parse the instruction and ensure it is a valid length string
	while(getline(MyReadFile, line)) {
		DEBUG_PRINT(line);
		std::string instruction;

		for(char& c : line) {
			if(c == '#' && instruction.length() < 32) {
				std::cerr << "Error: Invalid or malformed instruction, found character " << c << " before parsing 32 bits" << std::endl;
				exit(1);
			} else if(c == '#' && instruction.length() >= 32) {
				break;
			}
			if(c == '0' || c == '1') instruction.push_back(c);
		}

		if(instruction.length() != 32) {
			std::cerr << "Error: Invalid instruction length: " << instruction.length() << std::endl;
			exit(1);
		}
		try {
			load_instruction(instruction, curr_address);
			curr_address += 4;
			prog_instruction_count++;
		} catch(const std::invalid_argument& e) {
			std::cerr << "Error processing instruction: " << e.what() << std::endl;
			exit(1);
		}
	}

	MyReadFile.close();
}

/* COMMAND HANDLING FUNCTIONS */

bool handle_step() {
	return execute_instruction();
}

bool handle_reg(const std::vector<std::string> tokens) {
	if(tokens.size() == 1) {
		display_registers();
		return false;
	} else {
		for(size_t arg = 1; arg < tokens.size(); arg++) {
			try {
				display_register(RegisterParser::parse_register(tokens[arg]));
			} catch(const std::invalid_argument& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
		return false;
	}
}

bool handle_mem(const std::vector<std::string> tokens) {
	if(tokens.size() < 3) return false;
	try {
		if (tokens[1] == "regions") {
			std::cout << "Stack begin" << std::endl;
			std::cout << "Heap begin" << std::endl;
			std::cout << "BSS segment" << std::endl;
			std::cout << "Data segment" << std::endl;
			std::cout << "Text segment" << std::endl;
			return false;
		}
		uint32_t addr = string_to_int32(tokens[1]);
		uint32_t blocks = string_to_int32(tokens[2]);
		if (addr < TEXT_SEGMENT_BEGIN || addr > STACK_SEGMENT_BEGIN) {
			std::cerr << "Invalid memory address, out of bounds: " << addr << std::endl;
			return false;
		}
		display_memory(addr, blocks);
		return false;
	} catch(const std::invalid_argument& e) {
		std::cerr << "Error, invalid memory argument: " << e.what() << std::endl;
	}
	return false;
}

/* END COMMAND HANDLING FUNCTIONS */

/* Handle a given command in interactive mode 
	Current supported commands: reg, mem, step, end */
bool handle_command(const std::vector<std::string> tokens) {
	/* First, handle first token */
	if(tokens[0] == "step") {
		executed_instructions++;
		return handle_step();
	} else if(tokens[0] == "reg") {
		return handle_reg(tokens);
	} else if(tokens[0] == "mem") {
		return handle_mem(tokens);
	} else if(tokens[0] == "end") {
		std::cout << "Exiting program early. Total instructions: " << prog_instruction_count << " Executed instructions: " << executed_instructions << std::endl;
		return true;
	}
	print("Unknown command, try: mem, reg, step, end");
	return false;
}

/* Allows user to step through program and read variables for debugging purposes 
	This is probably going to end up quite a mess from all the string parsing */
void handle_interactive_mode() {
	std::string command;
	bool halt = false;
	while(command != "end" && !halt) {
		std::cout << "Command: ";
		std::getline(std::cin, command);
		std::vector<std::string> tokens = split_string(command);
		halt = handle_command(tokens);
	}
}

void execute_program(bool interactive_mode) {
	/* Interactive mode allows user to step through code 
	   Otherwise, we execute the entire program */
	if(interactive_mode) {
		handle_interactive_mode();
	} else {
		bool halt = false;
		while(!halt) {
			halt = execute_instruction();
			executed_instructions++;
		}
	}
	std::cout << "Program terminated." << std::endl;
}

/* Currently supported modes: interactive and non-interactive. */
bool handle_interactive(const std::string& int_string) {
	if(int_string.length() != 1) {
		std::cerr << "Invalid argument for interactive mode: " << int_string << std::endl;
		exit(1);
	}
	bool interactive_mode;

	if(int_string[0] == '0') interactive_mode = false;
	if(int_string[0] == '1') interactive_mode = true;

	if(interactive_mode != 0 && interactive_mode != 1) {
		std::cerr << "Invalid argument for interactive mode: " << interactive_mode << std::endl;
		exit(1);
	}

	return interactive_mode;
}

int main(int argc, char* argv[]) {
	print("Welcome to the program");
	/* User needs to provide a program file to run and a choice of execution mode. */
	if(argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <filename> <interactive>" << std::endl;
		std::cerr << "Filename is binary you wish to run, interactive mode is 1 or 0." << std::endl;
		exit(1);
	}

	bool interactive_mode = handle_interactive(argv[2]);

	std::string filename = argv[1];
	load_program(filename);

	init_registers(STACK_SEGMENT_BEGIN, TEXT_SEGMENT_BEGIN);

	#if DEBUG
	display_program();
	#endif

	execute_program(interactive_mode);

	return EXIT_SUCCESS;
}
