//
// Created by Kaloyan Petkov on 29.07.24.
//

#include "Note.h"

Note::Note(const string& text) {set_text(text);}

Note::Note(const string &text, const time_t &date) {
    set_text(text);
    set_date(date);
}

void Note::set_text(const string& text) {
    if (text.empty()) throw invalid_argument("note's text");
    this->text = text;
}

void Note::set_date(const time_t& date) {
    if (date <= 0) throw invalid_argument("note's date");
    this->date = date;
}

string Note::get_text() const {
    return this->text;
}

time_t Note::get_date() const {
    return this->date;
}

