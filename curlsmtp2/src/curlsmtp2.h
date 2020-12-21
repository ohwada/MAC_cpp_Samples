#pragma once
/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// curlsmtp2 C++ header file

#ifndef __CURL_SMTP2_H__
#define __CURL_SMTP2_H__

#include <string>
#include "curlsmtp.h"

class CurlSmtp2 : public CurlSmtp
{

public:
	CurlSmtp2(void);
	~CurlSmtp2(void);

void set_user(const std::string&user);
void set_str_to(const std::string & str_to);
void set_str_attach(std::string &str_attach);
void set_url(const std::string& url);
 void set_server_port(const std::string& server, int port);
void set_user_agent(const std::string user_agent);
void set_subject_charset( const std::string subject, const std::string charset );
 void set_message_charset( const std::string msg, const std::string charset );
 void set_token( const std::string token );
void set_verbose(bool verbose);
void set_ssl_verify(bool verify);
std::string get_send_buffer(void);

private:
void make_send_message(void);
void set_curl_option(void);
 size_t base64encode( const std::string str_data, std::string &ret_b64 );

private:
	std::string m_user;
	std::string m_url;
    std::string m_user_agent;
    std::string m_subject_b64;
    std::string m_subject_charset;
    std::string m_msg_b64;
    std::string m_msg_charset;
    bool m_xoauth;
     std::string m_token;
    bool m_ssl_verify;
   bool m_verbose;
    bool m_make_send_message_once;
};

#endif // !__CURL_SMTP2_H__
