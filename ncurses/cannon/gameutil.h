// 2022-05-01 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/


#ifndef GAMEUTIL_H
#define GAMEUTIL_H

// for test
extern void Fatal(char *msg);
extern void Debug(char *msg);

// curses 
extern void InitColor(int bg);
extern void UseColor(int c);
extern void DrawBlocks(int y, int x, char *s);
extern void CenterStr(int y, int x, char *s);

// random
extern void InitRand();
extern int Rand(int n);

// sound
extern void SetSnd(int sw);
extern void PlaySnd(char *file);
extern void SetPlay(char *cmd);

// timer
extern void InitWait();
extern void Wait(int msec);

#endif

