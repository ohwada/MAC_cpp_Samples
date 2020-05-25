/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

#include <string>
#include <stdio.h>

#ifndef _TEXT_READER_H_
#define _TEXT_READER_H_


#define TEXT_READER_NONE 0
#define TEXT_READER_SJIS 1
#define TEXT_READER_EUCJP 2
#define TEXT_READER_UTF8 3
#define TEXT_READER_UTF16 4
#define TEXT_READER_UTF16BE 5
#define TEXT_READER_UTF16LE 6
#define TEXT_READER_UTF32 7
#define TEXT_READER_UTF32BE 8
#define TEXT_READER_UTF32LE 9
#define TEXT_READER_EOF -1


/**
 * class TextReader
 */
class TextReader
{
public:
    TextReader(void);
    ~TextReader(void);
    int open(std::string filepath);
    void close();
    int getLine(char* buffer, int bufsize);
    int getEnc(std::string filename);
    void setEnc(int enc);
    std::u16string convLineToU16(char* buf, int len, bool debug);
    std::u32string convLineToU32(char* buf, int len, bool debug);

private:
    FILE* m_fp;
    char* m_tmp;
    int m_enc;
};

#endif //  _TEXT_READER_H_
