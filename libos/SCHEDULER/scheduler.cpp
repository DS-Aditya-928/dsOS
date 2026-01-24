#include "OS.h"
#include "UART.h"

int dsOS::taskCount = 0; // Initialize task count
int dsOS::curTask = 0; // Initialize current task index
TaskInfo dsOS::taskData[MAX_TASKS];

void dsOS::hiddenYield(uint32_t* cRegs)
{
    asm volatile (
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
        : "r"(&taskData[curTask].registers)             // %0 = C variable regs
        :      
        );

    /*
    asm volatile (
        "s32i PC, %0, 64\n" // Save return address
        :
        : "r"(&taskData[curTask].registers)
        :
    );
    */
    taskData[curTask].registers[0] -= 0x40000000;
    //UART0::print(taskData[curTask].registers[0]);
    
    curTask++;
    if(curTask >= taskCount) curTask = 0; // Switch tasks round robin style baybeeeee
    asm volatile (
        "l32i a0,  %0,  0\n"
        "l32i a1,  %0,  4\n"
        "l32i a2,  %0,  8\n"
        "l32i a3,  %0, 12\n"
        "l32i a4,  %0, 16\n"
        "l32i a5,  %0, 20\n"
        "l32i a6,  %0, 24\n"
        "l32i a7,  %0, 28\n"
        //"l32i a8,  %0, 32\n"
        "l32i a9,  %0, 36\n"
        "l32i a10, %0, 40\n"
        "l32i a11, %0, 44\n"
        "l32i a12, %0, 48\n"
        "l32i a13, %0, 52\n"
        "l32i a14, %0, 56\n"
        "l32i a15, %0, 64\n"
        "jx a0\n" 
        : //"+r"(taskData[curTask].registers)
        : "r"(taskData[curTask].registers)
        : 
        );
}

bool dsOS::createTask(void (*entry)(void), uint32_t stackSize)
{
    if(taskCount >= MAX_TASKS) return(false);
    taskData[taskCount].stackPointer = (uint32_t)malloc(stackSize) + stackSize; // Allocate stack memory
    if(taskData[taskCount].stackPointer == 0) return(false); // Check if memory allocation was successful
    taskData[taskCount].isActive = true;
    taskData[taskCount].registers[0] = (uint32_t)entry; // Set entry point
    //taskData[taskCount].returnAddress = (uint32_t)entry; // Set entry point
    taskData[taskCount].registers[1] = taskData[taskCount].stackPointer; // Set stack pointer

    taskCount++;
    
    return(true);
}

void dsOS::startScheduler()
{
    if(taskCount == 0) return; // No tasks to schedule
    
    asm volatile (
        "l32i a0,  %0,  0\n"
        "jx a0\n"
        :
        : "r"(&taskData[0].registers) // Load the entry point of the first task
        :
    );
}