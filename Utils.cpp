#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include "Utils.h"

using namespace std;

namespace sdds
{
	int inputInt(int& input, int min, int max, int type)
	{
		int check = 0;

		do
		{
			cin >> input;

			if (cin.fail())
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Invalid Integer, try again: ";
				check = 0;
			}
			else if (input < min || input > max)
			{
				cout << "[" << min << "<=value<=" << max << "], retry: ";
				if (type == 1)
				{
					cout << "> ";
				}
				else if (type == 2)
				{
					cout << "Enter the row number: ";
				}
				else if (type == 3)
				{
					cout << "Enter quantity to add: ";
				}
				check = 0;
			}
			else if (input >= min && input <= max)
			{
				check = 1;
			}
		} while (check == 0);


		return input;
	}
}