/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// curlsmtp2 C++ program file

// TODO:
// return value of send_mail

#include "curlsmtp2.h"

// consttant
const std::string CONTENT_TYPE_TEXT_UTF8_FLOWED( "Content-Type: text/plain; charset=utf-8; format=flowed" );

const std::string CONTENT_TYPE_TEXT_USASCII_FLOWED(
"Content-Type: text/plain; charset=us-ascii;  format=flowed" );

const std::string CONTENT_TRANSFER_7BIT( "Content-Transfer-Encoding: 7bit" );
const std::string CONTENT_TRANSFER_BASE64( "Content-Transfer-Encoding: base64" );


const char CONTENT_TYPE_MULTITYPE_BOUNDARY_FORMAT[] =
"Content-Type: multipart/mixed; boundary=\"%s";

const char CONTENT_DISPOSITION_FORMAT[] = "Content-Disposition: attachment; filename=%s; size=%d;";

const char CONTENT_TYPE_CHARSET_FORMAT[] = "Content-Type: text/plain; charset=%s";

const char SUBJECT_FORMAT[] = 
"Subject: %s";

const char SUBJECT_CHARSET_FORMAT[] = 
"Subject: =?%s?B?%s?="; 



/**
 * constractor
 */
CurlSmtp2::CurlSmtp2(void)
{

	m_xoauth = false;
    m_ssl_verify = false;
   m_verbose = false;
   m_make_send_message_once = false;
    m_subject_b64 = "";
    m_subject_charset = "";
    m_msg_b64 = "";
    m_msg_charset = "";
}


/**
 * destractor
 */
CurlSmtp2::~CurlSmtp2(void)
{
	//nop
}


void CurlSmtp2::set_user(const std::string& user)
{
	m_user.assign(user);
}


/**
 * set_str_to
 */
void CurlSmtp2::set_str_to(const std::string & str_to)
{

	const std::vector<std::string> vec_to =
	{
		str_to
	};

	set_to(vec_to);

}


/**
 * set_str_attach
 */
void CurlSmtp2::set_str_attach(std::string &str_attach)
{

	const std::vector<std::string> vec_attach =
	{
		str_attach
	};

	set_attach(vec_attach);

}

/**
* set_url
 */
void CurlSmtp2::set_url(const std::string& url)
{
	m_url.assign(url);
}



/**
* set_server_port
 */
 void CurlSmtp2::set_server_port(const std::string& server, int port)
{

    const std::string scheme("smtp://");
    const std::string colon(":"); 

    std::string url =  scheme + server+ colon + std::to_string(port);

	m_url.assign(url);
}


/**
*  set_user_agent
 */
void CurlSmtp2::set_user_agent(const std::string user_agent)
{
	m_user_agent.assign(user_agent);
}


/**
* set_subject_charset
 */
void CurlSmtp2::set_subject_charset( const std::string subject, const std::string charset )
{

    std::string b64;
    base64encode( subject, b64 );

    m_subject_b64.assign( b64 );
    m_subject_charset.assign( charset );

}


/**
* set_message_charset
 */
 void CurlSmtp2::set_message_charset( const std::string msg, const std::string charset )
{
    std::string b64;
    base64encode( msg, b64 );

    m_msg_b64.assign( b64 );
    m_msg_charset.assign( charset );
}


/**
* set_token
 */
 void  CurlSmtp2::set_token( const std::string token )
{
    m_xoauth = true;
    m_token.assign( token );
}


/**
* set_verbose
 */
void CurlSmtp2::set_verbose(bool verbose)
{ 
    m_verbose = verbose;
}


/**
* set_ssl_verify
 */
void CurlSmtp2::set_ssl_verify(bool verify)
{ 
    m_ssl_verify = verify;
}


/**
* base64encode
 */
 size_t CurlSmtp2::base64encode( const std::string str_data, std::string &ret_b64 )
{
    const char *chars_data = (char *)str_data.c_str();
    const int len = str_data.length();
    std::vector<char> vec_b64;  
    size_t size = ustd::string::base64encode( chars_data, len, vec_b64);



    size_t vec_size = vec_b64.size();
    std::string b64;
    b64.resize(vec_size);

    for(int i=0; i<vec_size; i++){
        b64[i] = (char)vec_b64[i];;
    }

    ret_b64 = b64;

    return size;
}


/**
 * make_send_message
 */
void CurlSmtp2::make_send_message(void)
{

    if( m_make_send_message_once ){
		return;
	}
	m_make_send_message_once = true;


    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

	send_buffer_.clear();

	// time
	time_t t;
	time(&t);
	char timestring[128] = {0};
	char * timeformat = (char *)"Date: %d %b %y %H:%M:%S %Z";
	if (strftime(timestring, 127, timeformat, localtime(&t)))
	{ // got the date
		send_buffer_.push_back(timestring);
	}

	// from
	send_buffer_.push_back("From: " LEFT_BRACE + from_ + RIGTH_BRACE);

	// to
	for (int i = 0; i < to_.size(); ++i)
	{
		send_buffer_.push_back("To: " LEFT_BRACE + to_[i] + RIGTH_BRACE);
	}
	// cc
	for (int i = 0; i < cc_.size(); ++i)
	{
		send_buffer_.push_back("Cc: " LEFT_BRACE + cc_[i] + RIGTH_BRACE);
	}

	// user agent
    if( !m_user_agent.empty() ){
        snprintf(buf, BUFSIZE, "User-Agent: %s",  
        (char *)m_user_agent.c_str() );
        send_buffer_.push_back( buf );
    }

	// subject
    if( !m_subject_b64.empty() &&  
    !m_subject_charset.empty() ) {
            snprintf(buf, BUFSIZE,
            SUBJECT_CHARSET_FORMAT,
            (char *)m_subject_charset.c_str(), 
            (char *)m_subject_b64.c_str() );
    } else {
            snprintf(buf, BUFSIZE,
            SUBJECT_FORMAT,
            (char *)subject_.c_str() );
    }

	send_buffer_.push_back( buf );


	if (attach_.empty())
	{
        if( !m_msg_b64.empty() && !m_msg_charset.empty() )
        {
          // header
                snprintf(buf, BUFSIZE,  
                CONTENT_TYPE_CHARSET_FORMAT,
                (char *)m_msg_charset.c_str() ); 

                send_buffer_.push_back( buf );

                send_buffer_.push_back( CONTENT_TRANSFER_BASE64 );

// split body
		    send_buffer_.push_back(ENTER);

               // message
	            send_buffer_.push_back( m_msg_b64 );

        } else {

	// split body
		    send_buffer_.push_back(ENTER);

		// message
		send_buffer_.push_back(message_ + ENTER);
	
        } // if m_msg_b64

	}
	else
	{

		send_buffer_.push_back(MIME_VER);
		send_buffer_.push_back(HEADER_CONTENT_TYPE);

		std::string boundary(get_boundary());
		// set boundary
		send_buffer_.push_back(" boundary=\"" + boundary + "\"" ENTER);

		// first part of body, boundary header and message
		send_buffer_.push_back(BOUNDARY_FLAG + boundary);


        if( !m_msg_b64.empty() && !m_msg_charset.empty() )
        {
          // header
                snprintf(buf, BUFSIZE,  
                CONTENT_TYPE_CHARSET_FORMAT,
                (char *)m_msg_charset.c_str() ); 

                send_buffer_.push_back( buf );

                send_buffer_.push_back( CONTENT_TRANSFER_BASE64 );

// split body
		    send_buffer_.push_back(ENTER);

               // message
	            send_buffer_.push_back( m_msg_b64 );

        } else {

		send_buffer_.push_back(MSG_CONTENT_TYPE);
		send_buffer_.push_back(MSG_ENCODING);

		// split body
		send_buffer_.push_back(ENTER);

// message
		send_buffer_.push_back(message_ + ENTER);

} // if m_msg_b64

		send_buffer_.push_back(BOUNDARY_FLAG + boundary);

		// attachment
		for (int i = 0; i < attach_.size(); ++i)
		{
			attach(attach_[i]);
		}
		for (std::vector<std::pair<std::vector<char>, std::string>>::iterator it1 = attachment_.begin();
			it1 != attachment_.end(); ++it1)
		{
			if (it1->second.length() > 3)
			{ // long enough for an extension
				std::string typ(it1->second.substr(it1->second.length() - 4, 4));
				
				if (typeMap_.count(typ) > 0)
				{
					send_buffer_.push_back(typeMap_[typ]);
				}
				else
				{ // add other types
					// everything else
					send_buffer_.push_back("Content-Type: application/X-other-1;");
				}
			}
			else
			{
				// default to don't know
				send_buffer_.push_back("Content-Type: application/X-other-1;");
			}

			send_buffer_.push_back(" name=\"" + it1->second + "\"");
			send_buffer_.push_back("Content-Transfer-Encoding: base64");
			send_buffer_.push_back("Content-Disposition: attachment; filename=\"" + it1->second + "\"");

			// split body
			send_buffer_.push_back(ENTER);

			send_buffer_.push_back(std::string(it1->first.begin(), it1->first.end()));
			// terminate the message with the boundary + "--"
			if ((it1 + 1) == attachment_.end())
				send_buffer_.push_back(BOUNDARY_FLAG + boundary + BOUNDARY_FLAG);
			else
				send_buffer_.push_back(BOUNDARY_FLAG + boundary);
		}
	}

	// add \r\n to each item
	for (int i = 0; i < send_buffer_.size(); ++i)
	{
		send_buffer_[i] += ENTER;
	}

}


/**
* get_send_buffer
 */
std::string CurlSmtp2::get_send_buffer(void)
{

	make_send_message();
  
    std::string msg;
	for( auto buf: send_buffer_ ){ 
        msg += buf;
    }

    return msg;
}


/**
 * set_curl_option
 */
void CurlSmtp2::set_curl_option(void)
{
	pooh_.pos = 0;
	pooh_.counter = 0;
	pooh_.data.resize(send_buffer_.size() + 1);
	pooh_.data.insert(pooh_.data.begin(), send_buffer_.begin(), send_buffer_.end());

// url
	curl_easy_setopt (curl_, CURLOPT_URL, (char *)m_url.c_str() );

// user
	curl_easy_setopt(curl_, CURLOPT_USERNAME, (char *)m_user.c_str());

// token
    if(m_xoauth && !m_token.empty() ) {
        curl_easy_setopt(curl_, CURLOPT_XOAUTH2_BEARER, (char *)m_token.c_str() );
    } else if ( !password_.empty() ){
// password
	    curl_easy_setopt(curl_, CURLOPT_PASSWORD, 
        (char *)password_.c_str());
    }

	curl_easy_setopt(curl_, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl_, CURLOPT_MAIL_FROM, std::string(LEFT_BRACE + from_ + RIGTH_BRACE).c_str());
	curl_easy_setopt(curl_, CURLOPT_MAIL_RCPT, rcpt_list_);
	curl_easy_setopt(curl_, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    if(m_ssl_verify){
	    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 1L);
	    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 1L);
    } else {
	    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
	    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
    }

	curl_easy_setopt(curl_, CURLOPT_READDATA, &pooh_);

    if (m_verbose){
		curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);
	}

	curl_easy_setopt(curl_, CURLOPT_SSLVERSION, 0L);
	curl_easy_setopt(curl_, CURLOPT_SSL_SESSIONID_CACHE, 0L);
	curl_easy_setopt(curl_, CURLOPT_UPLOAD, 1L);
}
