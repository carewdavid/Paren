# Paren
## Because Lisp didn't go far enough

Paren is an esoteric programming language whose syntax consists entirely of pairs of parentheses. It uses a stack based VM written in C.

## Syntax

A Paren program is a series of instructions each contained within a pair of parentheses.  Each instruction contains an opcode number, possibly followed by several arguments. e.g. `((...)[(...)...])(...)...`.

Numbers are written by nesting parentheses. 0 is `()`, 1 is `(())`. For convenience, documentation will use the notation `(x)` as a shorthand.

## Opcodes

The following table contains the opcodes in Paren:

| Code | Name     |
|------|----------|
| 0x00 | Exit     |
| 0x01 | Add      |
| 0x02 | Subtract |
| 0x03 | Multiply |
| 0x04 | Divide   |
| 0x05 | Compare  |
| 0x06 | Load     |
| 0x07 | Store    |
| 0x08 | I/O      |
| 0x09 | Dup      |
| 0x0A | Swap     |
| 0x0B | Drop     |
| 0x0C | Goto     |
| 0x0D | Call     |
| 0x0E | Ret      |

### Add
**Syntax:** `((1)[(x)[(y)]])`
**Behavior:** with zero arguments, pops the top two elements of the stack, adds them, and pushes the result; with one, pops the top value of the stack, adds x, and pushes the result; with two, computes `x + y` and pushes it onto the stack.

### Subtract
**Syntax:** `((2)[(x)[(y)]])`
**Behavior:** with zero arguments, pops the top two elements of the stack, subtracts them, and pushes the result; with one, pops the top value of the stack, subtracts x, and pushes the result; with two, computes `x - y` and pushes it onto the stack.

### Multiply
**Syntax:** `((3)[(x)[(y)]])`
**Behavior:** with zero arguments, pops the top two elements of the stack, multiplies them, and pushes the result; with one, pops the top value of the stack, multiplies by x, and pushes the result; with two, computes `x * y` and pushes it onto the stack.

### Divide
**Syntax:** `((4)[(x)[(y)]])`
**Behavior:** with zero arguments, pops the top two elements of the stack, divides them, and pushes the result; with one, pops the top value of the stack, divides by x, and pushes the result; with two, computes `x / y` and pushes it onto the stack. Note: Always performs integer division.

### Compare
**Syntax:** `((5)(c)[(x)[(y)]])`
**Behavior:** compares numbers. The first argument determines the type of comparison:
| c | operation |
|---|-----------|
| 0 | ==        |
| 1 | !=        |
| 2 | <         |
| 3 | <=        |
| 4 | >         |
| 5 | >=        |

The optional arguments are as with arithmetic: with none, compares the two top values on the stack; with one compares the argument to the top of the stack; with two compares its argument and pushes result. `0` indicates false; all other values are truthy.

### Load
**Syntax:** `((6)[(x)])`
**Behavior:** with no arguments, pops the top element of the stack and pushes the value in memory at that address. With an argument, pushes the value ad address x.

### Store
**Syntax:** `((7)[(x)[(y)]])`
**Behavior:** With no arguments, pops the top value off the stack and sets the address it points to to the next value on the stack (which is also popped). If `x` is

### I/O
**Syntax:** `((8)(d)(t))`
**Behavior:* if d is `0` read from standard in and pushes it onto the stack, if it is `1` pop the top of the stack and write it to standard out. If `t` is `0` operates on a character value, if it is `1` an integer.

### Dup
**Syntax:** `((9))`
**Behavior:** duplicates the top item of the stack. E.g. `x $ -> x x $`.

### Swap
**Syntax:** `((10))`
**Behavior:** swaps the two top items on the stack. E.g. `x y $ -> y x $`.

### Drop
**Syntax:** `((11))`
**Behavior:** pops the top item from the stack.

### Goto
**Syntax:** `((12)(x)[(d)])`
**Behavior:** Pops the top of the stack; if it is true jumps according to its arguments, otherwise falls through to the next instruction. With no optional arguments, jumps to instruction `x`; if d is `1`, jumps to `current instruction + x`; if `d` is `2`, jumps to  `current instruction - x`.

### Call
**Syntax:** `((13)(x)[(d)])`
**Behavior:** With no optional arguments, jumps to instruction `x`; if d is `1`, jumps to `current instruction + x`; if `d` is `2`, jumps to  `current instruction - x`. Pushes address of next instruction to the stack before jumping.

### Ret
**Syntax:** `((14))`
**Behavior:** Pops the top value off the stack and jumps to the instruction it points to.
