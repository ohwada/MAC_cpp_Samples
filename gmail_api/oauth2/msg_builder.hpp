#pragma once
/**
 * msg_builder.hpp
 * 2022-06-01 K.OHWADA
 */

// message build utility


#include <string>
#include<ctime>
#include <unistd.h>
#include "Poco/Format.h"
#include "poco_timestamp.hpp"
#include "poco_file_stream.hpp"


// prototype
std::string buildMessageText(std::string subject, std::string to, std::string from, std::string body );
std::string buildHeaders(std::string subject, std::string to, std::string from);
std::string getDate(void);
std::string getMessageID(void);
std::string getMessageTime(void);
std::string get_hostname();
std::string getDefaultBody(void);
std::string getCurlVersion(void);
bool saveMessage(std::string msg);
void printMessage(std::string msg) ;


/**
 * buildMessageText
 * RFC 2822 format
 */
std::string buildMessageText(std::string subject, std::string to, std::string from, std::string body)
{

const std::string CRLF("\r\n");

const std::string CONTENT_TYPE_TEXT_PLANE_USASCII(
"Content-Type: text/plain; charset=us-ascii; \r\n");

const std::string CONTENT_TRANSFER_7BIT("Content-Transfer-Encoding: 7bit\r\n");

// headers
    std::string headers =
    buildHeaders( subject,  to,  from);

    std::string msg =
    headers
    + CONTENT_TYPE_TEXT_PLANE_USASCII
    + CONTENT_TRANSFER_7BIT
    + CRLF // heder part end
    + body
    + CRLF;

    return msg;
}


/**
 * buildHeaders
 */
std::string buildHeaders(std::string subject, std::string to, std::string from)
{

const std::string MIME_VER("Mime-Version: 1.0\r\n") ;

    const std::string FORMAT_SUBJECT("Subject: %s\r\n");

    const std::string FORMAT_TO("To: %s\r\n");

    const std::string FORMAT_FROM("From: %s\r\n");

    const std::string FORMAT_DATE("Date: %s\r\n");

    const std::string FORMAT_MESSAGE_ID("Message-ID: <%s>\r\n");

    std::string hdr_subject;
    Poco::format(hdr_subject, FORMAT_SUBJECT, subject );

    std::string hdr_to;
    Poco::format(hdr_to, FORMAT_TO, to );

    std::string hdr_from;
    Poco::format(hdr_from, FORMAT_FROM, from );

    std::string hdr_date;
    Poco::format( hdr_date, FORMAT_DATE, getDate() );

  std::string hdr_msg_id;
    Poco::format(hdr_msg_id, FORMAT_MESSAGE_ID, getMessageID() );

    std::string header =
    hdr_subject 
    + hdr_to
    +  hdr_from
    +  hdr_date
    + hdr_msg_id
    + MIME_VER;

    return header;
}


/**
 * getDate
 */
std::string getDate(void)
{

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900

    const char FORMAT[] = "%a, %d %b %Y %H:%M:%S %z";

    const size_t BUFSIZE = 256;
    static char buf[BUFSIZE];

    std::time_t now = std::time(nullptr);

    std::strftime(buf, BUFSIZE, (char *)FORMAT, std::localtime(&now));

    return std::string(buf);
}



/**
 * getMessageID
 */
std::string getMessageID(void)
{
// RFC822 
// 20220926232640@MacBook-Air.local
// https://www.emaillab.org/essay/message-id.html#what

    const std::string FORMAT("%s@%s");

   std::string id;
    Poco::format(id, FORMAT, getMessageTime(), get_hostname() );

    return id;
}


/**
 * get_hostname
 */
std::string getMessageTime(void)
{
// year month day hour minute second
// 20220926232640

    const std::string FORMAT("%d%02d%02d%02d%02d%02d");

    std::time_t now = std::time(nullptr);

    std::tm tm; 
    localtime_r(&now,&tm);

    std::string datetime;
  Poco::format( datetime, FORMAT, 
        ( tm.tm_year + 1900 ), 
        (tm.tm_mon + 1), 
        tm.tm_mday, 
        tm.tm_hour, 
        tm.tm_min,
        tm.tm_sec );

    return datetime;
}


/**
 * get_hostname
 */
std::string get_hostname()
{
   const size_t BUFSIZE = 256;
    char buf[BUFSIZE]; 

// function 'gethostname' is invalid in C99
    gethostname(buf,  BUFSIZE);

    return std::string(buf);
}

/**
 * getDefaultBody(void
 */
std::string getDefaultBody(void)
{
    const std::string FORMAT("and %s \r\n");

    std::string ver;
     Poco::format(ver, FORMAT, getCurlVersion() );

    std::string body = 
    std::string("This is a test e-mail. \r\n")
    + std::string("This mail was sent using Gmail API \r\n")
    + ver;

    return body;
}

/**
 * getCurlVersion
 */
std::string getCurlVersion(void)
{
    const std::string FORMAT("libcurl %s");

    std::string ver;
    Poco::format(ver, FORMAT, LIBCURL_VERSION );

    return ver;
}


/**
 * printMessage
 */
void printMessage(std::string msg) 
{
    std::cout << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << msg << std::endl;
    std::cout << "----------" << std::endl;

}


/**
 * saveMessage
 */
bool saveMessage(std::string msg)
{

    std::string dir("log");
    std::string prefix("mail");
    std::string ext("eml"); 

    std::string path = build_timestamp_file_path(dir, prefix, ext);

    return file_text_write(path,  msg );
}
