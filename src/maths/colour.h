#ifndef WINTER_COLOUR_H
#define WINTER_COLOUR_H

#include "float4.h"
struct colour
{
    colour()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }

    uint8_t r, g, b, a;

    float4 to_float4() const
    {
        return float4(r / 255, g / 255, b / 255, a / 255);
    }
};

#endif // WINTER_COLOUR_H
