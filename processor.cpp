#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>

#include "processor.h"
#include "macros.h"

/* 64KB of program space. */
std::vector<uint8_t> memory(64 * 1024);

/* All our registers are 32-bits wide. */
class RegisterFile {
    public:
        uint32_t pc_reg;
        uint32_t rsp_reg;
        uint32_t ret_reg;
        uint32_t registers[16];
};

RegisterFile registerFile;

/* Flags. */
bool overflow_flag = 0;
bool sign_flag = 0;
bool carry_flag = 0;
bool zero_flag = 0;

/* Set the beginning of our code segment and stack segment in memory. */
void init_registers(uint32_t stack_begin, uint32_t program_begin) {
    DEBUG_PRINT_V("Stack begin: " << std::hex << stack_begin << " Program begin: " << program_begin);
    registerFile.rsp_reg = stack_begin;
    registerFile.pc_reg = program_begin;
}

/* GETTERS AND SETTERS FOR REGISTERS */
/* ///////////////////////////////// */

uint32_t get_pc() {
    return registerFile.pc_reg;
}

void set_pc(uint32_t val) {
    registerFile.pc_reg = val;
}

uint32_t get_rsp() {
    return registerFile.rsp_reg;
}

void set_rsp(uint32_t val) {
    registerFile.rsp_reg = val;
}

uint32_t get_ret() {
    return registerFile.ret_reg;
}

void set_ret(uint32_t val) {
    registerFile.ret_reg = val;
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
        registerFile.pc_reg, registerFile.rsp_reg, registerFile.ret_reg, registerFile.registers[0], registerFile.registers[1], registerFile.registers[2], registerFile.registers[4]);
    printf("R4:  0x%04X  R5:  0x%04X  R6:  0x%04X  R7:  0x%04X  R8:  0x%04X R9: 0x%04X  R10: 0x%04X\n", 
        registerFile.registers[5], registerFile.registers[6], registerFile.registers[7], registerFile.registers[8], registerFile.registers[9], registerFile.registers[10], registerFile.registers[11]);
    printf("R11: 0x%04X  R12: 0x%04X  R13: 0x%04X  R14: 0x%04X  R15: 0x%04X\n", 
        registerFile.registers[12], registerFile.registers[13], registerFile.registers[14], registerFile.registers[15], registerFile.registers[16]);
    std::cout << std::endl;
}

void display_register(uint32_t reg) {
    switch(reg) {
        case PC_REGISTER:
            printf("PC: 0x%04X\n", registerFile.pc_reg);
            break;
        case RET_REGISTER:
            printf("RET: 0x%04X\n", registerFile.ret_reg);
            break;
        case RSP_REGISTER:
            printf("RET: 0x%04X\n", registerFile.rsp_reg);
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
    uint32_t instruction = read_4_bytes(registerFile.pc_reg);
    registerFile.pc_reg += 4;
    /* Used for any opcodes that require an immediate */
    uint32_t immediate = read_4_bytes(registerFile.pc_reg);

    /* Decode. Extracting bits according to ISA specification. */
    uint32_t opcode = (instruction >> 14) & 0x3F;
    uint32_t flags = (instruction >> 10) & 0xF;
    uint32_t operand_1 = (instruction >> 5) & 0x1F;
    uint32_t operand_2 = (instruction) & 0x1F;

    DEBUG_PRINT_V("Instruction: 0x" << std::hex << std::setw(8) << std::setfill('0') << instruction);
    DEBUG_PRINT_V("Current PC:  0x" << std::hex << std::setw(8) << std::setfill('0') << registerFile.pc_reg);
    DEBUG_PRINT_V("Opcode:      0x" << std::hex << std::setw(4) << std::setfill('0') << opcode << " -> " << opcode_to_string(opcode));
    DEBUG_PRINT_V("Flags:       0x" << std::hex << std::setw(4) << std::setfill('0') << flags);
    DEBUG_PRINT_V("Operand 1:   0x" << std::hex << std::setw(4) << std::setfill('0') << operand_1);
    DEBUG_PRINT_V("Operand 2:   0x" << std::hex << std::setw(4) << std::setfill('0') << operand_2);
    DEBUG_PRINT_V("");
   
    /* Execute instruction. */
    switch (opcode) {
        case MOV_REG_REG_OPCODE:
            if(operand_1 == RSP_REGISTER) 
            break;
        case MOV_REG_MEM_OPCODE:
            
            break;
        case MOV_MEM_REG_OPCODE:
            
            break;
        case MOV_REG_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case MOV_MEM_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case ADD_REG_REG_OPCODE:
            
            break;
        case ADD_REG_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case SUB_REG_REG_OPCODE:
            
            break;
        case SUB_REG_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case MUL_REG_REG_OPCODE:
            // mul_reg_reg();
            break;
        case MUL_REG_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case DIV_REG_REG_OPCODE:
            // div_reg_reg();
            break;
        case DIV_REG_IMM_OPCODE:
            registerFile.pc_reg += 4;

            break;
        case AND_REG_REG_OPCODE:
            // and_reg_reg();
            break;
        case OR_REG_REG_OPCODE:
            // or_reg_reg();
            break;
        case XOR_REG_REG_OPCODE:
            // xor_reg_reg();
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
