#include <vector>
using namespace std;
#pragma once
struct px
{
	vector<int> rgba;
	vector<int> xy;
};
struct rectangle
{
	px point1;
	px point2;
};