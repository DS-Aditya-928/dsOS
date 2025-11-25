#include <CLOCK.h>
#define XTL_CLK_FREQ 40000000

#define RTC_CNTL_BASE_REG 0x3FF48000
#define SYSCON_BASE_REG 0x3FF66000

#define RTC_CNTL_CLK_CONF_REG (RTC_CNTL_BASE_REG + 0x70)

#define SYSCON_SYSCLK_CONF_REG (SYSCON_BASE_REG + 0x00)
#define SYSCON_XTAL_TICK_CONF_REG (SYSCON_BASE_REG + 0x04)
#define SYSCON_PLL_TICK_CONF_REG (SYSCON_BASE_REG + 0x08)
#define SYSCON_CK8M_TICK_CONF_REG (SYSCON_BASE_REG + 0x0C)
#define SYSCON_APLL_TICK_CONF_REG (SYSCON_BASE_REG + 0x3C)

#define DPORT_CPU_PER_CONF_REG (0x3FF00000 + 0x03C)

uint32_t CLOCK_CNTL::CPU_FREQ = 40;
uint32_t CLOCK_CNTL::APB_FREQ = 40;
volatile int CLOCK_CNTL::numLocks = 0;
CLOCK_CNTL::CLK_SRC CLOCK_CNTL::baseClock = CLOCK_CNTL::XTL_CLK;

void CLOCK_CNTL::init()
{
    //default clock is xtal 40 MHz
    baseClock = XTL_CLK;   
    setCPUClk(baseClock);
}

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
            *(uint32_t*)(SYSCON_SYSCLK_CONF_REG) &= ~(0x3FF);//set divider to 1 i.e 40 MHz when using xtal
            //in this case REFTICK is APB/SYSCON_XTAL_TICK_CONF_REG  so set to 39.
            *(uint32_t*)(SYSCON_XTAL_TICK_CONF_REG) &= ~0xFF;
            *(uint32_t*)(SYSCON_XTAL_TICK_CONF_REG) |= 39;
            break;
        case PLL_CLK_80:
            r2 |= 0;
            r1 |= (1 & 0b11) << 27;
            //in this case REFTICK is pulled from APB/ SYSCON_PLL_TICK_CONF_REG so set to 79.
            *(uint32_t*)(SYSCON_PLL_TICK_CONF_REG) &= ~0xFF;
            *(uint32_t*)(SYSCON_PLL_TICK_CONF_REG) |= 79;
            break;
        case PLL_CLK_160:
            r2 |= 1;
            r1 |= (1 & 0b11) << 27;
            //same here
            *(uint32_t*)(SYSCON_PLL_TICK_CONF_REG) &= ~0xFF;
            *(uint32_t*)(SYSCON_PLL_TICK_CONF_REG) |= 79;
            break;
        case RC_FAST_CLK:
            r2 |= 0;
            r1 |= (2 & 0b11) << 27;
            //CPU is at 8MHz. APB also at 8 MHz.
            *(uint32_t*)(SYSCON_CK8M_TICK_CONF_REG) &= ~0xFF;
            *(uint32_t*)(SYSCON_CK8M_TICK_CONF_REG) |= 7;
            break;
        /*
        case APLL_CLK_4:
            r2 |= 0;
            r1 |= (3 & 0b11) << 27;
            break;
        case APLL_CLK_2:
            r2 |= 1;
            r1 |= (3 & 0b11) << 27;
            */
    }

    *(uint32_t*)(RTC_CNTL_CLK_CONF_REG) = r1;
    *(uint32_t*)(DPORT_CPU_PER_CONF_REG) = r2;

    //recinfugyre ref_tick to output 1 MHz

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