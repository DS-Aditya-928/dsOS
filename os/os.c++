#include <stdint.h>
#include <string.h>
#include <CLOCK.h>
#include <UART.h>
#include <WDT.h>
#include <MMU.h>
#include <GPIO.h>
#include <OS.h>

void testFunc1(void)
{
    int x = 0;
    while(true)

    {
        UART0::print("1 ");
        UART0::print(x);
        UART0::print("\r\n");
        x++;

        yield();
    }
}

void testFunc2(void)
{
    int x = 0;
    while(true)
    {
        UART0::print("2 ");
        UART0::print(x);
        UART0::print("\r\n");
        x--;

        yield();
    }
}

void testFunc3(void)
{
    int x = 0;
    while(true)
    {
        UART0::print("3 ");
        UART0::print(x);
        UART0::print("\r\n");
        x +=2;

        yield();
    }
}
extern "C" void  __attribute__((noreturn)) call_start_cpu0(void)
{  
    WDTRTC::disableBootProtection();
    WDT0::disableBootProtection();
    UART0::init();
    UART0::print(*(uint32_t*)(0x3FF40014) & 0xFFFFF);UART0::print("\r\n");
    for(volatile int i = 0; i < 1000000; i++);
    cMMU::init();
    CLOCK_CNTL::setCPUClk(CLOCK_CNTL::CLK_SRC::PLL_CLK_160);
    //*(uint32_t*)(DPORT_CPU_PER_CONF_REG) = 
    UART0::print(*(uint32_t*)(0x3FF40014) & 0xFFFFF);UART0::print("\r\n");
    UART0::print((*(uint32_t*)(0x3FF40020) >> 27) & 1);
    UART0::print("Kernel loaded!\r\n");
    UART0::print("Compiled on "); UART0::print(__DATE__); UART0::print(" at "); UART0::print(__TIME__); UART0::print(".\r\n");
    GPIO::setMode(2, 1);

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);
    UART0::print("\r\n");

    #define DPORT_CPU_PER_CONF_REG (0x3FF00000 + 0x03C)
    UART0::print(*(uint32_t*)(DPORT_CPU_PER_CONF_REG));
    //dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    while(true)
    {
        GPIO::write(2, 1);
        for(volatile int i = 0; i < 1000000; i++);
        GPIO::write(2, 0);
        for(volatile int i = 0; i < 1000000; i++);
    }
}