#include "TIME.h"

#define TIMG0_BASE 0x3FF5F000
#define TIMG1_BASE 0x3FF60000

#define SUBT0_BASE 0
#define SUBT1_BASE 0x24

#define TIMGX_CONFIG_REG 0x0
#define TIMGX_TNLO_REG 0x4
#define TIMGX_TNHI_REG 0x8
#define TIMGX_TNUPDATE_REG 0xC
#define TIMGX_TNLOAD_REG 0x20


#define G0T0

#ifdef G0T0
#define CFG_REG (TIMG0_BASE + SUBT0_BASE + TIMGX_CONFIG_REG)
#define LO_REG (TIMG0_BASE + SUBT0_BASE + TIMGX_TNLO_REG)
#define HI_REG (TIMG0_BASE + SUBT0_BASE + TIMGX_TNHI_REG)
#define UPDATE_REG (TIMG0_BASE + SUBT0_BASE + TIMGX_TNUPDATE_REG)
#define LOAD_REG (TIMG0_BASE + SUBT0_BASE + TIMGX_TNLOAD_REG)
#endif

#ifdef G0T1
#define CFG_REG (TIMG0_BASE + SUBT1_BASE + TIMGX_CONFIG_REG)
#define LO_REG (TIMG0_BASE + SUBT1_BASE + TIMGX_TNLO_REG)
#define HI_REG (TIMG0_BASE + SUBT1_BASE + TIMGX_TNHI_REG)
#define UPDATE_REG (TIMG0_BASE + SUBT1_BASE + TIMGX_TNUPDATE_REG)
#define LOAD_REG (TIMG0_BASE + SUBT1_BASE + TIMGX_TNLOAD_REG)
#endif

#ifdef G1T0
#define CFG_REG (TIMG1_BASE + SUBT0_BASE + TIMGX_CONFIG_REG)
#define LO_REG (TIMG1_BASE + SUBT0_BASE + TIMGX_TNLO_REG)
#define HI_REG (TIMG1_BASE + SUBT0_BASE + TIMGX_TNHI_REG)
#define UPDATE_REG (TIMG1_BASE + SUBT0_BASE + TIMGX_TNUPDATE_REG)
#define LOAD_REG (TIMG1_BASE + SUBT0_BASE + TIMGX_TNLOAD_REG)
#endif

#ifdef G1T1
#define CFG_REG (TIMG1_BASE + SUBT1_BASE + TIMGX_CONFIG_REG)
#define LO_REG (TIMG1_BASE + SUBT1_BASE + TIMGX_TNLO_REG)
#define HI_REG (TIMG1_BASE + SUBT1_BASE + TIMGX_TNHI_REG)
#define UPDATE_REG (TIMG1_BASE + SUBT1_BASE + TIMGX_TNUPDATE_REG)
#define LOAD_REG (TIMG1_BASE + SUBT1_BASE + TIMGX_TNLOAD_REG)
#endif

void Timer::init()
{
    // Nothing to init for now
    uint32_t cfg = *((uint32_t*)CFG_REG);
    cfg |= (1 << 31); // Enable timer
    *(uint32_t*)CFG_REG = cfg;
}

uint64_t Timer::getTime()
{
    // Trigger an update
    *((uint32_t*)UPDATE_REG) = 1;

    uint32_t lo = *((uint32_t*)LO_REG);
    uint32_t hi = *((uint32_t*)HI_REG);

    uint64_t time = ((uint64_t)hi << 32) | lo;
    return time;
}

void Timer::delayMicroseconds(uint64_t us)
{
    uint64_t start = getTime();
    uint64_t target = start + us * 80;

    while(getTime() < target);
}

void Timer::delay(uint64_t ms)
{
    delayMicroseconds(ms * 1000);
}