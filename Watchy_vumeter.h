#ifndef WATCHY_vumeter_H
#define WATCHY_vumeter_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM
#include "FreeSans8pt7b.h"
#include "icons.h"

class Watchyvumeter : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
        void drawBattery();
};

#endif