# memdump (xv6 user program)

## Goal
Implement the function `memdump(char *fmt, char *data)` that prints the 
contents of memory pointed to by `data`, formatted according to `fmt`.

Each character in `fmt` describes how to interpret and print the next 
bytes of `data`. This allows printing any C struct or raw memory buffer 
by simply describing its layout as a format string.

## Concepts Practiced

### 1. Variable
- A variable is a `named` region of memory with a `type`, that stores a value.
### 2. Memory
Memory is a sequence of bytes. Each byte has a unique number called its address.

#### How it physically works

RAM is built as a grid internally (rows and columns), but the memory 
controller hides this complexity. From the CPU's perspective, memory 
looks like a simple flat list of numbered bytes:

address 0  →  [ byte ]
address 1  →  [ byte ]
address 2  →  [ byte ]
...

#### Two kinds of addresses

- **Physical address** — the real location in the RAM chip
- **Virtual address** — what your program sees

Your program never sees the real physical address. The MMU (Memory 
Management Unit), which lives inside the CPU chip, sits in between 
and translates:

your code  →  virtual address  →  MMU  →  physical address  →  RAM

#### The full picture

| Layer            | Deals with        |
|------------------|-------------------|
| Your C code      | virtual address   |
| MMU (inside CPU) | physical address  |
| Memory controller| row + column      |
| RAM chip         | actual cell       |

Each layer hides complexity from the layer above — this is called abstraction.

### 3. Pointer
...

### 4. Pointer casting
...

### 5. Pointer arithmetic
