#include "os.h"

using constructorSig = void (*)();
extern "C"
{
    extern constructorSig __init_array_start[]; // the type is what's at this location.
    extern constructorSig __init_array_end[];
    extern uint32_t _vecbase_start;
}

void dsOS::runInit()
{
    __asm__ __volatile__(
        "wsr.vecbase %0 \n"
        "isync \n"
        :
        : "r"(&_vecbase_start)
        : "memory");

    for (constructorSig* i = __init_array_start; i < __init_array_end; i++)
    {
        (*i)();
    }
}