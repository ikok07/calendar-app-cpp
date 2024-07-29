//
// Created by Kaloyan Petkov on 29.07.24.
//

#ifndef CALENDAR_APP_CPP_UTILS_H
#define CALENDAR_APP_CPP_UTILS_H
#include <iostream>
using namespace std;

enum class Month {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

struct ParsedDate {
    int m_day;
    int month;
    int year;
};

class Utils {
public:
    static bool year_is_leap(int year);
    static int days_in_month(int month, int year);
    static string month_name(int month);
    static ParsedDate parse_date_str(const string& date_str);
};


#endif //CALENDAR_APP_CPP_UTILS_H
