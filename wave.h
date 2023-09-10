#include "esp_structs.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

vector<wave_point_s> progress_all_points(vector<wave_point_s> points, scene_info_s scene)
{
    vector<wave_point_s> new_points;

    for (int i = 0; i < points.size(); i++)
    {
        // check if point is too far to the left
        if (points[i].pos.x > 0)
        {
            if (points[i].age < scene.max_age)
            {
                points[i].pos.x -= scene.wave_move_inc;
                points[i].age += scene.wave_age_inc;
                new_points.push_back(points[i]);
            }
        }
    }

    return new_points;
}

void draw_wave_point(vector<point_s> *pixels, scene_info_s scene, vector<wave_point_s> points)
{
    for (int i = 0; i < points.size(); i++)
    {
        pixels->push_back(
            {{points[i].pos.x, points[i].pos.y},
             {int(points[i].clr.r * (1.0 - (points[i].age / scene.max_age))), int(points[i].clr.g * (1.0 - (points[i].age / scene.max_age))), int(points[i].clr.b * (1.0 - (points[i].age / scene.max_age))), points[i].clr.a}});
    }
}