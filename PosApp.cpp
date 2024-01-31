#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include "PosApp.h"
#include "Utils.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"
#include "Bill.h"
#include "Date.h"
#include "Error.h"
#include "POS.h"

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
		title("Adding Item to the store");

		//Checking if max number of items is reached
		if (m_nptr < MAX_NO_ITEMS)
		{
			int loop = 0;
			char itemType;
			cout << "Is the Item perishable? (Y)es/(N)o: ";
			cin >> itemType;

			//checling if perishable or non perishable
			if (itemType == 'y')
			{
				m_Iptr[m_nptr] = new Perishable;

				//Looping untill a valid item is entered
				do
				{
					cin.ignore(1000, '\n');
					cin >> *m_Iptr[m_nptr];
					if (cin.fail())
					{
						loop = 1;
						cin.clear();
						cin.ignore(1000, '\n');
						cout << *m_Iptr[m_nptr];
						cout << ", try again..." << endl;
					}
					else
					{
						loop = 0;
					}
				} while (loop);
			}
			else if (itemType == 'n')
			{
				m_Iptr[m_nptr] = new NonPerishable;

				//Looping untill a valid item is entered
				do
				{
					cin.ignore(1000, '\n');
					cin >> *m_Iptr[m_nptr];
					if (cin.fail())
					{
						loop = 1;
						cin.clear();
						cin.ignore(1000, '\n');
						cout << *m_Iptr[m_nptr];
						cout << ", try again..." << endl;
					}
					else
					{
						loop = 0;
					}
				} while (loop);
			}
			m_nptr++;
			title("DONE!");
		}
		else
		{
			cout << "Inventory Full!";
		}
	}

	/*This function is to remove an item from the PosApp*/
	void PosApp::removeItem()
	{
		int choice;
		title("Remove Item");

		/*To display current item list*/
		choice = selectItem();
		cout << "Removing...." << endl;

		/*Displaying the selected item to be removed*/
		m_Iptr[(choice - 1)]->displayType(POS_FORM);
		cout << *m_Iptr[(choice - 1)];

		//Deallocating memory
		delete m_Iptr[(choice - 1)];
		m_Iptr[(choice - 1)] = nullptr;

		for (int i = 0; i < m_nptr; i++)
		{
			//Removing the selected item
			if (i >= (choice - 1))
			{
				m_Iptr[i] = m_Iptr[i + 1];
			}
		}

		//Decrementing number of items
		m_nptr -= 1;

		title("DONE!");
	}

	/*To restock an item in the PosApp*/
	void PosApp::stockItem()
	{
		int choice;
		int quantity;
		int max;
		title("Select an item to stock");
		choice = selectItem();
		cout << "Selected Item:" << endl;

		m_Iptr[(choice - 1)]->displayType(POS_FORM);
		cout << *m_Iptr[(choice - 1)];

		//Getting the no of quantity which can be added to PosApp
		max = MAX_STOCK_NUMBER - m_Iptr[(choice - 1)]->quantity();

		cout << "Enter quantity to add: ";
		inputInt(quantity, 1, max, 3);

		//Adding user entered number to the quantity
		*m_Iptr[(choice - 1)] += quantity;

		title("DONE!");
	}

	/*This function shows the list of all the items stored in m_Iptr*/
	void PosApp::listItems(bool total)
	{
		title("Listing Items");

		Item* ptr = nullptr;

		for (int i = 0; i < m_nptr; i++)
		{
			for (int j = (i + 1); j < m_nptr; j++)
			{
				if (*m_Iptr[i] > *m_Iptr[j])
				{
					ptr = m_Iptr[i];
					m_Iptr[i] = m_Iptr[j];
					m_Iptr[j] = ptr;
				}
			}
		}

		/*To print the header of the list*/
		printHeader();

		/*To print all the items os m_Iptr*/
		printBody();

		if (total)
		{
			/*To calculate and print total of items*/
			printTotal();
		}
	}
	void PosApp::POS()
	{
		title("Starting Point of Sale");

		//Local Variables
		Item* selectedItem = nullptr;
		char sku[MAX_SKU_LEN];
		Bill bill;

		cin.ignore(1000, '\n');
		do
		{
			strcpy(sku, "");
			cout << "Enter SKU or <ENTER> only to end sale..." << endl;
			cout << "> ";

			cin.getline(sku, MAX_SKU_LEN, '\n');

			//If cin is in good state and sku is not empty
			if (cin && sku[0] != '\0')
			{
				//Searching for the item
				selectedItem = search(sku);

				//if item not found
				if (selectedItem == nullptr)
				{
					cout << "!!!!! Item Not Found !!!!!" << endl;
				}
				else
				{
					//Checking if item is out of stock
					if (selectedItem->quantity())
					{
						//if item was added successfully to the bill updaiting item quantity
						if (bill.add(selectedItem))
						{
							*selectedItem -= 1;

							selectedItem->displayType(POS_FORM);
							cout << *selectedItem << endl;

							cout << ">>>>> Added to bill" << endl;
							cout << ">>>>> Total: " << bill.total() << endl;
						}
					}
					else
					{
						cout << "Item out of stock" << endl;
					}
				}
			}
			//if cin fails
			if (cin.fail())
			{
				cout << "SKU too long" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (sku[0] != '\0');

		//Printing and clearing bill
		bill.print(cout);
		bill.clear();
		cout.unsetf(ios::right);
	}

	/*To save the updated list of items in the file*/
	void PosApp::saveRecs() const
	{
		title("Saving Data");

		ofstream output(m_filename);

		if (output)
		{
			for (int i = 0; i < m_nptr; i++)
			{
				if (m_Iptr[i] != nullptr)
				{
					output << *m_Iptr[i] << endl;
				}
			}
		}
	}

	/*To laod all the items from the file to the m_Iptr*/
	void PosApp::loadRecs()
	{
		title("Loading Items");

		ifstream input(m_filename);

		if (!input.is_open())
		{
			ofstream output(m_filename);
			output.close();
		}

		//Setting PosApp to safe empty state
		setEmpty();
		char itemType;
		do
		{
			//Looping until max number of items is reached or end of file
			if (input && m_nptr < MAX_NO_ITEMS)
			{
				input >> itemType;
				input.ignore();

				//Checkinf if item is perishable or NonPerishable
				if (itemType == 'P')
				{
					m_Iptr[m_nptr] = new Perishable;
					input >> *m_Iptr[m_nptr];
					m_nptr++;
				}
				else if (itemType == 'N')
				{
					m_Iptr[m_nptr] = new NonPerishable;
					input >> *m_Iptr[m_nptr];
					m_nptr++;
				}

				input.ignore();

				if (input.peek() == EOF)
				{
					input.close();
				}
			}
		} while (m_nptr < MAX_NO_ITEMS && input.is_open());
	}

	/*To dislpay the action title*/
	void PosApp::title(const char* msg) const
	{
		cout << ">>>> ";
		cout.setf(ios::left);
		cout.width(72);
		cout.fill('.');
		cout << msg;
		cout << endl;
		cout.unsetf(ios::left);
	}

	/*To set PosApp to safe empty state*/
	void PosApp::setEmpty()
	{
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			if (m_Iptr[i] != nullptr)
			{
				delete m_Iptr[i];
			}
			m_Iptr[i] = nullptr;
		}
		m_nptr = 0;
	}

	/*To print list header*/
	void PosApp::printHeader()
	{
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
	}

	/*To print all the items in the PosApp*/
	void PosApp::printBody()
	{
		for (int i = 0; i < m_nptr; i++)
		{
			m_Iptr[i]->displayType(POS_LIST);

			cout.fill(' ');
			cout.setf(ios::right);
			cout.width(4);
			cout << (i + 1);
			cout << " | ";
			cout.unsetf(ios::right);

			m_Iptr[i]->write(cout);
			cout << endl;
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
	}

	/*To calculate and display total of all the items in PosApp*/
	void PosApp::printTotal()
	{
		double total = 0.0;

		for (int i = 0; i < m_nptr; i++)
		{
			total += m_Iptr[i]->cost() * m_Iptr[i]->quantity();
		}
		cout.fill(' ');
		cout.setf(ios::right);
		cout.width(48);
		cout << "Total Asset: $  |";

		cout.width(14);
		cout << total;
		cout << '|' << endl;

		cout << "-----------------------------------------------^--------------^\n" << endl;
		cout.unsetf(ios::right);
	}

	/*This function returns the user choice of row num of the item to be removed*/
	int PosApp::selectItem()
	{
		int itemNum;
		title("Item Selection by row number");
		cin.ignore(1000, '\n');
		cout << "Press <ENTER> to start....";
		cin.ignore(1000, '\n');
		listItems(false);
		cout << "Enter the row number: ";
		inputInt(itemNum, 1, m_nptr, 2);
		return itemNum;
	}


	/*This function gets sku from the user and returns the address of the item in PosApp or nullptr*/
	Item* PosApp::search(char* sku)
	{
		Item* ptr = nullptr;

		for (int i = 0; i < m_nptr && ptr == nullptr; i++)
		{
			if (*m_Iptr[i] == sku)
			{
				ptr = m_Iptr[i];
			}
		}
		return ptr;
	}

	/*One argument constructor
	Parameters:
	const char filename[]*/
	PosApp::PosApp(const char filename[])
	{
		strcpy(m_filename, filename);
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			m_Iptr[i] = nullptr;
		}
		m_nptr = 0;
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

	/*Default destructor*/
	PosApp::~PosApp()
	{
		setEmpty();
	}
}