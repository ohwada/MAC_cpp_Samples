/**
 * OpenAL Beep Sample
 * 2020-03-01 K.OHWADA
 */


// Keyboard Piano with beep
// chnge to run on macOS
// original : https://saeki-ce.xsrv.jp/C_src/piano02.html


#include "keyboard.h"
#include "Beep.hpp"

using namespace std;


/**
 * printHelp
 */
void printHelp(void)
{
// monospaced font
    printf("\033[2J"); // clear screen
    printf(" \n");
    printf("  |‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾| \n");
    printf("  |        Keyboard Pian (Beep)                               | \n");
    printf("  |       press Shift: go up one octave                       | \n");
    printf("  |                                                           | \n");
    printf(" *:._.:*‾*:._.:*‾*:._.:*‾*:._.:*‾*:._.:*‾*:._.:*‾*:._.:*‾*:._.:* \n");
    printf("  |                                                           |  \n");
    printf("  |----,----,----,----,----,----,----,----,----,----,----,----|  \n");
    printf("  |so #|ra #|    |do #|re #|    |fa #|so #|ra #|    |do #|re #|  \n");
    printf("  | A  |S   |D   |F   |G   |H   | J  | K  | L  | ;  | :  | ]  |  \n");
    printf("  '----'----'----'----'----'----'----'----'----'----'----'----'  \n");
    printf("  | ra | si | do | re | mi | fa | so | ra | si | do | re |  \n");
    printf("  | Z  | X  | C  | V  | B  | N  | M  |  , | .  | /  | \\  |  \n");
    printf("  |----'----'----'----'----'----'----'----'----'----'----|  \n");
}


/**
 * getFreq
 */
int getFreq(int ch)
{

    int Hz = 0; // Beep sound frequency
    switch (ch)
          {
            case  97: Hz= 208; break;    // a so #
            case 115: Hz= 233; break;    // s ra #
            case 102: Hz= 277; break;    // f do #
            case 103: Hz= 311; break;    // g re #
            case 106: Hz= 370; break;    // j fa #
            case 107: Hz= 415; break;    // k so #
            case 108: Hz= 466; break;    // l ra 3
            case  58: Hz= 554; break;    // ; do #
            case  93: Hz= 622; break;    // ] re #

            case 122: Hz= 220; break;    // z ra
            case 120: Hz= 247; break;    // x si
            case  99: Hz= 262; break;    // c do
            case 118: Hz= 294; break;    // v re
            case  98: Hz= 330; break;    // b mi
            case 110: Hz= 349; break;    // n fa
            case 109: Hz= 392; break;    // m so
            case  44: Hz= 440; break;    // , ra
            case  46: Hz= 494; break;    // . si
            case  47: Hz= 523; break;    // / do
            case  92: Hz= 587; break;    // \ re

            //--Shift--
            case  65: Hz= 415; break;    // A so #
            case  83: Hz= 466; break;    // S ra #
            case  70: Hz= 554; break;    // F do #
            case  71: Hz= 622; break;    // G re #
            case  72: Hz= 740; break;    // J fa #
            case  74: Hz= 831; break;    // K so #
            case  76: Hz= 932; break;    // L ra #
            case  43: Hz=1109; break;    // + do #
            case 125: Hz=1245; break;    // ] re #

            case  90: Hz= 440; break;    // Z ra
            case  88: Hz= 494; break;    // X si
            case  67: Hz= 523; break;    // C do
            case  86: Hz= 587; break;    // V re
            case  66: Hz= 659; break;    // B mi
            case  78: Hz= 698; break;    // N fa
            case  77: Hz= 784; break;    // M so
            case  60: Hz= 880; break;    // < ra
            case  62: Hz= 988; break;    // > si
            case  63: Hz=1047; break;    // ? do
            case  95: Hz=1175; break;    // _ re

    } // switch
    return Hz;
}


/**
 * main
 */
int main(int argc, char **argv)
{
    const int PLAY_DURATION = 200; // msec

  int   ch;   // Key number
  int  prev_ch = 0;   // previous Key number
  int   Hz; // Beep sound frequency

	Beep beep;

// open 
	int ret = beep.openAL();
	if (ret != 0){
		cout << "openAL Faild" << endl;
		return 1;
	}

    printHelp();

    while ( 1 )
      {

        if ( kbhit( )==0 ) {
            // do nothing, whenNo key is pressed
             ch = -1; 
            continue;
        }

        prev_ch = ch; // save previous key number
        ch = getchar( ); 
        if ( ch == KEY_ESC ) {
            // exit loop, if ESC
            break;             
        }
        if ( ch == prev_ch ) {
            // do nothing, if same key
            continue; 
        }

         Hz = getFreq(ch);

        beep.playBeep(Hz, PLAY_DURATION);  // play 200 msec
   
      } // while

// Cleanup
    beep.closeAL();

	return 0;
}

