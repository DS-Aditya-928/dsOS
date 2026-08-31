#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UART_0 0x3FF40000
#define UART_1 0x3FF50000
#define UART_2 0x3FF6E000

template <unsigned int base>
class UART
{
public:
    static void sendChar(char x);
    static void setActive(int);
    static int init(uint32_t baudRate);
    static void print(const char* data, size_t len);
    static unsigned int available();
    static char read();
};

using UART0 = UART<UART_0>;
using UART1 = UART<UART_1>;
using UART2 = UART<UART_2>;