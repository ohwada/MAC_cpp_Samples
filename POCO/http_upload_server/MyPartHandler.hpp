#pragma once
/**
 *  MyPartHandler.hpp
 * 2022-06-01 K.OHWADA
 */

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



/**
 *  MyPartHandler
 */
class MyPartHandler: public Poco::Net::PartHandler
{
public:
	MyPartHandler():
		m_length(0)
	{
	}

	void handlePart(const MessageHeader& header, std::istream& stream)
	{
		m_type = header.get("Content-Type", "(unspecified)");
		if (header.has("Content-Disposition"))
		{
			std::string disp;
			NameValueCollection params;
			MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
			 m_name = params.get("name", "(unnamed)");
			m_fileName = params.get("filename", "(unnamed)");
		}

		CountingInputStream istr(stream);

		//NullOutputStream ostr;
		//StreamCopier::copyStream(istr, ostr);

    	std::ostringstream oss;
		StreamCopier::copyStream(istr, oss);

		m_data = oss.str();
		m_length = istr.chars();
	}

	int length() const
	{
		return m_length;
	}

	const std::string& name() const
	{
		return m_name;
	}

	const std::string& fileName() const
	{
		return m_fileName;
	}

	const std::string& contentType() const
	{
		return m_type;
	}

	const std::string& data() const
	{
		return m_data;
	}

private:
	int m_length;
	std::string m_type;
	std::string m_name;
	std::string m_fileName;
	std::string m_data;
};


