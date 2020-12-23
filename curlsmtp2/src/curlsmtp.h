#pragma once
/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// change log
// modify to curlsmtp2

//original :  https://github.com/honeyligo/curlsmtp/blob/master/curlsmtp.h


#ifndef __CURL_SMTP_H__
#define __CURL_SMTP_H__

#include <vector>
#include <string.h>
#include <unordered_map>
#include <curl/curl.h>
#include "ustd_string.h"

#define LEFT_BRACE					"<"
#define RIGTH_BRACE					">"
#define ENTER						"\r\n"
#define BOUNDARY_FLAG				"--"

#define SMTP_SERVER				"smtp.exmail.qq.com"
#define SMTP_PORT				"587"



#define MIME_VER					"MIME-Version: 1.0"
#define HEADER_CONTENT_TYPE			"Content-Type: multipart/mixed;"

#define MSG_CONTENT_TYPE			"Content-Type: text/plain; charset=utf-8; format=flowed"
#define MSG_ENCODING				"Content-Transfer-Encoding: 7bit"

#define MULTI_PERFORM_HANG_TIMEOUT	60 * 1000


static struct timeval tvnow(void)
{
  /*
  ** time() returns the value of time in seconds since the Epoch.
  */
  struct timeval now;
  now.tv_sec = (long)time(NULL);
  now.tv_usec = 0;
  return now;
}


static long tvdiff(struct timeval newer, struct timeval older)
{
  return (newer.tv_sec-older.tv_sec)*1000+
    (newer.tv_usec-older.tv_usec)/1000;
}


class CurlSmtp
{
	struct WriteThis
	{
		int pos;
		int counter;
		std::vector<std::string> data;
	};

public:
	CurlSmtp(void);

	CurlSmtp(const std::string& from,
	const std::string& password,
	const std::vector<std::string>& to,
	const std::vector<std::string>& secret,
	const std::vector<std::string>& cc,
	const std::vector<std::string>& attach,
	const std::string& subject,
	const std::string& message,
	const std::string& server = SMTP_SERVER,
	const std::string& port = SMTP_PORT);

	~CurlSmtp();
	void closeCurlSmtp(void);

	void set_from(const std::string& from);
	void set_password(const std::string& password);
	void set_to(const std::vector<std::string>& to);
	void set_secret(const std::vector<std::string>& secret);
	void set_cc(const std::vector<std::string>& cc);
	void set_attach(const std::vector<std::string>& attach);
	void set_subject(const std::string& subject);
	void set_message(const std::string& message);
	void set_server(const std::string& server);
	void set_port(const std::string& port);


	void send_mail();

protected:
	 virtual void make_send_message();
	virtual bool attach(const std::string& filename);
	void set_receiver_list();
	 virtual  void set_curl_option();
	void clear();
	static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);

	std::string get_boundary()
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

protected:
	std::vector<std::string> send_buffer_;
	std::vector<std::string> to_;
	std::vector<std::string> cc_;
	std::vector<std::string> secret_;
	std::vector<std::string> attach_;
	std::string from_;
	std::string server_;
	std::string port_;
	std::string subject_;
	std::string message_;
	std::string password_;
	std::vector<std::pair<std::vector<char>, std::string>> attachment_;

	CURL *curl_;
	CURLM *mcurl_;
	struct curl_slist* rcpt_list_;
	struct WriteThis pooh_;

	std::unordered_map<std::string, std::string> typeMap_;
};

#endif // !__CURL_SMTP_H__