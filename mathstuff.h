#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<string> split_parenth(string input)
{
	bool open = false;
	string text;
	vector<string> out;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '(')
		{
			open = true;
			for (int m = i; m < input.size() - i; m++)
			{

				if (input[m] == ')')
				{
					open = false;
					out.emplace_back(text);
					text = "";
					break;
				}
				text += input[m];
			}
		}
	}
	return out;
}

float eval(string input)
{

}