#pragma once
#include <stdint.h>

class Timer
{
public:
    static void init();

    static uint64_t getTime();
    static void delayMicroseconds(uint64_t us);
    static void delay(uint64_t ms);//ms delay
};