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
}