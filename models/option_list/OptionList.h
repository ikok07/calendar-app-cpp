//
// Created by Kaloyan Petkov on 29.07.24.
//

#ifndef CALENDAR_APP_CPP_OPTIONLIST_H
#define CALENDAR_APP_CPP_OPTIONLIST_H

#include <iostream>
#include <vector>
using namespace std;

enum class Option {
    CURR_DAY = 1, DAYS_IN_MONTH, ADD_NOTE, DISP_NOTE, DEL_NOTE, FETCH_COORD, FRIENDLY_DATE, NONE = -1
};

class OptionList {
public:
    OptionList() = default;
    void list_options();
private:
    static string parse_option(Option opt);
    static void sel_option(int opt);

    vector<Option> options{
        Option::CURR_DAY,
        Option::DAYS_IN_MONTH,
        Option::ADD_NOTE,
        Option::DISP_NOTE,
        Option::DEL_NOTE,
        Option::FETCH_COORD,
        Option::FRIENDLY_DATE,
    };
};


#endif //CALENDAR_APP_CPP_OPTIONLIST_H
