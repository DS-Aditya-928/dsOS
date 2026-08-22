#include "os.h"

using constructorSig = void (*)();
extern "C"
{
    extern constructorSig __init_array_start[]; // the type is what's at this location.
    extern constructorSig __init_array_end[];
}

void dsOS::runInit()
{
    for (constructorSig* i = __init_array_start; i < __init_array_end; i++)
    {
        (*i)();
    }
}