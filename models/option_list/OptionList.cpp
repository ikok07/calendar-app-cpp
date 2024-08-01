//
// Created by Kaloyan Petkov on 29.07.24.
//

#include "OptionList.h"
#include "../option_handler/OptionHandler.h"

string OptionList::parse_option(Option opt) {
    switch (opt) {
        case Option::CURR_DAY:
            return "Display current day";
        case Option::DAYS_IN_MONTH:
            return "Display all the days of the current month";
        case Option::ADD_NOTE:
            return "Add note";
        case Option::DISP_NOTE:
            return "Display note";
        case Option::DEL_NOTE:
            return "Delete note";
        case Option::FETCH_COORD:
            return "Fetch live date for coordinates";
        case Option::FRIENDLY_DATE:
            return "Convert a date time into a friendly string";
        default:
            return "Invalid option!";
    }
}

void OptionList::sel_option(int opt) {
    switch (static_cast<Option>(opt)) {
        case Option::CURR_DAY:
            OptionHandler::display_current_date();
            break;
        case Option::DAYS_IN_MONTH:
            OptionHandler::display_days_of_month();
            break;
        case Option::ADD_NOTE:
            OptionHandler::add_note();
            break;
        case Option::DISP_NOTE:
            OptionHandler::display_note();
            break;
        case Option::DEL_NOTE:
            OptionHandler::delete_note();
            break;
        case Option::FETCH_COORD:
            OptionHandler::fetch_by_coordinates();
            break;
        case Option::FRIENDLY_DATE:
            OptionHandler::convert_to_friendly_date();
            break;
        case Option::NONE:
            exit(1);
        default:
            throw invalid_argument("Invalid option selected!");
    }
}

void OptionList::list_options() {
    int option;
    while (true) {
        try {
            cout << "Select one of the options: " << endl << endl;
            for (int i = 0; i < options.size(); i++) {
                cout << i + 1 << ". " << parse_option(options[i]) << endl;
            }
            cout << "-1. Exit" << endl;
            cin >> option;
            sel_option(option);
        } catch (const exception& ex) {
            cerr << ex.what() << endl;
        }
    }
}
