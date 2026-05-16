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
Most people define a pointer as "an address" — this is incorrect.

A pointer is a variable whose value is an address of a location in memory.

The difference matters because a pointer has TWO addresses involved:

- its **own address** — where the pointer variable itself lives in memory
- its **value** — the address it holds, pointing to another location

Example:

int x = 42;
int *p = &x;

p has its own address in memory        (where p lives)
p holds the address of x as its value  (what p points to)

A pointer is a variable first. It just happens to store an 
address as its value instead of a number or character.

**Reference:** K&R Section 5.1 — "A pointer is a variable that 
contains the address of a variable."

### 4. Pointer casting
When we cast a pointer we change how the program interprets the bytes 
at that address.

For example, a pointer points to a `char` variable (1 byte). 
Casting it to `int *` means we now read 4 bytes instead of 1:

char c = 'A';
char *p = &c;
```
*p           →  reads 1 byte   (char)
*((int *)p)  →  reads 4 bytes  (int)
```
The address did not change. The bytes in memory did not change.
Only the interpretation changed.

This is exactly what memdump uses — it receives a raw `char *` buffer 
and casts it to different types depending on the format character:
```
'i'  →  *((int *)ptr)     reads 4 bytes as integer
'h'  →  *((uint16 *)ptr)  reads 2 bytes as short
'c'  →  *ptr              reads 1 byte  as character
'p'  →  *((uint64 *)ptr)  reads 8 bytes as hex
```
### 5. Pointer arithmetic
Pointer arithmetic is a way to move a pointer forward or backward 
in memory. The movement is based on the size of the type it points to.
```
char *p  →  p + 1  moves 1 byte
int  *p  →  p + 1  moves 4 bytes
```
This is exactly why in memdump we use char *ptr as the base pointer — because char is 1 byte, so we have full control over exactly how many bytes we move:
```
ptr += 4;  // move exactly 4 bytes after reading 'i'
ptr += 2;  // move exactly 2 bytes after reading 'h'
ptr += 1;  // move exactly 1 byte  after reading 'c'
ptr += 8;  // move exactly 8 bytes after reading 'p'
```
If ptr was int * instead of char *, ptr += 1 would move 4 bytes and we would lose control of the exact byte position.
