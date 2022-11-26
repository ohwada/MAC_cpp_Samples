/**
 *  test_base64.c
 * 2022-06-01 K.OHWADA
 */ 

// reference : https://qiita.com/leak4mk0/items/6c7f708dd59d52e0bc5c

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base64.h"

typedef struct tagBASE64_TEST {
    BASE64_TYPE type;
    const char *data;
    size_t size;
    const char *base64;
} BASE64_TEST;
static const BASE64_TEST BASE64_TESTS[] = {
    { BASE64_TYPE_STANDARD, "",       0, "" },
    { BASE64_TYPE_STANDARD, "f",      1, "Zg==" },
    { BASE64_TYPE_STANDARD, "fo",     2, "Zm8=" },
    { BASE64_TYPE_STANDARD, "foo",    3, "Zm9v" },
    { BASE64_TYPE_STANDARD, "foob",   4, "Zm9vYg==" },
    { BASE64_TYPE_STANDARD, "fooba",  5, "Zm9vYmE=" },
    { BASE64_TYPE_STANDARD, "foobar", 6, "Zm9vYmFy" },
    { BASE64_TYPE_STANDARD, ">>>>>>", 6, "Pj4+Pj4+" },
    { BASE64_TYPE_STANDARD, "??????", 6, "Pz8/Pz8/" },
    { BASE64_TYPE_MIME,     ">>>>>>", 6, "Pj4+Pj4+" },
    { BASE64_TYPE_MIME,     "??????", 6, "Pz8/Pz8/" },
    { BASE64_TYPE_URL,      ">>>>>>", 6, "Pj4-Pj4-" },
    { BASE64_TYPE_URL,      "??????", 6, "Pz8_Pz8_" }
};
static const size_t BASE64_TESTS_LENGTH = {
    sizeof(BASE64_TESTS) / sizeof(BASE64_TESTS[0])
};

int main(void) {
    int i;

    for (i = 0; i < (int)BASE64_TESTS_LENGTH; i++) {
        BASE64_TEST test;
        char *data;
        char *base64;
        size_t size;

        test = BASE64_TESTS[i];

        base64 = base64Encode(test.data, test.size, test.type);
        printf("BASE64(\"%s\") = \"%s\"\n", test.data, base64);
        assert(strcmp(base64, test.base64) == 0);

        data = base64Decode(base64, &size, test.type);
        printf("DATA(\"%s\") = \"%s\"\n", base64, data);
        assert(size == test.size);
        assert(memcmp(data, test.data, size) == 0);

        free(base64);
        free(data);
    } // for

    printf("successful \n");

    return 0;
}

// BASE64("") = ""
// DATA("") = ""
// BASE64("f") = "Zg=="
// DATA("Zg==") = "f"
// successful