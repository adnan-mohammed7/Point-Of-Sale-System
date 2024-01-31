#pragma once
#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{
	class Perishable : public Item {
		Date m_expiry;
	public:
		char itemType()const;
		/*To display Perishable Item object to ostream
		Parameters:
		ostream& os*/
		std::ostream& write(std::ostream& os) const;

		/*To get input for Perishable Item object from user
		Parameters:
		istream& is*/
		std::istream& read(std::istream& is);

		/*To store Perishable Items to files
		Parameters:
		ofstream& os*/
		std::ofstream& save(std::ofstream& os) const;

		/*To get Perishable items from files
		Paraemters:
		ifstream& is*/
		std::ifstream& load(std::ifstream& is);
	};
}
#endif // !PERISHABLE_H
