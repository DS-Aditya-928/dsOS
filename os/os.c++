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

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);

    dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    
    while(true)
    { 

    }
}