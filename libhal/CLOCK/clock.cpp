#include <CLOCK.h>

#define RTC_CNTL_BASE_REG 0x3FF48000

#define RTC_CNTL_CLK_CONF_REG (RTC_CNTL_BASE_REG + 0x70)

#define DPORT_CPU_PER_CONF_REG (0x3FF00000 + 0x03C)

void CLOCK_CNTL::setCPUClk(CLOCK_CNTL::CLK_SRC c)
{
    uint32_t r1 = *(uint32_t*)(RTC_CNTL_CLK_CONF_REG);//RTC_CNTL_SOC_CLK_SEL
    uint32_t r2 = *(uint32_t*)(DPORT_CPU_PER_CONF_REG);// DPORT_CPU_PER_CONF_REG
    r1 &= ~(0b11 << 27);
    r2 &= ~(0b11);
    switch(c)
    {
        case XTL_CLK:
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
        case PLL_CLK_240:
            r2 |= 2;
            r1 |= (1 & 0b11) << 27;
            break;
    }

    *(uint32_t*)(RTC_CNTL_CLK_CONF_REG) = r1;
    *(uint32_t*)(DPORT_CPU_PER_CONF_REG) = r2;
}