#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include "PosIO.h"

namespace sdds
{
	PosIO::~PosIO()
	{
	}
	std::ostream& operator<<(std::ostream& os, const PosIO& rhs)
	{
		//Calling the defined function
		return rhs.write(os);
	}
	std::ofstream& operator<<(std::ofstream& os, const PosIO& rhs)
	{
		//Calling the defined function
		return rhs.save(os);
	}
	std::istream& operator>>(std::istream& is, PosIO& rhs)
	{
		//Calling the defined function
		return rhs.read(is);
	}
	std::ifstream& operator>>(std::ifstream& is, PosIO& rhs)
	{
		//Calling the defined function
		return rhs.load(is);
	}
}