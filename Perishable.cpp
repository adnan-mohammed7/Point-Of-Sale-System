#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Perishable.h"

using namespace std;

namespace sdds
{
	char sdds::Perishable::itemType() const
	{
		//Returns P to refer as perishable
		return 'P';
	}

	std::ostream& Perishable::write(std::ostream& os) const
	{
		//Base class write(item)
		Item::write(os);

		//if os and current object is valid displaying date object
		if (*this && os)
		{
			if (m_displayType == POS_LIST)
			{
				os << "  " << m_expiry;
				os << " |";
			}
			else
			{
				os << "Expiry date: ";
				os << m_expiry << endl;
				os << "=============^" << endl;
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		//base class read(item)
		Item::read(is);

		//If is and current object is valid getting user input for date
		if (*this && is)
		{
			Date input;
			input.dateOnly(true);

			cout << "Expiry date (YYYY/MM/DD)" << endl;
			cout << "> ";

			is >> input;
			if (is && input)
			{
				m_expiry = input;
			}
			else
			{
				m_status = input.error();
			}
		}
		return is;
	}

	std::ofstream& Perishable::save(std::ofstream& os) const
	{
		//Base class save function(Item)
		Item::save(os);

		//If os and current object is valid printing date to file
		if (*this && os)
		{
			os << ',';
			os << m_expiry;
		}
		return os;
	}

	std::ifstream& Perishable::load(std::ifstream& is)
	{
		//base class load function(Item)
		Item::load(is);

		//If is and current object are valid getting date object from file
		if (*this && is)
		{
			Date input;
			input.dateOnly(true);
			is.ignore();
			is >> input;

			if (is && input)
			{
				m_expiry = input;
			}
			else
			{
				m_status = input.error();
			}
		}
		return is;
	}
}