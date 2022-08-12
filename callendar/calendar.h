#pragma once
/**
 * calendar.h
 * 2022-06-01 K.OHWADA
 */

#include <stdbool.h>

// prototype
unsigned int  day_of_week(unsigned int y, unsigned int m, unsigned int d);
bool is_leap_year(unsigned  int y) ;
bool is_big_month(unsigned int m);
 unsigned int last_day_of_month(unsigned int y, unsigned int m);


/**
 * week_day
* Zeller's congruence
 * @return 0: Sun 6: Sat
 */
// https://en.wikipedia.org/wiki/Zeller%27s_congruence
unsigned int  day_of_week(unsigned int y, unsigned int m, unsigned int d)
{
   if(m < 1 || m > 12 || d < 1 || d > 31) {
        return -1;
    }

    if(m==1){
        m = 13;
        y--;
    }else if(m==2){
        m = 14;
        y--;
    }
    
    unsigned int  x = (y + (y/4) - (y/100) + (y/400) + ((13*m + 8)/5) + d)%7;
    
    return x;
}


/**
 * is_leap_year
 */
bool is_leap_year(unsigned  int y) 
{
    bool ret = ( (y%4) == 0 && ((y%100) != 0 || (y%400) == 0) )? true : false;
    return ret;
}


/**
 * is_big_month
 */
bool is_big_month(unsigned int m) 
{
    bool ret = ((m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12))? true:false;
    return ret;
}


/**
 *  last_day_of_month
 */
 unsigned int last_day_of_month(unsigned int y, unsigned int m) 
{
    unsigned int ret;
    if (m == 2) {
        ret = is_leap_year(y)? 29 : 28;
    } else {
        ret = is_big_month(m)? 31 : 30;
    }
    return ret;
}


