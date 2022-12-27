/**
 * test_str_join.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "str_join.h"
#include "two_dem_char_array.h"
#include "random_char.h"


/**
 * main
 */
int main()
{
    const char NUL = '\0';

    char* str1 = "hello";
    char* str2 = "world";

    char* expect = "hello, world";

    char *glue = ", ";

size_t bufsize = calc_joinsize(str1, str2, glue);

    char buf[bufsize+1];

    str_join(str1, str2, glue, (char *)buf, bufsize);

    printf("buf: %s \n", buf);

    assert(strcmp(buf, expect) == 0);

    printf("\n random \n");

    int num = 10;
    int len = 100;
    size_t text_size = 5;

    char** data = alloc_chars(num, len) ;

    for(int i=0; i< num; i++)
    {
        for(int j=0; j<text_size; j++){
            data[i][j] = getRandomCharMix();
        } // for j
        data[i][text_size] = NUL;
    } // for i

    print_chars(data, num);

    size_t result_size = calc_joinsize_array(data, num, glue);

  printf("result_size: %zu \n", result_size);

    char result[result_size];

// substruct number of terminating character
    int expect_len = result_size - 1;

    str_join_array(data, num, glue, (char *)result, result_size);

    printf("result: %s \n", result);

    int result_len = strlen(result);

    printf("result len: %d \n", result_len);

    assert(result_len == expect_len);

    free_chars(data, num);

    printf("\n successful \n");

    return 0;
}

// buf: hello, world 
 // random 
// 0 : y87RE 
// 1 : VbyPs 
// 2 : FJ4EC 
// 3 : rwwT2 
// 4 : Z7L93 
// 5 : QetzF 
// 6 : txN1O 
// 7 : cX0aw 
// 8 : tqGy5 
// 9 : Tp1PJ 
//result: y87RE, VbyPs, FJ4EC, rwwT2, Z7L93, QetzF, txN1O, cX0aw, tqGy5, Tp1PJ 

