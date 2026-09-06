#include "rtc.h"

#define MAGICNUM 0x050D83AA1

#define RTC_BASE 0x3FF48000
#define RTC_WP_OFF 0x00A4
#define RTC_CNTL_WDTCONFIG0_OFF 0x8C

void RTC::disableBootProtection()
{
    *(int*)(RTC_BASE + RTC_WP_OFF) = MAGICNUM;
    unsigned int status = *(unsigned int*)(RTC_BASE + RTC_CNTL_WDTCONFIG0_OFF);
    status &= ~(1U << 10);
    *(unsigned int*)(RTC_BASE + RTC_CNTL_WDTCONFIG0_OFF) = status;
    *(int*)(RTC_BASE + RTC_WP_OFF) = 1;
}