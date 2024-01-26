#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include"Error.h"

using namespace std;

namespace sdds
{
	//Deault constructor
	Error::Error()
	{
		errorMessage = nullptr;
	}

	//One argument constructor
	Error::Error(const char error[])
	{
		if (errorMessage == nullptr)
		{
			errorMessage = new char[(strlen(error) + 1)];
			strcpy(errorMessage, error);
		}
	}

	//Destructor
	Error::~Error()
	{
		if (errorMessage != nullptr)
		{
			delete[] errorMessage;
		}
	}

	//Copy constructor
	Error::Error(Error& rhs)
	{
		errorMessage = nullptr;
		*this = rhs;
	}

	//Copt assignment operator
	Error& Error::operator=(Error& rhs)
	{
		if (this != &rhs)
		{
			delete[] errorMessage;
			errorMessage = nullptr;

			if (rhs)
			{
				errorMessage = new char[(strlen(rhs.errorMessage) + 1)];
				strcpy(errorMessage, rhs.errorMessage);
			}

		}
		return *this;
	}

	//=operator overload
	void Error::operator=(const char error[])
	{
		if (error != NULL && error[0] != '\0')
		{
			if (errorMessage != nullptr)
			{
				delete[] errorMessage;
			}
			errorMessage = new char[(strlen(error) + 1)];
			strcpy(errorMessage, error);
		}
		else
		{
			errorMessage = nullptr;
		}
	}

	//Bool conversion operator
	Error::operator bool() const
	{
		return errorMessage != nullptr;
	}

	//sets the error object to safe empty state
	Error& Error::clear()
	{
		if (errorMessage != nullptr)
		{
			delete[] errorMessage;
			errorMessage = nullptr;
		}
		return *this;
	}

	//to display error class object
	char* Error::errorMsg() const
	{
		return errorMessage;
	}

}