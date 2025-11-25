#include <CLOCK.h>

#define RTC_CNTL_BASE_REG 0x3FF48000

#define RTC_CNTL_CLK_CONF_REG (RTC_CNTL_BASE_REG + 0x70)

#define DPORT_CPU_PER_CONF_REG (0x3FF00000 + 0x03C)

uint32_t CLOCK_CNTL::CPU_FREQ = 40;
uint32_t CLOCK_CNTL::APB_FREQ = 40;


volatile int CLOCK_CNTL::numLocks = 0;
volatile int CLOCK_CNTL::numDeps = 0;

void CLOCK_CNTL::setCPUClk(CLOCK_CNTL::CLK_SRC c)
{
    uint32_t r1 = *(uint32_t*)(RTC_CNTL_CLK_CONF_REG);//RTC_CNTL_SOC_CLK_SEL
    uint32_t r2 = *(uint32_t*)(DPORT_CPU_PER_CONF_REG);// DPORT_CPU_PER_CONF_REG
    r1 &= ~(0b11 << 27);
    r2 &= ~(0b11);
    switch(c)
    {
        case XTL_CLK:
            r2 |= 0;
            r1 |= (0 & 0b11) << 27;
            break;
        case PLL_CLK_80:
            r2 |= 0;
            r1 |= (1 & 0b11) << 27;
            break;
        case PLL_CLK_160:
            r2 |= 1;
            r1 |= (1 & 0b11) << 27;
            break;
        case RC_FAST_CLK:
            r2 |= 0;
            r1 |= (2 & 0b11) << 27;
            break;
        case APLL_CLK_4:
            r2 |= 0;
            r1 |= (3 & 0b11) << 27;
            break;
        case APLL_CLK_2:
            r2 |= 1;
            r1 |= (3 & 0b11) << 27;
    }

    *(uint32_t*)(RTC_CNTL_CLK_CONF_REG) = r1;
    *(uint32_t*)(DPORT_CPU_PER_CONF_REG) = r2;

    for(int i = 0; i < (CLOCK_CNTL::numDeps, __ATOMIC_RELAXED); i++)
    {
        CLOCK_CNTL::apbDeps[i]->onClkChange(APB_FREQ);
    }
}

void CLOCK_CNTL::getHPClock()
{
    if(__atomic_load_n(&numLocks, __ATOMIC_RELAXED) == 0)
    {
        //switch to the high freq clock
        setCPUClk(PLL_CLK_160);//apb is now 80MHz.
    }
    __atomic_fetch_add(&numLocks, 1, __ATOMIC_RELAXED);
}

void CLOCK_CNTL::releaseHPClock()
{
    if(__atomic_load_n(&numLocks, __ATOMIC_RELAXED) == 0)//invalid
    {
        return;
    }

    if(__atomic_sub_fetch(&numLocks, 1, __ATOMIC_RELAXED) == 0)
    {
        setCPUClk(baseClock);
    }
}