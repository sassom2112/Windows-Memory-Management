#include <Windows.h>
#include <stdio.h>

static const char* state_str(DWORD state) {
    switch (state) {
        case MEM_COMMIT:  return "COMMIT ";
        case MEM_FREE:    return "FREE   ";
        case MEM_RESERVE: return "RESERVE";
        default:          return "UNKNOWN";
    }
}

static const char* type_str(DWORD type) {
    switch (type) {
        case MEM_IMAGE:   return "IMAGE  ";
        case MEM_MAPPED:  return "MAPPED ";
        case MEM_PRIVATE: return "PRIVATE";
        default:          return "-      ";
    }
}

int main() {
    MEMORY_BASIC_INFORMATION mbi;
    PVOID addr = NULL;
    int regions = 0;
    SIZE_T committed_kb = 0;

    printf("%-20s  %-14s  %-9s  %-9s  %s\n",
           "Base Address", "Size (KB)", "State", "Type", "Protect");
    printf("%-20s  %-14s  %-9s  %-9s  %s\n",
           "--------------------", "--------------", "---------", "---------", "----------");

    while (VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi)) {
        SIZE_T kb = mbi.RegionSize / 1024;

        printf("0x%016llX  %-14llu  %s  %s  0x%08lX\n",
               (unsigned long long)(ULONG_PTR)mbi.BaseAddress,
               (unsigned long long)kb,
               state_str(mbi.State),
               type_str(mbi.Type),
               mbi.Protect);

        if (mbi.State == MEM_COMMIT)
            committed_kb += kb;

        addr = (PBYTE)mbi.BaseAddress + mbi.RegionSize;
        regions++;

        /* Bail out past 8 TB — 64-bit address space is enormous */
        if ((ULONG_PTR)addr > 0x800000000000ULL)
            break;
    }

    printf("\n[+] Walked %d regions | Committed: %llu KB (%llu MB)\n",
           regions,
           (unsigned long long)committed_kb,
           (unsigned long long)(committed_kb / 1024));

    return 0;
}
