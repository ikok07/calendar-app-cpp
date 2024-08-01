//
// Created by Kaloyan Petkov on 31.07.24.
//

#ifndef CALENDAR_APP_CPP_REQUEST_H
#define CALENDAR_APP_CPP_REQUEST_H

#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

struct rquery_t {
    string key;
    string value;
};

struct rheader_t {
    string key;
    string value;
};

struct roptions_t {
    vector<rquery_t> queries = {};
    vector<rheader_t> headers = {};
};

class Request {
public:
    explicit Request(const char *url, roptions_t *options = nullptr);

    template<typename T>
    T get();

    template<typename R, typename B>
    R post(B& body);
private:
    cURLpp::Easy req_handle;
    string url;
    string response_str;

    void build_query_url(vector<rquery_t> queries);
    void add_headers(vector<rheader_t> headers);

    template<typename T>
    string format_body(T& body);
};

template<typename T>
string Request::format_body(T& body) {
    json json_obj = body;
    return json_obj.dump(0);
}

template<typename R>
R Request::get() {
    ostringstream response_stream;
    req_handle.setOpt(cURLpp::Options::WriteStream(&response_stream));
    req_handle.perform();
    response_str = response_stream.str();
    return json::parse(response_str).get<R>();
}

template<typename R, typename B>
R Request::post(B& body) {
    string body_str = format_body(body);
    istringstream request_stream;
    req_handle.setOpt(cURLpp::Options::ReadStream(&request_stream));
    req_handle.setOpt(cURLpp::Options::PostFields(body_str));
    req_handle.setOpt(cURLpp::Options::PostFieldSize((long)body_str.size()));

    ostringstream response_stream;
    req_handle.setOpt(cURLpp::Options::WriteStream(&response_stream));
    req_handle.perform();
    response_str = response_stream.str();
    return json::parse(response_str).get<R>();
}

#endif //CALENDAR_APP_CPP_REQUEST_H
