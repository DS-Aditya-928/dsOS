#pragma once

#include "CLOCK.h"
#include <stdbool.h>
#include <stdint.h>

#define UART_0 0x3FF40000
#define UART_1 0x3FF50000
#define UART_2 0x3FF6E000

template<unsigned int base>
class UART: public ClkDep
{
private:
    //static const unsigned int uart = base;
    static void sendCharW(char x);
    static void onClkChange(uint16_t clock) override;
public:
    static void setActive(int);
    static int init();
    static bool print(const char* data);
    static bool print(int x);
    static bool print(uint32_t x);
    static bool print(char x);
    static unsigned int available();
    static char read();
};

using UART0 = UART<UART_0>;
using UART1 = UART<UART_1>;
using UART2 = UART<UART_2>;