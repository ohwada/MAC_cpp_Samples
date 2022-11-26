#pragma once
/**
 * base64.h
 * 2020-07-01 K.OHWADA
 */ 

// base64 Encode Decode
// reference : https://qiita.com/leak4mk0/items/6c7f708dd59d52e0bc5c

#include <stdlib.h>
#include <string.h>



/**
 * typedef enum tagBASE64_TYPE
 */ 
typedef enum tagBASE64_TYPE {
    BASE64_TYPE_STANDARD,
    BASE64_TYPE_MIME,
    BASE64_TYPE_URL
} BASE64_TYPE;


// prototype
char *base64Encode(const char *data, const size_t size, const BASE64_TYPE type);
char *base64Decode(const char *base64, size_t *retSize, const BASE64_TYPE type);


// global constant
static const char BASE64_TABLE[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
};

static const char BASE64_TABLE_URL[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"
};

static const int BASE64_TABLE_LENGTH = {
    sizeof(BASE64_TABLE) / sizeof(BASE64_TABLE[0]) - 1
};


/**
 * typedef struct tagBASE64_SPEC
 */ 
typedef struct tagBASE64_SPEC {
    BASE64_TYPE type;
    const char *table;
    char pad;
    int maxLineLength;
    char *lineSep;
    int lineSepLength;
} BASE64_SPEC;


// global constant
static const BASE64_SPEC BASE64_SPECS[] = {
    { BASE64_TYPE_STANDARD, BASE64_TABLE,     '=', 0,  NULL,   0 },
    { BASE64_TYPE_MIME,     BASE64_TABLE,     '=', 76, "\r\n", 2 },
    { BASE64_TYPE_URL,      BASE64_TABLE_URL, 0,   0,  NULL,   0 }
};

static const size_t BASE64_SPECS_LENGTH = {
    sizeof(BASE64_SPECS) / sizeof(BASE64_SPECS[0])
};


/**
 * base64Encode
 */ 
char *base64Encode(const char *data, const size_t size, const BASE64_TYPE type)
{
    BASE64_SPEC spec;
    size_t length;
    char *base64;
    char *cursor;
    int lineLength;
    int i;
    int j;

    if (data == NULL) {
        return NULL;
    }

    spec = BASE64_SPECS[0];
    for (i = 0; i < (int)BASE64_SPECS_LENGTH; i++) {
        if (BASE64_SPECS[i].type == type) {
            spec = BASE64_SPECS[i];
            break;
        }
    }

    length = size * 4 / 3 + 3 + 1;
    if (spec.maxLineLength > 0) {
        length += size / spec.maxLineLength * spec.lineSepLength;
    }
    base64 = malloc(length);
    if (base64 == NULL) {
        return NULL;
    }

    cursor = base64;
    lineLength = 0;
    for (i = 0, j = size; j > 0; i += 3, j -= 3) {
        if (spec.maxLineLength > 0) {
            if (lineLength >= spec.maxLineLength) {
                char *sep;

                for (sep = spec.lineSep; *sep != 0; sep++) {
                    *(cursor++) = *sep;
                }
                lineLength = 0;
            }
            lineLength += 4;
        }

        if (j == 1) {
            *(cursor++) = spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = spec.table[(data[i + 0] << 4 & 0x30)];
            *(cursor++) = spec.pad;
            *(cursor++) = spec.pad;
        }
        else if (j == 2) {
            *(cursor++) = spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = spec.table[(data[i + 0] << 4 & 0x30) | (data[i + 1] >> 4 & 0x0f)];
            *(cursor++) = spec.table[(data[i + 1] << 2 & 0x3c)];
            *(cursor++) = spec.pad;
        }
        else {
            *(cursor++) = spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = spec.table[(data[i + 0] << 4 & 0x30) | (data[i + 1] >> 4 & 0x0f)];
            *(cursor++) = spec.table[(data[i + 1] << 2 & 0x3c) | (data[i + 2] >> 6 & 0x03)];
            *(cursor++) = spec.table[(data[i + 2] << 0 & 0x3f)];
        }
    }
    *cursor = 0;

    return base64;
}


/**
 * base64Decode
 */ 
char *base64Decode(const char *base64, size_t *retSize, const BASE64_TYPE type)
{
    BASE64_SPEC spec;
    char table[0x80];
    size_t length;
    char *data;
    char *cursor;
    int i;
    int j;

    if (base64 == NULL) {
        return NULL;
    }

    spec = BASE64_SPECS[0];
    for (i = 0; i < (int)BASE64_SPECS_LENGTH; i++) {
        if (BASE64_SPECS[i].type == type) {
            spec = BASE64_SPECS[i];
            break;
        }
    }

    length = strlen(base64);
    data = malloc(length * 3 / 4 + 2 + 1);
    if (data == NULL) {
        return NULL;
    }

    memset(table, 0x80, sizeof(table));
    for (i = 0; i < BASE64_TABLE_LENGTH; i++) {
        table[spec.table[i] & 0x7f] = i;
    }

    cursor = data;
    for (i = 0, j = 0; i < (int)length; i++, j = i % 4) {
        char ch;

        if (base64[i] == spec.pad) {
            break;
        }

        ch = table[base64[i] & 0x7f];
        if (ch & 0x80) {
            continue;
        }
        if (j == 0) {
            *cursor = ch << 2 & 0xfc;
        }
        else if (j == 1) {
            *(cursor++) |= ch >> 4 & 0x03;
            *cursor = ch << 4 & 0xf0;
        }
        else if (j == 2) {
            *(cursor++) |= ch >> 2 & 0x0f;
            *cursor = ch << 6 & 0xc0;
        }
        else {
            *(cursor++) |= ch & 0x3f;
        }
    }
    *cursor = 0;
    *retSize = cursor - data;

    return data;
}
