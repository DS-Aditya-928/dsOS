#include <stdint.h>
#include <string.h>
#include <UART.h>
#include <WDT.h>
#include <MMU.h>
#include <GPIO.h>
#include <TIME.h>
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

    Timer::init();
    
    cMMU::init();
    UART0::init();

    UART0::print("Kernel loaded!\r\n");
    UART0::print("Compiled on "); UART0::print(__DATE__); UART0::print(" at "); UART0::print(__TIME__); UART0::print(".\r\n");
    GPIO::setMode(2, 1);

    dsOS::createTask(&testFunc1, 2048);
    dsOS::createTask(&testFunc2, 2048);
    dsOS::createTask(&testFunc3, 2048);
    UART0::print("\r\n");
    //dsOS::startScheduler();//flag as infinite non return blocking? shouldnt return bcos control is handed over solely to any tasks.
    while(true)
    {
        GPIO::write(2, 1);
        Timer::delay(1000);
        GPIO::write(2, 0);
        Timer::delay(1000);
        UART0::print("Time: ");
        UART0::print((uint32_t)Timer::getTime());
        UART0::print("\r\n");
    }
}