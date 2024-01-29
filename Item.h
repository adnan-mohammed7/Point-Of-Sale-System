#ifndef ITEM_H
#define ITEM_H

#include "POS.h"
#include "Error.h"
#include "PosIO.h"

#include <iostream>
#include <fstream>

namespace sdds
{
	class Item : public PosIO {
		/*Member variables*/
		char m_sku[MAX_SKU_LEN];
		char* m_name;
		double m_price;
		bool m_taxable;
		int m_quantity;
	protected:
		/*Protected member variables*/
		int m_displayType;
		Error m_status;
	public:
		/*Default no-argument constructor*/
		Item();

		/*Copy Constructor
		Parameters:
		Item& rhs*/
		Item(const Item& rhs);

		/*Copy assignment operator
		Paraemters:
		const Item& rhs*/
		Item& operator=(const Item& rhs);

		/*Default Destructor*/
		~Item();

		/*==operator overload which compares sku's
		Parameters:
		const char sku[]*/
		bool operator==(const char sku[]) const;

		/*>operator overload which compares sku's
		Parameters:
		Item& rhs*/
		bool operator>(const Item& rhs) const;

		/*+=operator overload which adds num to quantity
		Paraemeters:
		int num*/
		int operator+=(const int num);

		/*-=operator overload which subtracts num from quantity
		Paraemeters:
		int num*/
		int operator-=(const int num);

		/*bool operator overload*/
		operator bool() const;

		/*virtual function itemType()*/
		virtual char itemType()const = 0;

		/*For list or form type
		Parameters:
		const int num*/
		Item& displayType(const int num);

		/*returns price of item with tax if taxable*/
		double cost() const;

		/*returns quantity of items*/
		int quantity() const;

		/*clear the error object*/
		Item& clear();

		/*To display Item object to ostream
		Parameters:
		ostream& os*/
		std::ostream& write(std::ostream& os) const;

		/*To get input for Item object from user
		Parameters:
		istream& is*/
		std::istream& read(std::istream& is);

		/*To store Items to files
		Parameters:
		ofstream& os*/
		std::ofstream& save(std::ofstream& os) const;

		/*To get items from files
		Paraemters:
		ifstream& is*/
		std::ifstream& load(std::ifstream& is);

		/*to display Item obejct in bill format
		Parameters:
		ostream& os*/
		std::ostream& bprint(std::ostream& os);

		/*To set item object to safe empty state*/
		void setEmpty();

		/*To clear input buffer and istream object*/
		void flush(std::istream& is);
	};

	/*+= operator overload which returns the double value added to total of the item
	Parameters:
	double num
	Item& rhs*/
	double operator+=(double& num, const Item& rhs);
}
#endif // !ITEM_H
