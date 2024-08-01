//
// Created by Kaloyan Petkov on 31.07.24.
//

#include "BasicResponse.h"

bool BasicResponse::failed() {
    return status == "fail" || !message.empty() || !identifier.empty();
}

string& BasicResponse::get_message() {
    return message;
}

string& BasicResponse::get_identifier() {
    return identifier;
}