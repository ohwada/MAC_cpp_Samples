#pragma once
/*
 * buffer.hpp
 * 2022-0501 K.OHWADA 
*/

#ifndef  BUFFER_H
#define BUFFER_H

/**
 * class Buffer
 */
class  Buffer
{
public:
      Buffer();
    ~  Buffer();
    void setup(int buf_x, int buf_y, int buf_h);
    void addLine( char* str );
    void addTop( char *str);
    void  addF(char* format, ...);
    void enableDraw(bool flag);
    void scrollUp();
    void clearBuffer();
    void  dumpBuffer(int x, int y);

private:
    void addLineBuf( char *str );
    void addLineScr( char *str );
    void addTopBuf( char *str);
    void addTopScr( char *str);
    void clearBuf();
    void clearScr();
    void scrollUpBuf();
    void scrollUpScr();
    void clearScrLine( int x);
    int scr_h;
    int scr_w;
    int buf_x;
    int buf_y;
    int buf_h;
    int ptr_buf;
    int ptr_scr;
    bool  is_draw;
};

#endif 
