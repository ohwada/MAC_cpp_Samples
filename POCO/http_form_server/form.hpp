#pragma once
/**
 *  form.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/pocoproject/poco/blob/devel/Net/samples/HTTPFormServer/src/HTTPFormServer.cpp

#include <sstream>
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"

using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::StreamCopier;

// prototype
std::string get_string_form(HTTPServerRequest& request);
std::string form_to_string(HTMLForm* form);
std::string get_post_data(HTTPServerRequest& request);


/**
 *  get_string_form
 */
std::string get_string_form(HTTPServerRequest& request)
{
	HTMLForm* form = new HTMLForm(request, request.stream());

    return form_to_string(form);
}


/**
 *  form_to_string
 */
std::string form_to_string(HTMLForm* form)
{
    std::ostringstream oss;

	if (!form->empty()) {
			NameValueCollection::ConstIterator it = form->begin();
			NameValueCollection::ConstIterator end = form->end();
			for (; it != end; ++it){
				oss << it->first << ": " << it->second << "<br/>\n";
			} // for
	} // if

    return oss.str();
}


/**
 *  get_post_data
 */
std::string get_post_data(HTTPServerRequest& request)
{
    std::string recv_string;
    Poco::StreamCopier::copyToString(request.stream(), recv_string);

    return recv_string;
}


