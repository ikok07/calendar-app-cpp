//
// Created by Kaloyan Petkov on 29.07.24.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include "OptionHandler.h"
#include "../utils/Utils.h"
#include "../note/Note.h"

using namespace std;

void OptionHandler::display_current_date() {
    time_t timestamp = time(nullptr);
    struct tm *local_time = localtime(&timestamp);
    cout << "\n----------- Current date -----------" << endl;
    printf("%02d.%02d.%d, %02d:%02d:%02d\n", local_time->tm_mday, local_time->tm_mon, local_time->tm_year + 1900, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    cout << "\n";
}

void OptionHandler::display_days_of_month() {
    time_t timestamp = time(nullptr);
    struct tm *local_time = localtime(&timestamp);
    int days_in_month = Utils::days_in_month(local_time->tm_mon + 1, local_time->tm_year + 1900);
    for (int i = 0; i < days_in_month; i++) {
        printf("----------- %s %02d %d -----------\n", Utils::month_name(local_time->tm_mon + 1).c_str(), i + 1, local_time->tm_year + 1900);
    }
}

void OptionHandler::add_note() {
    fstream file{"notes.bin", ios::binary | ios::in | ios::app};
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter note's text: " << endl;
    string text;
    getline(cin, text);

    cout << "Enter note's date ('dd/mm/yyyy' or '0' for today): " << endl;
    string date_str;
    cin >> date_str;
    time_t note_date = time(nullptr);
    if (date_str != "0") {
        auto [m_day, month, year] = Utils::parse_date_str(date_str);
        struct tm *note_time = localtime(&note_date);
        note_time->tm_mday = m_day;
        note_time->tm_mon = month - 1;
        note_time->tm_year = year - 1900;
        note_date = mktime(note_time);
    }

    Note note{text, note_date};
    size_t text_size = note.get_text().size();

    file.write(reinterpret_cast<const char*>(&text_size), sizeof text_size);
    file.write(note.get_text().c_str(), (long)text_size);
    file.write(reinterpret_cast<const char*>(&note_date), sizeof(note_date));
    file.close();
    cout << "Note successfully added!\n" << endl;
}

void OptionHandler::display_note() {
    fstream file("notes.bin", ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string date_str;
    cout << "Enter note's date ('dd/mm/yyyy' or '0' for today): " << endl;
    cin >> date_str;
    time_t target_date = time(nullptr);
    struct tm target_time = *localtime(&target_date);
    if (date_str != "0") {
        auto [m_day, month, year] = Utils::parse_date_str(date_str);
        target_time.tm_mday = m_day;
        target_time.tm_mon = month - 1;
        target_time.tm_year = year - 1900;
        target_date = mktime(&target_time);
    }

    int curr_note = 0;
    while (true) {
        size_t text_size;
        if (!file.read(reinterpret_cast<char *>(&text_size), sizeof(text_size))) break;

        string text;
        text.resize(text_size);
        if (!file.read(&text[0], (long)text_size)) break;

        time_t date;
        if (!file.read(reinterpret_cast<char *>(&date), sizeof(date))) break;

        struct tm *note_time = localtime(&date);
        bool target_note = !text.empty() &&
                note_time->tm_year == target_time.tm_year &&
                note_time->tm_mon == target_time.tm_mon &&
                note_time->tm_mday == target_time.tm_mday;
        if (target_note) {
            curr_note++;
            cout << "------------------" << endl;
            cout << "Note #" << curr_note << ":\n" << endl;
            cout << text << endl;
            cout << "------------------" << endl;
        }
    }

    if (curr_note == 0) cout << "No note found for the selected date!" << endl;
    file.close();
}
