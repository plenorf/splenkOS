#include <apic.h>

bool check_apic() {
    uint32_t eax, edx;
   cpuid(1, &eax, &edx);
   return edx & CPUID_FEAT_EDX_APIC;
}