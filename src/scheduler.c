#include "scheduler.h"
#include <stddef.h>
#include "cpu/gdt.h"
#include "util/logging.h"


InterruptFrame* schedule(Scheduler *scheduler, InterruptFrame *context) {
	scheduler->currentProcess->context = context; // save the current process context

	if (scheduler->currentProcess->next != NULL) { // there is still another process in the linked list
		//print("Switching to next process\n");
		scheduler->currentProcess = scheduler->currentProcess->next;
	} else { // we've reached the end of the process list, go back to the beginning!
		//print("Wrapping around to first process\n");
		scheduler->currentProcess = scheduler->processesList;
	}

	context = scheduler->currentProcess->context;
}

Process* initProcess(Process* newProcess, void (*func)(void), bool isUser) {
	asm ("cli");

	newProcess->status = READY;
	newProcess->next = NULL;
	
	InterruptFrame frame;
	newProcess->context = &frame;
	newProcess->context->int_no = 0x20;
	newProcess->context->err_code = 0x0;
	newProcess->context->rip = (uint64_t)func;
	newProcess->context->rdi = 0;
	newProcess->context->rsi = 0;
	newProcess->context->rflags = 0x202;
	newProcess->context->cs = GDT_CODE_SEGMENT;

	char stack[4096];
	newProcess->context->rsp = (uint64_t)stack + sizeof(stack);

	asm ("sti");
	return newProcess;
}