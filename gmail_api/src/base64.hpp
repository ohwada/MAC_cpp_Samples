#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// utility for message part


#include <string>
#include "base64.h"


// prototype
void encodeB64(std::string bytes, std::string &b64);
void decodeB64(std::string base64, std::string &decode);


/**
 *  encodeB64
 */
void encodeB64(std::string bytes, std::string &b64)
{
		std::string out;
		out.resize(Base64encode_len(bytes.length()));
		Base64encode(&out[0], bytes.data(), bytes.length());
		b64 = out;
	}


/**
 *  decodeB64
 */
void decodeB64(std::string base64, std::string &decode)
{
		std::string out;
		out.resize(Base64decode_len(&base64[0]));
		size_t actualSize = Base64decode(&out[0], base64.data());
		out.resize(actualSize);
		decode = out;
}

