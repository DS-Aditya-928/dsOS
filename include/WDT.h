#pragma once
enum class WDTID
{
    TIMG0,
    TIMG1,
    RTCID
};

class WDTBase
{
protected:
    static void HdisableBootProtection(WDTID);
};


template<WDTID id>
class WDT : public WDTBase
{
public:
    static void disableBootProtection()
    {
        HdisableBootProtection(id);
    }
};

using WDT0 = WDT<WDTID::TIMG0>;
using WDT1 = WDT<WDTID::TIMG1>;
using WDTRTC = WDT<WDTID::RTCID>;