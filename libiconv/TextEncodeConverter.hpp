/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */


#include <string>
#include <iostream>
#include <fstream>
  
#include <iconv.h>


#ifndef _TEXT_ENC_CONV_H_
#define _TEXT_ENC_CONV_H_

// iconv -l
#define TEXT_ENC_SJIS "Shift_JIS"
#define TEXT_ENC_EUCJP "EUC-JP"
#define TEXT_ENC_UTF16 "UTF-16"
#define TEXT_ENC_UTF16BE "UTF-16BE"
#define TEXT_ENC_UTF16LE "UTF-16LE"
#define TEXT_ENC_UTF32 "UTF-32"
#define TEXT_ENC_UTF32BE "UTF-32BE"
#define TEXT_ENC_UTF32LE "UTF-32LE"

#define TEXT_ENC_RET_SUCCESS 0
#define TEXT_ENC_RET_ERR 1
#define TEXT_ENC_RET_FAILD 2

/*
 * class TextEncodeConverter
 */
class TextEncodeConverter
{
public:
    TextEncodeConverter(void);
    ~TextEncodeConverter(void);
    void setDebugPrint(bool flag);
    std::string getLibiconvVersion(void);
    bool convChars(char *buf, int buf_size, std::string enc, std::string &text);
    void dumpChars(char* buf, int buf_size);

private:
    bool convert(iconv_t icd, char* inbuf, int inbuf_size, std::string &dst);

    char*  m_dst_buffer;
    bool m_debug_print;

};

#endif // _TEXT_ENC_CONV_H_

