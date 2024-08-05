<div align="center">
<a name="readme-top"></a>
  
# ✳️ r86 Virtual Machine
A minimal LC-3 and x86 based virtual machine.

</div>

## Overview
r86 aims to be a simplistic, navigable, and educational virtual machine that offers a casual experience of running machine code instructions to emulate a processor. r86 plans to come with a program loader, debugging tools, and assembler.

## How To Load Machine Code Program
If you would like to run a program using machine code:
* Create a file ending in .txt
* Each line should be a single 32 bit instruction or immediate
* Immediates should go on a new line
* Individual bits can be seperated by whitespace (loader will ignore this)
* Lines can end with comments denoted by //, anything after is ignored by loaders

## Registers
r86 provides the following registers:
* PC: the program counter, holds the address of the currently executing instruction in memory
* RSP: the stack pointer, holds the address of the current top of the stack
* RET: the return register, a special register used as the container for a function return. Comparable to RAX in x86-64.
* R0 - R15: a set of 16 general purpose registers which can be used however the programmer would like. Callee and caller rules for function execution is a work-in-progress.

## Debugging
r86 provides a simple GDB-esque debugger with a few helpful commands for stepping through and analyzing a program as it runs.

Below are the currently supported commands, and the valid arguments you can provide when using them.

```bash
step
```
Step allows you to execute a single instruction in the program. This works fairly identically to step in GDB.

```bash
mem 0xFFFF 5
```
Mem allows you to provide a memory address in hex (currently only supported format) and the number of 32-byte blocks you want to display starting at that address.

```bash
reg rsp r4
```
Reg allows you to display either all registers by providing no argument, or a list of space separated arguments to display specific registers.

```bash
end
```

