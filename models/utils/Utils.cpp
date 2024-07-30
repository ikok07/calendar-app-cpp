//
// Created by Kaloyan Petkov on 29.07.24.
//

#include <sstream>

#include "Utils.h"

bool Utils::year_is_leap(const int year) {
    bool year_is_leap;

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) year_is_leap = true;
            else year_is_leap = false;
        } else {
            year_is_leap = true;
        }
    } else {
        year_is_leap = false;
    }
    return year_is_leap;
}

int Utils::days_in_month(const int month, const int year) {
    bool is_leap = year_is_leap(year);
    int days_in_month;

    if (is_leap && month == 2) days_in_month = 29;
    else if (!is_leap && month == 2) days_in_month = 28;
    else if (month < 8) {
        if (month % 2 == 0) days_in_month = 30;
        else days_in_month = 31;
    } else {
        if (month % 2 == 0) days_in_month = 31;
        else days_in_month = 30;
    }
    return days_in_month;
}

string Utils::month_name(const int month) {
    switch (static_cast<Month>(month)) {
        case Month::JAN: return "Jan";
        case Month::FEB: return "Feb";
        case Month::MAR: return "Mar";
        case Month::APR: return "Apr";
        case Month::MAY: return "May";
        case Month::JUN: return "Jun";
        case Month::JUL: return "Jul";
        case Month::AUG: return "Aug";
        case Month::SEP: return "Sep";
        case Month::OCT: return "Oct";
        case Month::NOV: return "Nov";
        case Month::DEC: return "Dec";
        default: return "Unknown";
    }
}

ParsedDate Utils::parse_date_str(const string &date_str) {
    ParsedDate parsed_date{};
    stringstream ss(date_str);
    string m_day_str;
    string month_str;
    string year_str;

    getline(ss, m_day_str, '/');
    getline(ss, month_str, '/');
    getline(ss, year_str, '/');
    parsed_date.m_day = stoi(m_day_str);
    parsed_date.month = stoi(month_str);
    parsed_date.year = stoi(year_str);
    return parsed_date;
}

int Utils::timestamp_same_day(const time_t &t1, const time_t &t2) {
    struct tm src_time = *localtime(&t1);
    struct tm *cmp_time = localtime(&t2);
    int result = 0;

    if (cmp_time->tm_year < src_time.tm_year) result = -1;
    else if (cmp_time->tm_year > src_time.tm_year) result = 1;
    if (result != 0) return result;

    if (cmp_time->tm_mon < src_time.tm_mon) result = -1;
    else if (cmp_time->tm_mon > src_time.tm_mon) result = 1;
    if (result != 0) return result;

    if (cmp_time->tm_mday < src_time.tm_mday) result = -1;
    else if (cmp_time->tm_mday > src_time.tm_mday) result = 1;
    return result;
}
