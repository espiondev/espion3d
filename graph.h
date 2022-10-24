#pragma once
#include <vector>
#include <cmath>
#include "line.h"
#include "px.h"

void graph(vector<int> screen, vector<int> rgba, float m, float h, float k, vector<px>* pixels)
{
	// y = m(x - h)^2 + k

	// interp: 1/x of points will be drawn
	// if interp == 0 or 1 interp count is ignored

	vector<int> y;
	bool draw = false;
	int count = 0;

	// for every pixel on screen width
	for (int iter = -(screen[0] / 2); iter < screen[0] / 2; iter++)
	{

		y.push_back(m * (pow((iter - h), 2)) + k);

		if (draw)
		{
			line(
				{

				iter,
				y[count]
				},
				{
				iter - 1,
				y[count - 1]
				},
				rgba,
				pixels
			);
		}
		count++;
		draw = true;
	}
}