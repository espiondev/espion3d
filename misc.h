#include <string>
#include <vector>
#include <iostream>
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