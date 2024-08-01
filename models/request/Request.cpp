//
// Created by Kaloyan Petkov on 31.07.24.
//

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>
#include "Request.h"
#include <sstream>

Request::Request(const char *url, roptions_t *options) {
    this->url = url;
    req_handle.setOpt(cURLpp::Options::Url(url));
    if (!options) return;
    if (!options->queries.empty()) build_query_url(options->queries);
    if (!options->headers.empty()) add_headers(options->headers);
}

void Request::build_query_url(vector<rquery_t> queries) {
    for (int i = 0; i < queries.size(); i++) {
        queries[i].key = cURLpp::escape(queries[i].key);
        queries[i].value = cURLpp::escape(queries[i].value);
        string start_symbol = i == 0 ? "?" : "&";
        this->url.append(start_symbol);
        this->url.append(queries[i].key);
        this->url.append("=");
        this->url.append(queries[i].value);
    }
}

void Request::add_headers(vector<rheader_t> headers) {
    std::list<std::string> headers_list;
    for (const rheader_t& header: headers) {
        headers_list.push_back(header.key + ": " + header.value);
    }
    req_handle.setOpt(cURLpp::Options::HttpHeader(headers_list));
}
