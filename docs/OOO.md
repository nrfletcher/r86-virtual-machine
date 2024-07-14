Eventually, I would like to add an OoO aspect to this

implement the OOO aspect:
* Functional units
* Issue queue (reservation station)
* Register renaming
* Reorder buffer
* Handling misspeculation
* OOO as a pipeline
* Common data bus

# Processor Design

## Pipelining
First step is to develop a simple pipelined processor
This includes:
* Recognizing dependencies
* Stalling
* Forwarding
* Speculative execution
* Look into optimal pipeline depth (?)