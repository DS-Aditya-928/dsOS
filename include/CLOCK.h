#pragma once
#include <stdint.h>

class CLOCK_CNTL
{
public:
    enum CLK_SRC
    {
        XTL_CLK,//external crystal, 40 MKz for my board but could be as low as 2 MHz.
        PLL_CLK_80,//Internal pll, 320 to 480 stepped down
        PLL_CLK_160,
        //PLL_CLK_240, need to figure out the internal i2c bus to switch to 480, disable for now
        RC_FAST_CLK,//8 MHz low power clk
        APLL_CLK_4,//audio pll clock
        APLL_CLK_2,
    };

    static void init();
    static void getHPClock();//requests for APB to be upped tp 80 MHz
    static void releaseHPClock();//done w it, need 2 make sure this is followed :p
    static void setBaseClock(CLK_SRC c);

private:
    static uint32_t CPU_FREQ;
    static uint32_t APB_FREQ;
    static CLK_SRC baseClock;
    static void setCPUClk(CLK_SRC c);
    static volatile int numLocks;
};