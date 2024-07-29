//
// Created by Kaloyan Petkov on 29.07.24.
//

#ifndef CALENDAR_APP_CPP_NOTE_H
#define CALENDAR_APP_CPP_NOTE_H
#include <string>
#include <ctime>
using namespace std;

class Note {
public:
    explicit Note(const string& text);
    Note(const string& text, const time_t& date);
    void set_text(const string& text);
    void set_date(const time_t& date);
    string get_text() const;
    time_t get_date() const;
private:
    string text;
    time_t date = time(nullptr);
};


#endif //CALENDAR_APP_CPP_NOTE_H
