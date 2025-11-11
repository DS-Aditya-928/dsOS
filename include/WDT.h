#pragma once
enum class WDTID
{
    TIMG0,
    TIMG1,
    RTCID
};

class TimerBase
{
protected:
    static void HdisableBootProtection(WDTID);
};


template<WDTID id>
class TIMG : public TimerBase
{
public:
    static void disableBootProtection()
    {
        HdisableBootProtection(id);
    }
};

using TIMG0 = TIMG<WDTID::TIMG0>;
using TIMG1 = TIMG<WDTID::TIMG1>;
using TIMRTC = TIMG<WDTID::RTCID>;