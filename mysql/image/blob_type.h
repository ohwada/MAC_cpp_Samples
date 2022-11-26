#pragma once
/**
 * blob_type.h
 * 2022-06-01 K.OHWADA
 */ 

const unsigned short TYPE_BASE64 = 1;
const unsigned short TYPE_HEX = 2;

// prototype
char* type_to_string(const unsigned short  type);


/**
 * type_to_string
 */ 
char* type_to_string(const unsigned short  type)
{
    switch(type)
    {
        case TYPE_BASE64:
            return "base64";
            break;
        case TYPE_HEX:
            return "hex";
            break;
    }
    return "";
}

