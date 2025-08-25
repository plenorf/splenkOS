#include "main.h"
#include <stdbool.h>
#include <stddef.h>
#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "gcc_functions.h"
#include "limine.h"
#include "cpu/gdt.h"
#include "cpu/interrupts/idt.h"
#include "libc/string.h"
#include "cpu/interrupts/pic.h"
#include "util/command_parser.h"
#include "hardware/pci.h"
#include "scheduler.h"
#include "mem/mem.h"

#include "drivers/timer.h"
#include "drivers/keyboard.h"


#define MIN_LOG_LEVEL DEBUG
#include "util/logging.h"


// Set the base revision to 3, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;


// half and catch fire, basically just "FUCK" if it were a function
static void hcf(void) {
	for (;;) {
		asm ("hlt");
	}
}


void kpanic(InterruptFrame* frame) {
    static const char* exceptionLabels[] = {
        "[0x00] Divide by Zero Exception",
        "[0x01] Debug Exception",
        "[0x02] Unhandled Non-maskable Interrupt",
        "[0x03] Breakpoint Exception",
        "[0x04] Overflow Exception",
        "[0x05] Bound Range Exceeded Exception",
        "[0x06] Invalid Opcode/Operand Exception",
        "[0x07] Device Unavailable Exception",
        "[0x08] Double Fault",
        "[0x09] Coprocessor Segment Overrun",
        "[0x0A] Invalid TSS Exception",
        "[0x0B] Absent Segment Exception",
        "[0x0C] Stack-segment Fault",
        "[0x0D] General Protection Fault",
        "[0x0E] Page Fault",
        "[0x0F] Inexplicable Error",
        "[0x10] x87 Floating Exception",
        "[0x11] Alignment Check",
        "[0x12] Machine Check",
        "[0x13] SIMD Floating Exception",
        "[0x14] Virtualized Exception",
        "[0x15] Control Protection Exception",
        "[0x16] Inexplicable Error",
        "[0x17] Inexplicable Error",
        "[0x18] Inexplicable Error",
        "[0x19] Inexplicable Error",
        "[0x1A] Inexplicable Error",
        "[0x1B] Inexplicable Error",
        "[0x1C] Hypervisor Intrusion Exception",
        "[0x1D] VMM Communications Exception",
        "[0x1E] Security Exception",
        "[0x1F] Inexplicable Error"
    };

    print("\x1b[2J\x1b[H\n"); // clear screen and reset cursor pos

    // display ascii art
    print("       @@@@@@                     @@@@@@        \n");
    print("    @@@@    @@                  @@:    @@       \n");
    print("    @@@  @  @@       @@@@@@@@  @@  @  @@@       \n");
    print("    @@@     @@@@@@@@@@@@@@@@@@@@*      @@@      \n");
    print("     @@@@@@@                    @@@@@@ @@@      \n");
    print("     @@                               @@@       \n");
    print("   @@@                                  @@      \n");
    print("  =@@                                    @@     \n");
    print("  @@@                                      @@   \n");
    print("  @@                                       @@   \n");
    print("  @@                    @@@@@@@            @@   \n");
    print("  @@                 @@@@     @@          @@    \n");
    print("  @@@               @@         @@.        @@    \n");
    print("   @@              @@           @@        @     \n");
    print("   @@              @@           *@        @@    \n");
    print("    @                                       =@@@\n");
    print("-@@@@                                         @@\n");
    print("@@               @@@@@@@@@@@@@       @@@@@@@@@@@\n");
    print("@     @@@@     @@@@          @@@     @@@ %@@@@@ \n");
    print("@@@@@@@@@     %@@               @@@@@@          \n");
    print("        @    @@                                 \n");
    print("         @@@@@                                  \n");

    print("\n\nUhh.. Something \x1b[1;31mBAD\x1b[0m happened...\n");
    print("There was a kernel panic, here's some error info.\n\n");

    print("Interrupt Info:\n");
    char itoaBuf[32];
    print("\t- ");
    print(exceptionLabels[frame->int_no]);
    print("\n\t- Error Code: 0x");
    print(itoa(frame->err_code, itoaBuf, 16));

    print("\n\nRegister Dump:\n");

    print("\t- RIP: 0x");
    print(itoa(frame->rip, itoaBuf, 16));
    print("\n\t- CS : 0x");
    print(itoa(frame->cs, itoaBuf, 16));
    print("\n\t- RF : 0x");
    print(itoa(frame->rflags, itoaBuf, 16));
    print("\n\t- RSP: 0x");
    print(itoa(frame->rsp, itoaBuf, 16));
    print("\n\t- RAX: 0x");
    print(itoa(frame->rax, itoaBuf, 16));
    print("\n\t- RCX: 0x");
    print(itoa(frame->rcx, itoaBuf, 16));
    print("\n\t- RDX: 0x");
    print(itoa(frame->rdx, itoaBuf, 16));
    print("\n\t- RDI: 0x");
    print(itoa(frame->rdi, itoaBuf, 16));
    print("\n\t- RSI: 0x");
    print(itoa(frame->rsi, itoaBuf, 16));
    print("\n\t- R8 : 0x");
    print(itoa(frame->r8, itoaBuf, 16));
    print("\n\t- R9 : 0x");
    print(itoa(frame->r9, itoaBuf, 16));
    print("\n\t- R10: 0x");
    print(itoa(frame->r10, itoaBuf, 16));
    print("\n\t- R11: 0x");
    print(itoa(frame->r11, itoaBuf, 16));

    print("\n\nThe computer will now halt.\n");

    // completely halt and catch fire
    hcf();
}

void idle() {
    while (1)
    {
        print("A\n");
        asm("hlt");
    }
    
}

void test() {
    while (1)
    {
        print("B\n");
        asm("hlt");
    }
    
}

// 1 MB heap + bitmap
static uint8_t heap_area[1024 * 1024];
static uint8_t pmm_bitmap[1024 * 128]; // enough for ~128MB RAM meaing we can track 1,048,576 frames or 4 GiB RAM add more if you feel like it

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
void kmain(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // setup flanterm
    init_console(framebuffer);

    print("\n\033[2m[===============    BOOT LOG    ===============]\033[22m\n\n");

    ok("Setting up memory manager...");
    pmm_init(128 * 1024 * 1024, (uintptr_t)pmm_bitmap); // pretend 128MB RAM
    heap_init(heap_area, sizeof(heap_area));
    mm_dump();

    // print out framebuffer resolution
    char xBuffer[8];
    char yBuffer[8];
    char finalBuf[128] = "Framebuffer resolution: \0";
    itoa(framebuffer->width, xBuffer, 10);
    itoa(framebuffer->height, yBuffer, 10);
    strcat(finalBuf, xBuffer);
    strcat(finalBuf, "x");
    strcat(finalBuf, yBuffer);
    info(finalBuf);

    // do setup
    ok("Starting task scheduler...");
    Scheduler mainScheduler;
    scheduler = &mainScheduler;

    Process idleProcess;
    initProcess(&idleProcess, idle, false);
    scheduler->processesList = &idleProcess;
    scheduler->currentProcess = &idleProcess;

    Process testProcess;
    initProcess(&testProcess, test, false);
    scheduler->currentProcess->next = &testProcess;

    ok("Detecting hardware...");
    select_drivers();
    ok("Starting drivers...");
    register_driver(timerDriver);
    register_driver(keyboardDriver);
    start_drivers();

    ok("Initialising GDT...");
    gdt_init();
    ok("Initialising IDT...");
    idt_init();
    ok("Remapping PIC...");
    PIC_remap(PIC1, PIC1);

    

    print("\n\033[2m[=============== BOOT COMPLETE  ===============]\033[22m\n\n");

    print("Welcome to SplenkOS!\n");
    print("Type \"help\" for a list of commands.\n\n");

    while (1)
    {
        print("> ");

        char userInput[255];
        input(userInput);

        parseCommand(userInput, framebuffer);

        userInput[0] = '\0';

        printChar('\n');
    }
    

    warn("Kernel has run out of work! Halting the computer...");

    // We're done, just hang...
    hcf();
    
}