#ifndef DATE_H
#define DATE_H

#include <iostream>
#include"Error.h"

namespace sdds
{
	class Date
	{
		/*Data members*/
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_min;
		bool m_onlyDate;
		Error m_msg;
	public:

		/*Default Constructor*/
		Date();

		/*Three argument consttuctor*/
		Date(int year, int month, int day);

		/*Five argument constructor*/
		Date(int year, int month, int day, int hour, int min = 0);

		/*==operator overload for date class
		Parameters
		Date& rhs*/
		bool operator==(const Date& rhs) const;

		/*!=operator overload for date class
		Parameters
		Date& rhs*/
		bool operator!=(const Date& rhs) const;

		/*<operator overload for date class
		Parameters
		Date& rhs*/
		bool operator<(const Date& rhs) const;

		/*>operator overload for date class
		Parameters
		Date& rhs*/
		bool operator>(const Date& rhs) const;

		/*<=operator overload for date class
		Parameters
		Date& rhs*/
		bool operator<=(const Date& rhs) const;

		/*>=operator overload for date class
		Parameters
		Date& rhs*/
		bool operator>=(const Date& rhs) const;

		/*To set the dateonly member variable
		Parameters
		bool input*/
		Date& dateOnly(bool input);

		/*Bool conversion operator
		Returns the opposite state of error obeject*/
		operator bool() const;

		/*Returns the refernece to the error object*/
		const Error& error() const;

		/*To display the date class object
		Parameters
		ostream& os*/
		std::ostream& displayDate(std::ostream& os);

		/*To read the date class object
		Parameters
		istream& is*/
		std::istream& read(std::istream& is);

		//Utilities Function

		/*To validate all the data members of date class*/
		void validate(int year, int month, int day, int hour, int min);
	};

	/*<<operator overload to insert date class into ostream*/
	std::ostream& operator<<(std::ostream& os, Date& rhs);

	/*>>operator overload to insert date class into istream*/
	std::istream& operator>>(std::istream& is, Date& rhs);

}
#endif // !DATE_H