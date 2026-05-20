#include <Windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char* src = "Isn't this awesome!";
    SIZE_T size = strlen(src) + 1;

    PVOID pBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    if (!pBuffer) {
        fprintf(stderr, "[-] HeapAlloc failed: %lu\n", GetLastError());
        return 1;
    }

    printf("[+] Heap buffer allocated at: 0x%p (%llu bytes)\n", pBuffer, (unsigned long long)size);

    memcpy(pBuffer, src, size);
    printf("[+] Copied to buffer:         \"%s\"\n", (char*)pBuffer);

    printf("[*] Inspect 0x%p in your debugger, then press Enter to free...\n", pBuffer);
    getchar();

    HeapFree(GetProcessHeap(), 0, pBuffer);
    printf("[+] Buffer freed. Memory returned to the heap.\n");

    return 0;
}
