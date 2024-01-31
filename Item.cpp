#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

namespace sdds
{
	Item::Item()
	{
		//Empty state
		m_name = nullptr;
		strcpy(m_sku, "");
		m_price = 0.0;
		m_taxable = false;
		m_quantity = 0;
		m_displayType = 0;
	}
	Item::Item(const Item& rhs)
	{
		//Initialising to nullptr
		m_name = nullptr;
		//copy assignment operator
		*this = rhs;
	}
	Item& Item::operator=(const Item& rhs)
	{
		if (this != &rhs)
		{
			setEmpty();
			clear();
			if (rhs.m_name != NULL && rhs.m_name[0] != '\0')
			{
				//Resource 
				m_name = new char[(strlen(rhs.m_name) + 1)];
				strcpy(m_name, rhs.m_name);
				m_name[strlen(rhs.m_name)] = '\0';

				//Static Variables
				strcpy(m_sku, rhs.m_sku);
				m_price = rhs.m_price;
				m_taxable = rhs.m_taxable;
				m_quantity = rhs.m_quantity;
				m_displayType = rhs.m_displayType;
			}
		}
		return *this;
	}
	Item::~Item()
	{
		//Deleting Resource
		delete[] m_name;
		m_name = nullptr;

		//Deletnig Error object resource
		clear();
	}
	bool Item::operator==(const char sku[]) const
	{
		//Checks if string are same
		return !strcmp(m_sku, sku);
	}
	bool Item::operator>(const Item& rhs) const
	{
		int result = true;
		if (m_name != nullptr && rhs.m_name != nullptr)
		{
			//To check if string1 is greater than string 2
			result = strcmp(m_name, rhs.m_name);
		}
		return result > 0 ? true : false;
	}
	int Item::operator+=(const int num)
	{
		m_quantity += num;
		//Checking if quantity is beyond max stock number
		if (m_quantity > MAX_STOCK_NUMBER)
		{
			m_status = ERROR_POS_QTY;
			m_quantity = MAX_STOCK_NUMBER;
		}
		return m_quantity;
	}
	int Item::operator-=(const int num)
	{
		//Checking if quantity is below 0
		if (num > m_quantity)
		{
			m_status = ERROR_POS_STOCK;
			m_quantity = 0;
		}
		else
		{
			m_quantity -= num;
		}
		return m_quantity;
	} ///
	Item::operator bool() const
	{
		//Reutrning opposite state of error object
		return !m_status;
	}
	Item& Item::displayType(int num)
	{
		//Displat format
		if (num == POS_LIST || num == POS_FORM)
		{
			m_displayType = num;
		}
		return *this;
	}
	double Item::cost() const
	{
		//Returning cost of item
		return m_taxable ? (m_price + (m_price * TAX)) : m_price;
	}
	int Item::quantity() const
	{
		//Returning quantity of item
		return m_quantity;
	}

	Item& Item::clear()
	{
		//clearing error object
		m_status.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& os) const
	{
		if (!(*this))
		{
			os << m_status;
		}
		else
		{
			os.fill(' ');
			if (m_displayType == POS_LIST)
			{
				if (m_name != NULL && m_name[0] != '\0')
				{
					os.setf(ios::left);
					os.width(7);
					os << m_sku;
					os << "|";
					if (strlen(m_name) > 20)
					{
						for (int i = 0; i < 20; i++)
						{
							os << m_name[i];
						}
					}
					else
					{
						os.width(20);
						os << m_name;
					}
					os << "|";
					os.width(7);
					os.setf(ios::fixed);
					os.precision(2);
					os.unsetf(ios::left);
					os.setf(ios::right);
					os << m_price;
					os << "| ";
					if (m_taxable)
					{
						os << 'X';
					}
					else
					{
						os << ' ';
					}
					os << " |";
					os.width(4);
					os << m_quantity;
					os << "|";
					os.width(9);
					os << (cost() * quantity());
					os << "|";
					os.unsetf(ios::right);
				}
			}
			else if (m_displayType == POS_FORM)
			{
				os << "=============v" << endl;
				os.setf(ios::left);
				os.width(13);
				os << "Name:";
				os << m_name << endl;
				os.width(13);
				os << "Sku:";
				os << m_sku << endl;
				os.setf(ios::fixed);
				os.precision(2);
				os.width(13);
				os << "Price:";
				os << m_price << endl;
				os.width(13);
				os << "Price + tax:";
				if (m_taxable)
				{
					os << cost() << endl;
				}
				else
				{
					os << "N/A" << endl;
				}
				os.width(13);
				os << "Stock Qty:";
				os << m_quantity << endl;
				os.unsetf(ios::left);
			}
		}
		return os;
	}

	std::istream& Item::read(std::istream& is)
	{
		//Setting object to empty state
		setEmpty();
		clear();

		//Getting sku input from the user
		cout << "Sku" << endl;
		int check = 0;
		do
		{
			cout << "> ";
			is.getline(m_sku, MAX_SKU_LEN, '\n');
			if (!(is.fail()))
			{
				check = 1;
			}
			else
			{
				check = 0;
				cout << ERROR_POS_SKU << endl;
				flush(is);
			}
		} while (!check);

		//Getting name input from the user
		cout << "Name" << endl;
		check = 0;
		do
		{
			char input[MAX_NAME_LEN] = "";
			cout << "> ";
			is.getline(input, MAX_NAME_LEN, '\n');
			if (!(is.fail()))
			{
				m_name = new char[strlen(input) + 1];
				strcpy(m_name, input);
				check = 1;
			}
			else
			{
				check = 0;
				cout << ERROR_POS_NAME << endl;
				flush(is);
			}
		} while (!check);

		//getting price input from the user
		cout << "Price" << endl;
		check = 0;
		do
		{
			cout << "> ";
			is >> m_price;

			if (is.fail())
			{
				flush(is);
				cout << ERROR_POS_PRICE << endl;
				check = 0;
			}
			else if (m_price < 0)
			{
				cout << ERROR_POS_PRICE << endl;
				check = 0;
			}
			else if (m_price >= 0)
			{
				check = 1;
			}
		} while (check == 0);

		//Getting tax input from the user
		cout << "Taxed?" << endl;
		cout << "(Y)es/(N)o: ";
		check = 0;
		char input = 'l';
		do
		{
			is >> input;

			if (input == 'y' || input == 'Y')
			{
				m_taxable = true;
				check = 1;
			}
			else if (input == 'n' || input == 'N')
			{
				m_taxable = false;
				check = 1;
			}
			else
			{
				flush(is);
				cout << "Only 'y' and 'n' are acceptable: ";
				check = 0;
			}
		} while (!check);

		//getting quantity input from the user
		cout << "Quantity" << endl;
		check = 0;
		do
		{
			cout << "> ";
			is >> m_quantity;

			if (is.fail())
			{
				flush(is);
				cout << ERROR_POS_QTY << endl;
				check = 0;
			}
			else if (m_quantity < 1 || m_quantity > MAX_STOCK_NUMBER)
			{
				cout << ERROR_POS_QTY << endl;
				check = 0;
			}
			else if (m_quantity >= 1 && m_quantity <= MAX_STOCK_NUMBER)
			{
				check = 1;
			}
		} while (!check);

		return is;
	}

	std::ofstream& Item::save(std::ofstream& os) const
	{
		os.fill(' ');
		//Writing to a file
		if (!(*this))
		{
			cerr << m_status << endl;
		}
		else
		{
			os.setf(ios::fixed);
			os.precision(2);
			os << itemType();
			os << ',' << m_sku;
			os << ',' << m_name;
			os << ',' << m_price;
			os << ',';
			if (m_taxable)
			{
				os << 1;
			}
			else
			{
				os << 0;
			}
			os << ',' << m_quantity;
		}
		return os;
	}

	std::ifstream& Item::load(std::ifstream& is)
	{
		//Local Variables to read from file
		char sku[MAX_SKU_LEN] = "";
		char name[MAX_NAME_LEN] = "";
		double price = 0.0;
		int taxable = 0;
		int quantity = 0;
		int fail = 0;

		clear();
		setEmpty();

		//Reading sku from file and validating
		is.getline(sku, MAX_SKU_LEN, ',');
		if (is.fail())
		{
			m_status = ERROR_POS_SKU;
			fail = 1;
			is.clear();
			setEmpty();
		}
		if (!fail)
		{
			//Reading name from file and validating
			is.getline(name, MAX_NAME_LEN, ',');
			if (is.fail())
			{
				m_status = ERROR_POS_NAME;
				fail = 1;
				is.clear();
				setEmpty();
			}
		}
		if (!fail)
		{
			//Reading price from file and validating
			is >> price;
			if (is.fail())
			{
				m_status = ERROR_POS_PRICE;
				fail = 1;
				is.clear();
				setEmpty();
			}
			is.get();
		}
		if (!fail)
		{
			//Reading tax value from file and validating
			is >> taxable;
			if (is.fail())
			{
				m_status = ERROR_POS_TAX;
				fail = 1;
				is.clear();
				setEmpty();
			}
			is.get();
		}
		if (!fail)
		{
			//Reading quantity from file and validating
			is >> quantity;
			if (is.fail())
			{
				m_status = ERROR_POS_QTY;
				fail = 1;
				is.clear();
				setEmpty();
			}
		}

		if (!fail)
		{
			//Validating all the values
			if (price < 0)
			{
				m_status = ERROR_POS_PRICE;
			}
			else if (taxable != 0 && taxable != 1)
			{
				m_status = ERROR_POS_TAX;
			}
			else if (quantity < 1 || quantity > MAX_STOCK_NUMBER)
			{
				m_status = ERROR_POS_QTY;
			}
		}

		if (!fail)
		{
			//storing data in original object variables
			strcpy(m_sku, sku);
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
			m_price = price;
			m_taxable = taxable;
			m_quantity = quantity;
		}

		//Checking if end of file is reached
		if (is.peek() == EOF)
		{
			//closing the file
			is.close();
		}

		return is;
	}
	std::ostream& Item::bprint(std::ostream& os) const
	{
		os.fill(' ');
		//Formatted output
		os << "| ";
		if (strlen(m_name) > 20)
		{
			for (int i = 0; i < 20; i++)
			{
				os << m_name[i];
			}
		}
		else
		{
			os.setf(ios::left);
			os.width(20);
			os << m_name;
		}
		os << '|';

		os.unsetf(ios::left);
		os.setf(ios::right);
		os.width(10);
		os << cost();
		os << " |  ";
		if (m_taxable)
		{
			os << 'T';
		}
		else
		{
			os << ' ';
		}
		os << "  |" << endl;
		os.unsetf(ios::right);

		return os;
	}
	void Item::setEmpty()
	{
		//delaocating resource
		delete[] m_name;
		m_name = nullptr;

		//setting member variables empty
		strcpy(m_sku, "");
		m_price = 0.0;
		m_taxable = false;
		m_quantity = 0;
		m_displayType = 0;
	}
	void Item::flush(istream& is)
	{
		//clearing buffer and istream object
		is.clear();
		is.ignore(1000, '\n');
	}
	double operator+=(double& num, const Item& rhs)
	{
		return (num + (rhs.cost() * rhs.quantity()));
	}
}