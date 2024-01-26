#ifndef ERROR_H
#define ERROR_H

#include<iostream>

namespace sdds
{
	class Error
	{
		char* errorMessage = nullptr;
	public:
		/*Default constructor*/
		Error();

		/*One argument Constuctor*/
		Error(const char error[]);

		/*Destuctor*/
		~Error();

		/*Copy constructor
		Parameters
		Error& rhs*/
		Error(Error& rhs);

		/*Copt assignment operator
		Parameters
		Error& rhs*/
		Error& operator=(Error& rhs);

		/*=operator overload
		Parameters
		const char error[]*/
		void operator=(const char error[]);

		/*Bool conervsion operator for error class*/
		operator bool() const;

		/*Set the error class object to empty state*/
		Error& clear();

		/*To display error class object*/
		char* errorMsg() const;

	};

	/*<< operator overload*/
	std::ostream& operator<<(std::ostream& os, const Error& rhs);
}
#endif // !ERROR_H