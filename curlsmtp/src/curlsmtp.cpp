/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */


// C++ wraper for libcurl smtp
// suport file atachment
// suport UTF-8 encoding
// support xoauth

// original : https://github.com/honeyligo/curlsmtp/blob/master/curlsmtp.cpp

#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include "curlsmtp.h"
#include "ustd_string.h"


// constant
const std::string LEFT_BRACE("<");
const std::string RIGTH_BRACE(">");

const std::string LF( "\n" );
const std::string CRLF( "\r\n");
const std::string BOUNDARY_FLAG	( "--" );

const std::string MIME_VER( "Mime-Version: 1.0" );
const std::string CONTENT_TYPE_MULTITYPE_MIXED( "Content-Type: multipart/mixed;" );

const std::string CONTENT_TYPE_TEXT_UTF8_FLOWED( "Content-Type: text/plain; charset=utf-8; format=flowed" );

const std::string CONTENT_TYPE_TEXT_USASCII_FLOWED(
"Content-Type: text/plain; charset=us-ascii;  format=flowed" );

const std::string CONTENT_TRANSFER_7BIT( "Content-Transfer-Encoding: 7bit" );
const std::string CONTENT_TRANSFER_BASE64( "Content-Transfer-Encoding: base64" );


const char CONTENT_TYPE_MULTITYPE_BOUNDARY_FORMAT[] =
"Content-Type: multipart/mixed; boundary=\"%s";

const char CONTENT_DISPOSITION_FORMAT[] = "Content-Disposition: attachment; filename=%s; size=%d;";

const char CONTENT_TYPE_CHARSET_FORMAT[] = "Content-Type: text/plain; charset=%s";

const char SUBJECT_CHARSET_FORMAT[] = 
"Subject: =?%s?B?%s?="; 


const int CHUNCK_SIZE = 1024 * 10;



/**
 * read_callback
 */
size_t CurlSmtp::read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct ReadData *pooh = (struct ReadData *)userp;
  const char *data;

  if(size * nmemb < 1)
    return 0;

  const std::string& str = pooh->data[pooh->counter];

  if(pooh->counter < pooh->data.size()) 
  {
	size_t len = str.size();
	int size = len - pooh->pos;
	if (len < CHUNCK_SIZE || size <= CHUNCK_SIZE)
	{
		memcpy(ptr, str.c_str() + pooh->pos, size);
		pooh->counter++; /* advance pointer */
		pooh->pos = 0;
		return size;
	}
	else
	{
		memcpy(ptr, str.c_str() + pooh->pos, CHUNCK_SIZE);
		pooh->pos += CHUNCK_SIZE;
		return CHUNCK_SIZE;
	}
	
  }
  return 0;
}


/**
* constractor
 */
CurlSmtp::CurlSmtp(void)
{
    initCurlSmtp();
}


/**
* constractor
 */
CurlSmtp::CurlSmtp(
	const std::string& url )
{
	set_url(url);
    initCurlSmtp();
}


/**
* initCurlSmtp
 */
void CurlSmtp::initCurlSmtp(void)
{

	curl_global_init(CURL_GLOBAL_DEFAULT);

	m_curl = curl_easy_init();

	m_rcpt_list = NULL;
    m_xoauth = false;
	m_make_send_message_once = false;
    m_verbose = false;
    m_ssl_verify = 1L;

	m_type_map_list.insert(std::make_pair(".gif", "Content-Type: image/gif;"));
	m_type_map_list.insert(std::make_pair(".jpg", "Content-Type: image/jpg;"));
	m_type_map_list.insert(std::make_pair(".jpeg", "Content-Type: image/jpeg;"));
	m_type_map_list.insert(std::make_pair(".png", "Content-Type: image/png;"));
	m_type_map_list.insert(std::make_pair(".bmp", "Content-Type: image/bmp;"));
	m_type_map_list.insert(std::make_pair(".txt", "Content-Type: plain/txt;"));
	m_type_map_list.insert(std::make_pair(".log", "Content-Type: plain/txt;"));
	m_type_map_list.insert(std::make_pair(".htm", "Content-Type: plain/htm;"));
	m_type_map_list.insert(std::make_pair(".html", "Content-Type: plain/htm;"));
	m_type_map_list.insert(std::make_pair(".exe", "Content-Type: application/X-exectype-1;"));
}


/**
* destractor
 */
CurlSmtp::~CurlSmtp(void)
{
	curl_global_cleanup();
	curl_easy_cleanup(m_curl);
}


/**
* set_user
 */
void CurlSmtp::set_user(const std::string& user)
{
	m_user.assign(user);
}


/**
* set_password
 */
void CurlSmtp::set_password(const std::string& password)
{
	m_password.assign(password);
}


/**
* set_from
 */
void CurlSmtp::set_from(const std::string & from)
{
	m_from.assign(from);
}


/**
* set_to
 */
void CurlSmtp::set_to(const std::string & to)
{
    m_to_list.clear();
    m_to_list.push_back(to);
}


/**
* set_to_list
 */
void CurlSmtp::set_to_list(const std::vector<std::string>& to)
{
	m_to_list.resize(to.size());
	m_to_list.assign(to.begin(), to.end());
}


/**
* set_cc_list
 */
void CurlSmtp::set_cc_list(const std::vector<std::string>& cc)
{
	m_cc_list.resize(cc.size());
	m_cc_list.assign(cc.begin(), cc.end());
}


/**
* set_attach_list
 */
void CurlSmtp::set_attach_list(const std::vector<std::string>& attach)
{
	m_attach_list.resize(attach.size());
	m_attach_list.assign(attach.begin(), attach.end());
}


/**
* set_attach
 */
void CurlSmtp::set_attach(const std::string & attach)
{
	m_attach_list.clear();
	m_attach_list.push_back(attach);
}


/**
* set_subject
 */
void CurlSmtp::set_subject(const std::string& subject)
{
	m_subject.assign(subject);
}


/**
* set_message
 */
void CurlSmtp::set_message(const std::string& message)
{
	m_msg.assign(message);
}


/**
* set_url
 */
void CurlSmtp::set_url(const std::string& url)
{
	m_url.assign(url);
}


/**
* set_server_port
 */
 void CurlSmtp::set_server_port(const std::string& server, const std::string& port)
{
    set_url_server_port(server, port);
}


/**
* set_server_port
 */
 void CurlSmtp::set_server_port(const std::string& server, const int port)
{
    set_url_server_port(server, std::to_string( port ) );
}


/**
* set_url_server_port
 */
 void CurlSmtp::set_url_server_port(const std::string& server, const std::string& port)
{
	const std::string protocol("smtp://");
	std::string url = protocol + server + ":" + port;
	m_url.assign(url);
}


/**
*  set_user_agent
 */
void CurlSmtp::set_user_agent(const std::string user_agent)
{
	m_user_agent.assign(user_agent);
}

/**
* set_subject_charset
 */
void CurlSmtp::set_subject_charset( const std::string subject, const std::string charset )
{

    std::string b64;
    base64encode( subject, b64 );

    m_subject_b64.assign( b64 );
    m_subject_charset.assign( charset );

}


/**
* set_message_charset
 */
 void CurlSmtp::set_message_charset( const std::string msg, const std::string charset )
{
    std::string b64;
    base64encode( msg, b64 );

    m_msg_b64.assign( b64 );
    m_msg_charset.assign( charset );
}

 void  CurlSmtp::set_token( const std::string token )
{
    m_xoauth = true;
    m_token.assign( token );
}


/**
* base64encode
 */
 size_t CurlSmtp::base64encode( const std::string str_data, std::string &ret_b64 )
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
* set_verbose
 */
void CurlSmtp::set_verbose(bool verbose)
{ 
    m_verbose = verbose;
}


/**
* set_ssl_verify
 */
void CurlSmtp::set_ssl_verify(bool verify)
{ 
    m_ssl_verify = verify?1L:0L;
}


/**
* get_send_buffer
 */
std::string CurlSmtp::get_send_buffer(void)
{

    if( !m_make_send_message_once ){
        m_make_send_message_once = true;
	    make_send_message();
    }

    std::string msg;
	for( auto buf: m_send_buffer_list ){ 
        msg += buf;
    }

    return msg;
}


/**
* get_error
 */
std::string CurlSmtp::get_error(void)
{

    std::string error;
    for(auto err: m_error_list){
        error += err + LF;
    }

    return error;
}


/**
* send_mail
 */
bool CurlSmtp::send_mail(void)
{

    set_receiver_list();

    if( !m_make_send_message_once ){
        m_make_send_message_once = true;
	    make_send_message();
    }

	set_curloption();

  CURLcode res = CURLE_OK;

    /* Send the message */
    res = curl_easy_perform(m_curl);

    /* Check for errors */
    if(res != CURLE_OK){
            std::string err("curl_easy_perform() failed: ");
            err += std::string( curl_easy_strerror(res) );
            m_error_list.push_back(err);
    }

    bool ret =  (m_error_list.size() == 0)? true: false;
    return ret;
}


/**
* attach
 */
bool CurlSmtp::attach(const std::string& filepath)
{

    std::vector<char> data;
    bool ret = read_binary_file(filepath, data);
	if ( !ret ) { 
		return false;
    }

	std::vector<char> outdata;
	ustd::string::base64encode(&data[0], data.size(), outdata);

    std::string filename;
    get_filename(filepath, filename );

	m_attachment.push_back(std::make_pair(outdata, filename));

	return true;
}


/**
* set_receive_list
 */
void CurlSmtp::set_receiver_list()
{

    std::string rcpt;

	for (int i = 0; i < m_to_list.size(); i++)
	{
        rcpt = LEFT_BRACE + m_to_list[i] + RIGTH_BRACE;
		m_rcpt_list = curl_slist_append(m_rcpt_list,  rcpt.c_str());
	}

	for (int i = 0; i < m_cc_list.size(); i++)
	{
        rcpt = LEFT_BRACE + m_cc_list[i] + RIGTH_BRACE;
		m_rcpt_list = curl_slist_append(m_rcpt_list,  rcpt.c_str());
	}

}


/**
* set_curloption
 */
void CurlSmtp::set_curloption()
{

	m_read.pos = 0;
	m_read.counter = 0;
	m_read.data.resize(m_send_buffer_list.size() + 1);
	m_read.data.insert(m_read.data.begin(), m_send_buffer_list.begin(), m_send_buffer_list.end());

	curl_easy_setopt( m_curl, CURLOPT_URL,  
    (char *)m_url.c_str() );


    if ( !m_user.empty() ){
	     curl_easy_setopt(m_curl, CURLOPT_USERNAME, 
        (char *)m_user.c_str());
    }


    if(m_xoauth && !m_token.empty() ) {
        curl_easy_setopt(m_curl, CURLOPT_XOAUTH2_BEARER, (char *)m_token.c_str() );
    } else if ( !m_password.empty() ){
	    curl_easy_setopt(m_curl, CURLOPT_PASSWORD, 
        (char *)m_password.c_str());
    }

    if ( !m_user.empty() ){
	     curl_easy_setopt(m_curl, CURLOPT_USERNAME, 
        (char *)m_user.c_str());
std::cout <<  "user: " << m_user << std::endl;
    }


	curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(m_curl, CURLOPT_MAIL_FROM, std::string(LEFT_BRACE + m_user + RIGTH_BRACE).c_str());
	curl_easy_setopt(m_curl, CURLOPT_MAIL_RCPT, m_rcpt_list);
	curl_easy_setopt(m_curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, m_ssl_verify);

	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, m_ssl_verify);

	curl_easy_setopt(m_curl, CURLOPT_READDATA, &m_read);

    if (m_verbose){
	    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
    }

	curl_easy_setopt(m_curl, CURLOPT_SSLVERSION, 0L);
	curl_easy_setopt(m_curl, CURLOPT_SSL_SESSIONID_CACHE, 0L);
	curl_easy_setopt(m_curl, CURLOPT_UPLOAD, 1L);
}


/**
* clear
 */
void CurlSmtp::clear()
{
	m_user.clear();
	m_password.clear();
	m_to_list.clear();
	m_cc_list.clear();
	m_from.clear();
	m_attach_list.clear();
	m_attachment.clear();
	m_subject.clear();
	m_user_agent.clear();
	m_subject_b64.clear();
	m_subject_charset.clear();
	m_msg.clear();
	m_msg_b64.clear();
	m_msg_charset.clear();
	m_token.clear();

	if (m_rcpt_list != NULL)
	{
		curl_slist_free_all(m_rcpt_list);
		m_rcpt_list = NULL;
	}
}


/**
* make_send_message
 */
void CurlSmtp::make_send_message()
{
    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

	m_send_buffer_list.clear();

	// date
   snprintf(buf, BUFSIZE, "Date: %s",  get_date() );
	m_send_buffer_list.push_back( buf );

	// msg id
   snprintf(buf, BUFSIZE, "MessageID: %s",  get_message_id() );
	m_send_buffer_list.push_back( buf );

	// user agent
    if( !m_user_agent.empty() ){
        snprintf(buf, BUFSIZE, "User-Agent: %s",  
        (char *)m_user_agent.c_str() );
        m_send_buffer_list.push_back( buf );
    }

	// from
    snprintf(buf, BUFSIZE, "From: <%s>",  
    (char *)m_from.c_str() );
	m_send_buffer_list.push_back( buf );

	// to list
	for (int i = 0; i < m_to_list.size(); i++)
	{
        std::string to = m_to_list[i];
        snprintf(buf, BUFSIZE, "To: <%s>",  
        (char *)to.c_str() );
		m_send_buffer_list.push_back( buf );
	}

	// cc list
	for (int i = 0; i < m_cc_list.size(); i++)
	{
       std::string cc = m_cc_list[i];
        snprintf(buf, BUFSIZE, "Cc: <%s>",  
        (char *)cc.c_str() );
		m_send_buffer_list.push_back( buf );
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
            "Subject: %s",
            (char *)m_subject.c_str() );
    }

	m_send_buffer_list.push_back( buf );


	if (m_attach_list.empty())
	{
	    // no attach

        if( !m_msg_b64.empty() && !m_msg_charset.empty() )
        {
          // header
                snprintf(buf, BUFSIZE,  
                CONTENT_TYPE_CHARSET_FORMAT,
                (char *)m_msg_charset.c_str() ); 

                m_send_buffer_list.push_back( buf );

                m_send_buffer_list.push_back( CONTENT_TRANSFER_BASE64 );

	            // split body
		        m_send_buffer_list.push_back(CRLF);

                // message
	            m_send_buffer_list.push_back( m_msg_b64 );

        } else {
	// split body
		    m_send_buffer_list.push_back(CRLF);

		// message
		 m_send_buffer_list.push_back( m_msg );

        } // if m_msg_b64
      
	}
	else
	{
        // attachment

        // mime version
		m_send_buffer_list.push_back( MIME_VER );

// multipart begin
        std::string boundary( get_boundary() );
        std::string boundary_begin = BOUNDARY_FLAG + boundary;
        std::string boundary_end = BOUNDARY_FLAG + boundary + BOUNDARY_FLAG;

        snprintf(buf, BUFSIZE, 
        CONTENT_TYPE_MULTITYPE_BOUNDARY_FORMAT, 
        (char *)boundary.c_str() );

        m_send_buffer_list.push_back( buf );
		m_send_buffer_list.push_back(CRLF);

		// first part of body, boundary header and message
		m_send_buffer_list.push_back( boundary_begin );
		m_send_buffer_list.push_back( CONTENT_TYPE_TEXT_USASCII_FLOWED );
		m_send_buffer_list.push_back( CONTENT_TRANSFER_7BIT );

		// split body
		m_send_buffer_list.push_back(CRLF);

		// message
		m_send_buffer_list.push_back( m_msg );


		m_send_buffer_list.push_back( boundary_begin );

		// attachment
		for (int i = 0; i < m_attach_list.size(); ++i)
		{
			attach(m_attach_list[i]);
		}

		for (std::vector<std::pair<std::vector<char>, std::string>>::iterator it1 = m_attachment.begin();
			it1 != m_attachment.end(); ++it1)
		{
			if (it1->second.length() > 3)
			{ // long enough for an extension
				std::string typ(it1->second.substr(it1->second.length() - 4, 4));
			
				if (m_type_map_list.count(typ) > 0)
				{
					m_send_buffer_list.push_back(m_type_map_list[typ]);
				}
				else
				{ // add other types
					// everything else
					m_send_buffer_list.push_back("Content-Type: application/X-other-1;");
				}
			}
			else
			{
				// default to don't know
				m_send_buffer_list.push_back("Content-Type: application/X-other-1;");
			}

			m_send_buffer_list.push_back("Content-Transfer-Encoding: base64");
			m_send_buffer_list.push_back("Content-Disposition: attachment; filename=\"" + it1->second + "\"");

			// split body
			m_send_buffer_list.push_back(CRLF);

			m_send_buffer_list.push_back(std::string(it1->first.begin(), it1->first.end()));

			// terminate the message with the boundary + "--"
			if ((it1 + 1) == m_attachment.end())
				m_send_buffer_list.push_back( boundary_end );
			else
				m_send_buffer_list.push_back( boundary_begin );
		}
	} // 	if m_attach_list

	// CurlSmtp:: \r\n to each item
	for (int i = 0; i < m_send_buffer_list.size(); ++i)
	{
		m_send_buffer_list[i] += CRLF;
	}

}


/**
 * get_boundary
 */
std::string CurlSmtp::get_boundary()
{
		std::string boundary;
		boundary.reserve(16);
		const char hex[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < 16; ++i)
		{
			int x = rand() % 62;
			boundary.append(1, hex[x]);
		}

		return boundary;
}


/**
 * read_binary_file
 */
bool CurlSmtp::read_binary_file(const std::string filepath, std::vector<char> &data)
{

	std::ifstream file;
    file.open( filepath, std::ios::binary | std::ios::in);
	if (!file){
        std::string err = std::string("can not open: ") + filepath;
        m_error_list.push_back(err);
		return false;
    }

	char c = file.get();
	for (; file.good(); c = file.get())
	{
		if (file.bad()){
			break;
        }

		data.push_back(c);

	} // for

    file.close();
    return true;
}


/**
* get_filename
 */
void CurlSmtp::get_filename(std::string filepath, std::string &filename )
{
	std::string fn(filepath);
	std::string::size_type p = fn.find_last_of('/');
	if (p == std::string::npos)
		p = fn.find_last_of('\\');
	if (p != std::string::npos)
	{
		p += 1; // get past folder delimeter
		fn = fn.substr(p, fn.length() - p);
	}
    filename = fn;
}


/**
 * get_date
 */
char* CurlSmtp::get_date(void)
{

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900

    const char* FORMAT = "%a, %d %b %Y %H:%M:%S %z";

    const size_t BUFSIZE = 256;
    static char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);

    strftime(buf, BUFSIZE, FORMAT, &tm);

    return buf;
}



/**
 * get_message_id
 */
char* CurlSmtp::get_message_id(void)
{
    const size_t BUF_SIZE = 256;
    static char buf[BUF_SIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);


    const size_t HOSTNAME_SIZE = 256;
    char hostname[HOSTNAME_SIZE]; 

// function 'gethostname' is invalid in C99
    gethostname(hostname,  HOSTNAME_SIZE);

    const char* FORMAT = "%d%02d%02d%02d%02d%02d.%s";

    snprintf(buf, BUF_SIZE, 
        (char *)FORMAT,
        ( tm.tm_year+1900 ),
        (tm.tm_mon+1),
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        hostname);

    return buf;
}

