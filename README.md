# Windows Memory Management Project

## Overview

In this project, I explored and applied concepts related to **Windows memory management**, including:

- **Virtual Memory** and **Paging**
- **Stack vs Heap** allocation
- Writing to and freeing memory to avoid **memory leaks**
- Debugging to inspect **raw memory** and understand how data is stored and retrieved.

#

1. **Virtual Memory and Paging**:
   - I learned how Windows manages memory using virtual memory and paging techniques to handle memory allocation efficiently.

2. **Memory Allocation**:
   - I wrote data to memory using `memcpy`, and then deallocated or freed the buffer. This highlights the importance of freeing memory to prevent memory leaks.

3. **Stack vs Heap Allocation**:
   - I got to differentiate between stack and heap allocation and observe how **heap allocation** dynamically manages memory at runtime.

4. **Using a Debugger**:
   - I was introduced to debuggers and inspected memory by entering specific memory addresses. I located the string stored using `memcpy` in the **raw memory** and stepped through the **HeapAlloc** function to observe how memory is allocated.
   - I explored the **call stack**, checked registers like `RIP` and `RAX`, and added watches for variables to gain deeper insight into the low-level execution of memory-related instructions.


This project provided valuable hands-on experience with memory management, debugging, and understanding how memory is allocated and deallocated in Windows. It emphasized the significance of properly freeing memory to prevent leaks and demonstrated how to use debuggers to inspect the state of memory during program execution.
