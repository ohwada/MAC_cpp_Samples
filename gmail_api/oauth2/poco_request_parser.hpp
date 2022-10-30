#pragma once
/**
 *  poco_request_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"

// prototype
bool parse_request(Poco::Net::HTTPServerRequest& request, std::string &code, std::string &scope);


/**
 *  parse_request
 */
bool parse_request(Poco::Net::HTTPServerRequest& request, std::string &code, std::string &scope)
{

    Poco::Net::HTMLForm* form = new Poco::Net::HTMLForm(request, request.stream());

    bool is_form = false;

    if (!form->empty()) {
        code = form->get("code", "");
        scope = form->get("scope", "");
        is_form = true;
    }

    return is_form;
}
