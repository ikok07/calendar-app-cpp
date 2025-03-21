//
// Created by Kaloyan Petkov on 29.07.24.
//

#ifndef CALENDAR_APP_CPP_OPTIONHANDLER_H
#define CALENDAR_APP_CPP_OPTIONHANDLER_H
#include <iostream>
using namespace std;

class OptionHandler {
public:
    static void display_current_date();
    static void display_days_of_month();
    static void add_note();
    static void display_note();
    static void delete_note();
    static void fetch_by_coordinates();
    static void convert_to_friendly_date();
};


#endif //CALENDAR_APP_CPP_OPTIONHANDLER_H
