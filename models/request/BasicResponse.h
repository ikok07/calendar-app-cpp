//
// Created by Kaloyan Petkov on 31.07.24.
//

#ifndef CALENDAR_APP_CPP_BASICRESPONSE_H
#define CALENDAR_APP_CPP_BASICRESPONSE_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

struct rerror_t {
    string message;
    string identifier;
};

class BasicResponse {
public:
    bool failed();
    string& get_message();
    string& get_identifier();
private:
    string status;
    string message;
    string identifier;
    friend void to_json(json& j, const BasicResponse& p) {
        j = json{{"status", p.status}, {"message", p.message}, {"identifier", p.identifier}};
    }

    friend void from_json(const json& j, BasicResponse& p) {
        if (j.contains("status")) j.at("status").get_to(p.status);
        if (j.contains("identifier")) j.at("message").get_to(p.message);
        if (j.contains("identifier")) j.at("identifier").get_to(p.identifier);
    }
};


#endif //CALENDAR_APP_CPP_BASICRESPONSE_H
