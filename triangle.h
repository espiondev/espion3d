#include <vector>
#include "px.h"
#include "line.h"
#include "sdl_stuff.h"
#include <cmath>
#include "distance.h"
#pragma once
using namespace std;

void printvec(vector<int> vec);

void triangle(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px>* pixels)
{

	// red
	line(point1, point2, rgba, pixels);
	// green
	line(point2, point3, rgba, pixels);
	//blue
	line(point3, point1, rgba, pixels);
}

void triangle_filled(vector<int> point1, vector<int> point2, vector<int> point3, vector<int> rgba, vector<px>* pixels)
{

	if (point2[1] < point1[1]) point2.swap(point1);
	if (point3[1] < point1[1]) point3.swap(point1);
	if (point3[1] < point2[1]) point3.swap(point2);

	vector<int> p1p2 = interpolate(point1[1], point1[0], point2[1], point2[0]);
	vector<int> p2p3 = interpolate(point2[1], point2[0], point3[1], point3[0]);
	vector<int> p1p3 = interpolate(point1[1], point1[0], point3[1], point3[0]);

	p1p2.pop_back();
	vector<int> p1p2p3 = p1p2;
	p1p2p3.insert(p1p2p3.end(), p2p3.begin(), p2p3.end());
	int m = floor(p1p2p3.size() / 2);

	vector<int> x_left, x_right;
	// if the middle of p1p3 if more to the left than the middle of p1p2p3
	if (p1p3[m] < p1p2p3[m])
	{
		x_left = p1p3;
		x_right = p1p2p3;
	}
	// if its more to the right
	else
	{
		x_left = p1p2p3;
		x_right = p1p3;
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

void printvec(vector<int> vec)
{
	cout << "{ ";
	for (int i = 0; i < vec.size(); i++) cout << vec[i] << ", ";
	cout << "}" << endl;
}
