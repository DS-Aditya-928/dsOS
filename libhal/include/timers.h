#pragma once

#define TIMG0_BASE 0x3FF5F000
#define TIMG1_BASE 0x3FF60000

template <unsigned int base>
class TIMG
{
public:
    static void disableBootProtection();
};

using TIMG0 = TIMG<TIMG0_BASE>;
using TIMG1 = TIMG<TIMG1_BASE>;
