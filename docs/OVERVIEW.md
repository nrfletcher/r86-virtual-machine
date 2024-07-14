resources:
https://www.cs.virginia.edu/~cr4bd/3130/S2024/

# Memory Design
How will memory look in this system. For sake of simplicity, and because this is a process simulation, not a full on OS, we will limit the scope to a single program.
## Memory Layout
Heavily inspired by Linux process virtual address space layout. While heap space is something to be implemented FAR DOWN the road (if ever), beginning with a traditional process memory design has no downsides I can make out, for now. Ignoring kernel space as there is no concept of user and kernel space in this program context.
### Sections
HIGH
<br>
Stack (grows down)
<br>
Heap (grows up)
<br>
BSS (Block Started by Symbol)
<br>
Data (Initialized static data)
<br>
Text (Binary instructions executed by processor)
<br>
LOW

# Registers
Registers will be inspired by x86 format but heavily minimized:
* PC (Program Counter)
* RT (Return value)
* SP (Stack pointer)
* R0 - R5 (First 6 arguments)
* R6 - R15 (General purpose registers)
Caller and callee saved:
* Handling this later

# Instruction Set Architecture
