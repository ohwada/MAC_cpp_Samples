/**
 * main.cpp
 * 2022-06-01 K.OHWA
 */


#ifdef MORNING
#include "good_morning.hpp"
#else
#include "hello.hpp"
#endif


/**
 * main
 */
int main() {
#ifdef MORNING
good_morning();
#else
hello();
#endif
	return 0;
}

