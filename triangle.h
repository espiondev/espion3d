#include <vector>
#include "px.h"
#include "line.h"
#include "sdl_stuff.h"
#include <cmath>
#include "distance.h"
#include "misc.h"
#include "interp_color.h"
using namespace std;

void triangle_wire(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px> *pixels)
{
	line(point1, point2, rgba, pixels);

	line(point2, point3, rgba, pixels);

	line(point3, point1, rgba, pixels);
}

void triangle_filled(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px> *pixels)
{

	if (point2[1] < point1[1])
		point2.swap(point1);
	if (point3[1] < point1[1])
		point3.swap(point1);
	if (point3[1] < point2[1])
		point3.swap(point2);

	vector<int> p12 = interpolate(point1[1], point1[0], point2[1], point2[0]);
	vector<int> p23 = interpolate(point2[1], point2[0], point3[1], point3[0]);
	vector<int> p13 = interpolate(point1[1], point1[0], point3[1], point3[0]);

	p12.pop_back();
	vector<int> p123 = p12;
	p123.insert(p123.end(), p23.begin(), p23.end());
	int m = floor(p123.size() / 2);

	vector<int> x_left, x_right;
	// if the middle of p1p3 if more to the left than the middle of p1p2p3
	if (p13[m] < p123[m])
	{
		x_left = p13;
		x_right = p123;
	}
	// if its more to the right
	else
	{
		x_left = p123;
		x_right = p13;
	}

	// go from the bottom of the triangle to the top
	for (int y = point1[1]; y < point3[1]; y++)
	{

		/*
		cout << "y: " << y << endl;

		cout << "x_left: " << x_left[y - point1[1]] << " x_right: " << x_right[y - point1[1]] << endl;
		*/

		// for every x value between x_left and x_right
		for (int x = x_left[y - point1[1]]; x < x_right[y - point1[1]]; x++)
		{
			pixels->push_back(
				{rgba,
				 {x, y}});
		}
	}
}

void triangle_shaded(px point1, px point2, px point3, vector<px> *pixels)
{
	// interp colors between points

	// sort points
	// point 3 > point 2 > point 1
	if (point2.xy[1] < point1.xy[1])
	{
		point2.xy.swap(point1.xy);
		point2.rgba.swap(point1.rgba);
	}
	if (point3.xy[1] < point1.xy[1])
	{
		point3.xy.swap(point1.xy);
		point3.rgba.swap(point1.rgba);
	}
	if (point3.xy[1] < point2.xy[1])
	{
		point3.xy.swap(point2.xy);
		point3.rgba.swap(point2.rgba);
	}

	vector<int> x12 = interpolate(point1.xy[1], point1.xy[0], point2.xy[1], point2.xy[0]);
	vector<int> x23 = interpolate(point2.xy[1], point2.xy[0], point3.xy[1], point3.xy[0]);
	vector<int> x13 = interpolate(point1.xy[1], point1.xy[0], point3.xy[1], point3.xy[0]);

	vector<vector<int>> clr12 =
		color_interp(point1.rgba, point2.rgba, x12.size());

	vector<vector<int>> clr23 =
		color_interp(point2.rgba, point3.rgba, x23.size());

	vector<vector<int>> clr13 =
		color_interp(point1.rgba, point3.rgba, x13.size());

	x12.pop_back();
	clr12.pop_back();

	vector<vector<int>> clr123 = clr12;
	for (int i = 0; i < 3; i++)
	{
		clr123.insert(clr123.end(), clr23.begin(), clr23.end());
	}

	vector<int> x123 = x12;
	x123.insert(x123.end(), x23.begin(), x23.end());

	int m = floor(x123.size() / 2);

	vector<int> x_left, x_right;
	vector<vector<int>> clr_right, clr_left;

	if (x13[m] < x123[m])
	{
		x_left = x13;
		x_right = x123;

		clr_right = clr13;
		clr_left = clr123;
	}
	else
	{
		x_left = x123;
		x_right = x13;

		clr_left = clr123;
		clr_right = clr13;
	}

	int x_r, x_l;
	vector<int> clr_r, clr_l;
	vector<vector<int>> clr_seg;
	for (int y = point1.xy[1]; y < point3.xy[1] - 1; y++)
	{
		x_l = x_left[y - point1.xy[1]];
		x_r = x_right[y - point1.xy[1]];

		clr_l =
			clr_left[y - point1.xy[1]];

		clr_r =
			clr_right[y - point1.xy[1]];
		clr_seg =
			color_interp(clr_l, clr_r, abs(x_l - x_r));
		for (int x = x_l; x < x_r; x++)
		{
			pixels->push_back(
				{{clr_seg[x - x_l][0],
				  clr_seg[x - x_l][1],
				  clr_seg[x - x_l][2],
				  255},
				 {x, y}

				});
		}
	}
}
