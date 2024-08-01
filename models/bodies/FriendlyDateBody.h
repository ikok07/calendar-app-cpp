//
// Created by Kaloyan Petkov on 1.08.24.
//

#ifndef CALENDAR_APP_CPP_FRIENDLYDATEBODY_H
#define CALENDAR_APP_CPP_FRIENDLYDATEBODY_H

#include <string>
using namespace std;

struct FriendlyDateBody {
    string dateTime;
    string languageCode;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FriendlyDateBody, dateTime, languageCode);
};

#endif //CALENDAR_APP_CPP_FRIENDLYDATEBODY_H
