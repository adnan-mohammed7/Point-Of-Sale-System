#ifndef POSIO_H
#define POSIO_H

#include <iostream>
#include <fstream>

namespace sdds
{
	class PosIO {
	public:
		//Pure Virtual Functions
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ofstream& save(std::ofstream& os) const = 0;
		virtual std::ifstream& load(std::ifstream& is) = 0;
		virtual ~PosIO();
	};
	//Iostream & Ifstream overload
	std::ostream& operator<<(std::ostream& os, const PosIO& rhs);
	std::ofstream& operator<<(std::ofstream& os, const PosIO& rhs);
	std::istream& operator>>(std::istream& is, PosIO& rhs);
	std::ifstream& operator>>(std::ifstream& is, PosIO& rhs);
}
#endif // !POSIO_H
