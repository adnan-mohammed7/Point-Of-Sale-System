#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include "PosApp.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
	int PosApp::menu()
	{
		int choice;

		do
		{
			cout << "The Sene-Store" << "\n" << "1- List items" << "\n" << "2- Add item" << endl;
			cout << "3- Remove item" << "\n" << "4- Stock item" << "\n" << "5- POS" << endl;
			cout << "0- exit program" << "\n" << "> ";

			inputInt(choice, 0, 5, 1);

			if (choice == 1)
			{
				listItems(true);
			}
			else if (choice == 2)
			{
				addItem();
			}
			else if (choice == 3)
			{
				removeItem();
			}
			else if (choice == 4)
			{
				stockItem();
			}
			else if (choice == 5)
			{
				POS();
			}
		} while (choice);

		return choice;
	}
