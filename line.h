#include <vector>
#include "espion3d_structs.h"
#include "sdl_functions.h"
#pragma once
using namespace std;

/*
interpolates between two points.
i0: independant variable start
d0: dependant variable start
i1: independant variable end
d1: dependant variable end
returns list of values of d
interval of i is 1.0
*/
vector<int> interpolate(float i0, float d0, float i1, float d1)
{

	vector<int> points;
	// do nothing if independant variable doesn't change
	if (i0 == i1)
	{
		points.push_back(d0);
		return points;
	}

	// calculate slope
	float a = (d1 - d0) / (i1 - i0);
	float d = d0;
	for (float i = i0; i <= i1; i++)
	{
		points.push_back(d);
		d = d + a;
	}
	return points;
}

vector<float> interpolate_float(float i0, float d0, float i1, float d1)
{
	vector<float> points;
	if (i0 == i1)
	{
		points.push_back(d0);
		return points;
	}

	float a = (d1 - d0) / (i1 - i0);
	float d = d0;
	for (int i = i0; i <= i1; i++)
	{
		points.push_back(d);
		d = d + a;
	}
	return points;
}

void line(coord2d point1, coord2d point2, color clr, vector<point> *pixels)
{

	// difference of the 2 points' x values is bigger than difference in y values; line is more horizontal
	if (abs(point2.x - point1.x) > abs(point2.y - point1.y))
	{
		if (point1.x > point2.x)
		{
			swap(point1, point2);
		}

		vector<int> y_values = interpolate(point1.x, point1.y, point2.x, point2.y);

		for (int i = point1.x; i < point2.x; i++)
		{
			pixels->push_back({{i, y_values[i - point1.x]}, {clr.r, clr.g, clr.b, clr.a}});
		}
	}
	// line is more vertical
	else
	{
		if (point1.y > point2.y)
		{
			swap(point1, point2);
		}

		vector<int> x_values = interpolate(point1.y, point1.x, point2.y, point2.x);

		for (int i = point1.y; i < point2.y; i++)
		{
			pixels->push_back(
				{{x_values[i - point1.y], i},
				 {clr.r, clr.g, clr.b, clr.a}});
		}
	}
}
