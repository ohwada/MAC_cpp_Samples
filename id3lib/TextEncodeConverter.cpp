/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// reference : https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

// TODO:
// convFile
// utf16le, utf16, utf32le, utf32 : not working properly

#include "TextEncodeConverter.hpp"


using namespace std;


// global
const char NUL = '\0';
const int BUF_SIZE  = 1024;
const char* TOCODE = "UTF-8//IGNORE";


/*
 * constractor
 */
TextEncodeConverter::TextEncodeConverter(void)
{
    m_dst_buffer = new char[BUF_SIZE];
    bool m_debug_print = false;
}


/*
 * destractor
 */
TextEncodeConverter::~TextEncodeConverter(void)
{
    delete[] m_dst_buffer;
}


/*
 * getLibiconvVersion
 */
string TextEncodeConverter::getLibiconvVersion(void)
{
    int major = (_LIBICONV_VERSION & 0xff00) >> 8;
    int minor = _LIBICONV_VERSION & 0x00ff;

    string ver =  to_string(major) + "." + to_string(minor);
    return ver;
}


/*
 * setDebugPrint
 */
void TextEncodeConverter::setDebugPrint(bool flag)
{
    m_debug_print = flag;
}


/*
 * convChars
 */
bool TextEncodeConverter::convChars(char *buf, int buf_size, string enc, string &text)
{

    char *fromcode = (char *)enc.c_str();

    bool is_error = false;
    try {

        iconv_t icd = iconv_open(TOCODE, fromcode);

        int ret = convert(icd, buf, buf_size, text);
        if (!ret) {
bool is_error = true;
                if(m_debug_print){
                    dumpChars(buf, buf_size);
                }
        }

        if(icd){
            iconv_close(icd);
        }

    } catch (char *e) {
        cerr << "EXCEPTION : " << e << endl;
        return false;
    }

    return !is_error;
}


/*
 * convert
 */
bool TextEncodeConverter::convert(iconv_t icd, char* inbuf, int inbuf_size, string &dst)
{
    char    *pSrc, *pDst;
    size_t  nSrc, nDst;

    if(inbuf_size > BUF_SIZE){
        cerr << "[ERROR] convert :  src text size is too large: " << inbuf_size << endl;
        return false;
    }

    bool is_error = false;
    try {

        pSrc = inbuf;
        nSrc = inbuf_size;

        pDst = m_dst_buffer;
        nDst = BUF_SIZE - 1;

        int ret;
        while (0 < nSrc) {
            ret = iconv(icd, &pSrc, &nSrc, &pDst, &nDst);
            if (ret == (size_t)-1) {
                is_error = true;
                if(!m_debug_print){
                    break;
                }

                string str_err = "";
                switch (errno) {
                    case E2BIG:
                        str_err = "E2BIG";
                        break;
                    case EILSEQ:
                         str_err = "EILSEQ";
                        break;
                    case EINVAL:
                        str_err = "EINVAL";
                        break;
                 } // switch

                    cerr << "[Err] iconv :  " << str_err << " ( " << errno << " ) left( " << nSrc << " , " << nDst << " ) " <<endl;
                     break; // exit while
            }

        } // whle

        *pDst = NUL;

        string str(m_dst_buffer);
        dst = str;

    } catch (char *e) {
        cerr << "EXCEPTION : " << e << endl;
        return false;
    }

    return !is_error;
}


/*
 * dumpChars
 */
void TextEncodeConverter::dumpChars(char* buf, int buf_size)
{
    cout << "dumpChars: " << buf_size << endl;
    for(int i=0; i < buf_size; i++ ){
        printf("%X, ", (char)buf[i]);
    }
    printf("\n \n");
}



