#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#pragma once
using namespace std;

void printvecflt(vector<float> vecflt)
{
	cout << "{ ";
	for (float f : vecflt)
	{
		cout << f << ", ";
	}
	cout << " }" << endl;
}

void printvecint(vector<int> vecint)
{
	cout << "{ ";
	for (int i : vecint)
	{
		cout << i << ", ";
	}
	cout << " }" << endl;
}

float distance_points(vector<int> point1, vector<int> point2)
{
	return sqrt(pow(abs(float(point2[1]) - float(point1[1])), 2) + pow(abs(float(point2[0]) - float(point2[1])), 2));
}
int compare_distance(vector<int> point1, vector<vector<int>> trianglepoints)
{
	// chosen point, 3 triangle points
	vector<float> distances;
	for (int i = 0; i < distances.size(); i++)
	{
		distances.push_back(distance_points(point1, trianglepoints[i]));
	}

	int biggest;
	for (int i = 1; i < 3; i++)
	{
		if (distances[i - 1] < distances[i])
		{
			biggest = i;
		}
	}
	return biggest;
}