#include <vector>
#include "espion3d_structs.h"
#include "line.h"
#include "misc_functions.h"
#include "sdl_functions.h"
#include <cmath>
#include "misc.h"
#include "interpolate_color.h"
using namespace std;

// function to draw wireframe triangle
void triangle_wire(coord2d point1, coord2d point2, coord2d point3, color rgba, vector<point> *pixels)
{
	cout << "p1: " << point1.x << ", " << point1.y << endl;
	cout << "p2: " << point2.x << ", " << point2.y << endl;
	cout << "p3: " << point3.x << ", " << point3.y << endl;
	line(point1, point2, rgba, pixels);

	line(point2, point3, rgba, pixels);

	line(point3, point1, rgba, pixels);
}

// function to draw triangle filled with solid color
void triangle_filled(coord2d point1, coord2d point2, coord2d point3, color rgba, vector<point> *pixels)
{

	// sort points so p1.y < p2.y < p3.y
	if (point2.y < point1.y)
		swap(point1, point2);
	if (point3.y < point1.y)
		swap(point3, point1);
	if (point3.y < point2.y)
		swap(point3, point2);

	// list of x values representing lines (y values are inferred by triangle size)
	vector<int> p12 = interpolate(point1.y, point1.x, point2.y, point2.x);
	vector<int> p23 = interpolate(point2.y, point2.x, point3.y, point3.x);
	vector<int> p13 = interpolate(point1.y, point1.x, point3.y, point3.x);

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
	for (int y = point1.y; y < point3.y; y++)
	{
		// for every x value between x_left and x_right
		for (int x = x_left[y - point1.y]; x < x_right[y - point1.y]; x++)
		{
			pixels->push_back(
				{{x, y},
				 rgba});
		}
	}
}

void triangle_shaded(point point1, point point2, point point3, vector<point> *pixels)
{

	// sort points
	// point 3 > point 2 > point 1
	if (point2.pos.y < point1.pos.y)
	{
		swap(point1, point2);
	}
	if (point3.pos.y < point1.pos.y)
	{
		swap(point3, point1);
	}
	if (point3.pos.y < point2.pos.y)
	{
		swap(point3, point2);
	}
	// list of x values representing lines (y values are inferred by triangle size)
	vector<int> x12 = interpolate(point1.pos.y, point1.pos.x, point2.pos.y, point2.pos.x);
	vector<int> x23 = interpolate(point2.pos.y, point2.pos.x, point3.pos.y, point3.pos.x);
	vector<int> x13 = interpolate(point1.pos.y, point1.pos.x, point3.pos.y, point3.pos.x);

	vector<color> clr12 =
		color_interp(point1.color, point2.color, x12.size());

	vector<color> clr23 =
		color_interp(point2.color, point3.color, x23.size());

	vector<color> clr13 =
		color_interp(point1.color, point3.color, x13.size());

	x12.pop_back();
	clr12.pop_back();

	vector<color> clr123 = clr12;
	clr123.insert(clr123.end(), clr23.begin(), clr23.end());

	vector<int> x123 = x12;
	x123.insert(x123.end(), x23.begin(), x23.end());

	int m = floor(x123.size() / 2);

	vector<int> x_left, x_right;
	vector<color> clr_right, clr_left;

	if (x13[m] < x123[m])
	{
		x_left = x13;
		x_right = x123;

		clr_left = clr13;
		clr_right = clr123;
	}
	else
	{
		x_left = x123;
		x_right = x13;

		clr_left = clr123;
		clr_right = clr13;
	}

	int x_r, x_l;
	color clr_r, clr_l;
	vector<color> clr_seg;
	for (int y = point1.pos.y; y < point3.pos.y - 1; y++)
	{
		x_l = x_left[y - point1.pos.y];
		x_r = x_right[y - point1.pos.y];

		clr_l =
			clr_left[y - point1.pos.y];

		clr_r =
			clr_right[y - point1.pos.y];
		clr_seg =
			color_interp(clr_l, clr_r, abs(x_l - x_r));
		for (int x = x_l; x < x_r; x++)
		{
			pixels->push_back(
				{{x, y},
				 clr_seg[x - x_l]

				});
		}
	}
}
