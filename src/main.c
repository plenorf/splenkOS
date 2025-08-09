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
    ok("Initialising GDT...");
    gdt_init();
    ok("Initialising IDT...");
    idt_init();
    ok("Remapping PIC...");
    pic_remap();

    for (;;) {
        
    }

    //warn("Kernel has run out of work! Halting the computer...");

    // We're done, just hang...
    //hcf();
}