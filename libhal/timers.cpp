#include "timers.h"

#define MAGICNUM 0x050D83AA1

#define TIMG_WP_OFF 0x0064
#define TIMG_WDTCONFIG0_OFF 0x48

template <unsigned int base>
void TIMG<base>::disableBootProtection()
{
    *(int*)(base + TIMG_WP_OFF) = MAGICNUM;
    unsigned int status = *(unsigned int*)(base + TIMG_WDTCONFIG0_OFF);
    status &= ~(1U << 14);
    *(unsigned int*)(base + TIMG_WDTCONFIG0_OFF) = status;
    *(int*)(base + TIMG_WP_OFF) = 1;
}

template class TIMG<TIMG0_BASE>;
template class TIMG<TIMG1_BASE>;