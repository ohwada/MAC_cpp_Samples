/**
 * codecvt Sample
 * 2020-03-01 K.OHWADA
 */

#include <string>

using namespace std;

/**
 * convLineToU16
 */
u16string convLineToU16(string str, bool debug)
{

    u16string u16;

    int len = str.length();
    int buflen = len / 2;

    for(int i =0; i<buflen; i++){
// big endlian
        int i2 = 2 * i;

        char16_t val = 
            ( ((str[i2+0] << 8)&0xff00) | 
            (str[i2+1]&0x00ff) ); 

        u16 += val;
        if(debug){
            printf("%0X, ", val);
        }
    }

    u16 += '\0';
    if(debug){
        printf("\n");
    }

    return u16;
}


/**
 * convLineToU32
 */
u32string convLineToU32(string str, bool debug)
{

    u32string u32;
    int len = str.length();
    int buflen = len / 4;

    for(int i =0; i<buflen; i++){
// big endlian
        int i4 = 4*i;

        char32_t val =
            ( ((str[i4+0] << 24)&0x0ff000000) | 
            ((str[i4+1] << 16)&0x0ff0000) | 
            ((str[i4+2] << 8)&0x0ff00) | 
            (str[i4+3]&0x00ff) ); 

        u32 +=  val;
        if(debug){
            printf("%0X, ", val);
        }
    }

    u32 += '\0';
    if(debug){
        printf("\n");
    }

    return u32;
}


