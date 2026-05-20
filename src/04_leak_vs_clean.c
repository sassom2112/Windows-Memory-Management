#include <Windows.h>
#include <stdio.h>
#include <string.h>

/*
 * Allocates but never frees. In a long-running process this accumulates
 * until the process runs out of virtual address space or physical memory.
 * The OS reclaims everything when the process exits, but that's a safety
 * net — not a substitute for HeapFree.
 */
static void leaky_alloc() {
    PVOID p = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 256);
    if (!p) return;
    memcpy(p, "This buffer is never freed!", 27);
    printf("[LEAK]  Allocated at 0x%p  |  \"%s\"\n", p, (char*)p);
    /* intentionally no HeapFree — this is the bug */
}

static void clean_alloc() {
    PVOID p = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 256);
    if (!p) return;
    memcpy(p, "This buffer is properly freed.", 30);
    printf("[CLEAN] Allocated at 0x%p  |  \"%s\"\n", p, (char*)p);
    HeapFree(GetProcessHeap(), 0, p);
    printf("[CLEAN] 0x%p freed — memory returned to heap.\n", p);
}

int main() {
    printf("=== Leaky Allocation (called 3 times) ===\n");
    leaky_alloc();
    leaky_alloc();
    leaky_alloc();

    printf("\n=== Clean Allocation (called 3 times) ===\n");
    clean_alloc();
    clean_alloc();
    clean_alloc();

    printf("\n[*] Process exiting. OS reclaims all memory now,\n"
           "    but the three leaked buffers above were inaccessible\n"
           "    for the entire lifetime of the process.\n");

    return 0;
}
