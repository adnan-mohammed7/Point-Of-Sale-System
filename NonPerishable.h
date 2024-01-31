#pragma once
#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H

#include "Item.h"

namespace sdds
{
	class NonPerishable : public Item {
	public:
		//To return the type of item nonperishable
		char itemType()const;

		//To display nonperishable item to ostream
		std::ostream& write(std::ostream& os) const;
	};
}

#endif 
