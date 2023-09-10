#pragma once
struct color
{
	int r, g, b, a;
};
// 2d coordinate
struct coord2d
{
	int x, y;
};
// 3d coordinate
struct coord3d
{
	float x, y, z;
};
// 2d point
// includes color for triangle vertex colors
struct point
{
	struct coord2d pos;
	struct color color;
};
struct rectangle
{
	struct point point1, point2;
};
struct triangle
{
	int type;
	// 0: line
	// 1: filled
	// 2: shaded
	struct point point1, point2, point3;
};
struct scene_info
{
	int coord_mode;
	struct coord2d dimensions;
};
struct wave_point_s
{
	coord2d pos;
	float age;
	color clr;
};