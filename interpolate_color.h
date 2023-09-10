#include <vector>
#include <iostream>
#include "misc.h"
using namespace std;

// get color at specific linear interpolation point (float from 0.0-1.0)
color get_interpolated_color(color color1, color color2, float time)
{

    color rgba =
        {
            int((float(color1.r) * (1.0 - time)) + (float(color2.r) * time)),
            int((float(color1.g) * (1.0 - time)) + (float(color2.g) * time)),
            int((float(color1.b) * (1.0 - time)) + (float(color2.b) * time)),
            int((float(color1.a) * (1.0 - time)) + (float(color2.a) * time))

        };
    return rgba;
}

vector<color> color_interp(color color1, color color2, int distance)
{
    vector<color> out;
    for (float i = 0; i < distance; i++)
    {
        out.push_back(get_interpolated_color(color1, color2, i / distance));
    }
    return out;
}