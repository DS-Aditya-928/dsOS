#include "os.h"
#include "uart.h"
#include <stdlib.h>
#include <string.h>

int dsOS::taskCount = 0; // Initialize task count
int dsOS::curTask = 0; // Initialize current task index
TaskInfo dsOS::taskData[MAX_TASKS];

bool dsOS::createTask(void (*entry)(void), uint32_t stackSize)
{
    if (taskCount >= MAX_TASKS)
        return (false);
    taskData[taskCount].registers[1] = (uint32_t)malloc(stackSize);
    if (taskData[taskCount].registers[1] == 0)
        return (false);
    taskData[taskCount].registers[1] += stackSize;
    taskData[taskCount].isActive = true;
    taskData[taskCount].registers[0] = (uint32_t)entry;

    taskCount++;

    return (true);
}

void dsOS::startScheduler()
{
    if (taskCount == 0)
        return;

    asm volatile(
        "l32i a0,  %0,  0\n"
        "jx a0\n"
        :
        : "r"(&taskData[0].registers)
        :);
}

void dsOS::yield()
{
    // 1.) Save true return of this function in a0
    // 2.) Save all registers to the current task's register array
    // 3.) Change saved a0's value to where we want to be when we return back to this task
    // 4.) Increment curTask and load next task, jump to its a0.
    // Point is we are using a0 as the next tasks entry point but it's also the return addr so we need to restore it

    asm volatile(
        "mov %0, a0\n"
        : "=r"(dsOS::taskData[dsOS::curTask].trueReturnAddress)
        :
        :);

    asm volatile(
        "s32i  a0,  %0,  0\n"
        "s32i  a1,  %0,  4\n"
        "s32i  a2,  %0,  8\n"
        "s32i  a3,  %0, 12\n"
        "s32i  a4,  %0, 16\n"
        "s32i  a5,  %0, 20\n"
        "s32i  a6,  %0, 24\n"
        "s32i  a7,  %0, 28\n"
        "s32i  a8,  %0, 32\n"
        "s32i  a9,  %0, 36\n"
        "s32i  a10, %0, 40\n"
        "s32i  a11, %0, 44\n"
        "s32i  a12, %0, 48\n"
        "s32i  a13, %0, 52\n"
        "s32i  a14, %0, 56\n"
        "s32i  a15, %0, 60\n"
        :
        : "r"(dsOS::taskData[dsOS::curTask].registers) // %0 = C variable regs
        :);

    dsOS::taskData[dsOS::curTask].registers[0] = (uint32_t)&&restorePoint; // lol. lmao even.

    curTask++;
    if (curTask >= taskCount)
        curTask = 0; // Switch tasks round robin style baybeeeee

    asm volatile(
        "l32i a0,  %0,  0\n"
        "l32i a1,  %0,  4\n"
        "l32i a2,  %0,  8\n"
        "l32i a3,  %0, 12\n"
        "l32i a4,  %0, 16\n"
        "l32i a5,  %0, 20\n"
        "l32i a6,  %0, 24\n"
        "l32i a7,  %0, 28\n"
        "l32i a8,  %0, 32\n"
        "l32i a10, %0, 40\n"
        "l32i a11, %0, 44\n"
        "l32i a12, %0, 48\n"
        "l32i a13, %0, 52\n"
        "l32i a14, %0, 56\n"
        "l32i a15, %0, 60\n"
        "l32i a9,  %0, 36\n"
        "jx a0\n"
        :
        : "r"(taskData[curTask].registers)
        :);

restorePoint:
    asm volatile(
        "mov a0, %0\n"
        :
        : "r"(dsOS::taskData[dsOS::curTask].trueReturnAddress)
        :);
}