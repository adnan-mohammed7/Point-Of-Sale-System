/* Citation and Sources...
Final Project Milestone 1
Module: Utils
Filename: Utils.cpp
Version 1.0
Author	Adnan Mohammed
Revision History
-----------------------------------------------------------
Date      13th March 2023
2023/03/13  Preliminary release
2023/03/13  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include "Utils.h"

using namespace std;

namespace sdds
{
	int inputInt(int& input, int min, int max)
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
				cout << "[" << min << "<=value<=" << max << "], retry: > ";
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