#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

#include "processor.h"
#include "macros.h"

/* 64KB of program space. */
std::vector<uint8_t> memory(64 * 1024);

/* All our registers are 32-bits wide. 
   Registers 0-16 are general purpose.
   Register 17 is PC.
   Register 18 is RSP
   Register 19 is RET. */
class RegisterFile {
    public:
        uint32_t registers[19];
};

RegisterFile registerFile;

const std::unordered_map<std::string, int> RegisterParser::registerMap = {
    {"R0", REGISTER_0},
    {"R1", REGISTER_1},
    {"R2", REGISTER_2},
    {"R3", REGISTER_3},
    {"R4", REGISTER_4},
    {"R5", REGISTER_5},
    {"R6", REGISTER_6},
    {"R7", REGISTER_7},
    {"R8", REGISTER_8},
    {"R9", REGISTER_9},
    {"R10", REGISTER_10},
    {"R11", REGISTER_11},
    {"R12", REGISTER_12},
    {"R13", REGISTER_13},
    {"R14", REGISTER_14},
    {"R15", REGISTER_15},
    {"PC", PC_REGISTER},
    {"RSP", RSP_REGISTER},
    {"RET", RET_REGISTER}
};

int RegisterParser::parse_register(const std::string& input) {
    std::string upperInput = input;
    std::transform(upperInput.begin(), upperInput.end(), upperInput.begin(), ::toupper);
    
    try {
        return registerMap.at(upperInput);
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("Invalid register name: " + input);
    }
}

/* Flags. */
bool overflow_flag = 0;
bool sign_flag = 0;
bool carry_flag = 0;
bool zero_flag = 0;

/* Set the beginning of our code segment and stack segment in memory. */
void init_registers(uint32_t stack_begin, uint32_t program_begin) {
    DEBUG_PRINT_V("Stack begin: " << std::hex << stack_begin << " Program begin: " << program_begin);
    registerFile.registers[RSP_REGISTER] = stack_begin;
    registerFile.registers[PC_REGISTER] = program_begin;
}

/* GETTERS AND SETTERS FOR REGISTERS */
/* ///////////////////////////////// */

uint32_t get_pc() {
    return registerFile.registers[PC_REGISTER];
}

void set_pc(uint32_t val) {
    registerFile.registers[PC_REGISTER] = val;
}

uint32_t get_rsp() {
    return registerFile.registers[RSP_REGISTER];
}

void set_rsp(uint32_t val) {
    registerFile.registers[RSP_REGISTER] = val;
}

uint32_t get_ret() {
    return registerFile.registers[RET_REGISTER];
}

void set_ret(uint32_t val) {
    registerFile.registers[RET_REGISTER] = val;
}

uint32_t get_register(int reg) {
    return registerFile.registers[reg];
}

void set_register(int reg, uint32_t val) {
    registerFile.registers[reg] = val;
}

/* GETTERS AND SETTERS FOR REGISTERS */
/* ///////////////////////////////// */

void display_registers() {
    printf("PC:  0x%04X  RSP: 0x%04X  RT:  0x%04X  R0:  0x%04X  R1:  0x%04X R2: 0x%04X  R3:  0x%04X\n", 
        registerFile.registers[PC_REGISTER], registerFile.registers[RSP_REGISTER], registerFile.registers[RET_REGISTER], registerFile.registers[0], registerFile.registers[1], registerFile.registers[2], registerFile.registers[4]);
    printf("R4:  0x%04X  R5:  0x%04X  R6:  0x%04X  R7:  0x%04X  R8:  0x%04X R9: 0x%04X  R10: 0x%04X\n", 
        registerFile.registers[5], registerFile.registers[6], registerFile.registers[7], registerFile.registers[8], registerFile.registers[9], registerFile.registers[10], registerFile.registers[11]);
    printf("R11: 0x%04X  R12: 0x%04X  R13: 0x%04X  R14: 0x%04X  R15: 0x%04X\n", 
        registerFile.registers[12], registerFile.registers[13], registerFile.registers[14], registerFile.registers[15], registerFile.registers[16]);
    std::cout << std::endl;
}

void display_register(uint32_t reg) {
    switch(reg) {
        case PC_REGISTER:
            printf("PC: 0x%04X\n", registerFile.registers[PC_REGISTER]);
            break;
        case RET_REGISTER:
            printf("RET: 0x%04X\n", registerFile.registers[RET_REGISTER]);
            break;
        case RSP_REGISTER:
            printf("RSP: 0x%04X\n", registerFile.registers[RSP_REGISTER]);
            break;
        default:
            if(reg <= REGISTER_15 && reg >= REGISTER_0) {
                printf("R%d: 0x%04X\n", reg, registerFile.registers[reg]);
                return;
            } else {
                std::cerr << "Invalid register: " << reg << std::endl;
                return; 
            }
            break;
    }
}

/* GENERIC MEMORY READ AND WRITE FUNCTIONS */
/* /////////////////////////////////////// */

uint32_t read_4_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8)
                  | ((uint32_t)memory[address + 2] << 16)
                  | ((uint32_t)memory[address + 3] << 24);
    return value;
}

uint32_t read_3_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8)
                  | ((uint32_t)memory[address + 2] << 16);
    return value;
}

uint32_t read_2_bytes(uint32_t address) {
    uint32_t value = (uint32_t)memory[address]
                  | ((uint32_t)memory[address + 1] << 8);
    return value;
}

uint32_t read_byte(uint32_t address) {
    uint32_t value = (uint32_t)memory[address];
    return value;
}

void write_4_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
    memory[address + 2] = (value >> 16) & 0xFF;
    memory[address + 3] = (value >> 24) & 0xFF;
}

void write_3_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
    memory[address + 2] = (value >> 16) & 0xFF;
}

void write_2_bytes(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
}

void write_byte(uint32_t address, uint32_t value) {
    memory[address] = value & 0xFF;
}

/* GENERIC MEMORY READ AND WRITE FUNCTIONS */
/* /////////////////////////////////////// */

/* Is the memory block we are attempting to access within program space. */
bool verify_safe_memory_access(uint32_t) {
    return false;
}

std::string opcode_to_string(int opcode) {
    if (opcode >= 0 && opcode < static_cast<int>(OPCODE_NAMES.size())) {
        return OPCODE_NAMES[opcode];
    } else {
        return "UNKNOWN_OPCODE";
    }
}

/** Main execution function that implements the fetch-decode-execute-memory-writeback cycle.
 *  Massive switch statement for now, could try to reduce this to a function pointer array later.
 *  Responsible for taking an instruction, and executing the appropriate
    opcode depending on what the instruction provides. 
    We return 0 for all opcodes, except HALT which returns 1. */ 
int execute_instruction() {
    /* Fetch instruction. */
    uint32_t instruction = read_4_bytes(registerFile.registers[PC_REGISTER]);
    registerFile.registers[PC_REGISTER] += 4;
    /* Used for any opcodes that require an immediate */
    uint32_t immediate = read_4_bytes(registerFile.registers[PC_REGISTER]);

    /* Decode. Extracting bits according to ISA specification. */
    uint32_t opcode = (instruction >> 14) & 0x3F;
    uint32_t flags = (instruction >> 10) & 0xF;
    uint32_t operand_1 = (instruction >> 5) & 0x1F;
    uint32_t operand_2 = (instruction) & 0x1F;

    DEBUG_PRINT_V("Instruction: 0x" << std::hex << std::setw(8) << std::setfill('0') << instruction);
    DEBUG_PRINT_V("Current PC:  0x" << std::hex << std::setw(8) << std::setfill('0') << registerFile.registers[PC_REGISTER]);
    DEBUG_PRINT_V("Opcode:      0x" << std::hex << std::setw(4) << std::setfill('0') << opcode << " -> " << opcode_to_string(opcode));
    DEBUG_PRINT_V("Flags:       0x" << std::hex << std::setw(4) << std::setfill('0') << flags);
    DEBUG_PRINT_V("Operand 1:   0x" << std::hex << std::setw(4) << std::setfill('0') << operand_1);
    DEBUG_PRINT_V("Operand 2:   0x" << std::hex << std::setw(4) << std::setfill('0') << operand_2);
    DEBUG_PRINT_V("");
   
    /* Execute instruction. */
    switch (opcode) {
        case MOV_REG_REG_OPCODE:
            registerFile.registers[operand_1] = registerFile.registers[operand_2];
            break;
        case MOV_REG_MEM_OPCODE:
            registerFile.registers[operand_1] = memory[registerFile.registers[operand_2]];
            break;
        case MOV_MEM_REG_OPCODE:
            memory[registerFile.registers[operand_1]] = registerFile.registers[operand_2];
            break;
        case MOV_REG_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;
            registerFile.registers[operand_1] = immediate;
            break;
        case MOV_MEM_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;
            memory[registerFile.registers[operand_1]] = immediate;
            break;
        case ADD_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 += value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case ADD_REG_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(immediate);
            value1 += value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case SUB_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 -= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case SUB_REG_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;

            break;
        case MUL_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 *= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case MUL_REG_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;

            break;
        case DIV_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 /= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case DIV_REG_IMM_OPCODE:
            registerFile.registers[PC_REGISTER] += 4;

            break;
        case AND_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 &= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case OR_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 |= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case XOR_REG_REG_OPCODE:
            {
            int32_t value1 = static_cast<int32_t>(registerFile.registers[operand_1]);
            int32_t value2 = static_cast<int32_t>(registerFile.registers[operand_2]);
            value1 ^= value2;
            registerFile.registers[operand_1] = static_cast<uint32_t>(value1); 
            }
            break;
        case NOT_REG_OPCODE:
            // not_reg();
            break;
        case SHL_REG_OPCODE:
            // shl_reg();
            break;
        case SHR_REG_OPCODE:
            // shr_reg();
            break;
        case JMP_OPCODE:
            // jmp();
            break;
        case JE_OPCODE:
            // je();
            break;
        case JNE_OPCODE:
            // jne();
            break;
        case JLE_OPCODE:
            // jle();
            break;
        case JGE_OPCODE:
            // jge();
            break;
        case JG_OPCODE:
            // jg();
            break;
        case JL_OPCODE:
            // jl();
            break;
        case PUSH_OPCODE:
            // push();
            break;
        case POP_OPCODE:
            // pop();
            break;
        case CALL_OPCODE:
            // call();
            break;
        case RET_OPCODE:
            // ret();
            break;
        case CMP_OPCODE:
            // cmp();
            break;
        case HALT_OPCODE:
            return 1;
        default:
            std::cerr << "INVALID OPCODE: " << std::hex << opcode << " at instruction: " << instruction << std::endl;
    }
    /* Return 0 for regular opcode. */
    return 0;
}
