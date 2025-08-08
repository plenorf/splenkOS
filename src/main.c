#include <stdbool.h>
#include <stddef.h>
#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "gcc_functions.h"
#include "limine.h"
#include "gdt.h"


#define MIN_LOG_LEVEL 


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
    

    // display "Hello, World!"
    const char message[] = "Hello, world!\n";
    flanterm_write(ft_ctx, message, sizeof(message));

    gdt_init();

    const char message2[] = "GDT!!\n";
    flanterm_write(ft_ctx, message2, sizeof(message2));

    // We're done, just hang...
    hcf();
}