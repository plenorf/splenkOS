#include "scheduler.h"
#include <stddef.h>
#include "cpu/gdt.h"
#include "util/logging.h"
#include "libc/string.h"
#include "mem/mem.h"
#include "gcc_functions.h"

InterruptFrame* schedule(Scheduler *scheduler, InterruptFrame *context) {
	scheduler->currentProcess->context = context; // save the current process context

	if (scheduler->currentProcess->next != NULL) { // there is still another process in the linked list
		//print("Switching to next process\n");
		scheduler->currentProcess = scheduler->currentProcess->next;
	} else { // we've reached the end of the process list, go back to the beginning!
		//print("Wrapping around to first process\n");
		scheduler->currentProcess = scheduler->processesList;
	}

	return scheduler->currentProcess->context;
}

Process* initProcess(Process* newProcess, void (*func)(void*), bool isUser) {
	asm volatile ("cli");

	newProcess->status = READY;
	newProcess->next = NULL;

	char *stack = kmalloc(4096);
	memset(stack, 0, 4096);

	InterruptFrame *frame = kmalloc(sizeof(InterruptFrame));
	*frame = (InterruptFrame){
		.int_no = 0x101,
		.err_code = 0x0,
		.rip = (uint64_t)func,
		.rdi = 0,
		.rsi = 0,
		.rflags = 0x202,
		.cs = GDT_CODE_SEGMENT,
		.rsp = ((uint64_t)stack + 4096),
		.rax = 1,
		.rcx = 0,
		.rdx = 0,
		.r8 = 0,
		.r9 = 0,
		.r10 = 0,
		.r11 = 0
	};
	newProcess->context = frame;

	char buf[32];
	itoa((uint64_t)newProcess->context->rsp, buf, 16);
	print("0x");
	print(buf);
	printChar('\n');
	itoa((uint64_t)newProcess->context->rip, buf, 16);
	print("0x");
	print(buf);
	printChar('\n');
	print("-----------\n");

	return newProcess;
}