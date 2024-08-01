//
// Created by Kaloyan Petkov on 1.08.24.
//

#ifndef CALENDAR_APP_CPP_FRIENDLYDATERESPONSE_H
#define CALENDAR_APP_CPP_FRIENDLYDATERESPONSE_H

#include <nlohmann/json.hpp>
#include <string>

#include "../../request/BasicResponse.h"

using namespace std;

struct fdate_t {
    string friendlyDateTime;
};

class FriendlyDateResponse : public BasicResponse {
public:
    fdate_t data();
private:
    string friendlyDateTime;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FriendlyDateResponse, friendlyDateTime);
};


#endif //CALENDAR_APP_CPP_FRIENDLYDATERESPONSE_H
