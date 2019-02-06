# Paren
## Because Lisp didn't go far enough

Paren is an esoteric programming language whose syntax consists entirely of pairs of parentheses. It uses a stack based VM written in C.

## Syntax

A Paren program is a series of instructions each contained within a pair of parentheses.  Each instruction represents an opcode number.

Numbers are written by nesting parentheses. 0 is `()`, 1 is `(())`. For convenience, documentation will use the notation `(x)` as a shorthand.

## Opcodes

The following table contains the opcodes in Paren:

| Code | Name     |
|------|----------|
| 0x00 | Exit     |
| 0x01 | Push     |
| 0x02 | Add      |
| 0x03 | Subtract |
| 0x04 | Multiply |
| 0x05 | Divide   |
| 0x06 | Compare  |
| 0x07 | Load     |
| 0x08 | Store    |
| 0x09 | I/O      |
| 0x0A | Dup      |
| 0x0B | Swap     |
| 0x0C | Drop     |
| 0x0D | Goto     |
| 0x0E | Call     |
| 0x0F | Ret      |

### Push
**Syntax:** `()`
**Behavior:** push the value of the next instruction onto the stack.

### Add
**Syntx:** `(())`
**Behavior:** pops the top two elements of the stack, adds them, and pushes the result.

### Subtract
**Syntax:** `((()))`
**Behavior:** pops the top two elements of the stack, subtracts them, and pushes the result.

### Multiply
**Syntax:** `((3))`
**Behavior:** pops the top two elements of the stack, multiplies them, and pushes the result.

### Divide
**Syntax:** `((4))`
**Behavior:** pops the top two elements of the stack, divides them, and pushes the result.

### Compare
**Syntax:** `((5))`
**Behavior:** Pops the top three items of the stack. The first argument determines the type of comparison:
| c | operation |
|---|-----------|
| 0 | ==        |
| 1 | !=        |
| 2 | <         |
| 3 | <=        |
| 4 | >         |
| 5 | >=        |
The result is pushed. `0` is false, all other values are true

### Load
**Syntax:** `((6))`
**Behavior:** pops the top element of the stack and pushes the value in memory at that address.

### Store
**Syntax:** `((7))`
**Behavior:** With no arguments, pops the top value off the stack and sets the address it points to to the next value on the stack (which is also popped).

### Read 
**Syntax:** `((8))`
**Behavior:** reads a character from standard in and pushes it to the stack

### Write
**Syntax:** `((9))`
**Behavior:** pops the top of the stack and writes it to standard out.

### Dup
**Syntax:** `((10))`
**Behavior:** duplicates the top item of the stack. E.g. `x $ -> x x $`.

### Swap
**Syntax:** `((11))`
**Behavior:** swaps the two top items on the stack. E.g. `x y $ -> y x $`.

### Drop
**Syntax:** `((12))`
**Behavior:** pops the top item from the stack.

### Goto
**Syntax:** `((13))`
**Behavior:** Pops the top of the stack; if it is true pops the next value and jumps to that address.

### Call
**Syntax:** `((14))`
**Behavior:** pops the top of the stack, pushes the address of the current instruction, and jumps to the address that was popped.

### Exit
**Syntax:** `((15))`
**Behavior:** halts execution of the program.
