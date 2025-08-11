#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct CPUState
{
	uint32_t rax;
	uint32_t rbx;
	uint32_t rcx;
	uint32_t rdx;

	uint32_t rsi;
	uint32_t rdi;
	uint32_t rbp;

	uint32_t error;

	uint32_t rip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t rsp;
	uint32_t ss;        
} __attribute__((packed)) CPUState;

typedef struct Task
{
	uint8_t stack[4096]; // 4KB
	CPUState* cpuState;
	void (*entryPoint)();
} Task;

typedef struct TaskManager
{
	Task *tasks[256];
	uint8_t currentTask;
	uint8_t numTasks;
} TaskManager;

void initTask(Task *task);
bool addTask(TaskManager taskManager, Task *task);
CPUState* schedule(TaskManager taskManager, CPUState* cpuState);