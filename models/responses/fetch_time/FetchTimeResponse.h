//
// Created by Kaloyan Petkov on 1.08.24.
//

#ifndef CALENDAR_APP_CPP_FETCHTIMERESPONSE_H
#define CALENDAR_APP_CPP_FETCHTIMERESPONSE_H

#include <iostream>
#include "../../request/BasicResponse.h"
using namespace std;

struct rdate_t {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int seconds;
    string timeZone;
};

class FetchTimeResponse : public BasicResponse {
public:
    rdate_t data();
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int seconds;
    string timeZone;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FetchTimeResponse, year, month, day, hour, minute, seconds, timeZone);
};


#endif //CALENDAR_APP_CPP_FETCHTIMERESPONSE_H
