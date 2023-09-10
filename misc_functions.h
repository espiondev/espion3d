#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string vector_to_string(const vector<int> &vec)
{
    ostringstream oss;
    oss << "{ ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        oss << vec[i];
        if (i != vec.size() - 1)
        {
            oss << ", ";
        }
    }
    oss << " }";
    return oss.str();
}