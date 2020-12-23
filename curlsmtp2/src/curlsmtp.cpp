/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// change log
// modify to curlsmtp2

// original : https://github.com/honeyligo/curlsmtp/blob/master/curlsmtp.cpp

#include <fstream>
#include "curlsmtp.h"

#define USER_AGENT					"User-Agent: Mail Client"


#define CHUNCK_SIZE					1024 * 10

size_t CurlSmtp::read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;
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


CurlSmtp::CurlSmtp(void)
{
	// nop
}


CurlSmtp::CurlSmtp(const std::string& from,
	const std::string& password,
	const std::vector<std::string>& to,
	const std::vector<std::string>& secret,
	const std::vector<std::string>& cc,
	const std::vector<std::string>& attach,
	const std::string& subject,
	const std::string& message,
	const std::string& server,
	const std::string& port)
	: from_(from)
	, password_(password)
	, to_(to)
	, secret_(secret)
	, cc_(cc)
	, subject_(subject)
	, server_(server)
	, port_(port)
	, message_(message)
	, attach_(attach)
	, rcpt_list_(NULL)
	, mcurl_(curl_multi_init())
	, curl_(curl_easy_init())
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	typeMap_.insert(std::make_pair(".gif", "Content-Type: image/gif;"));
	typeMap_.insert(std::make_pair(".jpg", "Content-Type: image/jpg;"));
	typeMap_.insert(std::make_pair(".jpeg", "Content-Type: image/jpeg;"));
	typeMap_.insert(std::make_pair(".png", "Content-Type: image/png;"));
	typeMap_.insert(std::make_pair(".bmp", "Content-Type: image/bmp;"));
	typeMap_.insert(std::make_pair(".txt", "Content-Type: plain/txt;"));
	typeMap_.insert(std::make_pair(".log", "Content-Type: plain/txt;"));
	typeMap_.insert(std::make_pair(".htm", "Content-Type: plain/htm;"));
	typeMap_.insert(std::make_pair(".html", "Content-Type: plain/htm;"));
	typeMap_.insert(std::make_pair(".exe", "Content-Type: application/X-exectype-1;"));
}

CurlSmtp::~CurlSmtp()
{
	curl_global_cleanup();
	curl_multi_cleanup(mcurl_);
	curl_easy_cleanup(curl_);
}


void CurlSmtp::closeCurlSmtp(void)
{
	curl_global_cleanup();
	curl_multi_cleanup(mcurl_);
	curl_easy_cleanup(curl_);
}


void CurlSmtp::set_from(const std::string& from)
{
	from_.assign(from);
}


void CurlSmtp::set_password(const std::string& password)
{
	password_.assign(password);
}

void CurlSmtp::set_to(const std::vector<std::string>& to)
{
	to_.resize(to.size());
	to_.assign(to.begin(), to.end());
}

void CurlSmtp::set_secret(const std::vector<std::string>& secret)
{
	secret_.resize(secret.size());
	secret_.assign(secret.begin(), secret.end());
}

void CurlSmtp::set_cc(const std::vector<std::string>& cc)
{
	cc_.resize(cc.size());
	cc_.assign(cc.begin(), cc.end());
}

void CurlSmtp::set_attach(const std::vector<std::string>& attach)
{
	attach_.resize(attach.size());
	attach_.assign(attach.begin(), attach.end());
}

void CurlSmtp::set_subject(const std::string& subject)
{
	subject_.assign(subject);
}

void CurlSmtp::set_message(const std::string& message)
{
	message_.assign(message);
}

void CurlSmtp::set_server(const std::string& server)
{
	server_.assign(server);
}

void CurlSmtp::set_port(const std::string& port)
{
	port_.assign(port);
}

void CurlSmtp::send_mail()
{
	set_receiver_list();
	make_send_message();
	set_curl_option();

	curl_multi_add_handle(mcurl_, curl_);

	int still_running = 1;
	struct timeval mp_start = tvnow();
	curl_multi_perform(mcurl_, &still_running);

	while (still_running)
	{
		struct timeval timeout;
		int rc;

		fd_set fdread;
		fd_set fdwrite;
		fd_set fdexcep;
		int maxfd = -1;

		long curl_timeo = -1;

		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcep);

		/* set a suitable timeout to play around with */
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		curl_multi_timeout(mcurl_, &curl_timeo);
		if (curl_timeo >= 0)
		{
			timeout.tv_sec = curl_timeo / 1000;
			if (timeout.tv_sec > 1)
				timeout.tv_sec = 1;
			else
				timeout.tv_usec = (curl_timeo % 1000) * 1000;
		}

		/* get file descriptors from the transfers */
		curl_multi_fdset(mcurl_, &fdread, &fdwrite, &fdexcep, &maxfd);

		rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

		if (tvdiff(tvnow(), mp_start) > MULTI_PERFORM_HANG_TIMEOUT)
		{
			fprintf(stderr, "ABORTING TEST, since it seems "
				"that it would have run forever.\n");
			break;
		}

		switch (rc)
		{
		case -1:
			/* select error */
			break;
		case 0: /* timeout */
			break;
		default: /* action */
			curl_multi_perform(mcurl_, &still_running);
			break;
		}
	}
	curl_multi_remove_handle(mcurl_, curl_);
	clear();
}

bool CurlSmtp::attach(const std::string& filename)
{
	if (!filename.length()) // do silly checks.
		return false;

	std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in);
	if (!file)
		return false;

	std::vector<char> filedata;
	char c = file.get();
	for (; file.good(); c = file.get())
	{
		if (file.bad())
			break;
		filedata.push_back(c);
	}

	std::vector<char> outdata;
	ustd::string::base64encode(&filedata[0], filedata.size(), outdata);

	std::string fn(filename);
	std::string::size_type p = fn.find_last_of('/');
	if (p == std::string::npos)
		p = fn.find_last_of('\\');
	if (p != std::string::npos)
	{
		p += 1; // get past folder delimeter
		fn = fn.substr(p, fn.length() - p);
	}

	attachment_.push_back(std::make_pair(outdata, fn));

	return true;
}

void CurlSmtp::set_receiver_list()
{

	for (int i = 0; i < to_.size(); i++)
	{
		rcpt_list_ = curl_slist_append(rcpt_list_, std::string(LEFT_BRACE + to_[i] + RIGTH_BRACE).c_str());
	}
	for (int i = 0; i < cc_.size(); i++)
	{
		rcpt_list_ = curl_slist_append(rcpt_list_, std::string(LEFT_BRACE + cc_[i] + RIGTH_BRACE).c_str());
	}
	for (int i = 0; i < secret_.size(); i++)
	{
		rcpt_list_ = curl_slist_append(rcpt_list_, std::string(LEFT_BRACE + secret_[i] + RIGTH_BRACE).c_str());
	}
}

void CurlSmtp::set_curl_option()
{
	pooh_.pos = 0;
	pooh_.counter = 0;
	pooh_.data.resize(send_buffer_.size() + 1);
	pooh_.data.insert(pooh_.data.begin(), send_buffer_.begin(), send_buffer_.end());

	curl_easy_setopt(curl_, CURLOPT_URL, std::string("smtp://" + server_ + ":" + port_).c_str());
	curl_easy_setopt(curl_, CURLOPT_USERNAME, from_.c_str());
	curl_easy_setopt(curl_, CURLOPT_PASSWORD, password_.c_str());
	curl_easy_setopt(curl_, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl_, CURLOPT_MAIL_FROM, std::string(LEFT_BRACE + from_ + RIGTH_BRACE).c_str());
	curl_easy_setopt(curl_, CURLOPT_MAIL_RCPT, rcpt_list_);
	curl_easy_setopt(curl_, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl_, CURLOPT_READDATA, &pooh_);
	curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl_, CURLOPT_SSLVERSION, 0L);
	curl_easy_setopt(curl_, CURLOPT_SSL_SESSIONID_CACHE, 0L);
	curl_easy_setopt(curl_, CURLOPT_UPLOAD, 1L);
}

void CurlSmtp::clear()
{
	from_.clear();
	password_.clear();
	to_.clear();
	cc_.clear();
	secret_.clear();
	attach_.clear();
	attachment_.clear();
	subject_.clear();
	message_.clear();
	server_.clear();
	port_.clear();

	if (rcpt_list_ != NULL)
	{
		curl_slist_free_all(rcpt_list_);
		rcpt_list_ = NULL;
	}
}

void CurlSmtp::make_send_message()
{
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

	// subject
	send_buffer_.push_back("Subject: " + subject_);

	if (attach_.empty())
	{
		// split body
		send_buffer_.push_back(ENTER);
		// message
		send_buffer_.push_back(message_ + ENTER);
	}
	else
	{
		// user agent
		send_buffer_.push_back(USER_AGENT);
		send_buffer_.push_back(MIME_VER);
		send_buffer_.push_back(HEADER_CONTENT_TYPE);

		std::string boundary(get_boundary());
		// set boundary
		send_buffer_.push_back(" boundary=\"" + boundary + "\"" ENTER);

		// first part of body, boundary header and message
		send_buffer_.push_back(BOUNDARY_FLAG + boundary);
		send_buffer_.push_back(MSG_CONTENT_TYPE);
		send_buffer_.push_back(MSG_ENCODING);

		// split body
		send_buffer_.push_back(ENTER);

		send_buffer_.push_back(message_ + ENTER);
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
