# OoO Processor
### Simulating an out of order processor and program execution

## Overview
An out-of-order processor is a CPU design which benefits from executing instructions out of their original "order" to avoid stalling.
By utilizing pipelining, which is essentially treating each execution unit (ALU, LOAD, etc.) as independent, we are able to make use of wasted cycles that an in-order processor would wait for. Being able to reorder instructions enables pipelining, which in turn also enables speculative execution. The majority of modern processors utilize OoO design due to the intense performance boosts. This project is purely academic, and is highly abstracted from the real hardware implementation of an OoO processor. 

## Purpose
The main purpose of this project is to re-teach myself how a computer program is executed, help myself learn C++ in a project-oriented way, and also (hopefully) provide a simple and insightful tool that others can use to learn about program execution as well as out-of-order processors at a high level. 

## Comparisons
The goal of this project is to implement both an in-order and out-of-order processor, keeping the rest of the the system interface the same to compare results. Once again, due to this all being based in software, it is strictly theoretical and the performance numbers cannot be viewed as legitimate comparisons to hardware implementations.

## Memory
Define regions of space for:
* Program memory
* Data memory
* Stack space

## Registers
Implement registers:
* Program counter
* Stack pointer
* General purpose

## Define ISA
Will need to define:
* Opcodes (add, sub, load, store, jump, etc.)
* Instruction format (16/32 bit, opcode, register, immediate)
# r86 Virtual Machine
r(iley)86 is a simplified x86 inspired virtual machine and program emulator.

## Overview
Currently under development.

## How To Load Machine Code Program
If you would like to run a program using machine code:
* Create a file ending in .txt
* Each line should be a single 32 bit instruction or immediate
* Immediates should go on a new line
* Individual bits can be seperated by whitespace (loader will ignore this)
* Lines can end with comments denoted by //, anything after is ignored by loaders




