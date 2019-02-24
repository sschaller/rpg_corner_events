#pragma once

#include <stdint.h>

namespace corner_event_detector
{
    typedef struct
    {
        double ts;
        uint16_t x;
        uint16_t y;
        bool polarity;
    } Event;
}