#include <Windows.h>
#include <stdio.h>

int main() {

	PVOID pAddress = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 100);
	CHAR* cString = "Isn't this awesome!";

	printf("[+] Base Address Allocated Memory: 0x%p \n", pAddress);
	getchar();

	HeapFree(GetProcessHeap(), 0, pAddress);

	return 0;

}