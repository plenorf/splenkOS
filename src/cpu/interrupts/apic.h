/*#define CPUID_FEAT_EDX_APIC (1 << 9)
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800
#include <stdbool.h>
#include <stdint.h>

void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value);
uint32_t cpuReadIoApic(void *ioapicaddr, uint32_t reg);
void enable_apic();
uintptr_t cpu_get_apic_base();
void check_apic_base(uintptr_t apic);
bool check_apic();*/