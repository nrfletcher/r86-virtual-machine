# Memory Design
How will memory look in this system. For sake of simplicity, and because this is a process simulation, not a full on OS, we will limit the scope to a single program.

## Memory Layout
Heavily inspired by Linux process virtual address space layout. While heap space is something to be implemented FAR DOWN the road (if ever), beginning with a traditional process memory design has no downsides I can make out, for now. Ignoring kernel space as there is no concept of user and kernel space in this program context (this is not an OS, therefor there is no kernel and no concept of permissions).

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

## Memory Space
A program will be 64KB in size (64,000 bytes). For sake of simplicity as of now, each section will be 12.8k bytes large.
* Stack (addresses 64000 - 51200)
* Heap (addresses 51199 - 38400)
* BSS (addresses 38399 - 25600)
* Data (addresses 25599 - 12800)
* Text (addresses 12799 - 0)