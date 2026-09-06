#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
    void windowExceptionHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("windowexc");
    }

    void Level2InterruptHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("level2intr");
    }

    void Level3InterruptHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("level3intr");
    }

    void Level4InterruptHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("level4intr");
    }

    void Level5InterruptHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("level5intr");
    }

    void DebugExceptionHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("debugexc");
    }

    void NMIHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("nmiexc");
    }

    void KernelExceptionHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("kernelexc");

        while (1)
        {
        }
    }

    void UserExceptionHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("userexc \r\n");
        uint8_t low4 = epc & 0xF;

        uint32_t instrSize = 3;
        if (low4 == 0x0C || low4 == 0x0D)
        {
            instrSize = 2;
        }

        uint32_t newEpc = epc + instrSize;
        printf("userexc3 \r\n");

        __asm__ __volatile__(
            "wsr.epc1 %0 \n\t"
            :
            : "r"(newEpc));

        printf("userexc2 \r\n");
    }

    void DoubleExceptionHandler(uint32_t cause, uint32_t epc, uint32_t vaddr)
    {
        printf("doubleexc\r\n");
        UART0::sendChar('a');
        UART0::sendChar(cause + '0');

        for (int i = 7; i >= 0; i--)
        {
            uint8_t nibble = (epc >> (i * 4)) & 0x0F;

            if (nibble < 10)
            {
                UART0::sendChar(nibble + '0');
            }
            else
            {
                UART0::sendChar(nibble - 10 + 'A');
            }
        }
    }
}