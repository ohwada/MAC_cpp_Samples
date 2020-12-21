// https://github.com/honeyligo/curlsmtp/blob/master/ustd_string.h

#ifndef __USTD_STRING_H__
#define __USTD_STRING_H__

#include <vector>
#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>
#include <cctype>

namespace ustd
{
namespace string
{

static std::string sprintf(const char *format, ...);
static size_t base64encode(const char *data, const int &len, std::vector<char> &dest);
static size_t base64decode(const char *data, const int &len, std::vector<char> &dest);
static size_t split(const std::string &src, const std::string &delim, std::vector<std::string> &dst);
static std::string ltrim(const std::string &src, const std::string &key = " ");
static std::string rtrim(const std::string &src, const std::string &key = " ");
static std::string trim(const std::string &src, const std::string &key = " ");
static int replace(std::string &base, const std::string &src, const std::string &dst = "");
static std::string url_encode(const std::string &url_text);
static std::string url_base64encode(const std::string &url);
static std::string url_decode(const std::string &url_text);
static std::string url_base64decode(const std::string &url);
static std::string tolower(const std::string &src_text);
static std::string toupper(const std::string &src_text);
static size_t args_parse(const std::string &args, std::unordered_map<std::string, std::string> &args_map, const std::string &delim = "&");

std::string url_base64encode(const std::string &url)
{
	std::string url_text(url);

	std::vector<char> buffer;
	if (ustd::string::base64encode(url_text.c_str(), url_text.size(), buffer) > 0)
	{
		url_text.assign(&buffer[0], buffer.size());
		ustd::string::replace(url_text, "+", "-");
		ustd::string::replace(url_text, "/", "_");

		return url_text;
	}

	return "";
}

std::string url_base64decode(const std::string &url)
{
	std::string url_text(url);
	ustd::string::replace(url_text, "-", "+");
	ustd::string::replace(url_text, "_", "/");

	std::vector<char> buffer;
	if (ustd::string::base64decode(url_text.c_str(), url_text.size(), buffer) > 0)
	{
		return (std::string(&buffer[0], buffer.size()));
	}

	return "";
}

std::string sprintf(const char *format, ...)
{
	char buffer[10240] = {0x00};

	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(buffer, format, arg_ptr);
	va_end(arg_ptr);

	return (buffer);
}

size_t base64encode(const char *data, const int &len, std::vector<char> &dest)
{
	static const char encodedict[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int div = len / 3;
	int mod = len % 3;
	int size = div * 4 + ((mod == 0) ? 0 : 4);

	dest.clear();
	dest.reserve(size);

	for (int i = 0; i < div; ++i)
	{
		unsigned char c1 = *data++;
		unsigned char c2 = *data++;
		unsigned char c3 = *data++;

		dest.push_back(encodedict[c1 >> 2]);
		dest.push_back(encodedict[((c1 << 4) | (c2 >> 4)) & 0x3f]);
		dest.push_back(encodedict[((c2 << 2) | (c3 >> 6)) & 0x3f]);
		dest.push_back(encodedict[c3 & 0x3f]);
	}

	switch (mod)
	{
	case 1:
		{
			unsigned char c1 = *data++;
			dest.push_back(encodedict[(c1 & 0xfc) >> 2]);
			dest.push_back(encodedict[((c1 & 0x03) << 4)]);
			dest.push_back('=');
			dest.push_back('=');

			break;
		}

	case 2:
		{
			unsigned char c1 = *data++;
			unsigned char c2 = *data++;
			dest.push_back(encodedict[(c1 & 0xfc) >> 2]);
			dest.push_back(encodedict[((c1 & 0x03) << 4) | ((c2 & 0xf0) >> 4)]);
			dest.push_back(encodedict[((c2 & 0x0f) << 2)]);
			dest.push_back('=');

			break;
		}

	default:
		{
			break;
		}
	}

	return dest.size();
}

size_t base64decode(const char *data, const int &len, std::vector<char> &dest)
{
	static const char decodedict[256] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62,        // '+'
		0, 0, 0,
		63,        // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61,						// '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,			// 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51			// 'a'-'z'
	};

	dest.clear();
	if (len % 4 != 0)
	{
		return dest.size();
	}

	int div = len / 4;
	int size = div * 3;
	dest.reserve(size);

	unsigned char *udata = (unsigned char *)data;
	for (int i = 0; i < div; ++i)
	{
		int key = decodedict[*udata++] << 18;
		key += decodedict[*udata++] << 12;
		dest.push_back((char)((key & 0x00ff0000) >> 16));

		if (*udata != '=')
		{
			key += decodedict[*udata++] << 6;
			dest.push_back((char)((key & 0x0000ff00) >> 8));

			if (*udata != '=')
			{
				key += decodedict[*udata++];
				dest.push_back((char)(key & 0x000000ff));
			}
		}
	}

	return dest.size();
}

size_t split(const std::string &src, const std::string &delim, std::vector<std::string> &dst)
{
    dst.clear();
    size_t idx = 0;
    size_t pos = src.find(delim, idx);
    while (pos != std::string::npos)
    {
        dst.push_back(src.substr(idx, pos - idx));
        idx = pos + delim.length();
        pos = src.find(delim, idx);
    }

	dst.push_back(src.substr(idx));
    return dst.size();
}

std::string ltrim(const std::string &src, const std::string &key)
{
	size_t pos = src.find_first_not_of(key);
	if (pos != std::string::npos)
	{
		return src.substr(pos);
	}

	return ("");
}

std::string rtrim(const std::string &src, const std::string &key)
{
	size_t pos = src.find_last_not_of(key);
	if (pos != std::string::npos)
	{
		return src.substr(0, pos + 1);
	}

	return ("");
}

std::string trim(const std::string &src, const std::string &key)
{
	return ltrim(rtrim(src, key), key);
}

int replace(std::string &base, const std::string &src, const std::string &dst)
{
	int count = 0;
	size_t src_len = src.length();
	size_t dst_len = dst.length();

	size_t pos = base.find(src, 0);
	while (pos != std::string::npos)
	{
		count += 1;
		base.replace(pos, src_len, dst);
		pos = base.find(src, pos + dst_len);
	}

	return count;
}

std::string url_encode(const std::string &url_text)
{
	size_t idx = 0;
	std::string encode_text;
	char hex[] = "0123456789abcdef";

	size_t str_size = url_text.size();

	while (idx < str_size)
	{
		unsigned char ch = url_text[idx++];

		//0-9 a-z A-Z
		//- _ . ! ~ * ( ) \'
		//: ; ? @ & =

		if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||	ch == '-' || ch == '_' || ch == '.')
		{
			encode_text += ch;
		}
		else
		{
			encode_text += "%";
			encode_text += hex[ch / 16];
			encode_text += hex[ch % 16];
		}
	}

	return encode_text;
}

std::string url_decode(const std::string &url_text)
{
	size_t idx = 0;
	std::string decode_text;
	size_t str_size = url_text.size();

	while (idx < str_size)
	{
		char ch = url_text[idx++];

		switch (ch)
		{
		case '%':
			{
				std::string str = url_text.substr(idx, 2);
				decode_text += static_cast<char>(strtol(str.c_str(), NULL, 16));
				idx += 2;
			}

			break;

		case '+':
			{
				decode_text += ' ';
			}

			break;

		default:
			{
				decode_text += ch;
			}

			break;
		}
	}

	return decode_text;
}

std::string tolower(const std::string &src_text)
{
	std::string lower_text = src_text;
	transform(lower_text.begin(), lower_text.end(), lower_text.begin(), (int (*)(int))::tolower);
	return lower_text;
}

std::string toupper(const std::string &src_text)
{
	std::string upper_text = src_text;
	transform(upper_text.begin(), upper_text.end(), upper_text.begin(), (int (*)(int))::toupper);
	return upper_text;
}

size_t args_parse(const std::string &args, std::unordered_map<std::string, std::string> &args_map, const std::string &delim)
{
	args_map.clear();
	size_t args_count = 0;
	std::string args_text = args;
	size_t idx = args.find("?");

	if (idx != std::string::npos)
	{
		args_text = args.substr(idx + 1);
	}

	std::vector<std::string> tokens;
	if (ustd::string::split(args_text, delim, tokens) > 0)
	{
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			size_t pos = tokens[i].find("=");
			if (pos != std::string::npos)
			{
				std::string key = ustd::string::tolower(ustd::string::trim(tokens[i].substr(0, pos)));
				std::string value = ustd::string::trim(tokens[i].substr(pos + 1));
				if (!key.empty() && args_map.find(key) == args_map.end())
				{
					args_map.insert(std::make_pair(key, value));
					args_count += 1;
				}
			}
		}
	}

	return args_count;
}

}
}

#endif
