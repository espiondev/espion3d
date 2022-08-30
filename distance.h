#include <vector>
#include <cmath>
using namespace std;
#pragma once

float distance2D(vector<float> point1, vector<float> point2)
{
	// point1, point2 = {x, y};

	float distance = sqrt(
		pow(
			abs(point1[0] - point2[0]), 2
		)

		+

		pow(
			abs(point1[1] - point2[1]), 2
		)
	);

	return distance;
}

float distance3D(vector<float> point1, vector<float> point2)
{
	// point1, point2 = {x, y, z};

	float distance = sqrt(
		pow(
			abs(point1[0] - point2[0]), 2
		)

		+

		pow(
			abs(point1[1] - point2[1]), 2
		)

		+

		pow(
			abs(point1[2] - point2[2]), 2
		)
	);

	return distance;
}