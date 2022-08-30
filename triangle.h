#include <vector>
#include "px.h"
#include "line.h"
#include "sdl_stuff.h"
#pragma once
using namespace std;

void triangle(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, SDL_Renderer* renderer, vector<px>* pixels)
{
	line(point1, point2, rgba, renderer, pixels);
	line(point2, point3, rgba, renderer, pixels);
	line(point1, point3, rgba, renderer, pixels);
}

void triangle_filled()