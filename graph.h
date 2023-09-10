#pragma once
#include <vector>
#include <cmath>
#include "line.h"
#include "esp_structs.h"

void graph(coord2_s screen, color_s rgba, float m, float h, float k, vector<point_s> *pixels)
{
	// y = m(x - h)^2 + k

	// interp: 1/x of points will be drawn
	// if interp == 0 or 1 interp count is ignored

	vector<int> y;
	bool draw = false;
	int count = 0;

	// for every pixel on screen width
	for (int iter = -(screen.x / 2); iter < screen.y / 2; iter++)
	{

		y.push_back(m * (pow((iter - h), 2)) + k);

		if (draw)
		{
			line(
				{

					iter,
					y[count]},
				{iter - 1,
				 y[count - 1]},
				rgba,
				pixels);
		}
		count++;
		draw = true;
	}
}