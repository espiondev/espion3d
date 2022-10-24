#include <vector>
#include "px.h"
#include "line.h"
#include "sdl_stuff.h"
#include <cmath>
#include "distance.h"
#include "misc.h"
#pragma once
using namespace std;

void triangle_wire(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px>* pixels)
{
	line(point1, point2, rgba, pixels);

	line(point2, point3, rgba, pixels);

	line(point3, point1, rgba, pixels);
}

void triangle_filled(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px>* pixels)
{

	if (point2[1] < point1[1]) point2.swap(point1);
	if (point3[1] < point1[1]) point3.swap(point1);
	if (point3[1] < point2[1]) point3.swap(point2);

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
				{
					rgba,
					{x, y}
				}
			);
		}
	}

}

void triangle_shaded(px point1, px point2, px point3, vector<px>* pixels)
{
	px temp;
	if (point2.xy[1] < point1.xy[1])
	{
		temp = point1;
		point1.xy = point2.xy;
		point2.xy = temp.xy;
	}
	if (point3.xy[1] < point1.xy[1])
	{
		temp = point1;
		point1.xy = point3.xy;
		point3.xy = temp.xy;
	}
	if (point3.xy[1] < point2.xy[1])
	{
		temp = point2;
		point2.xy = point3.xy;
		point3.xy = temp.xy;
	}

	vector<int> x12 = interpolate(point1.xy[1], point1.xy[0], point2.xy[1], point2.xy[0]);
	vector<int> x23 = interpolate(point2.xy[1], point2.xy[0], point3.xy[1], point3.xy[0]);
	vector<int> x13 = interpolate(point1.xy[1], point1.xy[0], point3.xy[1], point3.xy[0]);

	vector<float> h12 = interpolate_float(point1.xy[1], 1.0, point2.xy[1], 0.0);
	vector<float> h23 = interpolate_float(point2.xy[1], 1.0, point3.xy[1], 0.0);
	vector<float> h13 = interpolate_float(point1.xy[1], 1.0, point3.xy[1], 0.0);



	x12.pop_back();
	vector<int> x123 = x12;
	x123.insert(x123.end(), x23.begin(), x23.end());

	h12.pop_back();
	vector<float> h123 = h12;
	h123.insert(h123.end(), h23.begin(), h23.end());


	int m = floor(x123.size() / 2);
	vector<float> h_left, h_right;
	vector<int> x_left, x_right;

	if (x13[m] < x123[m])
	{
		x_left = x13;
		x_right = x123;

		h_left = h13;
		h_right = h123;
	}
	else
	{
		x_left = x123;
		x_right = x13;

		h_left = h123;
		h_right = h13;
	}

	int x_r, x_l;
	vector<float> h_seg;

	for (int y = point1.xy[1]; y < point3.xy[1] - 1; y++)
	{


		/*
		cout << "y: " << y << endl;
		cout << "POINT1 Y: " << point1.xy[1] << endl;
		cout << "POINT3 Y: " << point3.xy[1] << endl;
		cout << "y - point1 y = " << y - point1.xy[1] << endl;
		cout << "hleft size: " << h_left.size() << endl;
		cout << "hright size: " << h_right.size() << endl;
		cout << "x_right size: " << x_right.size() << endl;
		cout << "x_left size: " << x_left.size() << endl;
		*/

		//cout << endl;
		x_l = x_left[y - point1.xy[1]];
		x_r = x_right[y - point1.xy[1]];

		h_seg = interpolate_float(x_l, h_left[y - point1.xy[1]], x_r, h_right[y - point1.xy[1]]);
		//printvecflt(h_seg);

		for (int x = x_left[y - point1.xy[1]]; x < x_right[y - point1.xy[1]]; x++)
		{
			cout << y << endl;

			/*
			cout << "x: " << x << endl;
			cout << "x_l: " << x_l << endl;
			cout << "x - x_l = " << x - x_l << endl;
			cout << "x left size: " << x_left.size() << endl;
			cout << "h_seg size: " << h_seg.size() << endl;
			*/


			pixels->push_back(
				{
					{
						int(point1.rgba[0] * h_seg[x - x_l]),
						int(point1.rgba[1] * h_seg[x - x_l]),
						int(point1.rgba[2] * h_seg[x - x_l])

					},
					{x, y}
				}
			);
			//cout << "added pixel" << endl;
		}
	}
}
