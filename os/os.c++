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
    dsOS::yield();
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

        dsOS::yield();
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

        dsOS::yield();
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

    //0x3FF00040: 3 enable, 4 flush, 5 done

    volatile uint32_t v = *(volatile uint32_t*)(0x3FF00040);
    v = v | (1 << 3); 
    *(volatile uint32_t*)(0x3FF00040) = v;
    
    *(volatile uint32_t*)(0x3FF00044) &= ~0x1F;

    printf("MMU entry for VAddr2 for PID 0/1 for the PRO_CPU: %u\r\n", *(uint32_t*)(0x3FF10000 + (192*4)) & 0xFFFFFF);
    volatile uint32_t* mmuTable = (volatile uint32_t*)0x3FF10000;
    
    // 64 kb page size = 0x10000
    // VAddr3 page 0 corresponds to MMU entry 192
    // real addr 0x8000 is in page 0.
    mmuTable[192] = 0x000;
    
    printf("Val: %x\r\n", *(volatile uint32_t*)0x40808000);

    volatile uint32_t u = *(volatile uint32_t*)(0x3FF00040);
    u = u | (1 << 4); 
    *(volatile uint32_t*)(0x3FF00040) = u;

    while(((*(volatile uint32_t*)(0x3FF00040) >> 5) & 1U) == 0)
    {
        //wait for done bit to be set
    }

    // real addr 0x18000 is in page 1
    mmuTable[192] = 0x001;

    printf("Val: %x\r\n", *(volatile uint32_t*)0x40808000);

    printf("MMU entry for VAddr2 for PID 0/1 for the PRO_CPU: %u\r\n", *(uint32_t*)(0x3FF10000 + (192*4)) & 0xFFFFFF);

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);

    dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    
    while(true)
    { 

    }
}