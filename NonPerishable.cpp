#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"NonPerishable.h"

using namespace std;

namespace sdds
{
	char NonPerishable::itemType() const
	{
		//returns n to refer as NonPerishable
		return 'N';
	}
	std::ostream& NonPerishable::write(std::ostream& os) const
	{
		//base class wrtie function(ITEM)
		Item::write(os);

		//if os & curret=nt object are valid displaying date object
		if (os && *this)
		{
			if (m_displayType == POS_LIST)
			{
				os << "     N / A   |";
			}
			else
			{
				os << "=============^" << endl;
			}
		}
		return os;
	}
}