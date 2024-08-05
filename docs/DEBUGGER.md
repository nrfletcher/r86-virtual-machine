# Debugger
Documentation of all available commands in program debugger
## Current Existing Commands
* reg [reg*] - shows all register values or optionally provide a register to read it (ex: 'reg rsp')
* mem [address, blocks] - shows memory at given address, in units of 32-byte blocks
* step - executes an instruction

things i want to add:
* be able to display current instruction at PC (so see what is executed next step)
* provide an arg for reg that displays values as decimal instead of hex