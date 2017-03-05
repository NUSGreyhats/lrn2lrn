# Introduction to x86 Assembly

## Table of Contents
0. [Why Assembly](#why-assembly)
1. [Binary, Hex and Endians](#binary-hex-and-endians)
2. [How Does A Processor Work](#how-does-a-processor-work)
3. [Basic Registers](#basic-registers)
4. [Basic x86 Instructions](#basic-x86-instructions)
5. [Calling Conventions and Stack Frames](#calling-conventions-and-stack-frames)
6. [Hands-on Exercises](#hands-on-exercises)
7. [Resources](#resources)
8. [References](#references)

## Why Assembly

## Binary, Hex, and Endians
Our layman numbers are in base 10 form. Hexadecimal numbers, like its name suggests, are numbers in the base 16 form.

```
+-------------+----------+--------------+------------+
| Hexadecimal |  Decimal |  Hexadecimal |   Decimal  |
+-------------+----------+--------------+------------+
|      0      |     0    |       A      |      10    |
|      1      |     1    |       B      |      11    |
|      2      |     2    |       C      |      12    |
|      3      |     3    |       D      |      13    |
|      4      |     4    |       E      |      14    |
|      5      |     5    |       F      |      15    |
|      6      |     6    |              |            |
|      7      |     7    |              |            |
|      8      |     8    |              |            |
|      9      |     9    |              |            |
+-------------+----------+--------------+------------+
```

### Decimal
The value of a decimal number is as follows.
Considering the number: (1234) <sub>10</sub>

<p>(1234) <sub>10</sub> =  1(10)<sup>3</sup> + 2(10)<sup>2</sup> + 3(10)<sup>1</sup>+ 4(10)<sup>0</sup> = (1234) <sub>10</sub> </p>

###Hexadecimal
Similarly, the value of hexadecimals can be derived the same way.
Considering the number: (3D2F) <sub>16</sub>

<p>(3D2F) <sub>16</sub> =  3(16)<sup>3</sup> + 13(16)<sup>2</sup> + 2(16)<sup>1</sup>+ 15(16)<sup>0</sup> = (15663) <sub>10</sub> </p>

###0x prefix
In `C` based languages, hexadecimal numbers are prepended with a `0x` to tell the compiler that the number following is a hexadecimal.
 `(3D2F)` <sub>`16`</sub> will therefore appear as `0x3D2F`

##Little Endian and Big Endian
These two standards describe the order in which a sequence of bytes are stored in a computer’s memory.

![Little vs Big Endian](https://chortle.ccsu.edu/AssemblyTutorial/Chapter-15/bigLittleEndian.gif)

This order is important and must be known to the language compilers in order for values to be stored. 

Most of the time, the Big Endian standard is adopted as it is more intuitive. However, in certain cases like in Intel CPUs the Little Endian standard may be used, as this simplifies certain operations, thus improving efficiency.

###Big Endian
The ‘Big End’, ie. the most significant value in the sequence of bytes is stored into the smallest address, at the top of the stack.

###Little Endian
The ‘Little End’ ie. the least significant value in the sequence of bytes, is stored first into the smallest address, at the top of the stack.

The Little Endian standard is used in x86.


## How Does A Processor Work
This is not a computer architecture class. I am just going to tell you that a processor has a number of registers that can be used as temporary store of values, and one or more arithmetic and logic units (ALUs) that can perform operations on the registers.

The processor fetches instructions from the memory, determines what to do, be it adding two numbers or loading data from the memory, and executes it.

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
|                           |             |  ah  |  al  |
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
<h3>Syntax</h3>
There are two syntaxes of x86 Assembly:
<table>
<tr>
<th></th>
<th>AT&T</th>
<th>Intel</th>
</tr>
<tr>
<td>Parameter Order</td>
<td>`<operand> <src> <dst>`</td>
<td>`<operand> <dst> <src>`</td>
</tr>
  <tr>
    <td>Sigils</td>
    <td>Constants are prefixed with $<br/>
    Registers are prefixed with %</td>
<td>Assembler automatically detects</td>
  </tr>
</table>
In this lesson we’ll be referencing the AT&T syntax.

<h3>Memory Addressing Modes</h3>
There are 3 basic modes of addressing:<br>
- Immediate addressing
- Register addressing
- Memory addressing

```
     $0x1  = constant value 1
     %eax  = register value
 0x4(%eax) = memory address(register value + 4)
```

<h3>Data Movement Instructions</h3>
Commonly seen instruction suffixes:<br/>
- b (byte = 8 bits)
- w (word = 2 bytes = 16 bits)
- l (long = 4 bytes = 32 bits)

E.g. movw, pushl

<b>mov</b> - Move<br/>
Copies the data from src to dst. 
```
mov %eax, %edx       -->  edx = eax
mov $0x4, %edx       -->  edx = 0x4
mov $0x4, 0x4(%edx)  -->  mem(0x8) = 0x4
```

However memory-to-memory moves are not possible, you will have to load the value into register before copying into the destination memory.

Cannot be done:
```
mov 0x4(%eax), 0x8(%eax)
```

Correct method:
```
mov 0x4(%eax), %edx
mov %edx, 0x8(%eax)
```

<b>push</b> - Push stack<br/>
Writing a value into the stack.
```
push $0x4  -->  0x4 is now in stack
```

<b>pop</b> - Pop stack<br/>
Restoring value that is on top of the stack
```
pop %eax   -->  eax = 0x4, 0x4 is gone from stack
```

<h3>Arithmetic and Logic Instructions</h3>
<b>add</b> - Integer Addition<br/>Adds src and dst, and store results in dst
```
mov $0x4, %eax  -->  eax = 4
add $0x4, %eax  -->  eax = 8
```

<b>sub</b> - Integer Subtraction<br/>Subtracts src from dst, and store results in dst
```
mov $0x8, %eax  -->  eax = 8
sub $0x4, %eax  -->  eax = 4
```

<b>imul</b> - Integer Multiplication<br/>imul instruction has two formats - two-operands format and three-operands format. For both, the dst must be a register.<br>

Two operands:
```
mov  $0x4, %eax  -->  eax = 4
imul $0x4, %eax  -->  eax = 16
```

Three operands:
```
mov  $0x4, %eax        -->  eax = 4
imul $0x4, %eax, %edx  -->  edx = 16
```

<b>idiv</b> - Integer Division<br/>
idiv instruction takes in only one operand, either register value or memory location. It only works with signed numbers. Dividend is always either AH:AL (byte), DX:AX (word) or EDX:EAX (long). Quotient results will be stored in EAX and remainder is stored in EDX.

```
mov $0x4, %eax  -->  eax = 4
mov $0x2, %ebx  -->  ebx = 2
cltd            -->  convert signed long to signed double long (EAX -> EDX:EAX)
idiv %ebx       -->  eax = 2, edx = 0
```

<b>and, or, xor</b> - Bitwise Operations<br/>
Logical bitwise and, or, and exclusive or operations.

```
mov $0x4, %eax  -->  eax = 4
and $0xf, %eax  -->  eax = 4
and $0x0, %eax  -->  eax = 0

mov $0x4, %eax  -->  eax = 4
or  $0xf, %eax  -->  eax = 15
or  $0x0, %eax  -->  eax = 4

mov $0x4, %eax  -->  eax = 4
xor $0xf, %eax  -->  eax = 11
xor $0x0, %eax  -->  eax = 4
```

<b>not</b> - Bitwise Logical Not<br/>
not instruction takes in only one operand. Flips all bit values in the operand.

```
mov $0x4, %eax  -->  eax = 4
not %eax        -->  eax = 4294967291 (-5)
```

<b>neg</b> - Negate<br/>
Performs two’s complement negation on operand contents, which is essentially ‘not + 1’.

```
mov $0x4, %eax  -->  eax = 4
neg %eax        -->  eax = 4294967292 (-4)
```

<b>shl, shr</b> - Shift Left, Shift Right<br/>
Shift bits left and shift bits right.

```
mov $0x4 , %eax  -->  eax = 4
shl $0x1 , %eax  -->  eax = 8
shl $0x1c, %eax  -->  eax = 2,147,483,648 (negative if signed)
sh1 $0x1 , %eax  -->  eax = 0

mov $0x4,  %eax  -->  eax = 4
shr $0x1,  %eax  -->  eax = 2
shr $0x1c, %eax  -->  eax = 0
```

<h3>Control Flow Instructions</h3>
Control flow instructions allow you to make the program execute instructions at another address other than the next instruction in memory. The <u>label</u> notations are symbolic names for a memory address.

<b>jmp</b> - Jump<br/>
Causes the program to execute instruction at another memory address.

```
HelloWorld: mov $0x4, %eax
      jmp HelloWorld  --> Infinite loop, don’t do this.
```

<b>cmp</b> - Compare<br/>
Compare values of src and dst by using ‘sub’ instruction and stores into a special register called ‘Machine Status Word’ (MSW). cmp instruction is usually used before conditional jump instructions, and the result stored in the special register is referred to by them.

```
mov $0x4, %eax  -->  eax = 4
mov $0x1, %edx  -->  edx = 1
cmp %eax, %edx  -->  msw = -3
```

<b>jcondition</b> - Conditional Jump
<ul>
<li>je - Jump when Equal</li>
<li>jz - Jump when Zero</li>
<li>jne - Jump when Not Equal</li>
<li>jg - Jump when Greater Than</li>
<li>jge - Jump when Greater Than or Equal To</li>
<li>jl - Jump when Less Than</li>
<li>jle - Jump when Less Than or Equal To</li>
</ul>

```
mov $0x4, %eax  -->  eax = 4
mov $0x1, %edx  -->  edx = 1
cmp %eax, %edx  -->  msw = -3
je  HelloWorld  -->  don’t jump
jz  HelloWorld  -->  don’t jump
jne HelloWorld  -->  jump
jg  HelloWorld  -->  don’t jump
jge HelloWorld  -->  don’t jump
jl  HelloWorld  -->  jump
jle HelloWorld  -->  jump
```

## Calling Conventions and Stack Frames
To allow programs written by different programmers to be able to call one another, and to simplify the use of subroutines in general, programmers and compilers typically adopt a common calling convention. The calling convention is a protocol about how the call and return from subroutines, such as which registers are for arguments and which register stores the return value. With that, a programmer does not need to read the definition of a subroutine to determine how to pass parameters to that subroutine and how to get the return value from it.

Although we are not writing assembly, knowing the calling convention helps us to understand typical assembly code more easily. In this section, we will learn about the widely used C language calling convention.

These are the steps to call a subroutine:
1. Passing parameters
   a. On 32-bit systems, all arguments are pushed onto the stack in reverse order
   b. On 64-bit systems, the first 6 arguments are moved into registers in the following order: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`. Then the rest of the arguments are pushed onto the stack in reverse order
2. Invode `call` / `callq`, which will push the return address onto the stack, then jump to the subroutine (the callee)
3. The callee pushes the value of `rbp` / `ebp` onto the stack, then copies the value of`rsp` / `esp` into `rbp` / `ebp`
4. The callee allocates local variables by making space on the stack
5. When the callee returns, it leaves the return value in `rax` / `eax`, copies `rbp` / `ebp` back to `rsp` / `esp`, then pops the saved `rbp` / `ebp` and transfer control to the caller by invoking `ret`.

This is the stack frame of a subroutine that has 3 parameters and 3 local variables:
![A single stack frame](http://www.cs.virginia.edu/~evans/cs216/guides/stack-convention.png)

Note that the stack grows from higher addresses to lower addresses. The figure above is for a 32-bit system, so each cell in the stack is 32-bit wide, therefore the memory addresses are 4 bytes apart. (Use of e-prefixed registers also shows that it is 32-bit.)

Below is the assembly of a program that adds three hardcoded numbers and prints out the result, compiled in 32-bit.
```
0804840b <add_three>:
 804840b:       55                      push   %ebp
 804840c:       89 e5                   mov    %esp,%ebp
 804840e:       83 ec 10                sub    $0x10,%esp
 8048411:       8b 45 08                mov    0x8(%ebp),%eax
 8048414:       89 45 f4                mov    %eax,-0xc(%ebp)
 8048417:       8b 45 0c                mov    0xc(%ebp),%eax
 804841a:       89 45 f8                mov    %eax,-0x8(%ebp)
 804841d:       8b 45 10                mov    0x10(%ebp),%eax
 8048420:       89 45 fc                mov    %eax,-0x4(%ebp)
 8048423:       8b 55 f4                mov    -0xc(%ebp),%edx
 8048426:       8b 45 f8                mov    -0x8(%ebp),%eax
 8048429:       01 c2                   add    %eax,%edx
 804842b:       8b 45 fc                mov    -0x4(%ebp),%eax
 804842e:       01 d0                   add    %edx,%eax
 8048430:       c9                      leave
 8048431:       c3                      ret

08048432 <main>:
 8048432:       8d 4c 24 04             lea    0x4(%esp),%ecx
 8048436:       83 e4 f0                and    $0xfffffff0,%esp
 8048439:       ff 71 fc                pushl  -0x4(%ecx)
 804843c:       55                      push   %ebp
 804843d:       89 e5                   mov    %esp,%ebp
 804843f:       51                      push   %ecx
 8048440:       83 ec 14                sub    $0x14,%esp
 8048443:       6a 03                   push   $0x3
 8048445:       6a 02                   push   $0x2
 8048447:       6a 01                   push   $0x1
 8048449:       e8 bd ff ff ff          call   804840b <add_three>
 804844e:       83 c4 0c                add    $0xc,%esp
 8048451:       89 45 f4                mov    %eax,-0xc(%ebp)
 8048454:       83 ec 08                sub    $0x8,%esp
 8048457:       ff 75 f4                pushl  -0xc(%ebp)
 804845a:       68 00 85 04 08          push   $0x8048500
 804845f:       e8 7c fe ff ff          call   80482e0 <printf@plt>
 8048464:       83 c4 10                add    $0x10,%esp
 8048467:       b8 00 00 00 00          mov    $0x0,%eax
 804846c:       8b 4d fc                mov    -0x4(%ebp),%ecx
 804846f:       c9                      leave
 8048470:       8d 61 fc                lea    -0x4(%ecx),%esp
 8048473:       c3                      ret

```

Here's the 64-bit version of the same program. Take note that the arguments are passed using registers rather than pushing them onto the stack.
```
0000000000400526 <add_three>:
  400526:       55                      push   %rbp
  400527:       48 89 e5                mov    %rsp,%rbp
  40052a:       89 7d ec                mov    %edi,-0x14(%rbp)
  40052d:       89 75 e8                mov    %esi,-0x18(%rbp)
  400530:       89 55 e4                mov    %edx,-0x1c(%rbp)
  400533:       8b 45 ec                mov    -0x14(%rbp),%eax
  400536:       89 45 f4                mov    %eax,-0xc(%rbp)
  400539:       8b 45 e8                mov    -0x18(%rbp),%eax
  40053c:       89 45 f8                mov    %eax,-0x8(%rbp)
  40053f:       8b 45 e4                mov    -0x1c(%rbp),%eax
  400542:       89 45 fc                mov    %eax,-0x4(%rbp)
  400545:       8b 55 f4                mov    -0xc(%rbp),%edx
  400548:       8b 45 f8                mov    -0x8(%rbp),%eax
  40054b:       01 c2                   add    %eax,%edx
  40054d:       8b 45 fc                mov    -0x4(%rbp),%eax
  400550:       01 d0                   add    %edx,%eax
  400552:       5d                      pop    %rbp
  400553:       c3                      retq

0000000000400554 <main>:
  400554:       55                      push   %rbp
  400555:       48 89 e5                mov    %rsp,%rbp
  400558:       48 83 ec 10             sub    $0x10,%rsp
  40055c:       ba 03 00 00 00          mov    $0x3,%edx
  400561:       be 02 00 00 00          mov    $0x2,%esi
  400566:       bf 01 00 00 00          mov    $0x1,%edi
  40056b:       e8 b6 ff ff ff          callq  400526 <add_three>
  400570:       89 45 fc                mov    %eax,-0x4(%rbp)
  400573:       8b 45 fc                mov    -0x4(%rbp),%eax
  400576:       89 c6                   mov    %eax,%esi
  400578:       bf 14 06 40 00          mov    $0x400614,%edi
  40057d:       b8 00 00 00 00          mov    $0x0,%eax
  400582:       e8 79 fe ff ff          callq  400400 <printf@plt>
  400587:       b8 00 00 00 00          mov    $0x0,%eax
  40058c:       c9                      leaveq
  40058d:       c3                      retq

```

## Hands-on Exercises
Under [./build/](./build/) there are three programs whose names has the word "secret" in them. Try disassemble them and figure out what they do. Both 32-bit and 64-bit binaries are provided. The source code are in the `./src/` folder but please do not look at them before you attempt.

If you do not know how to disassemble a binary yet, one way to do it is:
```shell
$ objdump -d <binary_file>
```

## Resources
* [Intel x86 Instruction Set Reference](http://www.felixcloutier.com/x86/)
* [Difference Between Intel and AT&T Syntax](http://www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm)

## References
* <https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm>
* <http://www.cs.virginia.edu/~evans/cs216/guides/x86.html>
