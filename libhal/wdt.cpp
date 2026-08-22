#include "wdt.h"

#define MAGICNUM 0x050D83AA1

#define TIMG0_BASE 0x3FF5F000
#define TIMG1_BASE 0x3FF60000

#define TIMG_WP_OFF 0x0064
#define TIMG_WDTCONFIG0_OFF 0x48

#define RTC_BASE 0x3FF48000

#define RTC_WP_OFF 0x00A4
#define RTC_CNTL_WDTCONFIG0_OFF 0x8C

static void disableWP(WDTID tnum)
{
    switch (tnum)
    {
    case WDTID::TIMG0:
    {
        *(int*)(TIMG0_BASE + TIMG_WP_OFF) = MAGICNUM;
        break;
    }

    case WDTID::TIMG1:
    {
        *(int*)(TIMG1_BASE + TIMG_WP_OFF) = MAGICNUM;
        break;
    }

    case WDTID::RTCID:
    {
        *(int*)(RTC_BASE + RTC_WP_OFF) = MAGICNUM;
        break;
    }
    }
}

static void enableWP(WDTID tnum)
{
    switch (tnum)
    {
    case WDTID::TIMG0:
    {
        *(int*)(TIMG0_BASE + TIMG_WP_OFF) = 1;
        break;
    }

    case WDTID::TIMG1:
    {
        *(int*)(TIMG1_BASE + TIMG_WP_OFF) = 1;
        break;
    }

    case WDTID::RTCID:
    {
        *(int*)(RTC_BASE + RTC_WP_OFF) = 1;
        break;
    }
    }
}

void WDTBase::HdisableBootProtection(WDTID tnum)
{
    // first disable write protection
    disableWP(tnum);
    unsigned int* confReg = 0;
    switch (tnum)
    {
    case WDTID::TIMG0:
    {
        confReg = (unsigned int*)(TIMG0_BASE + TIMG_WDTCONFIG0_OFF);
        break;
    }

    case WDTID::TIMG1:
    {
        confReg = (unsigned int*)(TIMG1_BASE + TIMG_WDTCONFIG0_OFF);
        break;
    }

    case WDTID::RTCID:
    {
        confReg = (unsigned int*)(RTC_BASE + RTC_CNTL_WDTCONFIG0_OFF);
        break;
    }

    default:
        return;
    }

    unsigned int status = *(confReg);

    switch (tnum)
    {
    case WDTID::TIMG0:
    case WDTID::TIMG1:
    {
        status &= ~(1U << 14);
        break;
    }

    case WDTID::RTCID:
    {
        status &= ~(1U << 10);
        break;
    }
    }

    *confReg = status;
    enableWP(tnum);
}