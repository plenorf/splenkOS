#include "multitasking.h"
#include <stddef.h>
#include "gdt.h"

void initTask(Task *task) {
	task->cpuState = (CPUState*)(task->stack + 4096 - sizeof(CPUState));

	task->cpuState->rax = 0;
	task->cpuState->rbx = 0;
	task->cpuState->rcx = 0;
	task->cpuState->rdx = 0;

	task->cpuState->rsi = 0;
	task->cpuState->rdi = 0;
	task->cpuState->rbp = 0;

	task->cpuState->rip = (uint64_t)task->entryPoint;
	task->cpuState->cs = GDT_CODE_SEGMENT;
	//task->cpuState->ss = 0;  // < not used when not dealing with different security levels
	task->cpuState->eflags = 0x202;
}

bool addTask(TaskManager taskManager, Task *task) {
	// we've reached the task limit
	if (taskManager.numTasks >= 256) {
		return false;
	}

	// add a task to the tasks list and increase the numTasks value
	taskManager.tasks[taskManager.numTasks++] = task;
	return true;
}

CPUState* schedule(TaskManager taskManager, CPUState* cpuState) {
	if (taskManager.numTasks <= 0)
		return cpuState;

	if (taskManager.currentTask != NULL) 
		taskManager.tasks[taskManager.currentTask]->cpuState = cpuState;

	if (++taskManager.currentTask >= taskManager.numTasks)
		taskManager.currentTask %= taskManager.numTasks;

	return taskManager.tasks[taskManager.currentTask]->cpuState;
}