# Windows Memory Management

Hands-on C demos exploring how Windows allocates, manages, and releases memory. Each file is a standalone program targeting the Windows API.

---

## Demos

### 01 — Heap Allocation + memcpy
**[src/01_heap_memcpy.c](src/01_heap_memcpy.c)**

Allocates a buffer with `HeapAlloc`, copies a string into it with `memcpy`, pauses so you can inspect the raw bytes in a debugger, then frees the buffer with `HeapFree`. The `getchar()` pause is intentional — set a breakpoint there and examine the address printed to see exactly what the heap looks like before and after the write.

Key concepts: `HeapAlloc`, `HEAP_ZERO_MEMORY`, `memcpy`, `HeapFree`, `GetLastError`

---

### 02 — Stack vs Heap
**[src/02_stack_vs_heap.c](src/02_stack_vs_heap.c)**

Allocates the same data two ways — a fixed-size buffer on the stack inside a function, and a dynamic buffer on the heap — then prints both addresses. On x64 Windows the stack lives at a numerically higher address than the heap; the output makes this concrete.

Key concepts: stack frames, automatic storage, `HeapAlloc`/`HeapFree`, address space layout

---

### 03 — Virtual Address Space Walk
**[src/03_virtual_address_space.c](src/03_virtual_address_space.c)**

Calls `VirtualQuery` in a loop to enumerate every memory region in the process's virtual address space, printing its base address, size, state (FREE / RESERVE / COMMIT), type (PRIVATE / MAPPED / IMAGE), and protection flags. Run it and you can see exactly where your code, stack, heap, and mapped DLLs live.

Key concepts: `VirtualQuery`, `MEMORY_BASIC_INFORMATION`, `MEM_COMMIT`, `MEM_FREE`, `MEM_RESERVE`, page protection flags

---

### 04 — Leak vs Clean
**[src/04_leak_vs_clean.c](src/04_leak_vs_clean.c)**

Side-by-side comparison of a leaky allocation (HeapAlloc with no matching HeapFree) against a properly managed one. Calls each pattern three times so the addresses are visible. The OS reclaims everything at process exit, but the point is that leaked buffers are inaccessible for the entire process lifetime — in a long-running service this adds up.

Key concepts: memory leaks, `HeapFree`, process lifetime vs allocation lifetime

---

## Build

These programs use the Windows API and must be compiled on Windows.

**MSVC (Visual Studio Developer Command Prompt):**
```
cl /W4 src\01_heap_memcpy.c
cl /W4 src\02_stack_vs_heap.c
cl /W4 src\03_virtual_address_space.c
cl /W4 src\04_leak_vs_clean.c
```

**MinGW (gcc on Windows):**
```
gcc -Wall -o 01_heap_memcpy src/01_heap_memcpy.c
gcc -Wall -o 02_stack_vs_heap src/02_stack_vs_heap.c
gcc -Wall -o 03_virtual_address_space src/03_virtual_address_space.c
gcc -Wall -o 04_leak_vs_clean src/04_leak_vs_clean.c
```

---

## Debugger Tips

- Run `01_heap_memcpy` and when it pauses, open the **Memory** window in WinDbg or Visual Studio and navigate to the printed address. You'll see the ASCII string sitting in the heap buffer.
- In WinDbg: `db <address>` dumps raw bytes; `da <address>` displays as ASCII.
- Step into `HeapAlloc` with **Step Into** to watch the call stack build up and observe `RIP`/`RAX` as the allocator runs.
- Use **Watch** windows to track `pBuffer` and see its value change from `NULL` to the allocated address.
