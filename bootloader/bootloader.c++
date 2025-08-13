#include <stdint.h>
#include <string.h>
#include <UART.h>
#include <WDT.h>
#include <MMU.h>
#include <OS.h>

void testFunc1(void)
{
    int x = 0;
    while(true)
    {
        UART::print("1 ");
        UART::print(x);
        UART::print("\r\n");
        x++;

        yield();
    }
}

void testFunc2(void)
{
    int x = 0;
    while(true)
    {
        UART::print("2 ");
        UART::print(x);
        UART::print("\r\n");
        x--;

        yield();
    }
}

void testFunc3(void)
{
    int x = 0;
    while(true)
    {
        UART::print("3 ");
        UART::print(x);
        UART::print("\r\n");
        x +=2;

        yield();
    }
}
extern "C" void  __attribute__((noreturn)) call_start_cpu0(void)
{
    WDTRTC::disableBootProtection();
    WDT0::disableBootProtection();
    cMMU::init();
    UART::setActive(UART::UART0);
    UART::init();

    UART::print("Kernel loaded!\r\n");
    UART::print("Compiled on "); UART::print(__DATE__); UART::print(" at "); UART::print(__TIME__); UART::print(".\r\n");

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);

    dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    while(true)
    {

    }
}