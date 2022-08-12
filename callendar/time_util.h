#pragma once
/**
 * time_util.h
 * 2022-06-01 K.OHWADA
 */


#include <time.h>
#include <math.h>


// prototype
time_t get_unixtime
   (int const y, unsigned int const mon, unsigned int const d, unsigned int const h, unsigned int const min, unsigned int const sec);
unsigned int day_of_year(int const y, unsigned int const m, unsigned int const d);
unsigned int week_of_year(int const y, unsigned int const m, unsigned int const d);


/**
 * get_unixtime
 */
time_t get_unixtime
   (int const y, unsigned int const mon, unsigned int const d, unsigned int const h, unsigned int const min, unsigned int const sec)
{

    if ( (y<1900)||(mon<1)||(mon>12)||(d<1)||(d>31) ) {
        return 0;
    }

    if ( (h<0)||(h>23)||(min<0)||(min>59)||(sec<0)||(sec>60) ) {
        return 0;
    }

    struct tm tm1 = { 0 };

	tm1.tm_year = y - 1900;
	tm1.tm_mon = mon - 1;
	tm1.tm_mday = d;

	tm1.tm_hour = h;
	tm1.tm_min = min;
	tm1.tm_sec = sec;

	// convert tm structure to time_t type
	time_t t = mktime(&tm1);
    return t;
}


/**
 * day_of_year
 */
unsigned int day_of_year(int const y, unsigned int const m, unsigned int const d)
{

if(m < 1 || m > 12 || d < 1 || d > 31) {
    return 0;
}

    time_t unixtime = get_unixtime
   (y, m, d, 0, 0, 0);

 if (unixtime == 0){
    return 0;
}

struct tm date;
date = *localtime(&unixtime); 

return date.tm_yday + 1;

}



/**
 * week_of_year
 */
unsigned int week_of_year(int const y, unsigned int const m, unsigned int const d)
{

   
   if(m < 1 || m > 12 || d < 1 || d > 31) {
        return 0;
    }


unsigned int days = day_of_year(y, m, d);

 unsigned int weeks = (unsigned int)ceil( (double)days/7.0);

    return weeks;
}


