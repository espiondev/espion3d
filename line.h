#include <vector>
#include "px.h"
#include "sdl_stuff.h"
#pragma once
using namespace std;

vector<float> interpolate(float i0, float d0, float i1, float d1)
{
	vector<float> points;
	if (i0 == i1)
	{
		points.push_back(d0);
		return points;
	}

	float a = (d1 - d0) / (i1 - i0);
	float d = d0;
	for (int i = i0; i < i1 + 1; i++)
	{
		points.push_back(d);
		d = d + a;
	}
	return points;
}

void line(vector<int> point1, vector<int> point2, vector<int> rgba, SDL_Renderer* renderer, vector<px>* pixels)
{
	// point: {x, y}

	// difference of the 2 points' x values is bigger than difference in y values; line is more horizontal
	if (abs(point2[0] - point1[0]) > abs(point2[1] - point1[1]))
	{
		if (point1[0] > point2[0])
		{
			point1.swap(point2);
		}

		vector<float> y_values = interpolate(point1[0], point1[1], point2[0], point2[1]);

		for (int i = point1[0]; i < point2[0]; i++)
		{
			pixels->push_back(
				{
				rgba,
				{ i, (int)y_values[i - point1[0]] }
				});
		}
	}
	else
	{
		if (point1[1] > point2[1])
		{
			point1.swap(point2);
		}

		vector<float> x_values = interpolate(point1[1], point1[0], point2[1], point2[0]);

		for (int i = point1[1]; i < point2[1]; i++)
		{
			pixels->push_back(
				{
				rgba,
				{ i, (int)x_values[i - point1[1]] }
				});
		}
	}
}
