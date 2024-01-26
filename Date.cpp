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
}