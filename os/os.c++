#include <stdint.h>
#include <string.h>
#include <CLOCK.h>
#include <UART.h>
#include <WDT.h>
#include <MMU.h>
#include <GPIO.h>
#include <OS.h>

int a = 0;
int b = 0;
int c = 0;

uint32_t a0Val = 0;

void dumbFunc(void)
{
    //save a0 value
    asm volatile (
        "mov %0, a0\n"
        : "=r"(a0Val)
        :
        : 
    ); 
    yield();
    UART0::print("Dumb Func\r\n");
    //restore a0 value
    asm volatile (
        "mov a0, %0\n"
        :
        : "r"(a0Val)
        : 
    );
}

void testFunc1(void)
{
    int x = 0;
    while(true)
    {
        UART0::print("1 ");
        UART0::print(a++);
        UART0::print("\r\n");
        //x++;
        //yield();
        dumbFunc();
    }
}

void testFunc2(void)
{
    int x = 0;
    while(true)
    {
        UART0::print("2 ");
        UART0::print(b--);
        UART0::print("\r\n");
        //x--;

        yield();
    }
}

void testFunc3(void)
{
    int x = 0;
    while(true)
    {
        UART0::print("3 ");
        UART0::print(c);
        UART0::print("\r\n");
        c +=2;

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

    UART0::print("Kernel loaded!\r\n");
    UART0::print("Compiled on "); UART0::print(__DATE__); UART0::print(" at "); UART0::print(__TIME__); UART0::print(".\r\n");
    GPIO::setMode(2, 1);

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);
    UART0::print("\r\n");
    UART0::print(*(uint32_t*)(0x3FF40000 + 0x14) & 0xFFFFFF);UART0::print("\r\n");

    dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    //volatile int x = 0;
    
    while(true)
    {
        /*
        GPIO::write(2, 1);
        for(volatile int i = 0; i < 1000000; i++);
        GPIO::write(2, 0);
        for(volatile int i = 0; i < 1000000; i++);
        */
    }
}