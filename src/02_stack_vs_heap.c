#include <Windows.h>
#include <stdio.h>
#include <string.h>

void stack_demo() {
    char buf[64] = "I live on the stack";
    printf("[Stack] Address: 0x%p  |  Data: \"%s\"\n", (void*)buf, buf);
    /* buf is automatically reclaimed when this function returns — no free needed */
}

int main() {
    printf("=== Stack Allocation ===\n");
    stack_demo();
    /* buf is gone here — its stack frame was popped on return */

    printf("\n=== Heap Allocation ===\n");
    PVOID pHeap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 64);
    if (!pHeap) {
        fprintf(stderr, "[-] HeapAlloc failed: %lu\n", GetLastError());
        return 1;
    }
    memcpy(pHeap, "I live on the heap", 19);
    printf("[Heap]  Address: 0x%p  |  Data: \"%s\"\n", pHeap, (char*)pHeap);

    printf("\n=== Address Comparison ===\n");
    void* stack_ref = (void*)&pHeap;
    printf("[Stack var]  0x%p\n", stack_ref);
    printf("[Heap alloc] 0x%p\n", pHeap);
    /*
     * On x64 Windows the stack grows downward from a high address;
     * the heap sits in a lower region of the virtual address space.
     * You should see the stack address is numerically higher.
     */
    printf("Stack address is %s than heap address.\n",
           (ULONG_PTR)stack_ref > (ULONG_PTR)pHeap ? "higher" : "lower");

    HeapFree(GetProcessHeap(), 0, pHeap);
    printf("\n[+] Heap buffer freed.\n");

    return 0;
}
