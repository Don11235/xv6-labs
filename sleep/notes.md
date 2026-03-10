# Sleep Exercise (user/sleep.c)

**Goal:** Implement a user program `sleep` that pauses for a user-specified number of ticks in xv6.

---

## Concepts Learned

### 1. User Programs in xv6
- User programs are simple C programs in `user/` directory.
- Compiled and linked via `UPROGS` in the Makefile.
- They run in **user mode**, which has limited privileges.

### 2. System Calls
- `pause()` is a **system call** that pauses the process until the next tick.
- User code calls `pause()` — a **wrapper function**.
- Under the hood:
  1. Assembly wrapper loads system call number (`SYS_pause`) in a register.
  2. Executes `ecall` instruction → CPU switches to **kernel mode**.
  3. Kernel dispatches to `sys_pause()` in `kernel/sysproc.c`.
  4. `sys_pause()` does the actual work in kernel mode.

### 3. User ↔ Kernel Interaction
- **User mode:** Cannot access kernel memory directly.
- **Kernel mode:** Full access to memory, CPU, and hardware.
- System calls are a **controlled gate** from user mode to kernel mode.
- The CPU enforces this separation automatically.

### 4. Command-Line Arguments
- Programs receive `argc` and `argv`.
- Strings can be converted to integers using `atoi()`.
- Important to check input and handle errors (e.g., no argument passed).

### 5. Error Handling
- Always check for missing or invalid arguments.
- Print a clear error message to the user.

---
