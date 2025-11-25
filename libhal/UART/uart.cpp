#include "UART.h"
#include "string.h"
#include <stdint.h>

#define UART_FIFO_REG  0x0
#define UART_INT_ST_REG 0x8
#define UART_INT_ENA_REG 0xC
#define UART_INT_CLR_REG 0x10
#define UART_STATUS_REG 0x1C

#define UART_MEM_CNT_STATUS_REG 0x64

template<unsigned int uart>
void UART<uart>::onClkChange(uint16_t clock)
{
    UART0::print("UART Clock changed\r\n");
}

template<unsigned int uart>
int UART<uart>::init()
{
    unsigned int intEnable = *(unsigned int*)(uart + UART_INT_ENA_REG);
    intEnable |= (1 << 14);
   *(unsigned int*)(uart + UART_INT_ENA_REG) = intEnable;

   sendCharW('\r');
   sendCharW('\n');
    return(0);
}

template<unsigned int uart>
void UART<uart>::sendCharW(char c)
{
    *(char*)(uart + UART_FIFO_REG) = c;

    while(((*(unsigned int*)(uart + UART_INT_ST_REG) >> 14) & 1U) == 0)//endlessly loop while txdone bit is not set 
    {
        
    }
    *(unsigned int*)(uart + UART_INT_CLR_REG) |= (1U << 14);//clear the interrupt bit i.e set it to 0.
}

template<unsigned int uart>
bool UART<uart>::print(const char* x)
{
    int l = strlen(x);
    for(int i = 0; i < l; i++)
    {
        sendCharW(x[i]);
    }   

    return(true);
}

template<unsigned int uart>
bool UART<uart>::print(char x)
{
    sendCharW(x);

    return(true);
}

template<unsigned int uart>
bool UART<uart>::print(int x)
{
    int y = x;
    if(y < 0)
    {
        y = y * -1;
        sendCharW('-');
    }
    int b10 = 1;
    while(b10 * 10 <= y)
    {
        b10 = b10 * 10;
    }
    while(b10 > 0)
    {
        int digit = y/b10;
        y = y%b10;
        b10 = b10/10;
        sendCharW((char)(digit + '0'));
    }
    return(true);
}

template<unsigned int uart>
bool UART<uart>::print(uint32_t x)
{
    sendCharW('U');
    sendCharW('I');
    uint32_t y = x;
    uint32_t b10 = 1;
    while((b10 * 10) <= y)
    {
        b10 = b10 * 10;
    }
    while(b10 > 0)
    {
        int digit = y/b10;
        y = y%b10;
        b10 = b10/10;
        sendCharW((char)(digit + '0'));
    }
    return(true);
}

template <unsigned int uart>
unsigned int UART<uart>::available()
{
    unsigned int numBytes = (*(unsigned int*)(uart + UART_STATUS_REG)) & 0xFF; 
    unsigned int l3Bits = *(unsigned int*)(uart + UART_MEM_CNT_STATUS_REG) & 0b111;
    numBytes = numBytes | (l3Bits << 8);
    return(numBytes);
}

template <unsigned int uart>
char UART<uart>::read()
{
    return(*(char*)(uart));
}
template class UART<UART_0>;
template class UART<UART_1>;
template class UART<UART_2>;