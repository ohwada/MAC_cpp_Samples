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
 * convFile
 */
int TextEncodeConverter::convFile(string file_in, string enc_in, string file_out,  int flag_utf)
{

    m_fromcode = (char *)enc_in.c_str();

    ifstream ifs;
    ofstream ofs;

    bool is_error = false;
    int count = 0;
        iconv_t icd;

    try {

        ifs.open(file_in);
        if (ifs.fail()) {
            cerr << "[FAILED] Could not open " << file_in << endl;
            return TEXT_ENC_RET_FAILD;
        }

        ofs.open(file_out);
        if (ofs.fail()) {
            cerr << "[FAILED] Could not open " << file_out << endl;
            return TEXT_ENC_RET_FAILD;
        }

        m_icd = iconv_open(TOCODE, m_fromcode);
        if (m_icd == (iconv_t)-1) {
            cerr << "[FAILD] iconv_open Faild:  " << errno << endl;
            return TEXT_ENC_RET_FAILD;
        }

        string line;
        string str;
        char *inbuf;
        int inbuf_size;
        bool ret;
        int line_count = 0;

        while (getline(ifs, line)) {

            line_count++;
            inbuf = (char *)line.c_str();
            int len = line.length();
            int buflen = len;

// TODO:
// 仮対策
// ２バイト改行コード(00, 0A) が、
// 文字(00) と１バイト改行コード(0A) に解釈され、
// 末尾に文字(00)が付く
            if(flag_utf == 1){
                buflen = len - 1;
            }else if(flag_utf == 2){
                buflen = len - 3;
            }

            ret = convert(inbuf, buflen, str);
            if (ret) {
                cout <<  line_count << " : " << str << endl;
                ofs << str << endl;
            } else {
                is_error = true;
                cout <<  line_count << " : [err]" << endl;
                if(m_debug_print){
                    dumpLine(line);
                }
                continue;
            }

            if( !str.empty() ){
                count ++;
            }

        } // while

        if(m_icd){
            iconv_close(m_icd);
        }

        ifs.close();
        ofs.close();

    } catch (char *e) {
            cerr << "EXCEPTION : " << e << endl;
            return TEXT_ENC_RET_FAILD;
    }

    if(count == 0){
            return TEXT_ENC_RET_FAILD;
    }

    if(is_error){
        return TEXT_ENC_RET_ERR;
    }

    return TEXT_ENC_RET_SUCCESS;
}


/*
 * convText
 */
string TextEncodeConverter::convText(char *buf, int buf_size, string enc)
{

    m_fromcode = (char *)enc.c_str();

    string str;
    try {

        m_icd = iconv_open(TOCODE, m_fromcode);

        int ret = convert(buf, buf_size, str);
        if (!ret) {
                if(m_debug_print){
                    dumpText(buf, buf_size);
                }
        }

        if(m_icd){
            iconv_close(m_icd);
        }

    } catch (char *e) {
        cerr << "EXCEPTION : " << e << endl;
        return "";
    }

    return str;
}



/*
 * convert
 */
bool TextEncodeConverter::convert(char* inbuf, int inbuf_size, string &dst)
{
    char    *pSrc, *pDst;
    size_t  nSrc, nDst;

    if(inbuf_size > BUF_SIZE){
        cerr << "[ERROR] convert :  src text size is too large: " << inbuf_size << endl;
        return false;
    }

    bool is_error = false;
    try {

        if(!m_icd){
            m_icd = iconv_open(TOCODE, m_fromcode);
        }

        pSrc = inbuf;
        nSrc = inbuf_size;

        pDst = m_dst_buffer;
        nDst = BUF_SIZE - 1;

        int ret;
        while (0 < nSrc) {
            ret = iconv(m_icd, &pSrc, &nSrc, &pDst, &nDst);
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

                    if(m_icd){
                        iconv_close(m_icd);
                        m_icd = NULL;
                    }

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
 * dumpLine
 */
void TextEncodeConverter::dumpLine(string line)
{
    int len = line.length();
    cout << "dumpLine: " << len << endl;
    for(int i=0; i < len; i++ ){
        printf("%X, ", (char)line[i]);
    }
    printf("\n \n");

}



/*
 * dumpText
 */
void TextEncodeConverter::dumpText(char* buf, int buf_size)
{
    cout << "dumpText: " << buf_size << endl;
    for(int i=0; i < buf_size; i++ ){
        printf("%X, ", (char)buf[i]);
    }
    printf("\n \n");
}



