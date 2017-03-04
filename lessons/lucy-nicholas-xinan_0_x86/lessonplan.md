# Introduction to x86 Assembly

## Table of Contents
0. [Why Assembly](#why-assembly)
1. [Binary, Hex and Endians](#binary-hex-and-endians)
2. [How Does A Processor Work](#how-does-a-processor-work)
3. [Basic Registers](#basic-registers)
4. [Basic x86 Instructions](#basic-x86-instructions)
5. [Calling Conventions](#calling-conventions)
6. [Basic Stack Frames](#basic-stack-frames)
7. [Hands-on Exercises](#hands-on-exercises)
8. [Resources](#resources)
9. [References](#references)

## Why Assembly

## Binary, Hex, and Endians

## How Does A Processor Work

## Basic Registers
In x86, there are a lot of registers. We will only focus on the ones that we can usually see in assembly codes, including 8 of the 16 general purpose registers and 2 status registers.

### General Purpose Registers
First there are the 4 classical A, B, C, D registers. Take A as an example, the 64-bit version is named `rax`, the 32-bit version is named `eax`, the 16-bit version is named `ax`, the higher 8-bit of the 16-bit is named `ah` and the lower 8-bit of the 16-bit is named `al`. This is how it looks like:
```
                           rax
  _________________________/ \_________________________
 /                                                     \
+---------------------------+---------------------------+             
|                           |                           |             
|                           |            eax            |             
|                           |                           |             
|                           |             +-------------+             
|                           |             |     ax      |             
|                           |             +------+------+             
|                           |             |  al  |  al  |             
+---------------------------+-------------+------+------+             
```
It is the same for all the four A, B, C, D registers, even for the next four general purpose registers that we are going to talk about: `rsi`, `rdi`, `rbp`, and `rsp`. 

`rsi` and `rdi` are index registers, often used for indexed addressing. 

`rbp` and `rsp` are pointer registers. Although they are general purpose registers, they are often reserved for stack operations: `rbp` for base pointer, and `rsp` for stack pointer. We will talk more about stacks later. 

### Status Registers
There are only two status registers in x86. 

The first one is `rflags` / `eflags` / `flags`. It holds a lot of information about the ongoing processing, such as the last comparison result, last computation result, whether there was an overflow, whether interrupts should be ignored, etc. For example, if you have something in your code like `if (a > b) { ... }`, it will be compiled into two instructions. The first instruction compares `a` and `b` and store the result in `rflags`, the second instructions checks `rflags` and decide whether to branch or not.

The second one is `rip` / `eip` / `ip`, which is the instruction pointer. It points to the next instruction that the processor will be executing. If we can control where the instruction pointer poionts to, we can manipulate the control flow of the program.

## Basic x86 Instructions

## Calling Conventions

## Basic Stack Frames

## Hands-on Exercises

## Resources

## References
* <https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm>
* <http://www.cs.virginia.edu/~evans/cs216/guides/x86.html>
