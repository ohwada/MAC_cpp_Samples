 /**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */


#include <string>
#include <iostream>
#include <cstdint>
#include <array>

#ifndef _UTF_CONV_H_
#define _UTF_CONV_H_

bool ConvChU32ToU8(const char32_t u32Ch, std::array<char, 4>& u8Ch);

int GetU8ByteCount(char ch);

bool IsU8LaterByte(char ch);

bool ConvChU8ToU32(const std::array<char, 4>& u8Ch, char32_t& u32Ch);

bool ConvChU32ToU16(const char32_t u32Ch, std::array<char16_t, 2>& u16Ch);

bool IsU16HighSurrogate(char16_t ch);

bool IsU16LowSurrogate(char16_t ch);

bool ConvChU16ToU32(const std::array<char16_t, 2>& u16Ch, char32_t& u32Ch);

bool ConvChU8ToU16(const std::array<char, 4>& u8Ch,
                   std::array<char16_t, 2>& u16Ch);

bool ConvChU16ToU8(const std::array<char16_t, 2>& u16Ch,
                   std::array<char, 4>& u8Ch);

bool ConvU8ToU16(const std::string& u8Str, std::u16string& u16Str);

bool ConvU8ToU32(const std::string& u8Str, std::u32string& u32Str);

bool ConvU16ToU8(const std::u16string& u16Str, std::string& u8Str);

bool ConvU16ToU32(const std::u16string& u16Str, std::u32string& u32Str);

bool ConvU32ToU8(const std::u32string& u32Str, std::string& u8Str);

bool ConvU32ToU16(const std::u32string& u32Str, std::u16string& u16Str);


#endif  // _UTF_CONV_H_

