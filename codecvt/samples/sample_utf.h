/**
 * codecvt Sample
 * 2020-03-01 K.OHWADA
 */

 // header file for test_wstring_convert.cpp
// reference : http://ash.jp/code/unitbl21.htm

    const char SAMPLE_UTF8[] = 
    { (char)0xE3, (char)0x81, (char)0x82,  //あ
    (char)0xE3, (char)0x81, (char)0x84,  // い
    (char)0xE3, (char)0x81, (char)0x86, // う
    (char)0xE3, (char)0x81, (char)0x88,  // え
    (char)0xE3, (char)0x81, (char)0x8A,  // お
    0 };

    const char16_t SAMPLE_UTF16BE[] = 
    { (char16_t)0x3042, //あ
    (char16_t)0x3044, // い
    (char16_t)0x3046, // う
    (char16_t)0x3048, // え
    (char16_t)0x304A, // お
    0 };

    const char32_t SAMPLE_UTF32BE[] = 
    { (char32_t)0x00003042, //  あ
    (char32_t)0x00003044, //   い
    (char32_t)0x00003046, //  う
    (char32_t)0x00003048, //  え
    (char32_t)0x0000304A, //   お
    0 };

