#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// C++ wraper for libcurl smtp

// original : https://github.com/honeyligo/curlsmtp/blob/master/curlsmtp.h


#include <vector>
#include <string.h>
#include <unordered_map>
#include <curl/curl.h>


// costant



/**
 * class CurlSmtp
 */
class CurlSmtp
{
	struct ReadData
	{
		int pos;
		int counter;
		std::vector<std::string> data;
	};

public:
	CurlSmtp(void);
	~CurlSmtp(void);

	CurlSmtp( const std::string& url );

	void set_url(const std::string& url);
	void set_user(const std::string& user);
	void set_password(const std::string& password);
	void set_from(const std::string& from);
	void set_to(const std::string& to);
	void set_to_list(const std::vector<std::string>& to);
	void set_cc_list(const std::vector<std::string>& cc);
	void set_subject(const std::string& subject);
	void set_message(const std::string & message);
	void set_attach_list(const std::vector<std::string>& attach);
	void set_attach(const std::string & attach);
	void set_server_port(const std::string& server, const std::string& port);
 	void set_server_port(const std::string& server, const int port);
	void set_user_agent(const std::string user_agent);
	 void set_subject_charset( const std::string subject, const std::string charset );
 	void set_message_charset( const std::string msg, const std::string charset );
 	void set_token( const std::string token );
	void set_verbose(bool verbose);
	void set_ssl_verify(bool verify);
	bool send_mail(void);
	std::string  get_error(void);
	std::string get_send_buffer(void);

private:
    void initCurlSmtp(void);
	void set_url_server_port(const std::string& server, const std::string& port);
	void make_send_message();
	bool attach(const std::string& filename);
	void set_receiver_list();
	void set_curloption();
	void clear();
	static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);
 	size_t base64encode( const std::string data, std::string &ret_b64 );
	std::string get_boundary(void);
	bool read_binary_file(const std::string filepath, std::vector<char> &data);
	void get_filename(std::string filepath, std::string &filename );
	char* get_date(void);
	char* get_message_id(void);

private:
	std::vector<std::string> m_send_buffer_list;
	std::vector<std::string> m_to_list;
	std::vector<std::string> m_cc_list;
	std::string m_from;
	std::vector<std::string> m_attach_list;
	std::string m_user;
	std::string m_password;
	std::string m_url;
	std::string m_subject;
	std::string m_user_agent;
	std::string m_msg;

	std::vector<std::pair<std::vector<char>, std::string>> m_attachment;

    std::string m_subject_b64;
    std::string m_subject_charset;
    std::string m_msg_b64;
    std::string m_msg_charset;

    bool m_xoauth;
    std::string m_token;

	bool m_make_send_message_once;
	bool m_verbose;
	bool m_ssl_verify;

	CURL *m_curl;
	struct ReadData m_read;
	struct curl_slist *m_rcpt_list;

	std::unordered_map<std::string, std::string> m_type_map_list;

	std::vector<std::string> m_error_list;

};
// class
