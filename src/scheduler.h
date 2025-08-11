#pragma once 
#include "cpu/interrupts/irq.h"
#include <stdbool.h>

enum ProcessStatus {
	READY,
	RUNNING,
	DEAD
};

typedef struct Process
{
	enum ProcessStatus status;
	InterruptFrame *context;
	struct Process *next;
} Process;

typedef struct Scheduler
{
	Process* currentProcess;
	Process* processesList;
} Scheduler;

static Scheduler *scheduler = NULL;

InterruptFrame* schedule(Scheduler *scheduler, InterruptFrame *context);
Process* initProcess(Process* newProcess, void (*func)(void), bool isUser);