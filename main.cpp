#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>
#include "models/option_list/OptionList.h"

int main() {
    cURLpp::initialize(CURL_GLOBAL_SSL);

    OptionList list;
    list.list_options();

    cURLpp::terminate();
    return 0;
}
