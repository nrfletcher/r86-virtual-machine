# Out of Order Processor
Simulating an out of order processor

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

## Fetch Decode Execute
Will need to define functions for:
* Fetch instruction from memory
* Decode instruction
* Execute instruction

## Memory Management
Implement LOAD/STORE for registers and memory as well as stack space

## Program Loader
Will need to add a functionality for:
* Reading in a program
* Load that program into memory 
* Begin execution of program


# Processor Design

## Pipelining
First step is to develop a simple pipelined processor
This includes:
* Recognizing dependencies
* Stalling
* Forwarding
* Speculative execution
* Look into optimal pipeline depth (?)

Secondly, implement the OOO aspect:
* Functional units
* Issue queue (reservation station)
* Register renaming
* Reorder buffer
* Handling misspeculation
* OOO as a pipeline
* Common data bus

resources:
https://www.cs.virginia.edu/~cr4bd/3130/S2024/


## Possible additions
I/O
<br>
Assembler

