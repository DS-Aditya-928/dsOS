#include <stdint.h>
#include <string.h>
#include "clock.h"
#include "uart.h"
#include "wdt.h"
#include "mmu.h"
#include "gpio.h"
#include "os.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

class X
{
public:
    X(int a)
    {
        x = a;
    }

    int getX()
    {
        return x;
    }
private:
    int x;
};

X exm = X(4);
X exm2 = X(5);

int a = 0;
int b = 0;
int c = 0;

uint32_t a0Val = 0;

void dumbFunc(void)
{
    yield();
    printf("Dumb func called!\r\n");
}

void testFunc1(void)
{
    int x = 0;
    while(true)
    {
        //print a1 stack pointer value
        uint32_t sp;
        asm volatile (
            "mov %0, a1\n"
            : "=r"(sp)
            :
            : 
        );
        printf("1 %d \r\n", x);
        x++;
        //yield();
        dumbFunc();
    }
}

void testFunc2(void)
{
    int x = 0;
    while(true)
    {
        uint32_t sp;
        asm volatile (
            "mov %0, a1\n"
            : "=r"(sp)
            :
            : 
        );
        printf("2 %d \r\n", x);
        x--;

        yield();
    }
}

void testFunc3(void)
{
    int x = 0;
    while(true)
    {
        uint32_t sp;
        asm volatile (
            "mov %0, a1\n"
            : "=r"(sp)
            :
            : 
        );
        printf("3 %d \r\n", x);
        x +=2;

        yield();
    }
}

extern "C" void  __attribute__((noreturn)) call_start_cpu0(void)
{  
    WDTRTC::disableBootProtection();
    WDT0::disableBootProtection();
    for(volatile int i = 0; i < 1000000; i++);
    CLOCK_CNTL::init();
    UART0::init(115200);
    cMMU::init();
    heapInit((void*)cMMU::getHeapStart(), cMMU::getHeapSize());

    dsOS::runInit();

    printf("Kernel loaded!\r\n");
    printf("Compiled on %s at %s.\r\n", __DATE__, __TIME__);
    char x[10];
    printf("itoa test: %s\r\n", itoa(12345, x, 10));
    printf("itoa test: %s\r\n", itoa(-12345, x, 10));
    printf("itoa test: %s\r\n", itoa(0xABCD, x, 16));
    GPIO::setMode(2, 1);

    /*
    Example 1. A PRO_CPU process, with a PID of 1, needs to read external flash address 0x07_2375 via virtual
    address 0x3F70_2375. The MMU is not in the special mode.
    • According to Table 4.3-9, virtual address 0x3F70_2375 resides in the 0x30’th page of .VAddr0
    • According to Table 4.3-10, the MMU entry for VAddr0 for PID 0/1 for the PRO_CPU starts at 0.
    • The modified MMU entry is 0 + 0x30 = 0x30.
    • Address 0x07_2375 resides in the 7’th 64 KB-sized page.
    • MMU entry 0x30 needs to be set to 7 and marked as valid by setting the 8’th bit to 0. Thus, 0x007 is
    written to MMU entry 0x30.
    */

    volatile uint32_t v = *(volatile uint32_t*)(0x3FF00040);
    v = v | (1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = v;
    
    *(volatile uint32_t*)(0x3FF00044) &= ~0x1F;

    printf("MMU entry for VAddr0 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (0x30*4)) & 0xFFFFFF);
    *(uint32_t*)(0x3FF10000 + (0x30*4)) = 0x7;
    printf("Val: %d\r\n", *(uint32_t*)0x3F702375);
    printf("MMU entry for VAddr0 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (0x30*4)) & 0xFFFFFF);
    *(uint32_t*)(0x3FF10000 + (0x30*4)) = 0x8;
    printf("Val: %d\r\n", *(uint32_t*)0x3F702385);
    printf("MMU entry for VAddr0 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (0x30*4)) & 0xFFFFFF);


    /*
    Example 2. An APP_CPU process, with a PID of 4, needs to read external flash address 0x44_048C via virtual
    address 0x4044_048C. The MMU is not in special mode.
    • According to Table 4.3-9, virtual address 0x4044_048C resides in the 0x4’th page of VAddr2 .
    • According to Table 4.3-11, the MMU entry for VAddr2 for PID 0/1 for the PRO_CPU starts at 128.
    • The modified MMU entry is 128 + 0x4 = 132.
    • Address 0x44_048C resides in the 0x44’th 64 KB-sized page.
    • MMU entry 132 needs to be set to 0x44 and marked as valid by setting the 8’th bit to 0. Thus, 0x044 is
    written to MMU entry 132.
    */

    /*
    volatile uint32_t v = *(volatile uint32_t*)(0x3FF00040);
    v = v | (1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = v;
    
    *(volatile uint32_t*)(0x3FF00044) &= ~0x1F;
    */

    printf("MMU entry for VAddr2 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (132*4)) & 0xFFFFFF);
    *(uint32_t*)(0x3FF10000 + (132*4)) = 0x44;
    printf("Val: %d\r\n", *(uint32_t*)0x4044048C);
    
    for(volatile int i = 0; i < 1000000; i++);
    volatile uint32_t u = *(volatile uint32_t*)(0x3FF00040);
    u = u | (1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = u;

    u = *(volatile uint32_t*)(0x3FF00040);
    u = u & ~(1 << 4); 
    *(volatile uint32_t*)(0x3FF00040) = u;
    for(volatile int i = 0; i < 1000000; i++);

    for(volatile int i = 0; i < 1000000; i++);
    u = *(volatile uint32_t*)(0x3FF00040);
    u = u & ~(1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = u;
    
    printf("MMU entry for VAddr2 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (132*4)) & 0xFFFFFF);
    *(uint32_t*)(0x3FF10000 + (132*4)) = 0x40;
    for(volatile int i = 0; i < 1000000; i++);
     u = *(volatile uint32_t*)(0x3FF00040);
    u = u | (1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = u;

    u = *(volatile uint32_t*)(0x3FF00040);
    u = u & ~(1 << 4); 
    *(volatile uint32_t*)(0x3FF00040) = u;
    for(volatile int i = 0; i < 1000000; i++);

    for(volatile int i = 0; i < 1000000; i++);
     u = *(volatile uint32_t*)(0x3FF00040);
    u = u & ~(1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = u;
    for(volatile int i = 0; i < 1000000; i++);
    printf("Val: %d\r\n", *(uint32_t*)0x4044048C);
    printf("MMU entry for VAddr2 for PID 0/1 for the PRO_CPU: %d\r\n", *(uint32_t*)(0x3FF10000 + (132*4)) & 0xFFFFFF);

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);

    dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    
    while(true)
    { 

    }
}