#include <vector>
#include <cmath>
#include "espion3d_structs.h"
using namespace std;
#pragma once

float distance2D(coord2d point1, coord2d point2)
{
	// point1, point2 = {x, y};

	float distance = sqrt(
		pow(
			abs(point1.x - point2.x), 2)

		+

		pow(
			abs(point1.y - point2.y), 2));

	return distance;
}

float distance3D(coord3d point1, coord3d point2)
{
	// point1, point2 = {x, y, z};

	float distance = sqrt(
		pow(
			abs(point1.x - point2.x), 2)

		+

		pow(
			abs(point1.y - point2.y), 2)

		+

		pow(
			abs(point1.z - point2.z), 2));

	return distance;
}