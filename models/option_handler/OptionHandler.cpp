//
// Created by Kaloyan Petkov on 29.07.24.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

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
    fstream file{"notes.bin", ios::binary | ios::out | ios::app};
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

        bool target_note = !text.empty() && Utils::timestamp_same_day(target_date, date) == 0;
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

void OptionHandler::delete_note() {
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

    vector<Note> notes_for_date;
    while (true) {
        size_t text_length;
        if (!file.read(reinterpret_cast<char*>(&text_length), sizeof(text_length))) break;

        string text;
        text.resize(text_length);
        if (!file.read(&text[0], (long)text_length)) break;

        time_t date;
        if (!file.read(reinterpret_cast<char*>(&date), sizeof(date))) break;


        notes_for_date.emplace_back(text,date);
    }
    file.close();

    if (notes_for_date.empty()) {
        cout << "No note found for the selected date!" << endl;
        return;
    }

    int delete_all = -1;
    bool target_found = false;
    int delete_count = 0;
    auto iterator = remove_if(
            notes_for_date.begin(),
            notes_for_date.end(),
            [&](const Note& note) {
                bool exists = target_found && find_if(notes_for_date.begin(), notes_for_date.end(), [&](const Note& n) {
                    return Utils::timestamp_same_day(note.get_date(), n.get_date()) == 0;
                }) != notes_for_date.end();

                if (delete_all == -1 && exists) {
                    char input;
                    while (true) {
                        cout << "Multiple notes found! Do you want to delete all of them? (y/n)" << endl;
                        cin >> input;
                        if (input == 'y') {
                            delete_all = 1;
                            break;
                        } else if (input == 'n') {
                            delete_all = 0;
                            break;
                        }
                    }
                }

                if (Utils::timestamp_same_day(target_date, note.get_date()) == 0) {
                    if (exists) {
                        if (delete_all == 1) delete_count++;
                        return delete_all == 1;
                    }
                    else {
                        delete_count++;
                        target_found = true;
                        return true;
                    }
                }
                return false;
            }
    );

    if (iterator == notes_for_date.end()) {
        cout << "No note found for the selected date!" << endl;
        return;
    }

    notes_for_date.erase(iterator, notes_for_date.end());

    fstream out_file("notes.bin", ios::binary | ios::out | ios::trunc);
    if (!out_file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    for (const Note& note: notes_for_date) {
        size_t text_size = note.get_text().size();
        time_t note_date = note.get_date();
        if (!delete_all && Utils::timestamp_same_day(target_date, note_date) != 0) continue;

        out_file.write(reinterpret_cast<const char*>(&text_size), sizeof text_size);
        out_file.write(note.get_text().c_str(), (long)text_size);
        out_file.write(reinterpret_cast<const char*>(&note_date), sizeof(note_date));
    }

    out_file.close();
    string notes = delete_count > 1 ? " notes!" : " note!";
    cout << "Successfully deleted " << delete_count << notes << endl;
}
