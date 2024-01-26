/* Citation and Sources...
Final Project Milestone 1
Module: PosApp
Filename: PosApp.cpp
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

#include <iostream>
#include <cstring>
#include "PosApp.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
	int PosApp::menu() const
	{
		int choice;

		do
		{
			cout << "The Sene-Store" << "\n" << "1- List items" << "\n" << "2- Add item" << endl;
			cout << "3- Remove item" << "\n" << "4- Stock item" << "\n" << "5- Point of Sale" << endl;
			cout << "0- exit program" << "\n" << "> ";

			inputInt(choice, 0, 5);

			if (choice == 1)
			{
				listItems();
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
	void PosApp::addItem() const
	{
		cout << ">>>> Adding Item to the store................................................" << endl;
		cout << "Running addItem()" << endl;
	}
	void PosApp::removeItem() const
	{
		cout << ">>>> Remove Item............................................................." << endl;
		cout << "Running removeItem()" << endl;
	}
	void PosApp::stockItem() const
	{
		cout << ">>>> Select an item to stock................................................." << endl;
		cout << "Running stockItem()" << endl;
	}
	void PosApp::listItems() const
	{
		cout << ">>>> Listing Items..........................................................." << endl;
		cout << "Running listItems()" << endl;
	}
	void PosApp::POS() const
	{
		cout << ">>>> Starting Point of Sale.................................................." << endl;
		cout << "Running POS()" << endl;
	}
	void PosApp::saveRecs() const
	{
		cout << ">>>> Saving Data............................................................." << endl;
		cout << "Saving data in " << m_filename << endl;
	}
	void PosApp::loadRecs() const
	{
		cout << ">>>> Loading Items..........................................................." << endl;
		cout << "Loading data from " << m_filename << endl;
	}
	PosApp::PosApp(const char filename[])
	{
		strcpy(m_filename, filename);
	}

	void PosApp::run() const
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