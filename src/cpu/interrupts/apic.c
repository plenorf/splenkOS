
//TODO: Use the header instead of defining these here idk why but the header file doesn't include right
#define CPUID_FEAT_EDX_APIC (1 << 9)
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800
#include <stdbool.h>
#include <stdint.h>



bool check_apic() {
   uint32_t eax, edx;
   cpuid(1, &eax, &edx);
   return edx & CPUID_FEAT_EDX_APIC;
}



void check_apic_base(uintptr_t apic) {
    uint32_t edx = 0;
    uint32_t eax = (apic & 0xfffff0000) | IA32_APIC_BASE_MSR_ENABLE;

    #ifdef _PHYSICAL_MEMORY_EXTENSION_
        edx = (apic >> 32& 0x0f | IA32_APIC_BASE_MSR_ENABLE);
    #endif

        cpuSetMSR(IA32_APIC_BASE_MSR, eax, edx);
}

uintptr_t cpu_get_apic_base() {
   uint32_t eax, edx;
   cpuGetMSR(IA32_APIC_BASE_MSR, &eax, &edx);

#ifdef __PHYSICAL_MEMORY_EXTENSION__
   return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
#else
   return (eax & 0xfffff000);
#endif
}

void enable_apic() {
    cpu_set_apic_base(cpu_get_apic_base());
    write_reg(0xF0, ReadRegister(0xF0) | 0x100);
}