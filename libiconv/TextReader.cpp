/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// read text file
// support sjis, utf8, utf16be, utf32be, etc
// TODO :
// suport utf16, utf32


#include "TextReader.hpp"

using namespace std;

// global
const char NUL = 0x00;
const char LF = 0x0A;


/**
 * constractor
 */
TextReader::TextReader(void)
{
    m_tmp = new char[4];
    m_enc = 0;
}


/**
 * destractor
 */
TextReader::~TextReader(void)
{
    delete[] m_tmp;
}


/**
 * open
 */
int TextReader::open(string filepath)
{
    m_fp = fopen((char *)filepath.c_str(), "r");
    if(!m_fp){
            return 1;
    }
    return 0;
}


/**
 * close
 */
void TextReader::close(void)
{
    fclose(m_fp);
}


/**
 * getEnc
 */
int TextReader::getEnc(string filename)
{

    string parse_enc;

    int pos  = filename.find_last_of('_');
    if (pos != std::string::npos) {
        parse_enc = filename.substr(pos+1, filename.size()-pos);
    }

int enc = 0;
    if(parse_enc == "sjis"){
        enc = TEXT_READER_SJIS;
    }else if(parse_enc == "eucjp"){
        enc = TEXT_READER_EUCJP;
    }else if(parse_enc == "utf16"){
        enc = TEXT_READER_UTF16;
    }else if(parse_enc == "utf16be"){
        enc = TEXT_READER_UTF16BE;
    }else if(parse_enc == "utf16le"){
        enc = TEXT_READER_UTF16LE;
    }else if(parse_enc == "utf32"){
        enc = TEXT_READER_UTF32;
    }else if(parse_enc == "utf32be"){
        enc = TEXT_READER_UTF32BE;
    }else if(parse_enc == "utf32le"){
        enc = TEXT_READER_UTF32LE;
    }

    m_enc = enc;
    return enc;
}

/**
 * setEnc
 */
void TextReader::setEnc(int enc)
{
    m_enc = enc;
}


/**
 * getLine
 */
int TextReader::getLine(char* buf, int bufsize)
{

    int len;
    for(int i=0; i<bufsize; i++){
        len = i;
        int c = fgetc(m_fp);
        if(c == EOF){
            return TEXT_READER_EOF;
        }else if(m_enc == TEXT_READER_UTF16BE){
                if((m_tmp[3] == 0)&&(c == LF)){
                        break;
                }
        }else if(m_enc == TEXT_READER_UTF16LE){
                if((m_tmp[3] == LF)&&(c == 0)){
                    break;
                }
        }else if(m_enc == TEXT_READER_UTF32BE){
                if((m_tmp[1] == 0)&&(m_tmp[2] == 0)&&(m_tmp[3] == 0)&&(c == LF)){
                        break;
                }
        }else if(m_enc == TEXT_READER_UTF32LE){
                if((m_tmp[1] == LF)&&(m_tmp[2] == 0)&&(m_tmp[3] == 0)&&(c == 0)){
                    break;
                }
        }else{
                if(c == LF){
                    break;
                }
        }// if enc 

        buf[i] = (char)c;

        m_tmp[0] = m_tmp[1];
        m_tmp[1] = m_tmp[2];
        m_tmp[2] = m_tmp[3];
        m_tmp[3] = c;

    } // for

    buf[len] = NUL;
    return len;
}


/**
 * convLineToU16
 */
u16string TextReader::convLineToU16(char* buf, int len, bool debug)
{

    u16string u16;

    int buflen = len / 2;

    for(int i =0; i<buflen; i++){
// big endlian
        int i2 = 2 * i;

        char16_t val = 
            ( ((buf[i2+0] << 8)&0xff00) | 
            (buf[i2+1]&0x00ff) ); 

        u16 += val;
        if(debug){
            printf("%0X, ", val);
        }
    }

    if(debug){
        printf("\n");
    }

    return u16;
}


/**
 * convLineToU32
 */
u32string TextReader::convLineToU32(char* buf, int len, bool debug)
{

    u32string u32;
    int buflen = len / 4;

    for(int i =0; i<buflen; i++){
// big endlian
        int i4 = 4*i;

        char32_t val =
            ( ((buf[i4+0] << 24)&0x0ff000000) | 
            ((buf[i4+1] << 16)&0x0ff0000) | 
            ((buf[i4+2] << 8)&0x0ff00) | 
            (buf[i4+3]&0x00ff) ); 

        u32 +=  val;
        if(debug){
            printf("%0X, ", val);
        }
    }

    if(debug){
        printf("\n");
    }

    return u32;
}


