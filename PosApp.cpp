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
	void PosApp::addItem()
	{
		cout << ">>>> Adding Item to the store................................................" << endl;
		cout << "Running addItem()" << endl;
	}
	void PosApp::removeItem()
	{
		cout << ">>>> Remove Item............................................................." << endl;
		cout << "Running removeItem()" << endl;
	}
	void PosApp::stockItem()
	{
		cout << ">>>> Select an item to stock................................................." << endl;
		cout << "Running stockItem()" << endl;
	}
	void PosApp::listItems()
	{
		cout << ">>>> Listing Items..........................................................." << endl;
		cout << "Running listItems()" << endl;
	}
	void PosApp::POS()
	{
		cout << ">>>> Starting Point of Sale.................................................." << endl;
		cout << "Running POS()" << endl;
	}
	void PosApp::saveRecs() const
	{
		cout << ">>>> Saving Data............................................................." << endl;
		cout << "Saving data in " << m_filename << endl;
	}
	void PosApp::loadRecs()
	{
		cout << ">>>> Loading Items..........................................................." << endl;
		cout << "Loading data from " << m_filename << endl;
	}
	PosApp::PosApp(const char filename[])
	{
		strcpy(m_filename, filename);
	}

	void PosApp::run()
	{
		int check = 1;

		loadRecs();

		do
		{
			check = menu();
		} while (check);

		saveRecs();

		cout << "Goodbye!" << endl;
	}
}