#include <vector>
#include <iostream>
#include "misc.h"
using namespace std;

vector<int> get_interp_value(vector<int> color1, vector<int> color2, float point)
{

    vector<int> rgb =
        {
            int((float(color1[0]) * (1.0 - point)) + (float(color2[0]) * point)),
            int((float(color1[1]) * (1.0 - point)) + (float(color2[1]) * point)),
            int((float(color1[2]) * (1.0 - point)) + (float(color2[2]) * point))};
    return rgb;
}

vector<vector<int>> color_interp(vector<int> color1, vector<int> color2, int distance)
{
    vector<vector<int>> out;
    for (float i = 0; i < distance; i++)
    {
        out.push_back(get_interp_value(color1, color2, i / distance));
    }
    return out;
}