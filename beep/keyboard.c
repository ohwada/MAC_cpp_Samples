/**
 * keyboard
 * 2020-03-01 K.OHWADA
 */


// Linux emulater for kbhit function of Windows
//  reference: https://hotnews8.net/programming/tricky-code/c-code03

// password without echo
// reference : https://www.mm2d.net/main/prog/c/console-05.html


#include "keyboard.h"


/**
 * kbhit
 * return 0 if no keys are pressed
 * return 1 if any key is pressed
 */
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1; // any key is pressed
    }

    return 0; // no keys are pressed
}


/**
 * getKey
 * return 0 if no keys are pressed
 * return key value if any key is pressed
 */
int getKey(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        return ch; // any key is pressed
    }

    return 0; // no keys are pressed
}


/**
 * getCntrlCode
 */
char* getCntrlCode(int ch)
{

    char* buff = (char*)malloc(10);
    switch(ch)
    {
    case KEY_TAB:
        strcpy(buff, "TAB");
        break;
    case KEY_LF:
        strcpy(buff, "LF");
        break;
    case KEY_ESC:
        strcpy(buff, "ESC");
        break;
    } // switch

    return buff;

}


/**
 * get_password_without_echo
 */
char* get_password_without_echo(void) 
{
    const int BUFSIZE = 128;
    char* buff = (char*)malloc(BUFSIZE);

  struct termios term;
  struct termios save;
  tcgetattr(STDIN_FILENO, &term);
  save = term;
  term.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  scanf("%s", buff);
  tcsetattr(STDIN_FILENO, TCSANOW, &save);
  return buff;
}


/**
 * get_password_with_echo_star
 */
char* get_password_with_echo_star(void) 
{

    const int BUFSIZE = 128;
    const char STAR =  '*';

    char* buff = (char*)malloc(BUFSIZE);

    struct termios term;
    struct termios save;
    tcgetattr(STDIN_FILENO, &term);
    save = term;
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int cnt = 0;
    while(1){

        int tmp = fgetc(stdin);
        if  ((tmp < 0) || (iscntrl(tmp) != 0) ) {
            fprintf(stderr, "\n");
            break;
        }

        fprintf(stderr, "%c", STAR);

        if(cnt < BUFSIZE){
            buff[cnt] = tmp;
        }

        cnt++;
        if(cnt > BUFSIZE){
            break;
        }

    } // while

    tcsetattr(STDIN_FILENO, TCSANOW, &save);

    if(cnt < BUFSIZE){
        buff[cnt] = 0;
    }

    return buff;

}

