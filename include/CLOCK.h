#pragma once
#include <stdint.h>

class CLOCK_CNTL
{
    enum CLK_SRC
    {
        XTL_CLK,//external crystal, 40 MKz for my board but could be as low as 2 MHz.
        PLL_CLK_80,//Internal pll, 320 to 480 stepped down
        PLL_CLK_160,
        PLL_CLK_240,
        RC_FAST_CLK,//8 MHz low power clk
        APLL_CLK_4,//audio pll clock
        APLL_CLK_2,
    };

    void setCPUClk(CLK_SRC c);
    uint16_t getAPBf();
};