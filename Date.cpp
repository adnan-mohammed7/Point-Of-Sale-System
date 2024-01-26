#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include<ctime>
#include"Date.h"
#include"Error.h"
#include"POS.h"

using namespace std;

namespace sdds
{
    //To get system date
    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    //To check for unique date
    int uniqueDateValue(int year, int mon, int day, int hour, int min) {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    //To check for days in a month
    int daysOfMonth(int year, int month) {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    //Deault Constructor for date class
    Date::Date()
    {
        getSystemDate(m_year, m_month, m_day, m_hour, m_min, false);
        m_onlyDate = false;
    }

    //Three argument constructor for date class
    Date::Date(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = m_min = 0;
        m_onlyDate = true;

        validate(m_year, m_month, m_day, m_hour, m_min);
    }

    //Five argument constructor for date class
    Date::Date(int year, int month, int day, int hour, int min)
    {
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = hour;
        m_min = min;
        m_onlyDate = false;

        validate(m_year, m_month, m_day, m_hour, m_min);
    }

    //==operator overload for date class
    bool Date::operator==(const Date& rhs) const
    {
        bool flag = true;
        if (m_year != rhs.m_year)
        {
            flag = false;
        }
        else if (m_month != rhs.m_month)
        {
            flag = false;
        }
        else if (m_day != rhs.m_day)
        {
            flag = false;
        }
        else if (m_hour != rhs.m_hour)
        {
            flag = false;
        }
        else if (m_min != rhs.m_min)
        {
            flag = false;
        }
        return flag;
    }

    //!=operator overload for date class
    bool Date::operator!=(const Date& rhs) const
    {
        bool flag = false;
        if (m_year != rhs.m_year)
        {
            flag = true;
        }
        else
        {
            if (m_month != rhs.m_month)
            {
                flag = true;
            }
            else
            {
                if (m_day != rhs.m_day)
                {
                    flag = true;
                }
                else
                {
                    if (m_hour != rhs.m_hour)
                    {
                        flag = true;
                    }
                    else
                    {
                        if (m_min != rhs.m_min)
                        {
                            flag = true;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                }
            }
        }


        return flag;
    }

    //<operator overload for date class
    bool Date::operator<(const Date& rhs) const
    {
        bool flag = false;
        if (m_year < rhs.m_year)
        {
            flag = true;
        }
        else if (m_year > rhs.m_year)
        {
            flag = false;
        }
        else if (m_year == rhs.m_year)
        {
            if (m_month < rhs.m_month)
            {
                flag = true;
            }
            else if (m_month > rhs.m_month)
            {
                flag = false;
            }
            else if (m_month == rhs.m_month)
            {
                if (m_day < rhs.m_day)
                {
                    flag = true;
                }
                else if (m_day > rhs.m_day)
                {
                    flag = false;
                }
                else if (m_day == m_day)
                {
                    if (m_onlyDate == false)
                    {
                        if (m_hour < rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour > rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour == rhs.m_hour)
                        {
                            if (m_min < rhs.m_min)
                            {
                                flag = true;
                            }
                            else
                            {
                                flag = false;
                            }
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                }
            }
        }

        return flag;
    }

    //>operator overload for date class
    bool Date::operator>(const Date& rhs) const
    {
        bool flag = false;
        if (m_year > rhs.m_year)
        {
            flag = true;
        }
        else if (m_year < rhs.m_year)
        {
            flag = false;
        }
        else if (m_year == rhs.m_year)
        {
            if (m_month > rhs.m_month)
            {
                flag = true;
            }
            else if (m_month < rhs.m_month)
            {
                flag = false;
            }
            else if (m_month == rhs.m_month)
            {
                if (m_day > rhs.m_day)
                {
                    flag = true;
                }
                else if (m_day < rhs.m_day)
                {
                    flag = false;
                }
                else if (m_day == m_day)
                {
                    if (m_onlyDate == false)
                    {
                        if (m_hour > rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour < rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour == rhs.m_hour)
                        {
                            if (m_min > rhs.m_min)
                            {
                                flag = true;
                            }
                            else
                            {
                                flag = false;
                            }
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                }
            }
        }

        return flag;
    }

    //<=operator overload for date class
    bool Date::operator<=(const Date& rhs) const
    {
        bool flag = false;
        if (m_year < rhs.m_year)
        {
            flag = true;
        }
        else if (m_year > rhs.m_year)
        {
            flag = false;
        }
        else if (m_year == rhs.m_year)
        {
            if (m_month < rhs.m_month)
            {
                flag = true;
            }
            else if (m_month > rhs.m_month)
            {
                flag = false;
            }
            else if (m_month == rhs.m_month)
            {
                if (m_day < rhs.m_day)
                {
                    flag = true;
                }
                else if (m_day > rhs.m_day)
                {
                    flag = false;
                }
                else if (m_day == m_day)
                {
                    if (m_onlyDate == false)
                    {
                        if (m_hour < rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour > rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour == rhs.m_hour)
                        {
                            if (m_min < rhs.m_min)
                            {
                                flag = true;
                            }
                            else if (m_min > rhs.m_min)
                            {
                                flag = false;
                            }
                            else
                            {
                                flag = true;
                            }
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                }
            }
        }

        return flag;
    }

    //>=operator overload for date class
    bool Date::operator>=(const Date& rhs) const
    {
        bool flag = false;
        if (m_year > rhs.m_year)
        {
            flag = true;
        }
        else if (m_year < rhs.m_year)
        {
            flag = false;
        }
        else if (m_year == rhs.m_year)
        {
            if (m_month > rhs.m_month)
            {
                flag = true;
            }
            else if (m_month < rhs.m_month)
            {
                flag = false;
            }
            else if (m_month == rhs.m_month)
            {
                if (m_day > rhs.m_day)
                {
                    flag = true;
                }
                else if (m_day < rhs.m_day)
                {
                    flag = false;
                }
                else if (m_day == m_day)
                {
                    if (m_onlyDate == false)
                    {
                        if (m_hour > rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour < rhs.m_hour)
                        {
                            flag = true;
                        }
                        else if (m_hour == rhs.m_hour)
                        {
                            if (m_min > rhs.m_min)
                            {
                                flag = true;
                            }
                            else if (m_min < rhs.m_min)
                            {
                                flag = false;
                            }
                            else
                            {
                                flag = true;
                            }
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                }
            }
        }

        return flag;
    }

    //Sets the dateonly member variable
    Date& Date::dateOnly(bool input)
    {
        input ? m_onlyDate = true : m_onlyDate = false;
        return *this;
    }

    //bool operator overload for date class
    Date::operator bool() const
    {
        return !m_msg;
    }

    //returns a reference to the error object in date class
    const Error& Date::error() const
    {
        return m_msg;
    }

    //For displaying date class object
    std::ostream& Date::displayDate(std::ostream& os)
    {
        if (m_msg)
        {
            os << m_msg;
            os << '(';
        }
        os << m_year;
        os << '/';
        os.setf(ios::right);
        os.width(2);
        os.fill('0');
        os << m_month;
        os.unsetf(ios::right);
        os << '/';
        os.width(2);
        os << m_day;
        if (m_onlyDate)
        {
            if (m_msg)
            {
                os << ')';
            }
        }
        else
        {
            os << ", ";
            os.width(2);
            os << m_hour;
            os << ':';
            os.width(2);
            os << m_min;
            if (m_msg)
            {
                os << ')';
            }
        }
        return os;
    }

    //For inputting date class object
    std::istream& Date::read(std::istream& is)
    {
        bool check = true;
        m_msg.clear();
        m_year = m_month = m_day = m_hour = m_min = 0;

        is >> m_year;
        if (is.fail())
        {
            m_msg = "Cannot read year entry";
            is.clear();
            check = false;
        }
        is.ignore();
        if (check)
        {
            is >> m_month;
            if (is.fail())
            {
                m_msg = "Cannot read month entry";
                is.clear();
                check = false;
            }
            is.ignore();
        }

        if (check)
        {
            is >> m_day;
            if (is.fail())
            {
                m_msg = "Cannot read day entry";
                is.clear();
                check = false;
            }
        }

        if (check)
        {
            if (is.peek() != '\n')
            {
                is.ignore(2, isdigit(is.peek()));
                if (check)
                {
                    is >> m_hour;
                    if (is.fail())
                    {
                        m_msg = "Cannot read hour entry";
                        is.clear();
                        check = false;
                    }
                    is.ignore();
                }
                if (check)
                {
                    is >> m_min;
                    if (is.fail())
                    {
                        m_msg = "Cannot read minute entry";
                        is.clear();
                        check = false;
                    }
                }
            }
            else
            {
                m_hour = m_min = 0;
            }
        }

        if (check)
        {
            validate(m_year, m_month, m_day, m_hour, m_min);
        }
        return is;
    }

    //Helper function to overload << operator for date class
    std::ostream& operator<<(std::ostream& os, Date& rhs)
    {
        return rhs.displayDate(os);
    }

    //Helper function to overload >> operator for date class
    std::istream& operator>>(std::istream& is, Date& rhs)
    {
        return rhs.read(is);
    }
}