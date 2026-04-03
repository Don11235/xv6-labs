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
- Three things define a variable:
 - **name** — how you refer to it in code (`x`, `ptr`, `data`)
 - **type** — tells the compiler how many bytes to reserve and how to interpret them
 - **value** — the actual content stored in those bytes
- reference (K&R)

### 2. Memory
...

### 3. Pointer
...

### 4. Pointer casting
...

### 5. Pointer arithmetic
