#pragma once
/**
 * random sample
 * 2022-06-01 K.OHWADA
 */

// generate random password with random_char.h


#include "random_char.h"
 
int genPasswd(char *buf, int size, int len_lower, int len_upper, int  len_digit, int len_special, int min_mix);
void shuffle( char array[], int size);


/**
 * genPasswd
 * mix lowercase uppercase degit specialchar
 */
int genPasswd(char *buf, int size, int len_lower, int len_upper, int  len_digit, int len_special, int len_mix) 
{

const char ZERO = '\0';

int flag = 0;
int len = strlen(buf);
int j;
for(int i=0; i<len_lower; i++){
	j = len+i;
	if(j < size){
		buf[j] =  getRandomCharLower();
	} else {
		flag = 1;
		break;
	}
}
if(j+1 < size){
	buf[j+1] =  ZERO;
}
if(flag){
	return 1;
}

len = strlen(buf);
flag = 0;
for(int i=0; i<len_upper; i++){
	j = len+i;
	if(j < size){
		buf[j] =  getRandomCharUpper();
	} else {
		flag = 1;
		break;
	}
}if(j+1 < size){
	buf[j+1] =  ZERO;
}
if(flag){
	return 1;
}

len = strlen(buf);
flag = 0;
for(int i=0; i<len_digit; i++){
	j = len+i;
	if(j < size){
		buf[j] =  getRandomCharDigit();
	} else {
		flag = 1;
		break;
	}
}
if(j+1 < size){
	buf[j+1] =  ZERO;
}

len = strlen(buf);
flag = 0;
for(int i=0; i<len_special; i++){
	j = len+i;
	if(j < size){
		buf[j] =  getRandomCharSpecial();
	} else {
		flag = 1;
		break;
	}
}
if(j+1 < size){
	buf[j+1] =  ZERO;
}
if(flag){
	return 1;
}

len = strlen(buf);
flag = 0;
for(int i=0; i<len_mix; i++){
	j = len+i;
	if(j < size){
		buf[j] =  getRandomCharMix();
	} else {
		flag = 1;
		break;
	}
}
if(j+1 < size){
	buf[j+1] =  ZERO;
}
if(flag){
	return 1;
}

    return 0;
}


/**
 * shuffle
 *  http://shopping2.gmobb.jp/htdmnr/www08/c01/algorithm/shuffle.c
 */
void shuffle( char array[], int size) {
    for(int i = 0; i < size; i++) {
        int j = rand()%size;
        char t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}
