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
}