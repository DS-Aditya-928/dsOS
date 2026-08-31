#pragma once

#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_TASKS 32

struct TaskInfo
{
    uint32_t registers[16]; // General-purpose registers.
    uint32_t trueReturnAddress;
    bool isActive = false;
};

class dsOS
{
private:
    static int curTask; // Current task index
    static int taskCount; // Total number of tasks
    static TaskInfo taskData[MAX_TASKS];

public:
    static bool createTask(void (*entry)(void), uint32_t stackSize);
    static void startScheduler();
    static void runInit();

    static void yield();
};
